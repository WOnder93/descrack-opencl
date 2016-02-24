//#define RUN_TESTS
#ifdef RUN_TESTS
#include "tests/tests.h"

using namespace descrack::opencl;

int main()
{
    return tests::Tests().run();
}

#else

#include <iostream>
#include <chrono>

#include "descracker.h"
#include "desutils.h"

using namespace descrack::opencl;

static constexpr std::size_t BITS_GLOBAL = 18;
static constexpr std::size_t BITS_THREAD = 10;

int main()
{
    std::cout << "Initializing..." << std::endl;

    gpu::GlobalContext global("data");
    //std::cout << global.getAllDevices()[0].getInfo<CL_DEVICE_MAX_WORK_ITEM_SIZES>()[0] << std::endl;

    DesCracker cracker(&global, global.getAllDevices(),
                       BITS_GLOBAL, BITS_THREAD);

    cracker.findOptimalConfiguration(8);
    /*
    DesCracker::Configuration config(
                &cracker, {
                    { gpu::KernelConfig::SBoxes::KEY, gpu::KernelConfig::SBoxes::OPENWALL_BITSEL }
                });

    std::cout << "Running benchmark..." << std::endl;
    std::cout << config.benchmark(8) / 1e6 << " Mkeys/second" << std::endl;
    */
    return 0;
}

#endif

