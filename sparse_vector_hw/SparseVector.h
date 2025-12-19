#ifndef SPARSE_VECTOR_H
#define SPARSE_VECTOR_H

#include <cassert>

/*
    Класс SparseVector — разреженный вектор на односвязном списке.
    Хранит только ненулевые элементы, отсортированные по индексу.
*/
class SparseVector
{
private:
    /*
        Узел списка разреженного вектора.
        index — индекс элемента в логическом массиве.
        value — его значение (всегда != 0).
        next — указатель на следующий ненулевой элемент.
    */
    struct node
    {
        int index;
        int value;
        node* next;

        node(int index, int value, node* next = nullptr)
            : index(index), value(value), next(next) {}
    };

    int size;    // логический размер вектора (кол-во позиций)
    node* head;  // начало односвязного списка ненулевых элементов


        //Удаление всех узлов списка (используется в деструкторе и operator=).

    void clear();

        //Копирование списка из другого SparseVector.
        //Полностью пересоздаёт цепочку узлов.
  
    void copyList(const SparseVector& sv);

    
        //Устанавливает элемент index -> value, гарантировано что value != 0.
        //(Вставка нового узла или обновление существующего.)
    
    void setNonzeroElem(int index, int value);

    /*
        Удаляет узел с данным индексом, если он существует.
    */
    void removeElem(int index);

    /*
        Проверяет, что список строго отсортирован по индексам (для отладки).
    */
    void checkListOrder() const;

    /*
        Общая функция для += и -=.
        add = true  → выполняется +=
        add = false → выполняется -=
        Все изменения производятся прямо в текущем объекте.
    */
    void addSubVector(const SparseVector& sv, bool add);

    /*
        Удаляет узлы со значением 0 (используется после += и -=).
    */
    void removeZeros();

public:

    /*
        Конструктор разреженного вектора заданного размера.
        Создаёт пустой список ненулевых элементов.
    */
    explicit SparseVector(int size);

    /*
        Конструктор копирования — глубокое копирование.
    */
    SparseVector(const SparseVector& sv);

    /*
        Деструктор — освобождает память всех узлов.
    */
    ~SparseVector();

    /*
        Возвращает размер (количество логических элементов).
    */
    int getSize() const;

    /*
        Возвращает значение элемента по индексу.
        Если узла нет → возвращает 0.
    */
    int getElem(int col) const;

    /*
        Универсальная установка элемента.
        value == 0 → элемент удаляется;
        value != 0 → элемент добавляется/обновляется.
    */
    void setElem(int col, int value);

    /*
        Оператор присваивания — глубокое копирование.
    */
    SparseVector& operator=(const SparseVector& rhs);



    /*
        Сравнение двух векторов:
        == проверяет равенство размеров и всех ненулевых элементов;
        != — отрицание ==
    */
    bool operator==(const SparseVector& rhs) const;
    bool operator!=(const SparseVector& rhs) const;

    /*
        Арифметические операции над разреженными векторами.
        Возвращают новый SparseVector (не изменяют исходные).
    */
    SparseVector operator+(const SparseVector& rhs) const;
    SparseVector operator-(const SparseVector& rhs) const;

    /*
        Составные операторы: изменяют текущий вектор.
    */
    SparseVector& operator+=(const SparseVector& rhs);
    SparseVector& operator-=(const SparseVector& rhs);
};

#endif
