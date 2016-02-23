#include "devicecontext.h"

namespace descrack {
namespace opencl {
namespace gpu {

DeviceContext::DeviceContext(
        const ProgramContext *parentContext, const cl::Device &device,
        std::uint_fast64_t refInput, std::uint_fast64_t refOutput)
    : parentContext(parentContext), device(device),
      cmdQueue(parentContext->getDeviceListContext()->getClContext(), device),
      refInput(refInput), refOutput(refOutput)
{
    parentContext->writeRefData(cmdQueue, refInput, refOutput);
}

} // namespace gpu
} // namespace opencl
} // namespace descrack
