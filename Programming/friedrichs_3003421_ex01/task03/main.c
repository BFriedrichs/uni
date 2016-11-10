#include <stdio.h>

/**
* The main function.
*
* Prints "wrong input" if you didn't enter exactly two arguments
* Else it prints the length of your entered argument two times
*
* Once by counting an index while iterating over the char array.
* And once by starting a pointer at the first char and incrementing it and then substracting it from the initial pointer.
*
* @return 0
*/
int main(int argc, char *argv[]) {

  if(argc != 2) {
    printf("%s\n", "wrong input");
    return 0;
  }

  int i = 0;
  while(argv[1][i]) {
    i++;
  }
  printf("%i\n", i);


  char *ptrFirst = &argv[1][0];
  char *ptrCount = ptrFirst;
  while(*ptrCount) {
    ptrCount++;
  }
  printf("%ld\n", ptrCount - ptrFirst);

  return 0;
}
