#include <gtest/gtest.h>
#include "../include/lab1.hpp"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(lab1_var17(100, 10, 910) == 10);
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(lab1_var17(50, 20, 120) == 4);
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(lab1_var17(1000, 100, 4600) == 5);
}

TEST(test_04, basic_test_set)
{
    ASSERT_TRUE(lab1_var17(50, 20, 100) == 3);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
