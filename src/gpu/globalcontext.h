#ifndef DESCRACK_OPENCL_GPU_GLOBALCONTEXT_H
#define DESCRACK_OPENCL_GPU_GLOBALCONTEXT_H

#include "opencl.h"

#include <string>
#include <vector>

namespace descrack {
namespace opencl {
namespace gpu {

class GlobalContext
{
private:
    std::string dataDirectory;
    std::vector<cl::Device> devices;

public:
    const std::vector<cl::Device> &getAllDevices() const { return devices; }
    const std::string &getDataDirectory() const { return dataDirectory; }

    GlobalContext(const std::string &dataDirectory);
};

} // namespace gpu
} // namespace opencl
} // namespace descrack

#endif // DESCRACK_OPENCL_GPU_GLOBALCONTEXT_H
