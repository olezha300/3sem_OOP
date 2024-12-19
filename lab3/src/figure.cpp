#include "../include/figure.h"

std::ostream& operator<<(std::ostream& os, const Figure& fig) {
    fig.printf(os);
    return os;
}

std::istream& operator>>(std::istream& is, Figure& fig) {
    fig.readf(is);
    return is;
}
