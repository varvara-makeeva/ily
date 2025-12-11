#ifndef HEAP_H
#define HEAP_H

#include <stdexcept>   // std::overflow_error, std::underflow_error
#include <cstddef>     // std::size_t

//  Шаблон класса Heap
//  T — тип элементов
//  N — максимальное кол-во эл-тов (фиксированный размер).


template <typename T, std::size_t N>
class Heap {
public:

    // Конструктор: начинаем с пустой кучи
    Heap() : count(0) {}

    // true, если куча не содержит элементов
    bool empty() const { return count == 0; }

    // true, если достигнут максимальный размер N
    bool full() const { return count == N; }

    // Возврат текущего количества элементов
    std::size_t size() const { return count; }


    // Основная операция: вставка нового элемента
    void insert(const T& value) {
        // Если места больше нет — кидаем исключение
        if (full()) {
            throw std::overflow_error("Куча заполнена!");
        }

        // Добавляем элемент в конец массива
        data[count] = value;

        // Восстанавливаем свойства кучи (поднимаем вверх)
        siftUp(count);

        count++;
    }

    // Возвращает минимальный элемент
    const T& getMin() const {
        return top();
    }

    // Удаляет минимальный элемент
    void removeMin() {
        pop();
    }

   
    // Возврат минимального элемента (корня кучи)
    const T& top() const {
        if (empty()) {
            throw std::underflow_error("Куча пуста!");
        }
        return data[0];
    }

    // Удаление минимального элемента
    // Алгоритм:
    // 1) Перенести последний элемент на место корня
    // 2) Уменьшить количество элементов
    // 3) Провести siftDown — восстановить свойство кучи

    void pop() {
        if (empty()) {
            throw std::underflow_error("Куча пуста!");
        }

        // Перемещаем последний элемент на вершину
        data[0] = data[count - 1];

        // Уменьшаем количество элементов
        count--;

        // Восстанавливаем кучу
        siftDown(0);
    }

private:
 
    T data[N];

    // Текущее количество эл-тов в куче
    std::size_t count;

    // Поднятие элемента вверх (sift up)
    void siftUp(std::size_t idx) {
        while (idx > 0) {
            std::size_t parent = (idx - 1) / 2;

            // Если порядок соблюден — прекращаем
            if (!(data[idx] < data[parent]))
                break;

            // Иначе меняем местами и продолжаем подниматься
            std::swap(data[idx], data[parent]);
            idx = parent;
        }
    }


    // Опускание элемента вниз (sift down)

    void siftDown(std::size_t idx) {
        while (true) {
            std::size_t left = 2 * idx + 1;   // индекс левого 
            std::size_t right = 2 * idx + 2;  // индекс правого 
            std::size_t smallest = idx;       // предполагаем, что текущий — минимальный

            // Если левый существует и меньше текущего
            if (left < count && data[left] < data[smallest])
                smallest = left;

            // Если правый существует и меньше текущего минимального
            if (right < count && data[right] < data[smallest])
                smallest = right;

            // Если порядок не нарушен — заканчиваем
            if (smallest == idx)
                break;

            // Иначе меняем местами и спускаемся дальше
            std::swap(data[idx], data[smallest]);
            idx = smallest;
        }
    }
};

#endif 
