#include "SparseVector.h"
#include <iostream>
#include <cassert>

/*
    Конструктор разреженного вектора.
    size — логический размер вектора.
    head — начало односвязного списка (сначала пусто).
*/
SparseVector::SparseVector(int size)
    : size(size), head(nullptr)
{
    assert(size >= 0);
}

/*
    Конструктор копирования.
    Изначально создаём пустой объект, затем копируем узлы.
*/
SparseVector::SparseVector(const SparseVector& sv)
    : size(0), head(nullptr)
{
    copyList(sv);
}

/*
    Деструктор — освобождаем все узлы списка.
*/
SparseVector::~SparseVector()
{
    clear();
}

/*
    Возвращает логический размер вектора.
*/
int SparseVector::getSize() const
{
    return size;
}

/*
    Полностью очищает список узлов.
*/
void SparseVector::clear()
{
    node* current = head;
    while (current != nullptr)
    {
        node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}

/*
    Копирование списка из другого SparseVector.
    Узлы создаются заново, порядок сохраняется.
*/
void SparseVector::copyList(const SparseVector& sv)
{
    size = sv.size;
    head = nullptr;

    if (sv.head == nullptr)
        return;

    // копируем первый узел
    node* src = sv.head;
    head = new node(src->index, src->value, nullptr);
    node* tail = head;

    // копируем остальные
    src = src->next;
    while (src != nullptr)
    {
        tail->next = new node(src->index, src->value, nullptr);
        tail = tail->next;
        src = src->next;
    }

    checkListOrder();
}

/*
    Оператор присваивания.
*/
SparseVector& SparseVector::operator=(const SparseVector& sv)
{
    if (this == &sv)
        return *this; // защита от самоприсваивания

    clear();
    copyList(sv);
    return *this;
}

/*
    Устанавливает ненулевой элемент (вставка или изменение).
    Гарантируется что value != 0.
*/
void SparseVector::setNonzeroElem(int index, int value)
{
    assert(value != 0);

    // Если список пуст — создаём первый элемент.
    if (head == nullptr)
    {
        head = new node(index, value, nullptr);
        checkListOrder();
        return;
    }

    node* curr = head;
    node* prev = nullptr;

    // Идём до позиции для вставки/обновления
    while (curr != nullptr && curr->index < index)
    {
        prev = curr;
        curr = curr->next;
    }

    // Если индекс уже есть — обновляем значение
    if (curr != nullptr && curr->index == index)
    {
        curr->value = value;
        checkListOrder();
        return;
    }

    // Создание нового узла
    node* newNode = new node(index, value, curr);

    if (prev == nullptr)
        head = newNode;
    else
        prev->next = newNode;

    checkListOrder();
}

/*
    Удаляет элемент с данным индексом (если он есть).
*/
void SparseVector::removeElem(int index)
{
    node* curr = head;
    node* prev = nullptr;

    while (curr != nullptr && curr->index < index)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr || curr->index != index)
        return; // не найден

    // удаление узла
    if (prev == nullptr)
        head = curr->next;
    else
        prev->next = curr->next;

    delete curr;
    checkListOrder();
}

/*
    Универсальная установка элемента:
    value == 0 → удалить
    value != 0 → установить/вставить
*/
void SparseVector::setElem(int index, int value)
{
    assert(index >= 0 && index < size);

    if (value == 0)
        removeElem(index);
    else
        setNonzeroElem(index, value);
}

/*
    Возвращает значение элемента.
    Если узла нет — возвращает 0.
*/
int SparseVector::getElem(int idx) const
{
    assert(idx >= 0 && idx < size);

    node* curr = head;
    while (curr != nullptr)
    {
        if (curr->index == idx)
            return curr->value;
        if (curr->index > idx)
            return 0; // дальше будут только большие индексы
        curr = curr->next;
    }
    return 0;
}

/*
    Проверка на строго возрастающий порядок индексов.
    Используется в отладке.
*/
void SparseVector::checkListOrder() const
{
    if (head == nullptr)
        return;

    node* curr = head;
    while (curr->next != nullptr)
    {
        if (curr->index >= curr->next->index)
        {
            std::cerr << "List order error: index "
                      << curr->index << " >= "
                      << curr->next->index << std::endl;
            assert(false);
        }
        curr = curr->next;
    }
}


