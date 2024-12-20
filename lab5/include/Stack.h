#pragma once

#include <memory>
#include <memory_resource>
#include <iostream>
#include <iterator>

template <class T>
class Stack {
    struct _node {
        T value;
        _node* next;
    };

    using AT = std::pmr::polymorphic_allocator<_node>;

    class _const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

    private:
        const _node* _current;

    public:
        explicit _const_iterator(const _node* node) : _current(node) {}

        const T& operator*() const { return _current->value; }
        const T* operator->() const { return &_current->value; }

        _const_iterator& operator++() {
            _current = _current->next;
            return *this;
        }

        _const_iterator operator++(int) {
            _const_iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const _const_iterator& other) const { return _current == other._current; }
        bool operator!=(const _const_iterator& other) const { return _current != other._current; }
    };

    _node* _head = nullptr;
    AT _alloc;
    size_t _size = 0;

    void _clear();

public:
    explicit Stack(std::pmr::memory_resource* resource = std::pmr::get_default_resource());
    Stack(const Stack& other, std::pmr::memory_resource* resource = nullptr);
    Stack(Stack&& other) noexcept;
    ~Stack() noexcept;

    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;

    bool operator==(const Stack& other) const;
    bool operator!=(const Stack& other) const;

    void push(T element);
    std::shared_ptr<T> pop();
    std::shared_ptr<T> top() const;

    [[nodiscard]] size_t size() const { return _size; }
    [[nodiscard]] bool empty() const { return _size == 0; }
    void clear() { _clear(); }

    _const_iterator begin() const { return _const_iterator(_head); }
    _const_iterator end() const { return _const_iterator(nullptr); }

    template <class U>
    friend std::ostream& operator<<(std::ostream& os, const Stack<U>& stack);
};


template <class T>
Stack<T>::Stack(std::pmr::memory_resource* resource) : _alloc(resource), _size(0) {}

template <class T>
Stack<T>::Stack(const Stack& other, std::pmr::memory_resource* resource)
    : _alloc(resource ? resource : other._alloc.resource()), _size(0) {
    if (other._head != nullptr) {
        _head = _alloc.allocate(1);
        std::allocator_traits<AT>::construct(_alloc, _head, _node{other._head->value, nullptr});

        _node* current = _head;
        _node* other_current = other._head->next;

        while (other_current != nullptr) {
            _node* new_node = _alloc.allocate(1);
            std::allocator_traits<AT>::construct(_alloc, new_node, _node{other_current->value, nullptr});

            current->next = new_node;
            current = new_node;
            other_current = other_current->next;
        }
    }
    _size = other._size;
}

template <class T>
Stack<T>::Stack(Stack&& other) noexcept : _alloc(other._alloc), _head(other._head), _size(other._size) {
    other._head = nullptr;
    other._size = 0;
}

template <class T>
Stack<T>::~Stack() noexcept {
    _clear();
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
    if (this != &other) {
        _clear();

        if (other._head != nullptr) {
            _head = _alloc.allocate(1);
            std::allocator_traits<AT>::construct(_alloc, _head, _node{other._head->value, nullptr});

            _node* current = _head;
            _node* other_current = other._head->next;

            while (other_current != nullptr) {
                _node* new_node = _alloc.allocate(1);
                std::allocator_traits<AT>::construct(_alloc, new_node, _node{other_current->value, nullptr});

                current->next = new_node;
                current = new_node;
                other_current = other_current->next;
            }
        }
        _size = other._size;
    }
    return *this;
}

template <class T>
Stack<T>& Stack<T>::operator=(Stack&& other) noexcept {
    if (this != &other) {
        _clear();
        _head = other._head;
        _size = other._size;
        _alloc = other._alloc;

        other._head = nullptr;
        other._size = 0;
    }
    return *this;
}

template <class T>
bool Stack<T>::operator==(const Stack& other) const {
    if (_size != other._size) return false;

    _node* first_head = _head;
    _node* second_head = other._head;

    while (first_head != nullptr) {
        if (first_head->value != second_head->value) return false;

        first_head = first_head->next;
        second_head = second_head->next;
    }
    return true;
}

template <class T>
bool Stack<T>::operator!=(const Stack& other) const {
    return !(*this == other);
}

template <class T>
void Stack<T>::push(T element) {
    _node* node = _alloc.allocate(1);
    std::allocator_traits<AT>::construct(_alloc, node, _node{element, _head});
    _head = node;
    ++_size;
}

template <class T>
std::shared_ptr<T> Stack<T>::pop() {
    if (_head == nullptr) throw std::runtime_error("Stack is empty");

    _node* temp = _head;
    std::shared_ptr<T> result = std::make_shared<T>(_head->value);
    _head = _head->next;

    std::allocator_traits<AT>::destroy(_alloc, temp);
    _alloc.deallocate(temp, 1);
    --_size;

    return result;
}

template <class T>
std::shared_ptr<T> Stack<T>::top() const {
    if (_head == nullptr) throw std::runtime_error("Stack is empty");

    return std::make_shared<T>(_head->value);
}

template <class T>
void Stack<T>::_clear() {
    while (_head != nullptr) {
        _node* temp = _head;
        _head = _head->next;
        std::allocator_traits<AT>::destroy(_alloc, temp);
        _alloc.deallocate(temp, 1);
    }
    _size = 0;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& stack) {
    os << '[';
    auto* elem = stack._head;
    while (elem != nullptr) {
        os << elem->value;
        if (elem->next != nullptr) os << ", ";
        elem = elem->next;
    }
    os << ']';
    return os;
}
