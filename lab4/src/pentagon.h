#pragma once

#include "figure.h"

namespace Shape {

template <typename T>
class Pentagon : public Figure<T, 5> {
public:
    Pentagon() : Figure<T, 5>() {}

    Pentagon(const std::array<Point<T>, 5>& points) {
        for (size_t i = 0; i < 5; ++i) {
            this->vertices[i] = std::make_unique<Point<T>>(points[i]);
        }
    }

    Pentagon(const std::initializer_list<Point<T>>& points) {
        if (points.size() != 5) {
            throw std::invalid_argument("A Pentagon must have exactly 5 points.");
        }

        size_t i = 0;
        for (const auto& point : points) {
            this->vertices[i] = std::make_unique<Point<T>>(point);
            ++i;
        }
    }

    Pentagon(const Pentagon& other) : Figure<T, 5>(other) {}

    Pentagon(Pentagon&& other) noexcept : Figure<T, 5>(std::move(other)) {}

    Pentagon& operator=(const Pentagon& other) {
        if (this == &other) return *this;
        Figure<T, 5>::operator=(other);
        return *this;
    }

    Pentagon& operator=(Pentagon&& other) noexcept {
        if (this == &other) return *this;
        Figure<T, 5>::operator=(std::move(other));
        return *this;
    }

    bool operator==(const Pentagon& other) const {
        return Figure<T, 5>::operator==(other);
    }

    operator double() const override {
        return Figure<T, 5>::operator double();
    }

    std::unique_ptr<Point<T>> Center() const override {
        return Figure<T, 5>::Center();
    }

    void Rotate(double angle) override {
        Figure<T, 5>::Rotate(angle);
    }

    friend std::ostream& operator<<(std::ostream& os, const Pentagon& p) {
        os << "Pentagon vertices: ";
        os << static_cast<const Figure<T, 5>&>(p);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Pentagon& p) {
        std::cout << "Enter 5 points: ";
        for (auto& vertex : p.vertices) {
            T x, y;
            is >> x >> y;
            vertex = std::make_unique<Point<T>>(x, y);
        }
        return is;
    }

    virtual ~Pentagon() = default;
};

}
