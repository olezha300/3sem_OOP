#include "include/pentagon.h"
#include "include/hexagon.h"
#include "include/octagon.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<Figure*> figures;

    Pentagon* pentagon = new Pentagon();
    std::cout << "Введите координаты 5 вершин 5-угольника по часовой:" << std::endl;
    std::cin >> *pentagon;
    figures.push_back(pentagon);
    std::cout << "Добавлена фигура (5-угольник):" << std::endl << *pentagon << std::endl
              << "Area: " << double(*pentagon) << std::endl;


    Hexagon* hexagon = new Hexagon();
    std::cout << "Введите координаты 6 вершин 6-угольника по часовой:" << std::endl;
    std::cin >> *hexagon;
    figures.push_back(hexagon);
    std::cout << "Добавлена фигура (6-угольник):" << std::endl << *hexagon << std::endl
              << "Area: " << double(*hexagon) << std::endl;

    Octagon* octagon = new Octagon();
    std::cout << "Введите координаты 8 вершин 8-угольника по часовой:" << std::endl;
    std::cin >> *octagon;
    figures.push_back(octagon);
    std::cout << "Добавлена фигура (8-угольник):" << std::endl << *octagon << std::endl
              << "Area: " << double(*octagon) << std::endl;


    std::cout << "Все фигуры:" << std::endl;
    for (const auto& figure : figures) {
        std::cout << *figure << std::endl;
    }

    double totalArea = 0;
    for (const auto& figure : figures) {
        totalArea += double(*figure);
    }
    std::cout << "Общая площадь всех фигур: " << totalArea << std::endl;

    size_t index;
    std::cout << "Введите индекс объекта для удаления (0 для 5-угольника, 1 для 6-угольника, 2 для 8-угольника):" << std::endl;
    std::cin >> index;

    if (index < figures.size()) {
        delete figures[index];
        figures.erase(figures.begin() + index);
        std::cout << "Удалена фигура по индексу: " << index << std::endl;
    } else {
        std::cout << "Индекс вне диапазона!" << std::endl;
    }

    std::cout << "Оставшиеся фигуры:" << std::endl;
    for (const auto& figure : figures) {
        std::cout << *figure << std::endl;
    }

    for (auto& figure : figures) {
        delete figure;
    }

    return 0;
}
