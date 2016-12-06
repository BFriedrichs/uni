#include <iostream>

/*
========  ADD YOUR CODE HERE ================
* Implement macro MAXM()
* Implement both maxf() functions
*/

#define MAXM(X, Y) (X > Y ? X : Y)

int maxf(const int x, const int y) {
    std::cout << "In maxf(int)" << std::endl;
    return x > y ? x : y;
}

double maxf(const double x, const double y) {
    std::cout << "In maxf(double)" << std::endl;
    return x > y ? x : y;
}

int main(void) {
  int a = 10, b = 20;
  std::cout << "MAXM1 = " << MAXM(a,b)      << std::endl;
  std::cout << "MAXM2 = " << MAXM(a,b+0.2)  << std::endl;
  std::cout << "MAXM3 = " << MAXM(a,b++)    << std::endl;
  std::cout << "maxf1 = " << maxf(a,b)      << std::endl;
  // what's the problem with the following line?
  //std::cout << "maxf = " << maxf(a,b+0.2) << std::endl;
  std::cout << "maxf2 = " << maxf(a+0.1,b+0.2)  << std::endl;
  std::cout << "maxf3 = " << maxf(a,b++)        << std::endl;
  std::cout << "a = " << a << ", b = " << b     << std::endl;
}
