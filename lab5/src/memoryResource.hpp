#pragma once
#include <memory_resource>
#include <vector>
#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <cstdint>
#include <iostream>

namespace Containers {

class MemoryResource : public std::pmr::memory_resource {
private:
    struct Block {
        void* ptr;
        std::size_t size;
        bool is_free;

        Block(void* p, std::size_t s, bool free = true)
            : ptr(p), size(s), is_free(free) {}
    };

    std::vector<Block> blocks;
    void* memory_pool;
    std::size_t total_size;

    void* align_address(void* ptr, std::size_t alignment) {
        auto address = reinterpret_cast<std::uintptr_t>(ptr);
        std::uintptr_t aligned = (address + alignment - 1) & ~(alignment - 1);
        return reinterpret_cast<void*>(aligned);
    }

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        std::cout << "Allocating " << bytes << " bytes with alignment " << alignment << '\n';
        if ((alignment & (alignment - 1)) != 0) {
            throw std::invalid_argument("Alignment must be a power of 2.");
        }

        for (std::size_t i = 0; i < blocks.size(); ++i) {
            auto& block = blocks[i];
            if (block.is_free && block.size >= bytes) {
                void* aligned_ptr = align_address(block.ptr, alignment);
                std::size_t padding = static_cast<std::byte*>(aligned_ptr) - static_cast<std::byte*>(block.ptr);

                if (block.size < bytes + padding) {
                    continue;
                }

                if (padding > 0) {
                    blocks.emplace_back(block.ptr, padding, true);
                    block.ptr = static_cast<std::byte*>(block.ptr) + padding;
                    block.size -= padding;
                }

                if (block.size > bytes) {
                    blocks.emplace_back(
                        static_cast<std::byte*>(block.ptr) + bytes,
                        block.size - bytes,
                        true
                    );
                }

                block.size = bytes;
                block.is_free = false;

                std::cout << "Allocated at: " << block.ptr << '\n';
                return block.ptr;
            }
        }

        throw std::bad_alloc();
    }

    void do_deallocate(void* p, std::size_t bytes, std::size_t /*alignment*/) override {
        std::cout << "Deallocating " << bytes << " bytes at address " << p << '\n';
        auto it = std::find_if(blocks.begin(), blocks.end(), [p](const Block& block) {
            return block.ptr == p;
        });

        if (it == blocks.end()) {
            throw std::invalid_argument("Attempted to deallocate unmanaged memory.");
        }

        it->is_free = true;

        if (it != blocks.begin()) {
            auto prev = std::prev(it);
            if (prev->is_free) {
                prev->size += it->size;
                blocks.erase(it);
                it = prev;
            }
        }

        if (std::next(it) != blocks.end()) {
            auto next = std::next(it);
            if (next->is_free) {
                it->size += next->size;
                blocks.erase(next);
            }
        }
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }

public:
    MemoryResource(std::size_t total_size)
        : memory_pool(new std::byte[total_size]), total_size(total_size) {
        blocks.reserve(1000);
        blocks.emplace_back(memory_pool, total_size, true);
    }

    ~MemoryResource() override {
        delete[] static_cast<std::byte*>(memory_pool);
    }

    std::size_t get_total_size() const {
        return total_size;
    }

    std::size_t get_free_blocks_count() const {
        return std::count_if(blocks.begin(), blocks.end(), [](const Block& block) { return block.is_free; });
    }

    std::size_t get_allocated_blocks_count() const {
        return std::count_if(blocks.begin(), blocks.end(), [](const Block& block) { return !block.is_free; });
    }
};

}
