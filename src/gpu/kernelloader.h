#ifndef DESCRACK_OPENCL_GPU_KERNELLOADER_H
#define DESCRACK_OPENCL_GPU_KERNELLOADER_H

#include "opencl.h"
#include "kernelconfig.h"

#include <string>

namespace descrack {
namespace opencl {
namespace gpu {

class KernelLoader
{
public:
    static std::string getKernelFolder(const std::string &dataFolder)
    {
        return dataFolder + "/opencl/kernels";
    }

    static cl::Program loadProgram(
            const std::string &sourcePath,
            const cl::Context &context,
            const std::string &buildOptions = {});

    static cl::Program loadDesProgram(
            const std::string &kernelFolder,
            const std::string &kernelName,
            const cl::Context &context, std::size_t bitsGlobal,
            const KernelConfigData &config = {},
            bool debug = false);
};

} // namespace gpu
} // namespace opencl
} // namespace descrack

#endif // DESCRACK_OPENCL_GPU_KERNELLOADER_H
