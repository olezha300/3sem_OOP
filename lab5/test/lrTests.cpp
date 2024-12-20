#include <gtest/gtest.h>
#include <StackMemoryResource.h>
#include <Stack.h>


struct Pair {
    int x;
    int y;
};


TEST(Constructor, Test)
{
    StackMemoryResource mr1;
    StackMemoryResource mr2;

    auto stack1 = Stack<int>(&mr1);
    auto stack2 = Stack<Pair>(&mr2);

    EXPECT_EQ(stack1.size(), 0);
    EXPECT_EQ(stack2.size(), 0);
}

TEST(IntType, PushPopTest)
{
    StackMemoryResource mr1;

    auto stack1 = Stack<int>(&mr1);

    EXPECT_THROW(stack1.pop(), std::runtime_error);
    int elementInt = 10;
    stack1.push(elementInt);
    EXPECT_EQ(stack1.size(), 1);
    auto returnedElementInt = stack1.pop();
    EXPECT_EQ(*returnedElementInt, elementInt);
    EXPECT_EQ(stack1.size(), 0);
}

TEST(IntType, TopTest)
{
    StackMemoryResource mr1;

    auto stack1 = Stack<int>(&mr1);

    EXPECT_THROW(stack1.top(), std::runtime_error);
    int elementInt = 10;
    stack1.push(elementInt);
    EXPECT_EQ(stack1.size(), 1);
    auto returnedElementInt = stack1.top();
    EXPECT_EQ(*returnedElementInt, elementInt);
    EXPECT_EQ(stack1.size(), 1);
}

TEST(IntType, EmptySizeClearTest)
{
    StackMemoryResource mr1;

    auto stack1 = Stack<int>(&mr1);

    EXPECT_EQ(stack1.size(), 0);
    EXPECT_TRUE(stack1.empty());
    for (int i; i < 10; ++i)
        stack1.push(i);
    EXPECT_EQ(stack1.size(), 10);
    EXPECT_FALSE(stack1.empty());

    stack1.clear();
    EXPECT_EQ(stack1.size(), 0);
}

TEST(IntType, EqTest)
{
    StackMemoryResource mr1;
    StackMemoryResource mr2;
    auto stack1 = Stack<int>(&mr1);
    auto stack2 = Stack<int>(&mr2);

    for (int i = 0; i < 10; ++i)
        stack1.push(i);

    for (int i = 0; i < 10; ++i)
        stack2.push(i);

    EXPECT_TRUE(stack1 == stack2);

    stack2.pop();

    EXPECT_TRUE(stack1 != stack2);
}

TEST(PairType, PushPopTest)
{
    StackMemoryResource mr2;

    auto stack2 = Stack<Pair>(&mr2);

    EXPECT_THROW(stack2.pop(), std::runtime_error);
    auto elementPair = Pair{1, 2};
    stack2.push(elementPair);
    EXPECT_EQ(stack2.size(), 1);
    auto returnedElementPair = stack2.pop();
    EXPECT_EQ(returnedElementPair->x, elementPair.x);
    EXPECT_EQ(returnedElementPair->y, elementPair.y);
    EXPECT_EQ(stack2.size(), 0);
}

TEST(PairType, TopTest)
{
    StackMemoryResource mr2;

    auto stack2 = Stack<Pair>(&mr2);

    EXPECT_THROW(stack2.top(), std::runtime_error);
    auto elementPair = Pair{1, 2};
    stack2.push(elementPair);
    EXPECT_EQ(stack2.size(), 1);
    auto returnedElementPair = stack2.top();
    EXPECT_EQ(returnedElementPair->x, elementPair.x);
    EXPECT_EQ(returnedElementPair->y, elementPair.y);
    EXPECT_EQ(stack2.size(), 1);
}

TEST(PairType, EmptySizeClearTest)
{
    StackMemoryResource mr2;

    auto stack2 = Stack<Pair>(&mr2);

    EXPECT_EQ(stack2.size(), 0);
    EXPECT_TRUE(stack2.empty());
    for (int i; i < 10; ++i){
        auto element = Pair{i, i};
        stack2.push(element);
    }

    EXPECT_EQ(stack2.size(), 10);
    EXPECT_FALSE(stack2.empty());

    stack2.clear();
    EXPECT_EQ(stack2.size(), 0);
}

TEST(StackMemoryRes, DestructorTest)
{
    auto *mr = new StackMemoryResource();
    delete mr;
}

TEST(StackMemoryRes, AllocateAndDeallocateTest)
{
    StackMemoryResource mr;
    int element1 = 42, element2 = 100;

    auto* number1 = static_cast<int*>(mr.allocate(sizeof(int), alignof(int)));
    *number1 = element1;
    EXPECT_EQ(*number1, element1);

    mr.deallocate(number1, sizeof(int), alignof(int));

    auto* reused_number = static_cast<int*>(mr.allocate(sizeof(int), alignof(int)));
    *reused_number = element2;
    EXPECT_EQ(*reused_number, element2);

    EXPECT_EQ(number1, reused_number);

    mr.deallocate(reused_number, sizeof(int), alignof(int));

    EXPECT_THROW(mr.deallocate(reused_number, sizeof(int), alignof(int)), std::logic_error);

}





int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
