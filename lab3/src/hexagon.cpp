#include "../include/hexagon.h"
#include <cmath>

constexpr double PI = 3.14159265358979323846;

Hexagon::Hexagon() : vertices{} {}

Hexagon::Hexagon(const std::array<std::pair<double, double>, NUM_VERTICES>& vertices)
    : vertices(vertices) {}

Hexagon::Hexagon(const Hexagon& other)
    : vertices(other.vertices) {}

Hexagon::Hexagon(Hexagon&& other) noexcept
    : vertices(std::move(other.vertices)) {}

Hexagon& Hexagon::operator=(const Hexagon& other) {
    if (this != &other) {
        vertices = other.vertices;
    }
    return *this;
}

Hexagon& Hexagon::operator=(Hexagon&& other) noexcept{
    if (this != &other) {
        vertices = std::move(other.vertices);
    }
    return *this;
}

Figure& Hexagon::operator=(const Figure& other) {
    if (const Hexagon* h = dynamic_cast<const Hexagon*>(&other)) {
        *this = *h;
    }
    return *this;
}

Figure& Hexagon::operator=(Figure&& other) noexcept {
    if (Hexagon* h = dynamic_cast<Hexagon*>(&other)) {
        *this = std::move(*h);
    }
    return *this;
}

std::pair<double, double>  Hexagon::Center() const {
    double centerX{0}, centerY{0};
    for (const auto& vertex : vertices){
        centerX += vertex.first;
        centerY += vertex.second;
    }
    return {centerX / NUM_VERTICES, centerY / NUM_VERTICES};
}

Hexagon::operator double() const {
    double area{0.0};
    for (size_t i{0}; i < NUM_VERTICES; ++i){
        const auto& [x1, y1] = vertices[i];
        const auto& [x2, y2] = vertices[(i + 1) % NUM_VERTICES];
        area += x1 * y2 - y1 * x2;
    }
    return std::abs(area) / 2.0;
}

void Hexagon::Rotate(double angle) {
    double radianAngle = angle * PI / 180.0;
    double cosAngle = std::cos(radianAngle);
    double sinAngle = std::sin(radianAngle);

    auto [centerX, centerY] = Center();

    for(auto& vertex : vertices) {
        double x = vertex.first - centerX;
        double y  = vertex.second - centerY;
        vertex.first = centerX + x * cosAngle - y * sinAngle;
        vertex.second = centerY + x *sinAngle + y * cosAngle;
    }
}

bool Hexagon::operator==(const Figure& other) const {
    if (const Hexagon *h = dynamic_cast<const Hexagon*>(&other)) {
        return vertices == h->vertices;
    }
    return false;
}

void Hexagon::printf(std::ostream& os) const {
    for(const auto& vertex : vertices){
        os << "(" << vertex.first << ", " << vertex.second << ") ";
    }
}

void Hexagon::readf(std::istream& is) {
    for(auto& vertex : vertices){
        is >> vertex.first >> vertex.second;
    }
}
