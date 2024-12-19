#pragma once

#include <concepts>
#include <memory>

namespace Shape {

    template <typename T>
    concept Scalar = std::is_arithmetic_v<T>;

    template <Scalar T>
    class Point {
    public:
        T x, y;

        Point () : x(T{}), y(T{}) {}
        Point(const T& x_val, const T& y_val) : x{x_val}, y{y_val} {}
        Point(const Point<T>& other) : x{other.x}, y{other.y} {}
        Point(Point<T>&& other) noexcept : x(std::move(other.x)), y(std::move(other.y)) {}

        ~Point() = default;

        Point& operator=(const Point& other) {
            if (this != &other) {
                x = other.x;
                y = other.y;
            }
            return *this;
        }

        Point& operator=(Point&& other) noexcept {
            if (this != &other) {
                x = std::move(other.x);
                y = std::move(other.y);
            }
            return *this;
        }

        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }

        bool operator!=(const Point& other) const {
            return !(*this == other);
        }

        friend std::ostream& operator<<(std::ostream& os, const Point& point) {
            os << "(" << point.x << ", " << point.y << ")";
            return os;
        }

        friend std::istream& operator>>(std::istream& is, Point& point) {
            is >> point.x >> point.y;
            return is;
        }
    };

}
