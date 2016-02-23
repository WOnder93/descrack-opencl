#ifndef DESCRACK_OPENCL_GPU_DEVICELISTCONTEXT_H
#define DESCRACK_OPENCL_GPU_DEVICELISTCONTEXT_H

#include "globalcontext.h"

namespace descrack {
namespace opencl {
namespace gpu {

class DeviceListContext
{
private:
    const GlobalContext *parentContext;

    cl::Context clContext;

public:
    const GlobalContext *getGlobalContext() const { return parentContext; }

    const cl::Context &getClContext() const { return clContext; }

    DeviceListContext() { }

    DeviceListContext(const GlobalContext *parentContext,
                      const std::vector<cl::Device> &devices);
};

} // namespace gpu
} // namespace opencl
} // namespace descrack

#endif // DESCRACK_OPENCL_GPU_DEVICELISTCONTEXT_H
