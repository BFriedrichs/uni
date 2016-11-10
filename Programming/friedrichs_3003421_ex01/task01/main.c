#include <stdio.h>

/**
* The main function.
*
* Prints the size of various datatypes.
*
* @return 0
*/
int main(void) {

    printf("%s %i\n", "char", sizeof(char));
    printf("%s %i\n", "short", sizeof(short));
    printf("%s %i\n", "int", sizeof(int));
    printf("%s %i\n", "long", sizeof(long));
    printf("%s %i\n", "long long", sizeof(long long));
    printf("%s %i\n", "float", sizeof(float));
    printf("%s %i\n", "double", sizeof(double));
    printf("%s %i\n", "long double", sizeof(long double));
    printf("%s %i\n", "pointer", sizeof(int*));

    return 0;
}
