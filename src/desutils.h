#ifndef DESCRACK_OPENCL_DESUTILS_H
#define DESCRACK_OPENCL_DESUTILS_H

#include <cstdint>

namespace descrack {
namespace opencl {

class DesUtils
{
public:
    static std::uint_fast64_t generateKey();

    static std::uint_fast64_t keyFromOpenSSL(const unsigned char *block);
    static void keyToOpenSSL(std::uint_fast64_t key, unsigned char *block);

    static std::uint_fast64_t keyFromCd(std::uint_fast64_t cd);
    static std::uint_fast64_t keyToCd(std::uint_fast64_t key);
};

} // namespace opencl
} // namespace descrack

#endif // DESCRACK_OPENCL_DESUTILS_H
