#ifndef DESCRACK_OPENCL_TESTS_TESTS_H
#define DESCRACK_OPENCL_TESTS_TESTS_H

#include "gpu/globalcontext.h"
#include "descracker.h"

#include <string>
#include <cstdint>

namespace descrack {
namespace opencl {
namespace tests {

class Tests
{
private:
    static constexpr std::size_t BITS_GLOBAL = 10;
    static constexpr std::size_t BITS_THREAD = 4;

    int testsFailed, testsTotal;

    gpu::GlobalContext globalContext;
    DesCracker cracker;
    DesCracker::Configuration config;

    void processTest(bool condition, const std::string &name);
    void testCrack(const std::string &name,
                   std::uint_fast64_t input, std::uint_fast64_t key);

public:
    Tests() :
        testsFailed(0), testsTotal(0), globalContext("data"),
        cracker(&globalContext, globalContext.getAllDevices(),
                BITS_GLOBAL, BITS_THREAD), config(&cracker)
    {
    }

    int run();
};

} // namespace tests
} // namespace opencl
} // namespace descrack

#endif // DESCRACK_OPENCL_TESTS_TESTS_H
