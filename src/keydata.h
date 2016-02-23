#ifndef DESCRACK_OPENCL_KEYDATA_H
#define DESCRACK_OPENCL_KEYDATA_H

#include <cstdint>

namespace descrack {
namespace opencl {

class KeyData
{
private:
    std::uint_least64_t refInput;
    std::uint_least64_t refOutput;

public:
    std::uint_least64_t getRefInput() const { return refInput; }
    std::uint_least64_t getRefOutput() const { return refOutput; }

    KeyData(std::uint_least64_t refInput, std::uint_least64_t refOutput)
        : refInput(refInput), refOutput(refOutput)
    {
    }
};

} // namespace opencl
} // namespace descrack

#endif // DESCRACK_OPENCL_KEYDATA_H
