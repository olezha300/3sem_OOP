#include "StackMemoryResource.h"
#include <stdexcept>
#include <new>

StackMemoryResource::~StackMemoryResource() {
    for (auto& block : blocks) {
        if (!block.free) {
            ::operator delete(block.ptr);
        }
    }
}

void* StackMemoryResource::do_allocate(size_t bytes, size_t alignment) {
    for (auto& block : blocks) {
        if (block.free && block.size >= bytes) {
            block.free = false;
            return block.ptr;
        }
    }

    void* new_block = ::operator new(bytes, std::align_val_t(alignment));
    blocks.push_back({ new_block, bytes, false });
    return new_block;
}

void StackMemoryResource::do_deallocate(void* ptr, size_t bytes, size_t alignment) {
    for (auto& block : blocks) {
        if (block.ptr == ptr && block.size == bytes && !block.free) {
            block.free = true;
            return;
        }
    }
    throw std::logic_error("Attempted to deallocate unmanaged or already free memory.");
}

bool StackMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}
