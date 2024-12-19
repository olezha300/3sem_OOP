#include <gtest/gtest.h>
#include "../src/stack.h"
#include "../src/memoryResource.h"

struct CustomStruct {
    int a;
    float b;
    std::string c;

    bool operator==(const CustomStruct& other) const {
        return a == other.a && b == other.b && c == other.c;
    }
};

namespace Containers {

    template<class T>
    bool compare_stack(const Stack<T, std::pmr::polymorphic_allocator<T>>& stack, const std::vector<T>& expected) {
        if (stack.size() != expected.size()) return false;
        std::size_t idx = 0;
        for (const auto& item : stack) {
            if (!(item == expected[idx])) return false;
            ++idx;
        }
        return true;
    }

    TEST(StackTests, ShouldPushElementsCorrectly) {
        MemoryResource customResource(1024);
        std::pmr::polymorphic_allocator<int> allocator(&customResource);
        Stack<int, std::pmr::polymorphic_allocator<int>> stack(allocator);

        stack.push(42);
        stack.push(24);
        stack.push(7);

        std::vector<int> expected = {7, 24, 42};
        EXPECT_TRUE(compare_stack(stack, expected));
    }

    TEST(StackTests, ShouldPopElementsCorrectly) {
        MemoryResource customResource(1024);
        std::pmr::polymorphic_allocator<int> allocator(&customResource);
        Stack<int, std::pmr::polymorphic_allocator<int>> stack(allocator);

        stack.push(10);
        stack.push(20);
        stack.push(30);
        stack.pop();

        std::vector<int> expected = {20, 10};
        EXPECT_TRUE(compare_stack(stack, expected));
    }

    TEST(StackTests, ShouldHandleCustomStructsCorrectly) {
        MemoryResource customResource(2048);
        std::pmr::polymorphic_allocator<CustomStruct> allocator(&customResource);
        Stack<CustomStruct, std::pmr::polymorphic_allocator<CustomStruct>> stack(allocator);

        stack.push(CustomStruct{1, 1.1f, "first"});
        stack.push(CustomStruct{2, 2.2f, "second"});
        stack.push(CustomStruct{3, 3.3f, "third"});

        std::vector<CustomStruct> expected = {
            {3, 3.3f, "third"},
            {2, 2.2f, "second"},
            {1, 1.1f, "first"}
        };

        EXPECT_TRUE(compare_stack(stack, expected));
    }

    TEST(StackTests, ShouldThrowWhenPoppingEmptyStack) {
        MemoryResource customResource(1024);
        std::pmr::polymorphic_allocator<int> allocator(&customResource);
        Stack<int, std::pmr::polymorphic_allocator<int>> stack(allocator);

        EXPECT_THROW(stack.pop(), std::out_of_range);
    }

    TEST(StackTests, ShouldAccessTopElementCorrectly) {
        MemoryResource customResource(1024);
        std::pmr::polymorphic_allocator<int> allocator(&customResource);
        Stack<int, std::pmr::polymorphic_allocator<int>> stack(allocator);

        stack.push(10);
        stack.push(20);

        EXPECT_EQ(stack.top(), 20);

        stack.pop();
        EXPECT_EQ(stack.top(), 10);
    }

    TEST(StackTests, CopyConstructorCreatesIndependentStack) {
        MemoryResource customResource(2048);
        std::pmr::polymorphic_allocator<CustomStruct> allocator(&customResource);
        Stack<CustomStruct, std::pmr::polymorphic_allocator<CustomStruct>> originalStack(allocator);

        originalStack.push(CustomStruct{10, 1.5f, "node1"});
        originalStack.push(CustomStruct{20, 2.5f, "node2"});
        originalStack.push(CustomStruct{30, 3.5f, "node3"});

        Stack<CustomStruct, std::pmr::polymorphic_allocator<CustomStruct>> copiedStack(originalStack);

        std::vector<CustomStruct> expected = {
            {30, 3.5f, "node3"},
            {20, 2.5f, "node2"},
            {10, 1.5f, "node1"}
        };
        EXPECT_TRUE(compare_stack(copiedStack, expected));

        originalStack.pop();
        std::vector<CustomStruct> expectedOriginal = {
            {20, 2.5f, "node2"},
            {10, 1.5f, "node1"}
        };
        EXPECT_TRUE(compare_stack(originalStack, expectedOriginal));
        EXPECT_TRUE(compare_stack(copiedStack, expected));
    }

    TEST(StackTests, MoveConstructorTransfersOwnership) {
        MemoryResource customResource(2048);
        std::pmr::polymorphic_allocator<CustomStruct> allocator(&customResource);
        Stack<CustomStruct, std::pmr::polymorphic_allocator<CustomStruct>> originalStack(allocator);

        originalStack.push(CustomStruct{42, 4.2f, "move1"});
        originalStack.push(CustomStruct{84, 8.4f, "move2"});

        Stack<CustomStruct, std::pmr::polymorphic_allocator<CustomStruct>> movedStack(std::move(originalStack));

        std::vector<CustomStruct> expectedMoved = {
            {84, 8.4f, "move2"},
            {42, 4.2f, "move1"}
        };
        EXPECT_TRUE(compare_stack(movedStack, expectedMoved));

        EXPECT_TRUE(originalStack.empty());
        EXPECT_EQ(originalStack.size(), 0);
    }

    TEST(StackTests, CopyAssignmentOperatorWorksCorrectly) {
        MemoryResource customResource(2048);
        std::pmr::polymorphic_allocator<CustomStruct> allocator(&customResource);
        Stack<CustomStruct, std::pmr::polymorphic_allocator<CustomStruct>> stack1(allocator);

        stack1.push(CustomStruct{5, 0.5f, "A"});
        stack1.push(CustomStruct{15, 1.5f, "B"});

        Stack<CustomStruct, std::pmr::polymorphic_allocator<CustomStruct>> stack2(allocator);
        stack2.push(CustomStruct{25, 2.5f, "C"});

        stack2 = stack1;

        std::vector<CustomStruct> expected = {
            {15, 1.5f, "B"},
            {5, 0.5f, "A"}
        };
        EXPECT_TRUE(compare_stack(stack2, expected));

        stack1.push(CustomStruct{35, 3.5f, "D"});
        std::vector<CustomStruct> expectedStack1 = {
            {35, 3.5f, "D"},
            {15, 1.5f, "B"},
            {5, 0.5f, "A"}
        };
        std::vector<CustomStruct> expectedStack2 = {
            {15, 1.5f, "B"},
            {5, 0.5f, "A"}
        };
        EXPECT_TRUE(compare_stack(stack1, expectedStack1));
        EXPECT_TRUE(compare_stack(stack2, expectedStack2));
    }

    TEST(StackTests, ShouldThrowOnExceedingMemory) {
        MemoryResource customResource(64);
        std::pmr::polymorphic_allocator<CustomStruct> allocator(&customResource);
        Stack<CustomStruct, std::pmr::polymorphic_allocator<CustomStruct>> stack(allocator);

        EXPECT_THROW({
            stack.push(CustomStruct{1, 1.1f, "Overflow"});
            stack.push(CustomStruct{2, 2.2f, "Overflow"});
        }, std::bad_alloc);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
