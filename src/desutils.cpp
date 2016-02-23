#include "desutils.h"

#include <random>

namespace descrack {
namespace opencl {

static const int PC1[56] = {
    57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18, 10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22, 14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4,
};

static std::mt19937_64 random { 42 };

std::uint_fast64_t DesUtils::generateKey()
{
    return random();
}

std::uint_fast64_t DesUtils::keyFromOpenSSL(const unsigned char *block)
{
    std::uint_fast64_t result = 0x0u;
    for(int k = 0; k < 8; k++) {
        unsigned char c = block[k];
        for(int i = 0; i < 8; i++) {
            if((c & (static_cast<unsigned char>(0x1u) << i)) != 0) {
                result |= static_cast<std::uint_fast64_t>(0x1u) << (8 * k + 7 - i);
            }
        }
    }
    return result;
}

void DesUtils::keyToOpenSSL(std::uint_fast64_t key, unsigned char *block)
{
    for(int k = 0; k < 8; k++) {
        unsigned char c = 0x0u;
        for(int i = 0; i < 8; i++) {
            if((key & (static_cast<std::uint_fast64_t>(0x1u) << (8 * k + i))) != 0)
                c |= static_cast<unsigned char>(0x1u) << (7 - i);
        }
        block[k] = c;
    }
}

std::uint_fast64_t DesUtils::keyFromCd(std::uint_fast64_t cd)
{
    std::uint_fast64_t key = 0x0u;
    for(int i = 0; i < 56; i++) {
        if((cd & (static_cast<std::uint_fast64_t>(0x1u) << i)) != 0)
            key |= static_cast<std::uint_fast64_t>(0x1u) << (PC1[i] - 1);
    }
    return key;
}

std::uint_fast64_t DesUtils::keyToCd(std::uint_fast64_t key)
{
    std::uint_fast64_t cd = 0x0u;
    for(int i = 0; i < 56; i++) {
        if((key & (static_cast<std::uint_fast64_t>(0x1u) << (PC1[i] - 1))) != 0)
            cd |= static_cast<std::uint_fast64_t>(0x1u) << i;
    }
    return cd;
}

} // namespace opencl
} // namespace descrack

