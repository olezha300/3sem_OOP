#include "../include/octagon.h"
#include <cmath>

constexpr double PI = 3.14159265358979323846;

Octagon::Octagon() : vertices{} {}

Octagon::Octagon(const std::array<std::pair<double, double>, NUM_VERTICES>& vertices)
    : vertices(vertices) {}

Octagon::Octagon(const Octagon& other)
    : vertices(other.vertices) {}

Octagon::Octagon(Octagon&& other) noexcept
    : vertices(std::move(other.vertices)) {}

Octagon& Octagon::operator=(const Octagon& other) {
    if (this != &other) {
        vertices = other.vertices;
    }
    return *this;
}

Octagon& Octagon::operator=(Octagon&& other) noexcept {
    if (this != &other) {
        vertices = std::move(other.vertices);
    }
    return *this;
}

Figure& Octagon::operator=(const Figure& other) {
    if (const Octagon* o = dynamic_cast<const Octagon*>(&other)) {
        *this = *o;
    }
    return *this;
}

Figure& Octagon::operator=(Figure&& other) noexcept {
    if (Octagon* o = dynamic_cast<Octagon*>(&other)) {
        *this = std::move(*o);
    }
    return *this;
}

std::pair<double, double> Octagon::Center() const {
    double centerY{0}, centerX{0};
    for (const auto& vertex : vertices) {
        centerX += vertex.first;
        centerY += vertex.second;
    }
    return {centerX / NUM_VERTICES, centerY / NUM_VERTICES};
}

Octagon::operator double() const {
    double area = 0.0;
    for (size_t i{0}; i < NUM_VERTICES; ++i) {
        const auto& [x1, y1] = vertices[i];
        const auto& [x2, y2] = vertices[(i + 1) % NUM_VERTICES];
        area += x1 * y2 - y1 * x2;
    }
    return std::abs(area) / 2.0;
}

void Octagon::Rotate(double angle) {
    double radianAngle = angle * PI / 180.0;
    double cosAngle = std::cos(radianAngle);
    double sinAngle = std::sin(radianAngle);

    auto [centerX, centerY] = Center();

    for (auto& vertex : vertices) {
        double x = vertex.first - centerX;
        double y = vertex.second - centerY;
        vertex.first = centerX + x * cosAngle - y * sinAngle;
        vertex.second = centerY + x * sinAngle + y * cosAngle;
    }
}

bool Octagon::operator==(const Figure& other) const {
    if (const Octagon* p = dynamic_cast<const Octagon*>(&other)) {
        return vertices == p->vertices;
    }
    return false;
}

void Octagon::printf(std::ostream& os) const {
    for (const auto& vertex : vertices) {
        os << "(" << vertex.first << ", " << vertex.second << ") ";
    }
}

void Octagon::readf(std::istream& is) {
    for (auto& vertex : vertices) {
        is >> vertex.first >> vertex.second;
    }
}
