#pragma once

#include <iostream>
#include <memory>

namespace Shape {
    class IFigure {
    public:
        virtual ~IFigure() = default;

        virtual explicit operator double() const = 0;
        virtual void Rotate(double angle) = 0;

        virtual void print(std::ostream& os) const = 0;
    };

    inline std::ostream& operator<<(std::ostream& os, const IFigure& f) {
        f.print(os);
        return os;
    };

}

