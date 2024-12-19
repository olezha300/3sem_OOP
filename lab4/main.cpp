#include "src/figureArray.h"
#include "src/pentagon.h"
#include "src/octagon.h"
#include "src/hexagon.h"

using namespace Shape;

int main() {
    try {
        FigureArray<std::shared_ptr<IFigure>> figureArray;

        std::cout << "Меню: \n";
        std::cout << "1. Добавить пятиугольник\n";
        std::cout << "2. Добавить шестиугольник\n";
        std::cout << "3. Добавить восьмиугольник\n";
        std::cout << "4. Удалить фигуру по индексу\n";
        std::cout << "5. Вывести все фигуры\n";
        std::cout << "6. Вычислить суммарную площадь\n";
        std::cout << "7. Выход\n";

        int choice;
        while (true) {
            std::cout << "Введите номер действия: ";
            std::cin >> choice;

            switch (choice) {
                case 1: {
                    std::cout << "Введите координаты 5 вершин пятиугольника (x y):\n";
                    std::array<Point<double>, 5> points;
                    for (auto& point : points) {
                        std::cin >> point.x >> point.y;
                    }
                    figureArray.push_back(std::make_shared<Pentagon<double>>(points));
                    break;
                }
                case 2: {
                    std::cout << "Введите координаты 6 вершин шестиугольника (x y):\n";
                    std::array<Point<double>, 6> points;
                    for (auto& point : points) {
                        std::cin >> point.x >> point.y;
                    }
                    figureArray.push_back(std::make_shared<Hexagon<double>>(points));
                    break;
                }
                case 3: {
                    std::cout << "Введите координаты 8 вершин восьмиугольника (x y):\n";
                    std::array<Point<double>, 8> points;
                    for (auto& point : points) {
                        std::cin >> point.x >> point.y;
                    }
                    figureArray.push_back(std::make_shared<Octagon<double>>(points));
                    break;
                }
                case 4: {
                    size_t index;
                    std::cout << "Введите индекс фигуры для удаления: ";
                    std::cin >> index;
                    figureArray.remove_at(index);
                    std::cout << "Фигура удалена.\n";
                    break;
                }
                case 5: {
                    std::cout << "Список всех фигур:\n";
                    figureArray.PrintAll();
                    break;
                }
                case 6: {
                    std::cout << "Суммарная площадь всех фигур: " << figureArray.TotalArea() << "\n";
                    break;
                }
                case 7:
                    std::cout << "Выход.\n";
            }
        }
    } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    }
}

