#include <gtest/gtest.h>

#include "dragon.h"
#include "frog.h"
#include "knight.h"
#include "npc.h"
#include "visitor.h"

TEST(NPCTest, IsCloseTest) {
    auto frog = std::make_shared<Frog>("Frog1", 112, 50);
    auto knight = std::make_shared<Knight>("Knight1", 120, 30);
    auto dragon = std::make_shared<Dragon>("Dragon1", 90, 15);

    EXPECT_EQ(knight->is_close(frog, 40), 1);
    EXPECT_EQ(frog->is_close(dragon, 100), 1);
    EXPECT_EQ(dragon->is_close(knight, 10), 0);
}

TEST(NPCTest, AcceptTest) {
    auto frog = std::make_shared<Frog>("Frog1", 112, 50);
    auto knight = std::make_shared<Knight>("Knight1", 120, 30);
    auto dragon = std::make_shared<Dragon>("Dragon1", 90, 15);

    // жаба
    EXPECT_EQ(frog->accept(frog), 1);
    EXPECT_EQ(knight->accept(frog), 1);
    EXPECT_EQ(dragon->accept(frog), 1);

    // драконы только рыцарей
    EXPECT_EQ(frog->accept(dragon), 0);
    EXPECT_EQ(knight->accept(dragon), 1);
    EXPECT_EQ(dragon->accept(dragon), 0);

    // рыцари только драконов
    EXPECT_EQ(frog->accept(knight), 0);
    EXPECT_EQ(knight->accept(knight), 0);
    EXPECT_EQ(dragon->accept(knight), 1);
}

TEST(NPCTest, VisitTest) {
    std::shared_ptr<NPC> knight, frog, dragon;
    frog = std::make_shared<Frog>("Frog1", 112, 50);
    knight = std::make_shared<Knight>("Knight1", 120, 30);
    dragon = std::make_shared<Dragon>("Dragon1", 90, 15);
    std::shared_ptr<Visitor> knight_visitor, frog_visitor, dragon_visitor;
    frog_visitor = std::make_shared<FrogVisitor>();
    knight_visitor = std::make_shared<KnightVisitor>();
    dragon_visitor = std::make_shared<DragonVisitor>();

    // жаба
    EXPECT_EQ(frog_visitor->visit(frog), 1);
    EXPECT_EQ(frog_visitor->visit(knight), 1);
    EXPECT_EQ(frog_visitor->visit(dragon), 1);

    // дракон
    EXPECT_EQ(dragon_visitor->visit(frog), 0);
    EXPECT_EQ(dragon_visitor->visit(knight), 1);
    EXPECT_EQ(dragon_visitor->visit(dragon), 0);

    // рыцарь
    EXPECT_EQ(knight_visitor->visit(frog), 0);
    EXPECT_EQ(knight_visitor->visit(knight), 0);
    EXPECT_EQ(knight_visitor->visit(dragon), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
