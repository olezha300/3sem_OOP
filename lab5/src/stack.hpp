#pragma once

#include <memory>
#include <functional>
#include <vector>
#include "iterator.h"

namespace Containers {

    template <class T, class Allocator = std::pmr::polymorphic_allocator<T>>
    class Stack {
    public:
        struct Node {
            using value_type = T;

            T data;
            Node* next;

            Node(const T& value) : data(value), next(nullptr) {}
            Node(T&& value) : data(std::move(value)), next(nullptr) {}
        };

        using NodeAllocator = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
        using NodeAllocatorTraits = std::allocator_traits<NodeAllocator>;

        using iterator = StackIterator<Node>;
        using const_iterator = StackIterator<const Node>;

    private:
        Node* top_ptr;
        std::size_t stack_size;
        NodeAllocator allocator;

    public:
        explicit Stack(const Allocator& alloc = Allocator())
            : top_ptr(nullptr), stack_size(0), allocator(alloc) {}

        Stack(const Stack& other)
            : top_ptr(nullptr), stack_size(0), allocator(NodeAllocatorTraits::select_on_container_copy_construction(other.allocator)) {
            std::vector<T> elems;
            Node* current = other.top_ptr;
            while(current) {
                elems.push_back(current->data);
                current = current->next;
            }
            for(auto it = elems.rbegin(); it != elems.rend(); ++it) {
                push(*it);
            }
        }

        Stack(Stack&& other) noexcept
            : top_ptr(other.top_ptr), stack_size(other.stack_size), allocator(std::move(other.allocator)) {
            other.top_ptr = nullptr;
            other.stack_size = 0;
        }

        Stack& operator=(const Stack& other) {
            if (this != &other) {
                clear();
                if constexpr (NodeAllocatorTraits::propagate_on_container_copy_assignment::value) {
                    allocator = other.allocator;
                }
                std::vector<T> elems;
                Node* current = other.top_ptr;
                while(current) {
                    elems.push_back(current->data);
                    current = current->next;
                }
                for(auto it = elems.rbegin(); it != elems.rend(); ++it) {
                    push(*it);
                }
            }
            return *this;
        }

        Stack& operator=(Stack&& other) noexcept {
            if (this != &other) {
                clear();
                if (NodeAllocatorTraits::propagate_on_container_move_assignment::value) {
                    allocator = std::move(other.allocator);
                }
                top_ptr = other.top_ptr;
                stack_size = other.stack_size;
                other.top_ptr = nullptr;
                other.stack_size = 0;
            }
            return *this;
        }

        ~Stack() {
            clear();
        }

        void push(const T& item) {
            Node* new_node = NodeAllocatorTraits::allocate(allocator, 1);
            try {
                NodeAllocatorTraits::construct(allocator, new_node, item);
            } catch (...) {
                NodeAllocatorTraits::deallocate(allocator, new_node, 1);
                throw;
            }

            new_node->next = top_ptr;
            top_ptr = new_node;
            ++stack_size;
        }

        void push(T&& item) {
            Node* new_node = NodeAllocatorTraits::allocate(allocator, 1);
            try {
                NodeAllocatorTraits::construct(allocator, new_node, std::move(item));
            } catch (...) {
                NodeAllocatorTraits::deallocate(allocator, new_node, 1);
                throw;
            }

            new_node->next = top_ptr;
            top_ptr = new_node;
            ++stack_size;
        }

        void pop() {
            if (empty()) {
                throw std::out_of_range("Pop from empty stack.");
            }
            Node* old_top = top_ptr;
            top_ptr = top_ptr->next;
            NodeAllocatorTraits::destroy(allocator, old_top);
            NodeAllocatorTraits::deallocate(allocator, old_top, 1);
            --stack_size;
        }

        T& top() {
            if (empty()) {
                throw std::out_of_range("Accessing top of empty stack.");
            }
            return top_ptr->data;
        }

        const T& top() const {
            if (empty()) {
                throw std::out_of_range("Accessing top of empty stack.");
            }
            return top_ptr->data;
        }

        bool empty() const {
            return stack_size == 0;
        }

        std::size_t size() const {
            return stack_size;
        }

        void clear() {
            while (!empty()) {
                pop();
            }
        }

        iterator begin() { return iterator(top_ptr); }
        iterator end() { return iterator(nullptr); }

        const_iterator begin() const { return const_iterator(top_ptr); }
        const_iterator end() const { return const_iterator(nullptr); }

        T& at(std::size_t idx) {
            if (idx >= stack_size) {
                throw std::out_of_range("Index out of range.");
            }
            Node* current = top_ptr;
            for (std::size_t i = 0; i < idx; ++i) {
                current = current->next;
            }
            return current->data;
        }

        const T& at(std::size_t idx) const {
            if (idx >= stack_size) {
                throw std::out_of_range("Index out of range.");
            }
            Node* current = top_ptr;
            for (std::size_t i = 0; i < idx; ++i) {
                current = current->next;
            }
            return current->data;
        }
    };

}
