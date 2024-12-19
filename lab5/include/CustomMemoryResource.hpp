#pragma once
#include <vector>
#include <memory_resource>
#include <iostream>
#include <concepts>
#include <cstddef>

class CustomMemoryResource : public std::pmr::memory_resource
{
    public :
        CustomMemoryResource() = default;

        ~CustomMemoryResource() {
            for(int i = 0; i < clean_blocks.size(); ++i) {
                ::operator delete(clean_blocks[i].offset, clean_blocks[i].alignment);
            }

            for(int i = 0; i < used_blocks.size(); ++i) {
                ::operator delete(used_blocks[i].offset, used_blocks[i].alignment);
            }
        }

    protected :
        struct Block
        {
            size_t *offset {nullptr};//
            size_t size {0};
            size_t alignment {0};
        };

        void* do_allocate(size_t bytes, size_t alignment) override
        {
            int index = -1;
            void* ptr;

            for(int i = 0; i < clean_blocks.size(); ++i) {
                if(clean_blocks[i].size >= bytes && clean_blocks[i].alignment == alignment) {
                    ptr = clean_blocks[i].offset;
                    Block tmp{clean_blocks[i].offset, clean_blocks[i].size, clean_blocks[i].alignment};
                    used_blocks.push_back(tmp);
                    index = i;
                    break;
                }
            }

            if(index != -1) {
                clean_blocks.erase(clean_blocks.begin() + index);
                return ptr;
            } else {
                void* ptr = ::operator new(bytes, std::align_val_t{alignment});
                Block tmp{static_cast<size_t*>(ptr), bytes, alignment};
                used_blocks.push_back(tmp);
                return ptr;
            }

        }



        void do_deallocate(void *ptr, size_t bytes, size_t alignment) override
        {
            int index = -1;
            for(int i = 0; i < used_blocks.size(); ++i) {
                if(used_blocks[i].offset == ptr && used_blocks[i].size == bytes && used_blocks[i].alignment == alignment) {
                    clean_blocks.push_back(used_blocks[i]);
                    index = i;
                    break;
                }
            }
            if(index != -1) {
                used_blocks.erase(used_blocks.begin() + index);
                return;
            }

        }

        bool do_is_equal(const std::pmr::memory_resource &other) const noexcept override{
            return this == &other;
        }

    private:
        std::vector<Block> clean_blocks;
        std::vector<Block> used_blocks;
};
