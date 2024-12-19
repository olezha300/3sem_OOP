#include <gtest/gtest.h>
#include "../include/pentagon.h"
#include "../include/hexagon.h"
#include "../include/octagon.h"
#include "../include/figureArray.h"

TEST(PentagonTest, Area) {
    std::array<std::pair<double, double>, 5> vertices = {{
        {2.0, 1.0},
        {1.618, 2.902},
        {-0.618, 2.618},
        {-1.618, 0.618},
        {1.0, -1.0}
    }};
    Pentagon pentagon(vertices);
    EXPECT_NEAR(double(pentagon), 9.0346, 1e-3);
}

TEST(PentagonTest, Center) {
    std::array<std::pair<double, double>, 5> vertices = {{
        {1, 0}, {0.309, 0.951}, {-0.809, 0.588},
        {-0.809, -0.588}, {0.309, -0.951}
    }};
    Pentagon pentagon(vertices);
    auto center = pentagon.Center();
    EXPECT_NEAR(center.first, 0.0, 1e-3);
}

TEST(PentagonTest, AssignAndCompare) {
    std::array<std::pair<double, double>, 5> vertices = {{
        {1, 0}, {0.309, 0.951}, {-0.809, 0.588},
        {-0.809, -0.588}, {0.309, -0.951}
    }};
    Figure* p1 = new Pentagon(vertices);
    Figure* p2 = new Pentagon();
    *p2 = *p1;
    EXPECT_TRUE(*p1 == *p2);
    delete p1;
    delete p2;
}

TEST(HexagonTest, Area) {
    std::array<std::pair<double, double>, 6> vertices = {{
        {1, 0}, {0.5, 0.866}, {-0.5, 0.866},
        {-1, 0}, {-0.5, -0.866}, {0.5, -0.866}
    }};
    Hexagon hexagon(vertices);
    EXPECT_NEAR(double(hexagon), 2.598, 1e-3);
}

TEST(HexagonTest, Center) {
    std::array<std::pair<double, double>, 6> vertices = {{
        {1, 0}, {0.5, 0.866}, {-0.5, 0.866},
        {-1, 0}, {-0.5, -0.866}, {0.5, -0.866}
    }};
    Hexagon hexagon(vertices);
    auto center = hexagon.Center();
    EXPECT_NEAR(center.first, 0.0, 1e-3);
    EXPECT_NEAR(center.second, 0.0, 1e-3);
}

TEST(HexagonTest, AssignCompare) {
    std::array<std::pair<double, double>, 6> vertices = {{
        {1, 0}, {0.5, 0.866}, {-0.5, 0.866},
        {-1, 0}, {-0.5, -0.866}, {0.5, -0.866}
    }};
    Figure* h1 = new Hexagon(vertices);
    Figure* h2 = new Hexagon();
    *h2 = *h1;
    EXPECT_TRUE(*h1 == *h2);
    delete h1;
    delete h2;
}

TEST(OctagonTest, Area) {
    std::array<std::pair<double, double>, 8> vertices = {{
        {1, 0}, {0.707, 0.707}, {0, 1},
        {-0.707, 0.707}, {-1, 0}, {-0.707, -0.707},
        {0, -1}, {0.707, -0.707}
    }};
    Octagon octagon(vertices);
    EXPECT_NEAR(double(octagon), 2.828, 1e-3);
}

TEST(OctagonTest, Center) {
    std::array<std::pair<double, double>, 8> vertices = {{
        {1, 0}, {0.707, 0.707}, {0, 1},
        {-0.707, 0.707}, {-1, 0}, {-0.707, -0.707},
        {0, -1}, {0.707, -0.707}
    }};
    Octagon octagon(vertices);
    auto center = octagon.Center();
    EXPECT_NEAR(center.first, 0.0, 1e-3);
    EXPECT_NEAR(center.second, 0.0, 1e-3);
}

TEST(OctagonTest, AssignCompare) {
    std::array<std::pair<double, double>, 8> vertices = {{
        {1, 0}, {0.707, 0.707}, {0, 1},
        {-0.707, 0.707}, {-1, 0}, {-0.707, -0.707},
        {0, -1}, {0.707, -0.707}
    }};
    Figure* o1 = new Octagon(vertices);
    Figure* o2 = new Octagon();
    *o2 = *o1;
    EXPECT_TRUE(*o1 == *o2);
    delete o1;
    delete o2;
}

TEST(FigureArrayTest, AddAndTotalArea) {
    Array array;

    std::array<std::pair<double, double>, 5> vertices1 = {{
        {2.0, 1.0},
        {1.618, 2.902},
        {-0.618, 2.618},
        {-1.618, 0.618},
        {1.0, -1.0}
    }};
    Figure* pentagon1 = new Pentagon(vertices1);

    std::array<std::pair<double, double>, 6> vertices2 = {{
        {1, 0}, {0.5, 0.866}, {-0.5, 0.866},
        {-1, 0}, {-0.5, -0.866}, {0.5, -0.866}
    }};
    Figure* hexagon = new Hexagon(vertices2);

    std::array<std::pair<double, double>, 8> vertices3 = {{
        {1, 0}, {0.707, 0.707}, {0, 1},
        {-0.707, 0.707}, {-1, 0}, {-0.707, -0.707},
        {0, -1}, {0.707, -0.707}
    }};
    Figure* octagon = new Octagon(vertices3);

    array.Add(std::move(pentagon1));
    array.Add(std::move(hexagon));
    array.Add(std::move(octagon));

    EXPECT_NEAR(array.TotalArea(), 9.0346 + 2.598 + 2.828, 1e-3);
}

TEST(FigureArrayTest, RemoveAndRemainingArea) {
    Array array;

    std::array<std::pair<double, double>, 5> vertices1 = {{
        {1, 0}, {0.309, 0.951}, {-0.809, 0.588},
        {-0.809, -0.588}, {0.309, -0.951}
    }};
    Figure* pentagon1 = new Pentagon(vertices1);

    std::array<std::pair<double, double>, 6> vertices2 = {{
        {1, 0}, {0.5, 0.866}, {-0.5, 0.866},
        {-1, 0}, {-0.5, -0.866}, {0.5, -0.866}
    }};
    Figure* hexagon = new Hexagon(vertices2);

    std::array<std::pair<double, double>, 8> vertices3 = {{
        {1, 0}, {0.707, 0.707}, {0, 1},
        {-0.707, 0.707}, {-1, 0}, {-0.707, -0.707},
        {0, -1}, {0.707, -0.707}
    }};
    Figure* octagon = new Octagon(vertices3);

    array.Add(std::move(pentagon1));
    array.Add(std::move(hexagon));
    array.Add(std::move(octagon));

    array.Remove(0);

    EXPECT_NEAR(array.TotalArea(), 2.598 + 2.828, 1e-3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
