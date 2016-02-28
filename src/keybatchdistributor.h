#ifndef DESCRACK_OPENCL_KEYBATCHDISTRIBUTOR_H
#define DESCRACK_OPENCL_KEYBATCHDISTRIBUTOR_H

#include <atomic>
#include <cstdint>

namespace descrack {
namespace opencl {

class KeyBatchDistributor
{
private:
    std::atomic_uint_fast64_t next;
    std::uint_fast64_t limit;

public:
    KeyBatchDistributor(std::uint_fast64_t from, std::uint_fast64_t to);

    bool getNextBatch(std::uint_fast64_t &res);
};

} // namespace opencl
} // namespace descrack

#endif // DESCRACK_OPENCL_KEYBATCHDISTRIBUTOR_H
