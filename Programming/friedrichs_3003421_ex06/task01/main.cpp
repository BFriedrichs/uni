#include <iostream>
#include "matrix.hpp"

int main() {
    Matrix m1(2, 2);
    m1.fill();
    std::cout << m1 << std::endl;
    std::cout << m1.computeDeterminant() << std::endl;

    Matrix m2(3, 3);
    m2.fill();
    m2.addValue(19, 1, 2);
    std::cout << m2 << std::endl;
    std::cout << m2.computeDeterminant() << std::endl;

    Matrix m3 = m2 + m2;
    m3 += m2;
    std::cout << m3 << std::endl;
    Matrix m4 = m3 - m2;
    m4 -= m2;
    std::cout << m4 << std::endl;

    Matrix m5(3, 3);
    m5.fill();
    m5 += 6;
    m5 -= 3;
    m5 *= 2;
    std::cout << m5 << std::endl;

    Matrix m6(1, 3);
    Matrix m7(3, 4);
    m6.fill();
    m7.fill();
    Matrix m8 = m6 * m7;
    std::cout << m8 << std::endl;

    Matrix m9(3, 3);
    m9.addValue(1, 0, 0);
    m9.addValue(2, 0, 1);
    m9.addValue(3, 0, 2);
    m9.addValue(0, 1, 0);
    m9.addValue(1, 1, 1);
    m9.addValue(4, 1, 2);
    m9.addValue(5, 2, 0);
    m9.addValue(6, 2, 1);
    m9.addValue(0, 2, 2);

    std::cout << m9 << std::endl;
    std::cout << m9.computeInverse() << std::endl;

    Matrix m10(2, 2);
    m10.addValue(2, 0, 0);
    m10.addValue(-3, 0, 1);
    m10.addValue(1, 1, 0);
    m10.addValue(5, 1, 1);

    std::cout << m10 << std::endl;
    std::cout << m10.computeInverse() << std::endl;

    Matrix m11(3, 3);
    m11 = m9;
    m11 = std::move(m9);

    std::cout << m11 << std::endl;
    return 0;
}