#ifndef DESCRACK_OPENCL_DEVICECRACKINGCONTEXT_H
#define DESCRACK_OPENCL_DEVICECRACKINGCONTEXT_H

#include "keybatchdistributor.h"
#include "keydata.h"
#include "gpu/processingunit.h"

#include <cstdint>
#include <atomic>
#include <functional>

namespace descrack {
namespace opencl {

typedef void KeyFoundCallback(std::uint_least64_t key);

class DeviceCrackingContext
{
private:
    std::function<KeyFoundCallback> callback;

    gpu::DeviceContext deviceContext;
    gpu::ProcessingUnit pu1;
    gpu::ProcessingUnit pu2;

    std::atomic_bool stop;

public:
    DeviceCrackingContext() { }

    DeviceCrackingContext(const gpu::ProgramContext *programContext,
            const KeyData *keyData, std::function<KeyFoundCallback> callback,
            const cl::Device &device, std::size_t bitsThread);

    void runCracking(KeyBatchDistributor *kbDistributor);

    void requestStopCracking();
};

} // namespace opencl
} // namespace descrack

#endif // DESCRACK_OPENCL_DEVICECRACKINGCONTEXT_H
