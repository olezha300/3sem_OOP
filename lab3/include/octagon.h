#ifndef OCTAGON_H
#define OCTAGON_H

#include "figure.h"
#include <array>
#include <utility>

class Octagon final: public Figure{
public:
    static constexpr int NUM_VERTICES = 8;

private:
    std::array<std::pair<double, double>, NUM_VERTICES> vertices;

public:
    Octagon();
    explicit Octagon(const std::array<std::pair<double, double>, NUM_VERTICES>& vertices);
    Octagon(const Octagon& other);
    Octagon(Octagon&& other) noexcept;

    Octagon& operator=(const Octagon& other);
    Octagon& operator=(Octagon&& other) noexcept;
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
