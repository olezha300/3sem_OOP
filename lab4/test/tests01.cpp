#include <gtest/gtest.h>
#include "../src/pentagon.h"
#include "../src/hexagon.h"
#include "../src/octagon.h"
#include "../src/figureArray.h"
#include <cmath>

using namespace Shape;

TEST(PentagonTests, RotationAndCenter) {
    auto pentagon = Pentagon<double>({
        Point<double>{0, 0},
        Point<double>{2, 0},
        Point<double>{3, 1},
        Point<double>{2, 3},
        Point<double>{0, 2}
    });

    pentagon.Rotate(45.0); // Rotate the pentagon
    auto center = pentagon.Center();
    EXPECT_NEAR(center->x, 1.4, 1e-6);
    EXPECT_NEAR(center->y, 1.2, 1e-6);
    EXPECT_NEAR(static_cast<double>(pentagon), 6.5, 1e-4); // Approximate area after rotation
}

TEST(HexagonTests, VerifyAreaAndCenter) {
    auto hexagon = Hexagon<double>({
        Point<double>{0, 0},
        Point<double>{2, 0},
        Point<double>{3, 1},
        Point<double>{2, 3},
        Point<double>{0, 3},
        Point<double>{-1, 1}
    });

    auto center = hexagon.Center();
    EXPECT_NEAR(center->x, 1.0, 1e-6);
    EXPECT_NEAR(center->y, 1.3333, 1e-2);
    EXPECT_NEAR(static_cast<double>(hexagon), 9.0, 1e-6);
}

TEST(OctagonAreaTests, AreaAndCenter) {
    auto octagon = Octagon<double>({
        Point<double>{0, 0},
        Point<double>{2, 0},
        Point<double>{3, 1},
        Point<double>{4, 3},
        Point<double>{3, 5},
        Point<double>{1, 5},
        Point<double>{0, 3},
        Point<double>{-1, 1}
    });

    auto center = octagon.Center();
    EXPECT_NEAR(center->x, 1.5, 1e-6);
    EXPECT_NEAR(center->y, 2.25, 1e-6);
    EXPECT_NEAR(static_cast<double>(octagon), 17.0, 1e-6);
}

TEST(FigureArrayTests, CheckAllElementsInitialized) {
    auto pentagon = std::make_shared<Pentagon<double>>(
        Pentagon<double>({
            Point<double>{0, 0},
            Point<double>{2, 0},
            Point<double>{3, 1},
            Point<double>{2, 3},
            Point<double>{0, 2}
        })
    );
    auto hexagon = std::make_shared<Hexagon<double>>(
        Hexagon<double>({
            Point<double>{0, 0},
            Point<double>{2, 0},
            Point<double>{3, 1},
            Point<double>{2, 3},
            Point<double>{0, 3},
            Point<double>{-1, 1}
        })
    );
    auto octagon = std::make_shared<Octagon<double>>(
        Octagon<double>({
            Point<double>{0, 0},
            Point<double>{2, 0},
            Point<double>{3, 1},
            Point<double>{4, 3},
            Point<double>{3, 5},
            Point<double>{1, 5},
            Point<double>{0, 3},
            Point<double>{-1, 1}
        })
    );

    FigureArray<std::shared_ptr<IFigure>> shapes;
    shapes.push_back(pentagon);
    shapes.push_back(hexagon);
    shapes.push_back(octagon);

    for (size_t i = 0; i < shapes.get_size(); ++i) {
        EXPECT_NO_THROW(static_cast<double>(*shapes[i]));
    }
}

TEST(FigureArrayTests, SumOfAreas) {
    auto pentagon = std::make_shared<Pentagon<double>>(
        Pentagon<double>({
            Point<double>{0, 0},
            Point<double>{2, 0},
            Point<double>{3, 1},
            Point<double>{2, 3},
            Point<double>{0, 2}
        })
    );
    auto hexagon = std::make_shared<Hexagon<double>>(
        Hexagon<double>({
            Point<double>{0, 0},
            Point<double>{2, 0},
            Point<double>{3, 1},
            Point<double>{2, 3},
            Point<double>{0, 3},
            Point<double>{-1, 1}
        })
    );
    auto octagon = std::make_shared<Octagon<double>>(
        Octagon<double>({
            Point<double>{0, 0},
            Point<double>{2, 0},
            Point<double>{3, 1},
            Point<double>{4, 3},
            Point<double>{3, 5},
            Point<double>{1, 5},
            Point<double>{0, 3},
            Point<double>{-1, 1}
        })
    );

    FigureArray<std::shared_ptr<IFigure>> shapes;
    shapes.push_back(pentagon);
    shapes.push_back(hexagon);
    shapes.push_back(octagon);

    EXPECT_EQ(shapes.get_size(), 3);
    EXPECT_NEAR(shapes.TotalArea(), 6.5 + 9.0 + 17.0, 1e-2);
}

TEST(FigureArrayTests, AccessByIndex) {
    auto pentagon = std::make_shared<Pentagon<double>>(
        Pentagon<double>({
            Point<double>{0, 0},
            Point<double>{2, 0},
            Point<double>{3, 1},
            Point<double>{2, 3},
            Point<double>{0, 2}
        })
    );
    auto hexagon = std::make_shared<Hexagon<double>>(
        Hexagon<double>({
            Point<double>{0, 0},
            Point<double>{2, 0},
            Point<double>{3, 1},
            Point<double>{2, 3},
            Point<double>{0, 3},
            Point<double>{-1, 1}
        })
    );
    auto octagon = std::make_shared<Octagon<double>>(
        Octagon<double>({
            Point<double>{0, 0},
            Point<double>{2, 0},
            Point<double>{3, 1},
            Point<double>{4, 3},
            Point<double>{3, 5},
            Point<double>{1, 5},
            Point<double>{0, 3},
            Point<double>{-1, 1}
        })
    );

    FigureArray<std::shared_ptr<IFigure>> figures;
    figures.push_back(pentagon);
    figures.push_back(hexagon);
    figures.push_back(octagon);

    EXPECT_EQ(figures.get_size(), 3);

    EXPECT_EQ(static_cast<double>(*figures[1]), 9.0);
    EXPECT_EQ(static_cast<double>(*figures[2]), 17.0);
}

TEST(FigureArrayTests, RemoveShape) {
    auto pentagon = std::make_shared<Pentagon<double>>(
        Pentagon<double>({
            Point<double>{0, 0},
            Point<double>{2, 0},
            Point<double>{3, 1},
            Point<double>{2, 3},
            Point<double>{0, 2}
        })
    );
    auto hexagon = std::make_shared<Hexagon<double>>(
        Hexagon<double>({
            Point<double>{0, 0},
            Point<double>{2, 0},
            Point<double>{3, 1},
            Point<double>{2, 3},
            Point<double>{0, 3},
            Point<double>{-1, 1}
        })
    );

    FigureArray<std::shared_ptr<IFigure>> figures;
    figures.push_back(pentagon);
    figures.push_back(hexagon);

    EXPECT_EQ(figures.get_size(), 2);
    figures.remove_at(0);
    EXPECT_EQ(figures.get_size(), 1);
    EXPECT_NEAR(static_cast<double>(*figures[0]), 9.0, 1e-6);
}

TEST(FigureArrayTests, InvalidAccess) {
    FigureArray<std::shared_ptr<IFigure>> figures;
    EXPECT_THROW(figures[0], std::out_of_range);
    EXPECT_THROW(figures.remove_at(0), std::out_of_range);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
