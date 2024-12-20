#pragma once

#include <memory_resource>
#include <vector>

class StackMemoryResource : public std::pmr::memory_resource {
    struct Block {
        void* ptr;
        size_t size;
        bool free;
    };

    std::vector<Block> blocks;

protected:
    void* do_allocate(size_t bytes, size_t alignment) override;
    void do_deallocate(void* ptr, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

public:
    ~StackMemoryResource() override;
};
