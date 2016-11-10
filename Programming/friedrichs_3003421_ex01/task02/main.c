#include <stdio.h>

int sum2nd(int *ptr, int first, int second, int third);

/**
* The main function.
*
* Prints the size of the second column for 2 cubes
*
* @return 0
*/
int main(void) {
    int cube1[3][2][4] = { {{1,2,3,4}}, {{2,3}, {4,6,8,10}}, {{3,4,5,6}, {6,8,10}} };
    int cube2[2][3][3] = { {{9,8,7}, {6}, {5,4}}, {{3,2}, {1,2,3}, {4}} };

    int sum = sum2nd(&cube1[0][0][0], 3, 2, 4);
    printf("%i\n", sum);

    sum = sum2nd(&cube2[0][0][0], 2, 3, 3);
    printf("%i\n", sum);

    return 0;
}

/**
* Returns the sum of all values in the second column.
*
* @param Pointer to a cube.
* @param Depth of the "cube".
* @param Row count of the "cube".
* @param Column count of the "cube".
* @return Sum of all values in the second column.
*/
int sum2nd(int *ptr, int first, int second, int third) {
  int sum = 0;

  ptr++; // initial offset by 4 byte for the second column

  for(int i = 0; i < first; i++) {
    for(int j = 0; j < second; j++) {
      sum += *ptr; // add value in second column to sum
      ptr += third; // increase pointer by 16 to land
    }
  }
  return sum;
}