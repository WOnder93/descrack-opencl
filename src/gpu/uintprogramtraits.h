#ifndef DESCRACK_OPENCL_GPU_UINTPROGRAMTRAITS_H
#define DESCRACK_OPENCL_GPU_UINTPROGRAMTRAITS_H

#include "devicelistcontext.h"
#include "kernelconfig.h"

#include <cstdint>

namespace descrack {
namespace opencl {
namespace gpu {

class UIntProgramTraits
{
public:
    static constexpr std::size_t vectorBits = 5;

    static cl::Program loadProgram(
            const DeviceListContext *dlContext, std::size_t bitsGlobal,
            const KernelConfigData &config);

    static void writeCdBase(void *hostBuffer, std::uint_fast64_t cd, std::size_t bits);
    static void writeReferenceData(void *hostBuffer, std::uint_fast64_t ref);
};

} // namespace gpu
} // namespace opencl
} // namespace descrack

#endif // DESCRACK_OPENCL_GPU_UINTPROGRAMTRAITS_H
