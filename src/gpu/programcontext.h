#ifndef DESCRACK_OPENCL_GPU_PROGRAMCONTEXT_H
#define DESCRACK_OPENCL_GPU_PROGRAMCONTEXT_H

#include "devicelistcontext.h"
#include "kernelconfig.h"

#include <cstdint>

namespace descrack {
namespace opencl {
namespace gpu {

class ProgramContext
{
private:
    typedef void (*CdWriter)(void *hostBuffer, std::uint_fast64_t cd, std::size_t bits);
    typedef void (*RefDataWriter)(void *hostBuffer, std::uint_fast64_t ref);

    const DeviceListContext *dlContext;

    cl::Program program;

    std::size_t bitsGlobal;
    std::size_t vectorLevel;

    CdWriter cdBaseWriter;
    RefDataWriter refDataWriter;

    cl::Buffer refInputBuffer;
    cl::Buffer refOutputBuffer;

    ProgramContext(const DeviceListContext *dlContext,
                   std::size_t bitsGlobal, cl::Program program,
                   std::size_t vectorLevel,
                   CdWriter cdBaseWriter, RefDataWriter refDataWriter);

public:
    template<class Traits>
    static ProgramContext create(
            const DeviceListContext *dlContext,
            std::size_t bitsGlobal,
            const KernelConfigData &config)
    {
        return ProgramContext {
            dlContext, bitsGlobal,
            Traits::loadProgram(dlContext, bitsGlobal, config),
            Traits::vectorLevel, Traits::writeCdBase, Traits::writeReferenceData
        };
    }

    const DeviceListContext *getDeviceListContext() const { return dlContext; }

    cl::Program getProgram() const { return program; }

    std::size_t getBitsGlobal() const { return bitsGlobal; }
    std::size_t getVectorLevel() const { return vectorLevel; }
    std::size_t getVectorBits() const { return 1 << vectorLevel; }
    std::size_t getVectorBytes() const { return 1 << (vectorLevel - 3); }

    cl::Buffer getRefInputBuffer() const { return refInputBuffer; }
    cl::Buffer getRefOutputBuffer() const { return refOutputBuffer; }

    std::size_t getRefInputBufferSize() const { return 64 * getVectorBytes(); }
    std::size_t getRefOutputBufferSize() const { return 64 * getVectorBytes(); }

    void writeCdBase(void *hostBuffer, std::uint_fast64_t batch) const;
    void writeRefData(cl::CommandQueue cmdQueue, std::uint_fast64_t refInput,
                      std::uint_fast64_t refOutput) const;
};

} // namespace gpu
} // namespace opencl
} // namespace descrack

#endif // DESCRACK_OPENCL_GPU_PROGRAMCONTEXT_H
