#include "keybatchdistributor.h"

namespace descrack {
namespace opencl {

KeyBatchDistributor::KeyBatchDistributor(
        std::uint_fast64_t from, std::uint_fast64_t to)
    : next(from), limit(to)
{
}

bool KeyBatchDistributor::getNextBatch(std::uint_fast64_t &res)
{
    res = next++;
    return res < limit;
}

} // namespace opencl
} // namespace descrack
