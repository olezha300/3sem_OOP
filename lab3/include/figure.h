#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <utility>
#include <array>

class Figure {
public:
    virtual ~Figure() noexcept = default;

    virtual std::pair<double, double> Center() const = 0;
    virtual operator double() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Figure& fig);
    friend std::istream& operator>>(std::istream& is, Figure& fig);

    virtual Figure& operator=(const Figure& other) = 0;
    virtual Figure& operator=(Figure&& other) noexcept = 0;

    virtual bool operator==(const Figure& other) const = 0;

protected:
    virtual void printf(std::ostream& os) const = 0;
    virtual void readf(std::istream& is) = 0;
};

#endif
