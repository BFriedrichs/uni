#include <iostream>

/*
* === Add your code here, implement MAKEVAR macro
*/


/**
 *
 * First create the global VAR from type TYPE ex: "int weight" or "float price"
 * Then use the ## operator to connect and create "set_" + VAR function, accept a parameter of type TYPE and set the VAR to desired value
 * Lastly create the return function of type TYPE in the same way which returns the VAR
 *
 */
 
#define MAKEVAR(VAR, TYPE)  TYPE VAR; \
                            void set_##VAR(TYPE val) { VAR = val; } \
                            TYPE get_##VAR(void) { return VAR; }

MAKEVAR(weight, int)
MAKEVAR(price, float)

int main(void) {
  set_weight(100);
  set_price(1.25);
  std::cout << "Weight: " << get_weight() << ", Price: " << get_price() << std::endl;
}
