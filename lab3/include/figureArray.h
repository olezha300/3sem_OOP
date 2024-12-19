#ifndef ARRAY_H
#define ARRAY_H

#include "figure.h"
#include <vector>
#include <memory>
#include <iostream>

class Array {
private:
    std::vector<Figure*> figures;

public:
    void Add(Figure* f);
    void Remove(size_t index);
    double TotalArea() const;
    void PrintCenters() const;
    void PrintAreas() const;
    size_t Size() const;

    Figure& operator[](size_t index) const;

    friend std::ostream& operator<<(std::ostream& os, const Array& arr);
    friend std::istream& operator>>(std::istream& is, Array& arr);
};

#endif
