#ifndef PENTAGON_H
#define PENTAGON_H

#include "figure.h"
#include <array>
#include <utility>

class Pentagon final : public Figure {
public:
    static constexpr int NUM_VERTICES = 5;

private:
    std::array<std::pair<double, double>, NUM_VERTICES> vertices;

public:
    Pentagon();
    explicit Pentagon(const std::array<std::pair<double, double>, NUM_VERTICES>& vertices);
    Pentagon(const Pentagon& other);
    Pentagon(Pentagon&& other) noexcept;

    Pentagon& operator=(const Pentagon& other);
    Pentagon& operator=(Pentagon&& other) noexcept;
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
