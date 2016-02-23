#include "keybatchdistributor.h"

namespace descrack {
namespace opencl {

KeyBatchDistributor::KeyBatchDistributor(
        std::size_t from, std::size_t to)
    : next(from), limit(to)
{
}

bool KeyBatchDistributor::getNextBatch(std::size_t &res)
{
    res = next++;
    // FIXME: prevent overflow (research on lock-free queues)
    if (res > limit) {
        return false;
    }
    return true;
}

} // namespace opencl
} // namespace descrack
