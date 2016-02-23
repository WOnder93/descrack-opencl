#include "processingunit.h"

#include "alignment.h"
#include "desutils.h"

namespace descrack {
namespace opencl {
namespace gpu {

ProcessingUnit::ProcessingUnit(const DeviceContext *context,
                               std::size_t bitsThread)
    : context(context), cmdQueue(context->getCommandQueue())
{
    auto programContext = context->getProgramContext();
    auto dlContext = programContext->getDeviceListContext();
    auto &clContext = dlContext->getClContext();
    auto &device = context->getDevice();

    auto bitsGlobal = programContext->getBitsGlobal();

    kernel = cl::Kernel(programContext->getProgram(), "des_kernel");

    items = std::size_t(1) << (bitsGlobal - bitsThread);

    groupSize = std::min(items, kernel.getWorkGroupInfo<CL_KERNEL_WORK_GROUP_SIZE>(device));
    groupCount = BLOCK_COUNT(groupSize, items);

    cdBaseBufferSize = (56 - bitsGlobal) * programContext->getVectorLength();
    resultBufferSize = groupCount * sizeof(cl_ulong);

    cdBaseBuffer = cl::Buffer(clContext, CL_MEM_READ_ONLY, cdBaseBufferSize);
    resultBuffer = cl::Buffer(clContext, CL_MEM_WRITE_ONLY, resultBufferSize);

    kernel.setArg<cl::Buffer>(0, programContext->getRefInputBuffer());
    kernel.setArg<cl::Buffer>(1, programContext->getRefOutputBuffer());
    kernel.setArg<cl::Buffer>(2, cdBaseBuffer);
    kernel.setArg<cl::Buffer>(3, resultBuffer);
    kernel.setArg<cl_uint>   (4, static_cast<cl_uint>(bitsThread));
}

void ProcessingUnit::setBatch(std::uint_fast64_t index)
{
    batch = index;
    void *hostBuffer = cmdQueue.enqueueMapBuffer(
                cdBaseBuffer, true, CL_MAP_WRITE,
                0, cdBaseBufferSize);

    auto programContext = context->getProgramContext();
    programContext->writeCdBase(hostBuffer, index);

    cmdQueue.enqueueUnmapMemObject(cdBaseBuffer, hostBuffer);
}

bool ProcessingUnit::getResult(std::uint_fast64_t &key)
{
    static constexpr std::uint_fast64_t FOUND_MASK = 0x8000000000000000ULL;
    static constexpr std::uint_fast64_t CD_MASK = ~FOUND_MASK;

    auto mappedResultBuffer = static_cast<cl_ulong *>(
                cmdQueue.enqueueMapBuffer(
                    resultBuffer, true, CL_MAP_READ, 0,
                    resultBufferSize, nullptr, &event));

    bool res = false;
    for (std::size_t i = 0; i < groupCount; i++) {
        auto res = static_cast<std::uint_fast64_t>(mappedResultBuffer[i]);
        if ((res & FOUND_MASK) != 0) {
            std::size_t cd = res & CD_MASK;
            key = DesUtils::keyFromCd(cd);
            res = true;
            break;
        }
    }

    cmdQueue.enqueueUnmapMemObject(resultBuffer, mappedResultBuffer);
    return res;
}

void ProcessingUnit::beginProcessing()
{
    cmdQueue.enqueueNDRangeKernel(
                kernel, cl::NullRange, cl::NDRange(items), cl::NDRange(groupSize),
                nullptr, &event);
}

void ProcessingUnit::endProcessing()
{
    event.wait();
    event = cl::Event();
}

} // namespace gpu
} // namespace opencl
} // namespace descrack
