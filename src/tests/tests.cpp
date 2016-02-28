#include "tests.h"

#include "desutils.h"
#include "descracker.h"

#include <iostream>
#include <openssl/des.h>

namespace descrack {
namespace opencl {
namespace tests {

static constexpr std::size_t SHIFT_TEST = 0x100u;

static std::uint_fast64_t encrypt(std::uint_fast64_t input, std::uint_fast64_t key) {
    DES_cblock input_os, output_os, key_os;
    DesUtils::keyToOpenSSL(input, input_os);
    DesUtils::keyToOpenSSL(key, key_os);

    DES_key_schedule ks;
    DES_set_key_unchecked(&key_os, &ks);
    DES_ecb_encrypt(&input_os, &output_os, &ks, DES_ENCRYPT);
    return DesUtils::keyFromOpenSSL(output_os);
}

void Tests::processTest(bool condition, const std::string &name)
{
    if (!condition) {
        std::cerr << "TEST '" << name << "' FAILED!" << std::endl;
        testsFailed++;
    }
    testsTotal++;
}

void Tests::testCrack(const std::string &name,
                      std::uint_fast64_t input, std::uint_fast64_t key)
{
    auto output = encrypt(input, key);
    KeyData keyData(input, output);

    auto batch = cracker.getBatchFromKey(key);

    DesCracker::Configuration::Session session(&config, &keyData,
                                               batch, batch + 2);
    session.finishCracking();

    bool found = session.wasKeyFound();
    processTest(found, name + " (key not found)");
    if (found) {
        processTest(session.getKey() == (key & 0x7f7f7f7f7f7f7f7fu),
                    name + " (wrong key value)");
    }
}

int Tests::run()
{
    for(int i = 0; i < 3; i++) {
        DES_cblock os_block;
        uint_fast64_t key = DesUtils::generateKey();
        DesUtils::keyToOpenSSL(key, os_block);
        processTest(DesUtils::keyFromOpenSSL(os_block) == key,
                    "Correctness of openssl <-> des_crack block conversion");
    }

    DES_cblock zero_output = { 0x8cu, 0xa6u, 0x4du, 0xe9u, 0xc1u, 0xb1u, 0x23u, 0xa7u };
    processTest(encrypt(0, 0) == DesUtils::keyFromOpenSSL(zero_output),
                "Zero output test");

    testCrack("Crack test on zero key and zero input", 0x0u, 0x0u);
    testCrack("Crack test on zero key and input 0x1u", 0x1u, 0x0u);
    testCrack("Crack test on zero input and key 0xfu", 0x0u, 0xfu);

    for(int cdb = 0; cdb < 56; cdb++) {
        auto cd = static_cast<std::uint_fast64_t>(0x1u) << cdb;
        auto key = DesUtils::keyFromCd(cd);
        testCrack("Crack test on zero input and CD 1 << " + std::to_string(cdb),
                  0x0u, key);
    }

    for(int i = 0; i < 10; i++) {
        auto input = DesUtils::generateKey();
        testCrack("Crack test on zero key", input, 0x0u);
    }

    for(int i = 0; i < 10; i++) {
        auto key = DesUtils::generateKey();
        testCrack("Crack test on zero input", 0x0u, key);
    }

    for(int i = 0; i < 10; i++) {
        auto input = DesUtils::generateKey();
        auto key = DesUtils::generateKey();
        testCrack("Crack test", input, key);
    }

    for(int i = 0; i < 10; i++) {
        auto input = DesUtils::generateKey();
        auto key = DesUtils::generateKey();
        processTest(encrypt(input, key) == ~encrypt(~input, ~key),
                    "Complementary key test.");
    }

    std::cerr << "Tests run: " << testsTotal << ", failed: "
              << testsFailed << std::endl;
    return testsFailed;
}

} // namespace tests
} // namespace opencl
} // namespace descrack