/*
    Оператор == : сравниваем размер и все узлы.
*/
bool SparseVector::operator==(const SparseVector& rhs) const
{
    if (size != rhs.size)
        return false;

    node* a = head;
    node* b = rhs.head;

    while (a != nullptr && b != nullptr)
    {
        if (a->index != b->index || a->value != b->value)
            return false;

        a = a->next;
        b = b->next;
    }

    return (a == nullptr && b == nullptr);
}

/*
    Оператор != — логическое отрицание ==.
*/
bool SparseVector::operator!=(const SparseVector& rhs) const
{
    return !(*this == rhs);
}



/*
    Оператор + : создаём новый вектор и выполняем слияние списков.
*/
SparseVector SparseVector::operator+(const SparseVector& rhs) const
{
    assert(size == rhs.size);

    SparseVector result(size);

    node* a = head;
    node* b = rhs.head;

    while (a != nullptr || b != nullptr)
    {
        if (b == nullptr || (a != nullptr && a->index < b->index))
        {
            result.setElem(a->index, a->value);
            a = a->next;
        }
        else if (a == nullptr || b->index < a->index)
        {
            result.setElem(b->index, b->value);
            b = b->next;
        }
        else
        {
            int sum = a->value + b->value;
            if (sum != 0)
                result.setElem(a->index, sum);

            a = a->next;
            b = b->next;
        }
    }

    return result;
}


/*
    Оператор - : аналогично +, но вычитаем значения.
*/
SparseVector SparseVector::operator-(const SparseVector& rhs) const
{
    assert(size == rhs.size);

    SparseVector result(size);

    node* a = head;
    node* b = rhs.head;

    while (a != nullptr || b != nullptr)
    {
        if (b == nullptr || (a != nullptr && a->index < b->index))
        {
            result.setElem(a->index, a->value);
            a = a->next;
        }
        else if (a == nullptr || b->index < a->index)
        {
            result.setElem(b->index, -b->value);
            b = b->next;
        }
        else
        {
            int diff = a->value - b->value;
            if (diff != 0)
                result.setElem(a->index, diff);

            a = a->next;
            b = b->next;
        }
    }

    return result;
}


/*
    Составной оператор +=
*/
SparseVector& SparseVector::operator+=(const SparseVector& rhs)
{
    assert(size == rhs.size);
    addSubVector(rhs, true);
    removeZeros(); // чистим нули после сложения
    return *this;
}

/*
    Составной оператор -=
*/
SparseVector& SparseVector::operator-=(const SparseVector& rhs)
{
    assert(size == rhs.size);
    addSubVector(rhs, false);
    removeZeros();
    return *this;
}


/*
    Вспомогательная функция: выполняет += или -= в зависимости от флага add.
    Обходит два списка и модифицирует *this* на месте.
*/
void SparseVector::addSubVector(const SparseVector& sv, bool add)
{
    int sign = (add ? 1 : -1);

    node* a = head;
    node* b = sv.head;
    node* prev = nullptr;

    // Сливаем два списка, прямо меняя текущий
    while (a != nullptr || b != nullptr)
    {
        // (a.index < b.index) → просто идём дальше
        if (b == nullptr || (a != nullptr && a->index < b->index))
        {
            prev = a;
            a = a->next;
        }
        // элемент присутствует только в b → вставляем его
        else if (a == nullptr || b->index < a->index)
        {
            int newVal = sign * b->value;
            node* newNode = new node(b->index, newVal, a);

            if (prev == nullptr)
                head = newNode;
            else
                prev->next = newNode;

            prev = newNode;
            b = b->next;
        }
        // одинаковые индексы → изменяем значение
        else
        {
            a->value += sign * b->value;
            prev = a;
            a = a->next;
            b = b->next;
        }
    }
}

/*
    Удаляет все узлы с value = 0.
*/
void SparseVector::removeZeros()
{
    node* curr = head;
    node* prev = nullptr;

    while (curr != nullptr)
    {
        if (curr->value == 0)
        {
            node* toDelete = curr;
            if (prev == nullptr)
                head = curr->next;
            else
                prev->next = curr->next;

            curr = curr->next;
            delete toDelete;
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
}
