#pragma once
#include <vector>
#include <memory_resource>
#include <iostream>
#include <CustomMemoryResource.hpp>

template <typename T>
class CustomStack {
    public :
        CustomStack(std::pmr::memory_resource* mr = std::pmr::get_default_resource());

        ~CustomStack();

        void push_back(const T &other);
        void pop_back();
        void clear();
        T top();
        size_t get_size();
        size_t get_capacity();

        class iterator {
            public :
                iterator(T* ptr) : ptr(ptr) {}

                T& operator*() { return *ptr; }

                T* get_pointer() { return ptr; }

                iterator& operator++(int) {//postfix
                    iterator tmp(this->ptr);
                    ++this->ptr;
                    return tmp;
                }

                iterator& operator++() {//pref
                    ++this->ptr;
                    return *this;
                }

                bool operator==(const iterator &it) const { return ptr == it.ptr; }
                bool operator!=(const iterator &it) const { return ptr != it.ptr; }

        private:
            T* ptr;
        };

        iterator begin();
        iterator end();

    private:
        void resize();
        T* data = nullptr;
        size_t capacity = 0;
        size_t size = 0;
        std::pmr::polymorphic_allocator<T> allocator;
};

template <typename T>
CustomStack<T>::CustomStack(std::pmr::memory_resource* mr) : data(nullptr), capacity(0), size(0), allocator(mr) {}



template <typename T>
CustomStack<T>::~CustomStack() {
    for(int i = 0; i < size; ++i) { allocator.destroy(data + i); }
    size = 0;
    allocator.deallocate(data, capacity);
}

template <typename T>
void CustomStack<T>::resize() {
    T* new_data = allocator.allocate(capacity * 2 + 10);
    for(int i = 0; i < size; ++i) {
        new_data[i] = std::move(data[i]);
    }

    for(int i = 0; i < size; ++i) {
        allocator.destroy(data + i);
    }
    allocator.deallocate(data, size);
    data = std::move(new_data);
    capacity = capacity * 2 + 10;
}

template <typename T>
void CustomStack<T>::clear() {
    for(int i = 0; i < size; ++i) { allocator.destroy(data + i); }
    size = 0;
}

template <typename T>
T CustomStack<T>::top() {
    if(size > 0) { return data[size - 1]; }
}

template <typename T>
size_t CustomStack<T>::get_size() { return this->size; }

template <typename T>
size_t CustomStack<T>::get_capacity() { return this->capacity; }

template <typename T>
void CustomStack<T>::push_back(const T& other) {
    if(size * 10 >= capacity * 8) { resize(); }
    allocator.construct(data + size, other);
    ++size;
}

template <typename T>
void CustomStack<T>::pop_back() {
    if(size == 0) { return; }
    --size;
    allocator.destroy(data + size);
}

template <typename T>
typename CustomStack<T>::iterator CustomStack<T>::begin() {
    iterator tmp(this->data);
    return tmp;
}

template <typename T>
typename CustomStack<T>::iterator CustomStack<T>::end() {
    iterator tmp(this->data + this->capacity);
    return tmp;
}
