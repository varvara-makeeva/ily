#include <gtest/gtest.h>
#include "../heap.h"

// Тест 1: вставка элементов и проверка минимального (для int)
TEST(HeapTest, InsertAndGetMinInt) {
    Heap<int, 10> h;   // создаём кучу на 10 элементов

    h.insert(5);
    h.insert(3);
    h.insert(8);

    // минимальный должен быть 3
    EXPECT_EQ(h.top(), 3);
}

// Тест 2: много вставок и последовательное удаление min
TEST(HeapTest, InsertManyAndExtractAll) {
    Heap<int, 10> h;

    // Заполняем кучку
    h.insert(4);
    h.insert(1);
    h.insert(7);
    h.insert(0);

    // Проверяем порядок удаления минимальных
    EXPECT_EQ(h.top(), 0);  // Мин: 0
    h.pop();                // удалили 0

    EXPECT_EQ(h.top(), 1);  // Мин: 1
    h.pop();                // удалили 1

    EXPECT_EQ(h.top(), 4);  // Следующий мин: 4
}

// Тест 3: переполнение — пытаемся вставить больше, чем позволяет размер
TEST(HeapTest, ThrowsOnInsertOverflow) {
    Heap<int, 2> h;

    h.insert(1);
    h.insert(2);

    // третья вставка должна выбросить исключение overflow_error
    EXPECT_THROW(h.insert(3), std::overflow_error);
}

// Тест 4: вызов top() на пустой куче должен бросать underflow_error
TEST(HeapTest, ThrowsOnTopUnderflow) {
    Heap<int, 5> h;

    EXPECT_THROW(h.top(), std::underflow_error);
}

// Тест 5: проверяем работу со строками и лексикографический порядок
TEST(HeapTest, StringsWork) {
    Heap<std::string, 5> hs;

    hs.insert("red");
    hs.insert("green");
    hs.insert("blue");

    EXPECT_EQ(hs.top(), "blue");
}
