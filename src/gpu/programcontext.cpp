#include "programcontext.h"

namespace descrack {
namespace opencl {
namespace gpu {

ProgramContext::ProgramContext(
        const DeviceListContext *dlContext, std::size_t bitsGlobal,
        cl::Program program, std::size_t vectorLevel,
        CdWriter cdBaseWriter, RefDataWriter refDataWriter)
    : dlContext(dlContext), program(program), bitsGlobal(bitsGlobal),
      vectorLevel(vectorLevel),
      cdBaseWriter(cdBaseWriter), refDataWriter(refDataWriter)
{
    auto &clContext = dlContext->getClContext();
    refInputBuffer = cl::Buffer(clContext, CL_MEM_READ_ONLY, getRefInputBufferSize());
    refOutputBuffer = cl::Buffer(clContext, CL_MEM_READ_ONLY, getRefOutputBufferSize());
}

void ProgramContext::writeCdBase(void *hostBuffer, std::uint_fast64_t batch) const
{
    cdBaseWriter(hostBuffer, batch, 56 - bitsGlobal);
}


void ProgramContext::writeRefData(
        cl::CommandQueue cmdQueue,
        std::uint_fast64_t refInput, std::uint_fast64_t refOutput) const
{
    void *hostBuffer;
    hostBuffer = cmdQueue.enqueueMapBuffer(
                refInputBuffer, true, CL_MAP_WRITE,
                0, getRefInputBufferSize());

    refDataWriter(hostBuffer, refInput);

    cmdQueue.enqueueUnmapMemObject(refInputBuffer, hostBuffer);

    hostBuffer = cmdQueue.enqueueMapBuffer(
                refOutputBuffer, true, CL_MAP_WRITE,
                0, getRefOutputBufferSize());

    refDataWriter(hostBuffer, refOutput);

    cmdQueue.enqueueUnmapMemObject(refOutputBuffer, hostBuffer);
}

} // namespace gpu
} // namespace opencl
} // namespace descrack
