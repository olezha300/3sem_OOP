#include "../include/pentagon.h"
#include <cmath>

constexpr double PI = 3.14159265358979323846;

Pentagon::Pentagon() : vertices{} {}

Pentagon::Pentagon(const std::array<std::pair<double, double>, NUM_VERTICES>& vertices)
    : vertices(vertices) {}

Pentagon::Pentagon(const Pentagon& other)
    : vertices(other.vertices) {}

Pentagon::Pentagon(Pentagon&& other) noexcept
    : vertices(std::move(other.vertices)) {}

Pentagon& Pentagon::operator=(const Pentagon& other) {
    if (this != &other) {
        vertices = other.vertices;
    }
    return *this;
}

Pentagon& Pentagon::operator=(Pentagon&& other) noexcept {
    if (this != &other) {
        vertices = std::move(other.vertices);
    }
    return *this;
}

Figure& Pentagon::operator=(const Figure& other) {
    if (const Pentagon* p = dynamic_cast<const Pentagon*>(&other)) {
        *this = *p;
    }
    return *this;
}

Figure& Pentagon::operator=(Figure&& other) noexcept {
    if (Pentagon* p = dynamic_cast<Pentagon*>(&other)) {
        *this = std::move(*p);
    }
    return *this;
}

std::pair<double, double> Pentagon::Center() const {
    double centerY{0}, centerX{0};
    for (const auto& vertex : vertices) {
        centerX += vertex.first;
        centerY += vertex.second;
    }
    return {centerX / NUM_VERTICES, centerY / NUM_VERTICES};
}

Pentagon::operator double() const {
    double area = 0.0;
    for (size_t i{0}; i < NUM_VERTICES; ++i) {
        const auto& [x1, y1] = vertices[i];
        const auto& [x2, y2] = vertices[(i + 1) % NUM_VERTICES];
        area += x1 * y2 - y1 * x2;
    }
    return std::abs(area) / 2.0;
}

void Pentagon::Rotate(double angle) {
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

bool Pentagon::operator==(const Figure& other) const {
    if (const Pentagon* p = dynamic_cast<const Pentagon*>(&other)) {
        return vertices == p->vertices;
    }
    return false;
}

void Pentagon::printf(std::ostream& os) const {
    for (const auto& vertex : vertices) {
        os << "(" << vertex.first << ", " << vertex.second << ") ";
    }
}

void Pentagon::readf(std::istream& is) {
    for (auto& vertex : vertices) {
        is >> vertex.first >> vertex.second;
    }
}
