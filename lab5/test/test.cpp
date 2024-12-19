#include "CustomStack.hpp"
#include <gtest/gtest.h>
#include <memory_resource>

TEST(CustomStackTest, CreateAndDestroy) {
    CustomStack<int> stack;
    EXPECT_EQ(stack.get_size(), 0);
    EXPECT_EQ(stack.get_capacity(), 0);
}

TEST(CustomStackTest, PushBack) {
    CustomStack<int> stack;
    stack.push_back(1);
    stack.push_back(2);
    stack.push_back(3);

    EXPECT_EQ(stack.get_size(), 3);
    EXPECT_EQ(stack.top(), 3);
}

TEST(CustomStackTest, PopBack) {
    CustomStack<int> stack;
    stack.push_back(1);
    stack.push_back(2);
    stack.push_back(3);

    stack.pop_back();
    EXPECT_EQ(stack.get_size(), 2);
    EXPECT_EQ(stack.top(), 2);

    stack.pop_back();
    EXPECT_EQ(stack.get_size(), 1);
    EXPECT_EQ(stack.top(), 1);

    stack.pop_back();
    EXPECT_EQ(stack.get_size(), 0);
}

TEST(CustomStackTest, Clear) {
    CustomStack<int> stack;
    stack.push_back(1);
    stack.push_back(2);
    stack.push_back(3);

    stack.clear();
    EXPECT_EQ(stack.get_size(), 0);
}

TEST(CustomStackTest, Iterator) {
    CustomStack<int> stack;
    stack.push_back(1);
    stack.push_back(2);
    stack.push_back(3);

    auto it = stack.begin();
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(it.get_pointer(), stack.begin().get_pointer());

    ++it;
    EXPECT_EQ(*it, 2);

    it++;
    EXPECT_EQ(*it, 3);

}

TEST(CustomStackTest, Resize) {
    CustomStack<int> stack;
    for (int i = 0; i < 10; ++i) {
        stack.push_back(i);
    }

    EXPECT_EQ(stack.get_size(), 10);
    EXPECT_GE(stack.get_capacity(), 10);
}

TEST(CustomStackTest, CustomMemoryResource) {
    std::pmr::monotonic_buffer_resource mr;
    CustomStack<int> stack(&mr);

    for (int i = 0; i < 10; ++i) {
        stack.push_back(i);
    }

    EXPECT_EQ(stack.get_size(), 10);
    EXPECT_GE(stack.get_capacity(), 10);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
