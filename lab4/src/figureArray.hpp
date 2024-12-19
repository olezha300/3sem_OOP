#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include "figure.h"

namespace Shape {

template <typename T>
concept ValidFigureType =
    std::is_same_v<T, std::shared_ptr<std::remove_cv_t<std::remove_reference_t<typename T::element_type>>>> &&
    std::is_base_of_v<IFigure, typename T::element_type>;

template <ValidFigureType T>
class FigureArray {
private:
    std::shared_ptr<T[]> data;
    size_t size;
    size_t capacity;

    void resize(size_t newCapacity) {
        if (newCapacity < size) {
            throw std::logic_error("New capacity cannot be less than the current size.");
        }

        std::shared_ptr<T[]> newData(new T[newCapacity], std::default_delete<T[]>());
        for (size_t i = 0; i < size; ++i) {
            newData[i] = std::move(data[i]);
        }
        data = std::move(newData);
        capacity = newCapacity;
    }

public:
    FigureArray() : data(nullptr), size(0), capacity(0) {}

    FigureArray(size_t initialCapacity)
        : data(std::make_shared<T[]>(initialCapacity)), size(0), capacity(initialCapacity) {}

    ~FigureArray() = default;

    FigureArray(const FigureArray& other)
        : data(std::make_shared<T[]>(other.capacity)), size(other.size), capacity(other.capacity) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    FigureArray(FigureArray&& other) noexcept
        : data(std::move(other.data)), size(other.size), capacity(other.capacity) {
        other.size = 0;
        other.capacity = 0;
    }

    FigureArray& operator=(const FigureArray& other) {
        if (this == &other) {
            return *this;
        }

        data = std::make_shared<T[]>(other.capacity);
        size = other.size;
        capacity = other.capacity;

        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }

    FigureArray& operator=(FigureArray&& other) noexcept {
        if (this == &other) {
        return *this;
        }

        data = std::move(other.data);
        size = other.size;
        capacity = other.capacity;

        other.size = 0;
        other.capacity = 0;

        return *this;
    }

    void push_back(const T& element) {
        if (size >= capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = element;
    }

    void remove_at(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range.");
        }
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --size;
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range.");
        }
        return data[index];
    }

    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range.");
        }
        return data[index];
    }

    size_t get_size() const {
        return size;
    }

    size_t get_capacity() const {
        return capacity;
    }

    double TotalArea() const {
        double total = 0.0;
        for (size_t i = 0; i < size; ++i) {
            double area = static_cast<double>(*data[i]);
            total += area;
        }
        return total;
    }

    void PrintAll() const {
        for (size_t i = 0; i < size; ++i) {
           std::cout << *data[i] << std::endl;
        }
    }
};

}
