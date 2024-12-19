#pragma once

#include "figure.h"

namespace Shape {

template <typename T>
class Hexagon : public Figure<T, 6> {
public:
    Hexagon() : Figure<T, 6>() {}

    Hexagon(const std::array<Point<T>, 6>& points) {
        for (size_t i = 0; i < 6; ++i) {
            this->vertices[i] = std::make_unique<Point<T>>(points[i]);
        }
    }

    Hexagon(const std::initializer_list<Point<T>>& points) {
        if (points.size() != 6) {
            throw std::invalid_argument("A Hexagon must have exactly 6 points.");
        }

        size_t i = 0;
        for (const auto& point : points) {
            this->vertices[i] = std::make_unique<Point<T>>(point);
            ++i;
        }
    }

    Hexagon(const Hexagon& other) : Figure<T, 6>(other) {}

    Hexagon(Hexagon&& other) noexcept : Figure<T, 6>(std::move(other)) {}

    Hexagon& operator=(const Hexagon& other) {
        if (this == &other) return *this;
        Figure<T, 6>::operator=(other);
        return *this;
    }

    Hexagon& operator=(Hexagon&& other) noexcept {
        if (this == &other) return *this;
        Figure<T, 6>::operator=(std::move(other));
        return *this;
    }

    bool operator==(const Hexagon& other) const {
        return Figure<T, 6>::operator==(other);
    }

    operator double() const override {
        return Figure<T, 6>::operator double();
    }

    std::unique_ptr<Point<T>> Center() const override {
        return Figure<T, 6>::Center();
    }

    void Rotate(double angle) override {
        Figure<T, 6>::Rotate(angle);
    }

    friend std::ostream& operator<<(std::ostream& os, const Hexagon& h) {
        os << "Hexagon vertices: ";
        os << static_cast<const Figure<T, 6>&>(h);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Hexagon& h) {
        std::cout << "Enter 6 points";
        for (auto& vertex : h.vertices) {
            T x, y;
            is >> x >> y;
            vertex = std::make_unique<Point<T>>(x, y);
        }
        return is;
    }

    virtual ~Hexagon() = default;
};

}
