#ifndef DESCRACK_OPENCL_GPU_KERNELCONFIG_H
#define DESCRACK_OPENCL_GPU_KERNELCONFIG_H

#include <string>
#include <unordered_map>

namespace descrack {
namespace opencl {
namespace gpu {

typedef std::unordered_map<std::string, std::string> KernelConfigData;

namespace KernelConfig
{
    namespace Vector
    {
        static constexpr const char *KEY = "CONFIG_VECTOR";

        static constexpr const char *UINT = "CONFIG_VECTOR_UINT";
    }

    namespace SBoxes
    {
        static constexpr const char *KEY = "CONFIG_SBOXES";

        static constexpr const char *OPENWALL = "CONFIG_SBOXES_OPENWALL";
        static constexpr const char *OPENWALL_BITSEL = "CONFIG_SBOXES_OPENWALL_BITSEL";
        static constexpr const char *MKWAN = "CONFIG_SBOXES_MKWAN";

        static constexpr std::size_t SBOX_COUNT = 8;

        static constexpr const char *OPENWALL_SBOX_VER_KEYS[SBOX_COUNT] = {
            "CONFIG_OPENWALL_SBOX_0",
            "CONFIG_OPENWALL_SBOX_1",
            "CONFIG_OPENWALL_SBOX_2",
            "CONFIG_OPENWALL_SBOX_3",
            "CONFIG_OPENWALL_SBOX_4",
            "CONFIG_OPENWALL_SBOX_5",
            "CONFIG_OPENWALL_SBOX_6",
            "CONFIG_OPENWALL_SBOX_7",
        };
        static constexpr std::size_t OPENWALL_SBOX_VER_COUNTS[SBOX_COUNT] = {
            3, 5, 6, 1, 3, 4, 14, 5
        };
        static constexpr std::size_t OPENWALL_BITSEL_SBOX_VER_COUNTS[SBOX_COUNT] = {
            2, 3, 2, 2, 5, 4, 2, 2
        };
    }

    inline void generateConfigValues(std::ostream &out)
    {
        out << "-D" << Vector::UINT << "=0 "
            << "-D" << SBoxes::OPENWALL << "=0 "
            << "-D" << SBoxes::OPENWALL_BITSEL << "=1 "
            << "-D" << SBoxes::MKWAN << "=2 ";
    }

    inline void generateOptions(std::ostream &out,
                                const KernelConfigData &config)
    {
        for (auto &pair : config) {
            out << "-D" << pair.first << "=" << pair.second << " ";
        }
    }
}

} // namespace gpu
} // namespace opencl
} // namespace descrack

#endif // DESCRACK_OPENCL_GPU_KERNELCONFIG_H
