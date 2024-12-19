#pragma once

#include <iostream>
#include <memory>
#include "point.h"
#include "ifigure.h"
#include <cmath>
#include <array>
#include <stdexcept>
#include <initializer_list>

namespace Shape {

template <typename T, size_t NUM_VERTICES>
class Figure : public IFigure {
protected:
    std::array<std::unique_ptr<Point<T>>, NUM_VERTICES> vertices;
public:
    Figure() {
        for (size_t i = 0; i < NUM_VERTICES; ++i) {
            vertices[i] = std::make_unique<Point<T>>();
        }
    }

    Figure(const std::initializer_list<Point<T>>& points) {
        if (points.size() != NUM_VERTICES) {
            throw std::invalid_argument("The number of points must be equal to the number of vertices.");
        }

        size_t i = 0;
        for (const auto& point : points) {
            vertices[i] = std::make_unique<Point<T>>(point);
            ++i;
        }
    }

    virtual ~Figure() = default;

    Figure(Figure<T, NUM_VERTICES>&& other) noexcept : vertices(std::move(other.vertices)) {}
    Figure(const Figure<T, NUM_VERTICES>& other) {
        for (size_t i = 0; i < NUM_VERTICES; ++i) {
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        }
    }

    virtual Figure& operator=(const Figure<T, NUM_VERTICES>& other) {
        if (this == &other) {
            return *this;
        }
        for (size_t i = 0; i < NUM_VERTICES; ++i) {
            if (other.vertices[i]) {
                vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
            } else {
                vertices[i].reset();
            }
        }
        return *this;
    }

    virtual Figure& operator=(Figure<T, NUM_VERTICES>&& other) noexcept {
        if (this == &other) return *this;
        vertices = std::move(other.vertices);
        return *this;
    }

    virtual bool operator==(const Figure<T, NUM_VERTICES>& other) const {
        if (this == &other) return true;
        for (size_t i = 0; i < NUM_VERTICES; ++i) {
            if (!(*vertices[i] == *other.vertices[i])) {
                return false;
            }
        }
        return true;
    }

    virtual explicit operator double() const override {
        double area = 0.0;
        for (size_t i = 0; i < NUM_VERTICES; ++i) {
            size_t j = (i + 1) % NUM_VERTICES;
            area += static_cast<double>(vertices[i]->x) * static_cast<double>(vertices[j]->y) -
                    static_cast<double>(vertices[j]->x) * static_cast<double>(vertices[i]->y);
        }
        return 0.5 * std::abs(area);
    }



    virtual std::unique_ptr<Point<T>> Center() const {
        double centerX{0}, centerY{0};
        for (const auto& vertex : vertices) {
            centerX += vertex->x;
            centerY += vertex->y;
        }
        return std::make_unique<Point<T>>(centerX / NUM_VERTICES, centerY / NUM_VERTICES);
    }

    virtual void Rotate(double angle) override {
        double rad = angle * M_PI / 180.0;
        T cosAngle = static_cast<T>(std::cos(rad));
        T sinAngle = static_cast<T>(std::sin(rad));
        Point<T> c = *Center();
        for (auto& vertex : vertices) {
            T xNew = c.x + (vertex->x - c.x) * cosAngle - (vertex->y - c.y) * sinAngle;
            T yNew = c.y + (vertex->x - c.x) * sinAngle + (vertex->y - c.y) * cosAngle;
            vertex->x = xNew;
            vertex->y = yNew;
        }
    }

    void print(std::ostream& os) const override {
        os << "Figure with " << NUM_VERTICES << " vertices:\n";
        for (const auto& vertex : vertices) {
            os << *vertex << " ";
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Figure<T, NUM_VERTICES>& f) {
        os << "Vertices";
        for (const auto& vertex : f.vertices) {
            os << "(" << vertex->x << "," << vertex->y << ")";
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Figure<T, NUM_VERTICES>& f) {
        for (auto& vertex : f.vertices) {
            T x, y;
            is >> x >> y;
            vertex = std::make_unique<Point<T>>(x, y);
        }
        return is;
    }
};

}
