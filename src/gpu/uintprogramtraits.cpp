#include "uintprogramtraits.h"

#include "kernelloader.h"

namespace descrack {
namespace opencl {
namespace gpu {

static const int IP[64] = {
    58,    50,   42,    34,    26,   18,    10,    2,
    60,    52,   44,    36,    28,   20,    12,    4,
    62,    54,   46,    38,    30,   22,    14,    6,
    64,    56,   48,    40,    32,   24,    16,    8,
    57,    49,   41,    33,    25,   17,     9,    1,
    59,    51,   43,    35,    27,   19,    11,    3,
    61,    53,   45,    37,    29,   21,    13,    5,
    63,    55,   47,    39,    31,   23,    15,    7,
};

static const cl_uint CD_PREFIX[] = {
    0xAAAAAAAAU,
    0xCCCCCCCCU,
    0xF0F0F0F0U,
    0xFF00FF00U,
    0xFFFF0000U,
};

cl::Program UIntProgramTraits::loadProgram(
        const DeviceListContext *dlContext, std::size_t bitsGlobal,
        const KernelConfigData &config)
{
    auto globalContext = dlContext->getGlobalContext();
    auto kernelFolder = KernelLoader::getKernelFolder(
                globalContext->getDataDirectory());
    return KernelLoader::loadDesProgram(
                kernelFolder, "des", dlContext->getClContext(),
                bitsGlobal, config);
}

void UIntProgramTraits::writeCdBase(void *hostBuffer, std::uint_fast64_t cd, std::size_t bits)
{
    cl_uint *uintBuffer = static_cast<cl_uint *>(hostBuffer);

    for (std::size_t i = 0; i < vectorBits; i++) {
        uintBuffer[i] = CD_PREFIX[i];
    }
    for (std::size_t i = 0; i < bits - vectorBits; i++) {
        uintBuffer[vectorBits + i] = ((cd >> i) & 1) != 0 ? 0xffffffffu : 0x0u;
    }
}

void UIntProgramTraits::writeReferenceData(void *hostBuffer, std::uint_fast64_t ref)
{
    cl_uint *uintBuffer = static_cast<cl_uint *>(hostBuffer);
    for (std::size_t i = 0; i < 64; i++) {
        uintBuffer[i] = ((ref >> (IP[i] - 1)) & 1) != 0 ? 0xffffffffu : 0x0u;
    }
}


} // namespace gpu
} // namespace opencl
} // namespace descrack

