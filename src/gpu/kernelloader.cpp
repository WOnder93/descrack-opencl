#include "kernelloader.h"

#include <fstream>
#include <sstream>
#include <iostream>

namespace descrack {
namespace opencl {
namespace gpu {

cl::Program KernelLoader::loadProgram(
        const std::string &sourcePath,
        const cl::Context &context,
        const std::string &buildOptions)
{
    std::ifstream sourceStream(sourcePath);
    if (sourceStream.fail()) {
        throw std::ifstream::failure("unable to open file");
    }
    sourceStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    std::string sourceText {
        std::istreambuf_iterator<char>(sourceStream),
        std::istreambuf_iterator<char>()
    };

    cl::Program prog(context, sourceText);
    try {
        prog.build(buildOptions.c_str());
    } catch (const cl::Error &err) {
        std::cerr << "ERROR: Failed to build program!" << std::endl;
        for (cl::Device &device : context.getInfo<CL_CONTEXT_DEVICES>()) {
            std::string buildLog = prog.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device);
            if (!buildLog.empty()) {
                std::cerr << "INFO: Build log from device '" << device.getInfo<CL_DEVICE_NAME>() << "':" << std::endl;
                std::cerr << buildLog << std::endl;
            }
        }
        throw;
    }
    return prog;
}

cl::Program KernelLoader::loadDesProgram(
        const std::string &kernelFolder, const std::string &kernelName,
        const cl::Context &context, std::size_t bitsGlobal,
        const KernelConfigData &config,
        bool debug)
{
    std::string sourcePath = kernelFolder + "/" + kernelName + ".cl";

    std::ostringstream opts;
    opts << "-I" << kernelFolder << " ";
    opts << "-DBITS_GLOBAL=" << bitsGlobal << " ";

    KernelConfig::generateConfigValues(opts);
    KernelConfig::generateOptions(opts, config);

    for (auto &pair : config) {
        opts << "-D" << pair.first << "=" << pair.second << " ";
    }
    if (debug) {
        opts << "-g -s \"" << sourcePath << "\" ";
    }
    return loadProgram(sourcePath, context, opts.str());
}

} // namespace gpu
} // namespace opencl
} // namespace descrack
