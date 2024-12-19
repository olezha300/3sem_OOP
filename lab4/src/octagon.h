#pragma once

#include "figure.h"

namespace Shape {

template <typename T>
class Octagon : public Figure<T, 8> {
public:
    Octagon() : Figure<T, 8>() {}

    Octagon(const std::array<Point<T>, 8>& points) {
        for (size_t i = 0; i < 8; ++i) {
            this->vertices[i] = std::make_unique<Point<T>>(points[i]);
        }
    }

    Octagon(const std::initializer_list<Point<T>>& points) {
        if (points.size() != 8) {
            throw std::invalid_argument("A Octagon must have exactly 8 points.");
        }

        size_t i = 0;
        for (const auto& point : points) {
            this->vertices[i] = std::make_unique<Point<T>>(point);
            ++i;
        }
    }

    Octagon(const Octagon& other) : Figure<T, 8>(other) {}

    Octagon(Octagon&& other) noexcept : Figure<T, 8>(std::move(other)) {}

    Octagon& operator=(const Octagon& other) {
        if (this == &other) return *this;
        Figure<T, 8>::operator=(other);
        return *this;
    }

    Octagon& operator=(Octagon&& other) noexcept {
        if (this == &other) return *this;
        Figure<T, 8>::operator=(std::move(other));
        return *this;
    }

    bool operator==(const Octagon& other) const {
        return Figure<T, 8>::operator==(other);
    }

    operator double() const override {
        return Figure<T, 8>::operator double();
    }

    std::unique_ptr<Point<T>> Center() const override {
        return Figure<T, 8>::Center();
    }

    void Rotate(double angle) override {
        Figure<T, 8>::Rotate(angle);
    }

    friend std::ostream& operator<<(std::ostream& os, const Octagon& o) {
        os << "Octagon vertices: ";
        os << static_cast<const Figure<T, 8>&>(o);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Octagon& o) {
        std::cout << "Enter 8 points";
        for (auto& vertex : o.vertices) {
            T x, y;
            is >> x >> y;
            vertex = std::make_unique<Point<T>>(x, y);
        }
        return is;
    }

    virtual ~Octagon() = default;
};

}
