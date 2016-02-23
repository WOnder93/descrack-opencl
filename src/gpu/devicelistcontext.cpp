#include "devicelistcontext.h"

namespace descrack {
namespace opencl {
namespace gpu {

DeviceListContext::DeviceListContext(
        const GlobalContext *parentContext,
        const std::vector<cl::Device> &devices)
    : parentContext(parentContext), clContext(devices)
{
}

} // namespace gpu
} // namespace opencl
} // namespace descrack
