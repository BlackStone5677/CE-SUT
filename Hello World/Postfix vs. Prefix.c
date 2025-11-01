// This is to show the difference between Prefixing and Postfixing inc/decrements in C.
#include <stdio.h>

int main() {

    int i = 5;

    printf("Using i--: \n");
    printf("Value printed: %d \n", i--); // postfixing: prints 5, then i becomes 4
    printf("Value of i now: %d", i);

    printf("\n \n");
    i = 5;

    printf("Using --i: \n");
    printf("Value printed: %d \n", --i); // prefixing: turns i into 4, then prints
    printf("Value of i now: %d", i);

    return 0;
}