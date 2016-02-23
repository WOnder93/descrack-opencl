#include "descracker.h"

#include "gpu/uintprogramtraits.h"
#include "desutils.h"

#include <iostream>
#include <chrono>

namespace descrack {
namespace opencl {

DesCracker::Configuration::Session::Session(
        const Configuration *parent, const KeyData *keyData,
        std::size_t batchFrom, std::size_t batchTo)
    : parent(parent), threads(), devContexts(),
      kbDistributor(batchFrom, batchTo),
      keyMutex(), key(), keyFound(false)
{
    auto cracker = parent->parent;

    std::size_t devCount = cracker->devices.size();
    devContexts.reserve(devCount);
    threads.reserve(devCount);

    auto callback = [this] (std::uint_fast64_t found) {
        setFoundKey(found);
    };
    for (auto &dev : cracker->devices) {
        auto ctx = new DeviceCrackingContext(
                    &parent->programContext, keyData, callback, dev,
                    cracker->bitsThread);
        devContexts.emplace_back(ctx);
        threads.emplace_back(&DeviceCrackingContext::runCracking,
                             ctx, &kbDistributor);
    }
}

void DesCracker::Configuration::Session::setFoundKey(std::uint_fast64_t found)
{
    std::lock_guard<std::mutex> guard(keyMutex);
    key = found;
    keyFound = true;
    requestStopCracking();
}

void DesCracker::Configuration::Session::requestStopCracking()
{
    for (auto &ctx : devContexts) {
        ctx->requestStopCracking();
    }
}

void DesCracker::Configuration::Session::finishCracking()
{
    for (auto &thread : threads) {
        thread.join();
    }
}

DesCracker::Configuration::Configuration(
        const DesCracker *parent,
        const gpu::KernelConfigData &config)
    : parent(parent),
      programContext(gpu::ProgramContext::create<gpu::UIntProgramTraits>(
                         &parent->dlContext, parent->bitsGlobal, config))
{
}

double DesCracker::Configuration::benchmark(std::uint_fast64_t batches) const
{
    using clock_type = std::chrono::steady_clock;

    static constexpr double CLOCK_MULTIPLIER =
            double(clock_type::period::num) / clock_type::period::den;

    std::uint_fast64_t keysTotal = batches * parent->getKeysInBatch();

    KeyData keyData(0, 0xE5C48D8397B26531ULL);
    clock_type::time_point checkpt0 = clock_type::now();
    {
        Session session(this, &keyData, 1, batches);
        session.finishCracking();
    }
    clock_type::time_point checkpt1 = clock_type::now();

    clock_type::duration compTime = checkpt1 - checkpt0;
    double seconds = compTime.count() * CLOCK_MULTIPLIER;
    return keysTotal / seconds;
}

DesCracker::DesCracker(
        const gpu::GlobalContext *globalContext,
        const std::vector<cl::Device> &devices,
        std::size_t bitsGlobal, std::size_t bitsThread)
    : devices(devices), bitsGlobal(bitsGlobal), bitsThread(bitsThread),
      dlContext(globalContext, devices)
{
}

std::uint_fast64_t DesCracker::getBatchFromKey(std::uint_fast64_t key) const
{
    constexpr auto mask = (static_cast<std::uint_fast64_t>(1)
                           << (56 - gpu::UIntProgramTraits::vectorBits)) - 1;
    auto cd = DesUtils::keyToCd(key);
    return (cd & mask) >> bitsGlobal;
}

std::uint_fast64_t DesCracker::getBatchCount() const
{
    return static_cast<std::uint_fast64_t>(1)
            << (56 - gpu::UIntProgramTraits::vectorBits - bitsGlobal);
}

std::uint_fast64_t DesCracker::getKeysInBatch() const
{
    return static_cast<std::uint_fast64_t>(1)
            << (gpu::UIntProgramTraits::vectorBits + bitsGlobal);
}

gpu::KernelConfigData DesCracker::findOptimalConfiguration(std::uint_fast64_t batches) const
{
    using namespace gpu;

    KernelConfigData configData {
        { KernelConfig::SBoxes::KEY, KernelConfig::SBoxes::OPENWALL }
    };

    std::cerr << "[INFO] Benchmarking s-box versions..." << std::endl;

    for (std::size_t box = 0; box < KernelConfig::SBoxes::SBOX_COUNT; box++) {
        auto &key = KernelConfig::SBoxes::OPENWALL_SBOX_VER_KEYS[box];
        auto versionCount = KernelConfig::SBoxes::OPENWALL_SBOX_VER_COUNTS[box];

        if (versionCount <= 1) {
            continue;
        }

        std::cerr << "[INFO]   Benchmarking s-box #" << box << "..." << std::endl;

        std::size_t bestVersion = 0;
        double bestPerformance = 0.0;
        for (std::size_t version = 1; version <= versionCount; version++) {
            configData[key] = std::to_string(version);

            std::cerr << "[INFO]     Initializing version " << version
                      << "/" << versionCount << "..." << std::endl;

            Configuration config(this, configData);
            std::cerr << "[INFO]     Benchmarking version " << version
                      << "/" << versionCount << "..." << std::endl;
            double perf = config.benchmark(batches);
            std::cerr << "[INFO]     Measured performance: " << (perf / 1e6)
                      << " Mkeys/second" << std::endl;
            if (perf > bestPerformance) {
                bestPerformance = perf;
                bestVersion = version;
            }
        }
        std::cerr << "[INFO]   Best s-box #" << box << " version: "
                  << bestVersion << std::endl;

        configData[key] = std::to_string(bestVersion);
    }

    return std::move(configData);
}

} // namespace opencl
} // namespace descrack
