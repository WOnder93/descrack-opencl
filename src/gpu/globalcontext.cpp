#include "globalcontext.h"

namespace descrack {
namespace opencl {
namespace gpu {

GlobalContext::GlobalContext(const std::string &dataDirectory)
    : dataDirectory(dataDirectory)
{
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    for (cl::Platform platform : platforms) {
        platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
    }
}

} // namespace gpu
} // namespace opencl
} // namespace descrack
