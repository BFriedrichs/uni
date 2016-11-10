#include <stdio.h>

/**
* Function that modifies it's on return address in a way that "i = 0;" in the main function is skipped.
*
* @param void
*/
void modify(void) {
  int x = 0;
  int *xPtr = &x;
  *(xPtr + 5) += 7;
}

/**
* The main function.
*
* Prints "The answer is 42!" because "i = 0" is skipped by modify()
*
* @return 0
*/
int main(void) {
  int i = 42;
  modify();
  i = 0;
  printf("The answer is %d!\n", i);
}