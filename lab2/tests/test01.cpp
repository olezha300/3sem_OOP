#include <gtest/gtest.h>
#include "../include/Octal.hpp"

// Тест на конструктор по умолчанию
TEST(OctalTest, DefaultConstructor)
{
  Octal num;
  EXPECT_EQ(num.Size(), 0);
  EXPECT_EQ(num.Capacity(), 0);
  EXPECT_EQ(num.toString(), "");
}

// Тест на конструктор с параметрами (размер и символ)
TEST(OctalTest, ParamConstructor)
{
  Octal num(5, 3); // Передаем восьмеричное число, а не символ
  EXPECT_EQ(num.Size(), 5);
  EXPECT_EQ(num.Capacity(), 5);
  EXPECT_EQ(num.toString(), "33333");
}

// Тест на конструктор с передачей строки
TEST(OctalTest, StringConstructor)
{
  Octal num("123");
  EXPECT_EQ(num.Size(), 3);
  EXPECT_EQ(num.Capacity(), 3);
  EXPECT_EQ(num.toString(), "123");
}

// Тест на конструктор копирования
TEST(OctalTest, CopyConstructor)
{
  Octal original("123");
  Octal copy(original);
  EXPECT_EQ(copy.Size(), 3);
  EXPECT_EQ(copy.Capacity(), 3);
  EXPECT_EQ(copy.toString(), "123"); // ожидаем строку "123", а не "4123"
  copy.push_back(4);
  EXPECT_EQ(original.toString(), "123");
  EXPECT_EQ(copy.toString(), "4123");
}

// Тест на конструктор перемещения
TEST(OctalTest, MoveConstructor)
{
  Octal original("123");
  Octal moved(std::move(original));
  EXPECT_EQ(moved.Size(), 3);
  EXPECT_EQ(moved.Capacity(), 3);
  EXPECT_EQ(moved.toString(), "123");
  // Проверка
  EXPECT_EQ(original.Size(), 0);
  EXPECT_EQ(original.Capacity(), 0);
  EXPECT_EQ(original.toString(), "");
}

// Тест на оператор присваивания копированием
TEST(OctalTest, CopyAssignment)
{
  Octal original("123");
  Octal copy;
  copy = original; // Присваиваем копию
  EXPECT_EQ(copy.Size(), 3);
  EXPECT_EQ(copy.Capacity(), 3);
  EXPECT_EQ(copy.toString(), "123");
  // Проверяем, что копия независима от оригинала
  copy.push_back(4);
  EXPECT_EQ(original.toString(), "123"); // Оригинал не должен измениться
  EXPECT_EQ(copy.toString(), "4123");
}

// Тест на оператор присваивания перемещением
TEST(OctalTest, MoveAssignment)
{
  Octal original("123");
  Octal moved;
  moved = std::move(original); // Перемещаем объект
  EXPECT_EQ(moved.Size(), 3);
  EXPECT_EQ(moved.Capacity(), 3);
  EXPECT_EQ(moved.toString(), "123");
  // Проверяем, что оригинальный объект был перемещен
  EXPECT_EQ(original.Size(), 0);
  EXPECT_EQ(original.Capacity(), 0);
  EXPECT_EQ(original.toString(), "");
}

// Тест на проверку деструктора (неявно через создание и удаление объектов)
TEST(OctalTest, DestructorTest)
{
  Octal *num = new Octal("123");
  EXPECT_EQ(num->Size(), 3);
  EXPECT_EQ(num->toString(), "123");
  delete num; // должен корректно освободить память, проверяется утечка памяти инструментами
}

// Основная функция для запуска тестов Google Test
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv); // инициализирую Google Test
  return RUN_ALL_TESTS();                 // запуск тестов
}
