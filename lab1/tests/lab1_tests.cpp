#include <gtest/gtest.h>
#include "../include/lab1.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(lab1_var17(100, 10, 910) == 10);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
