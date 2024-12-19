#ifndef HEXAGON_H
#define HEXAGON_H

#include "figure.h"
#include <array>
#include <utility>

class Hexagon final: public Figure{
public:
    static constexpr int NUM_VERTICES = 6;

private:
    std::array<std::pair<double, double>, NUM_VERTICES> vertices;

public:
    Hexagon();
    explicit Hexagon(const std::array<std::pair<double, double>, NUM_VERTICES>& vertices);
    Hexagon(const Hexagon& other);
    Hexagon(Hexagon&& other) noexcept ;

    Hexagon& operator=(const Hexagon& other);
    Hexagon& operator=(Hexagon&& other) noexcept;
    Figure& operator=(const Figure& other) override;
    Figure& operator=(Figure&& other) noexcept override;

    std::pair<double, double> Center() const override;
    operator double() const override;
    bool operator==(const Figure& other) const override;
    void Rotate(double angle);

protected:
    void printf(std::ostream& os) const override;
    void readf(std::istream& is) override;
};

#endif
