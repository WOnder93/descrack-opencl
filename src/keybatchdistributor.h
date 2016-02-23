#ifndef DESCRACK_OPENCL_KEYBATCHDISTRIBUTOR_H
#define DESCRACK_OPENCL_KEYBATCHDISTRIBUTOR_H

#include <atomic>
#include <cstdint>

namespace descrack {
namespace opencl {

class KeyBatchDistributor
{
private:
    std::atomic_size_t next;
    std::size_t limit;

public:
    KeyBatchDistributor(std::size_t from, std::size_t to);

    bool getNextBatch(std::size_t &res);
};

} // namespace opencl
} // namespace descrack

#endif // DESCRACK_OPENCL_KEYBATCHDISTRIBUTOR_H
