#ifndef DESCRACK_OPENCL_DESCRACKER_H
#define DESCRACK_OPENCL_DESCRACKER_H

#include "devicecrackingcontext.h"

#include <thread>
#include <mutex>
#include <memory>

namespace descrack {
namespace opencl {

class DesCracker
{
private:
    const std::vector<cl::Device> devices;
    std::size_t bitsGlobal, bitsThread;

    gpu::DeviceListContext dlContext;

public:
    class Configuration
    {
    private:
        const DesCracker *parent;
        gpu::ProgramContext programContext;

    public:
        class Session
        {
        private:
            const Configuration *parent;
            std::vector<std::thread> threads;
            std::vector<std::unique_ptr<DeviceCrackingContext>> devContexts;

            KeyBatchDistributor kbDistributor;

            std::mutex keyMutex;
            std::uint_fast64_t key;
            bool keyFound;

            void setFoundKey(std::uint_fast64_t found);

        public:
            bool wasKeyFound() const { return keyFound; }
            std::uint_fast64_t getKey() const { return key; }

            Session(const Configuration *parent, const KeyData *keyData,
                    std::uint_fast64_t batchFrom, std::uint_fast64_t batchTo);

            void requestStopCracking();
            void finishCracking();
        };

        Configuration(
                const DesCracker *parent,
                const gpu::KernelConfigData &config = {});

        double benchmark(std::uint_fast64_t batches) const;
    };

    DesCracker(const gpu::GlobalContext *globalContext,
               const std::vector<cl::Device> &devices,
               std::size_t bitsGlobal, std::size_t bitsThread);

    std::uint_fast64_t getBatchFromKey(std::uint_fast64_t key) const;
    std::uint_fast64_t getBatchCount() const;
    std::uint_fast64_t getKeysInBatch() const;

    gpu::KernelConfigData findOptimalConfiguration(std::uint_fast64_t batches) const;
};

} // namespace opencl
} // namespace descrack

#endif // DESCRACK_OPENCL_DESCRACKER_H
