#ifndef DESCRACK_OPENCL_GPU_PROCESSINGUNIT_H
#define DESCRACK_OPENCL_GPU_PROCESSINGUNIT_H

#include "devicecontext.h"

#include <cstdint>

namespace descrack {
namespace opencl {
namespace gpu {

class ProcessingUnit
{
private:
    const DeviceContext *context;

    std::size_t items;
    std::size_t resultBits;

    cl::CommandQueue cmdQueue;

    std::size_t groupSize;
    std::size_t groupCount;

    std::uint_fast64_t batch;

    cl::Buffer cdBaseBuffer;
    cl::Buffer resultBuffer;

    std::size_t cdBaseBufferSize;
    std::size_t resultBufferSize;

    cl::Kernel kernel;
    cl::Event event;

public:
    ProcessingUnit() { }

    ProcessingUnit(const DeviceContext *context, std::size_t bitsThread);

    void setBatch(std::uint_fast64_t index);
    bool getResult(std::uint_fast64_t &key);

    void beginProcessing();
    void endProcessing();
};

} // namespace gpu
} // namespace opencl
} // namespace descrack

#endif // DESCRACK_OPENCL_GPU_PROCESSINGUNIT_H
