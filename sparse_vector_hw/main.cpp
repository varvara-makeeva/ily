#include <iostream>
#include "SparseVector.h"

/*
    Тестируем функциональность класса SparseVector:
    - сравнение (==, !=)
    - арифметические операторы (+, -)
    - составные операторы (+=, -=)
*/

int main()
{
    //                 TEST equality (== и !=)

    std::cout << "=== TEST equality ===\n";

    SparseVector a(10);
    a.setElem(1, 5);
    a.setElem(3, -2);

    SparseVector b(10);
    b.setElem(1, 5);
    b.setElem(3, -2);

    // Проверяем равенство двух одинаковых векторов
    std::cout << "a==b? " << (a == b) << "\n";   // ожидаем 1 (true)
    std::cout << "a!=b? " << (a != b) << "\n";   // ожидаем 0 (false)

    // Изменяем b и сравниваем снова
    b.setElem(3, 0);  // удаляется элемент (3:-2)
    std::cout << "after change: a==b? " << (a == b) << "\n"; // ожидаем 0


    //                       TEST operator+

    std::cout << "\n=== TEST operator+ ===\n";

    SparseVector x(10);
    x.setElem(1, 5);
    x.setElem(3, -2);

    SparseVector y(10);
    y.setElem(3, 2);
    y.setElem(4, 10);

    // Проверяем x + y
    SparseVector z = x + y;

    std::cout << "z[1]=" << z.getElem(1) << "\n"; // 5
    std::cout << "z[3]=" << z.getElem(3) << "\n"; // 0 ( -2 + 2 )
    std::cout << "z[4]=" << z.getElem(4) << "\n"; // 10


    //                       TEST operator-

    std::cout << "\n=== TEST operator- ===\n";

    SparseVector p(10);
    p.setElem(2, 7);
    p.setElem(5, 3);

    SparseVector q(10);
    q.setElem(2, 2);
    q.setElem(4, 10);

    // Проверяем p - q
    SparseVector r = p - q;

    std::cout << "r[2]=" << r.getElem(2) << "\n"; // 7 - 2 = 5
    std::cout << "r[4]=" << r.getElem(4) << "\n"; // 0 - 10 = -10
    std::cout << "r[5]=" << r.getElem(5) << "\n"; // 3 - 0 = 3


    //                  TEST operator+= и operator-=

    std::cout << "\n=== TEST operator+= / operator-= ===\n";

    SparseVector u(10);
    u.setElem(1, 5);
    u.setElem(3, -2);

    SparseVector v(10);
    v.setElem(3, 2);
    v.setElem(4, 10);

    
    u += v;
    // (1:5, 3:-2) + (3:2, 4:10) = (1:5, 3:0, 4:10)
    // после removeZeros → (1:5, 4:10)

    std::cout << "u[1]=" << u.getElem(1) << "\n"; // 5
    std::cout << "u[3]=" << u.getElem(3) << "\n"; // 0
    std::cout << "u[4]=" << u.getElem(4) << "\n"; // 10

    // u = u - v → возвращаемся к исходному (1:5, 3:-2)
    u -= v;

    std::cout << "after -= : u[1]=" << u.getElem(1) << "\n"; // 5
    std::cout << "after -= : u[3]=" << u.getElem(3) << "\n"; // -2
    std::cout << "after -= : u[4]=" << u.getElem(4) << "\n"; // 0

    return 0;
}
