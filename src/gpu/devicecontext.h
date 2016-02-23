#ifndef DESCRACK_OPENCL_GPU_DEVICECONTEXT_H
#define DESCRACK_OPENCL_GPU_DEVICECONTEXT_H

#include "programcontext.h"

namespace descrack {
namespace opencl {
namespace gpu {

class DeviceContext
{
private:
    const ProgramContext *parentContext;

    cl::Device device;
    cl::CommandQueue cmdQueue;

    std::uint_fast64_t refInput;
    std::uint_fast64_t refOutput;

public:
    const ProgramContext *getProgramContext() const { return parentContext; }
    const cl::Device &getDevice() const { return device; }
    const cl::CommandQueue &getCommandQueue() const { return cmdQueue; }

    std::uint_fast64_t getRefInput() const { return refInput; }
    std::uint_fast64_t getRefOutput() const { return refOutput; }

    DeviceContext() { }

    DeviceContext(const ProgramContext *parentContext, const cl::Device &device,
                  std::uint_fast64_t refInput, std::uint_fast64_t refOutput);
};

} // namespace gpu
} // namespace opencl
} // namespace descrack

#endif // DESCRACK_OPENCL_GPU_DEVICECONTEXT_H
