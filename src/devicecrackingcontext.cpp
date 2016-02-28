#include "devicecrackingcontext.h"

namespace descrack {
namespace opencl {

using namespace gpu;

DeviceCrackingContext::DeviceCrackingContext(
        const ProgramContext *programContext, const KeyData *keyData,
        std::function<KeyFoundCallback> callback, const cl::Device &device,
        std::size_t bitsThread)
    : callback(callback),
      deviceContext(programContext, device,
                    keyData->getRefInput(), keyData->getRefOutput()),
      pu1(&deviceContext, bitsThread), pu2(&deviceContext, bitsThread),
      stop()
{
}

void DeviceCrackingContext::runCracking(KeyBatchDistributor *kbDistributor)
{
    bool firstLoop = true;
    bool lastLoop = false;
    while (true) {
        if (!firstLoop) {
            pu1.endProcessing();
            std::uint_fast64_t key;
            if (pu1.getResult(key)) {
                callback(key);
                stop = true;
            }
        }
        if (!lastLoop) {
            std::uint_fast64_t batch;
            if (kbDistributor->getNextBatch(batch)) {
                pu1.setBatch(batch);
                pu1.beginProcessing();
            } else {
                lastLoop = true;
            }
        }
        if (!firstLoop) {
            pu2.endProcessing();
            std::uint_fast64_t key;
            if (pu2.getResult(key)) {
                callback(key);
                stop = true;
            }
        }
        if (!lastLoop) {
            std::uint_fast64_t batch;
            if (kbDistributor->getNextBatch(batch)) {
                pu2.setBatch(batch);
                pu2.beginProcessing();
            } else {
                lastLoop = true;
            }
        }

        if (lastLoop) {
            break;
        }

        firstLoop = false;
        if (stop) {
            lastLoop = true;
        }
    }
}

void DeviceCrackingContext::requestStopCracking()
{
    stop = true;
}

} // namespace opencl
} // namespace descrack
