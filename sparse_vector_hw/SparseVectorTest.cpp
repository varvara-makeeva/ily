#include <gtest/gtest.h>
#include "SparseVector.h"

TEST(SparseVectorBasics, SizeAndDefaultZeros) {
    SparseVector v(10);
    EXPECT_EQ(v.getSize(), 10);
    EXPECT_EQ(v.getElem(0), 0);
    EXPECT_EQ(v.getElem(9), 0);
}

TEST(SparseVectorBasics, SetAndGet) {
    SparseVector v(10);
    v.setElem(2, 5);
    v.setElem(7, -3);
    EXPECT_EQ(v.getElem(2), 5);
    EXPECT_EQ(v.getElem(7), -3);
    v.setElem(2, 0);              // удаление
    EXPECT_EQ(v.getElem(2), 0);
}

TEST(SparseVectorCompare, Equality) {
    SparseVector a(10), b(10);
    a.setElem(1, 5); a.setElem(3, -2);
    b.setElem(1, 5); b.setElem(3, -2);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);

    b.setElem(3, 0);
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(SparseVectorArith, PlusMinus) {
    SparseVector x(10), y(10);
    x.setElem(1, 5);
    x.setElem(3, -2);

    y.setElem(3, 2);
    y.setElem(4, 10);

    SparseVector z = x + y;
    EXPECT_EQ(z.getElem(1), 5);
    EXPECT_EQ(z.getElem(3), 0);   //  -2 + 2 = 0  (должен исчезнуть из списка)
    EXPECT_EQ(z.getElem(4), 10);

    SparseVector r = x - y;
    EXPECT_EQ(r.getElem(1), 5);
    EXPECT_EQ(r.getElem(3), -4);  // -2 - 2
    EXPECT_EQ(r.getElem(4), -10); // 0 - 10
}

TEST(SparseVectorArith, PlusMinusAssign) {
    SparseVector u(10), v(10);
    u.setElem(1, 5);
    u.setElem(3, -2);

    v.setElem(3, 2);
    v.setElem(4, 10);

    u += v; // (1:5, 3:0, 4:10) -> после removeZeros должно быть (1:5, 4:10)
    EXPECT_EQ(u.getElem(1), 5);
    EXPECT_EQ(u.getElem(3), 0);
    EXPECT_EQ(u.getElem(4), 10);

    u -= v; // вернёт (1:5, 3:-2)
    EXPECT_EQ(u.getElem(1), 5);
    EXPECT_EQ(u.getElem(3), -2);
    EXPECT_EQ(u.getElem(4), 0);
}
