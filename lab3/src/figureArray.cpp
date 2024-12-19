#include "../include/figureArray.h"

void Array::Add(Figure* f) {
    figures.push_back(std::move(f));
}

void Array::Remove(size_t index) {
    if (index < figures.size()) {
        figures.erase(figures.begin() + index);
    } else {
        std::cerr << "Индекс вне диапазона\n";
    }
}

double Array::TotalArea() const {
    double total = 0;
    for (const auto& f: figures) {
        total += static_cast<double>(*f);
    }
    return total;
}

void Array::PrintCenters() const {
    for (const auto& f : figures) {
        auto [x, y] = f->Center();
        std::cout << "Центр: (" << x << ", " << y << ")\n";
    }
}

void Array::PrintAreas() const {
    for (const auto& f : figures) {
        std::cout << "Площадь: " << static_cast<double>(*f) << "\n";
    }
}

size_t Array::Size() const {
    return figures.size();
}

Figure& Array::operator[](size_t index) const {
    if (index < figures.size()) {
        return *figures[index];
    }
    throw std::out_of_range("Индекс вне диапазона");
}

std::ostream& operator<<(std::ostream& os, const Array& arr) {
    for (const auto& f : arr.figures) {
        os << *f << "\n";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Array& arr) {
    while (is) {
        Figure* f;
        is >> *f;
        if (is) arr.Add(std::move(f));
    }
    return is;
}
