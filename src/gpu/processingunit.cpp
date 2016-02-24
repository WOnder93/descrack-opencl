#include "processingunit.h"

#include "alignment.h"
#include "desutils.h"

namespace descrack {
namespace opencl {
namespace gpu {

static constexpr std::size_t MAX_FOUND_KEYS = 16;

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
    resultBits = programContext->getVectorLevel() + bitsGlobal;

    groupSize = std::min(items, kernel.getWorkGroupInfo<CL_KERNEL_WORK_GROUP_SIZE>(device));
    groupCount = BLOCK_COUNT(groupSize, items);

    cdBaseBufferSize = (56 - bitsGlobal) * programContext->getVectorBytes();
    resultBufferSize = (MAX_FOUND_KEYS + 1) * sizeof(cl_uint);

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
    auto mappedResultBuffer = static_cast<cl_uint *>(
                cmdQueue.enqueueMapBuffer(
                    resultBuffer, true, CL_MAP_READ, 0,
                    resultBufferSize, nullptr, &event));

    // FIXME: allow reporting multiple found keys (just in case)
    bool res = false;
    auto count = mappedResultBuffer[0];
    if (count > 0) {
        std::uint_fast64_t cd = (batch << resultBits) |
                std::uint_fast64_t(mappedResultBuffer[1]);
        key = DesUtils::keyFromCd(cd);
        res = true;
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
