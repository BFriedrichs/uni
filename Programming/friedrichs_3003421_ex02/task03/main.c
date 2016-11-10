#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "main.h"

char ops[] = {'+', '-', '*', '/'};

char currOp = 0;
int firstNumber = 0,
    secondNumber = 0,
    shouldClose = 0;

/**
* The main function.
*
* In a loop accepting terms in the form of <int> <op> <int> and printing the result.
* Inputting a single 0 terminates the program.
* Faulty inputs cause an "invalid output" message.
*
* @return 0
*/
int main(int argc, char *argv[]) {
  while(!shouldClose) {
    resetCalculator();

    int check = parseInput();
    switch(check) {
      case 0:
        printf("%d %c %d = %d\n", firstNumber, currOp, secondNumber, calcResult());
        break;
      case 1:
        printf("invalid input\n");
        break;
      case 2:
        printf("Goodbye\n");
        shouldClose = 1;
        break;
    }
  }

  return 0;
}

/**
* Parses input given from stdin by using fgets and sscanf.
*
* @return 0 to indicate correct parsing, 1 to indicate invalid input, 2 to close the program
*/
int parseInput() {
  char input[80] = { 0 }; // more or less arbitrary array size
  char dummy;

  printf("Enter <int> <op> <int>, single '0' to exit: ");
  fgets(input, sizeof(input), stdin);
  
  // use of a dummy element to check for inputs that include too many symbols
  int check = sscanf(input, "%d %c %d %c", &firstNumber, &currOp, &secondNumber, &dummy);

  if(check == 1 && firstNumber == 0) {
    return 2;
  } else if(check != 3 || !inArray(&currOp, &ops[0])) {
    return 1; // invalid - parse failed or invalid operator
  }

  // special cases
  if(currOp == '/' && secondNumber == 0) {
    return 1; // invalid - division by zero
  }

  return 0;
}

/**
* Calculates the result of our term based on operator and numbers.
*
* @return Result of calculation based on current operator and numbers.
*/
int calcResult() {
  switch(currOp) {
    case '+':
      return firstNumber + secondNumber;
    case '-':
      return firstNumber - secondNumber;
    case '*':
      return firstNumber * secondNumber;
    case '/':
      return round(firstNumber / secondNumber);
  }
}

/**
* Resets calculator to default state before every new term is entered.
*/
void resetCalculator() {
  firstNumber = secondNumber = 0;
}

/**
* Searches an array for a specific element.
*
* @param Pointer to the needle.
* @param Pointer to the first element in the haystack.
* @return 1 if needle is found in haystack, 0 if the search fails.
*/
int inArray(char *needle, char *haystack) {
  while(*haystack) {
      if(*haystack == *needle) {
        return 1;
      }
      haystack++;
  }
  return 0;
}