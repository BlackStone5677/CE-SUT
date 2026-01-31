#include <stdio.h>

void swapNumbers(int *x, int *y, int *z);

int main() {
    int e1, e2, e3;

    scanf("%d %d %d", &e1, &e2, &e3);

    swapNumbers(&e1, &e2, &e3);

    printf("%d %d %d", e1, e2, e3);

    return 0;
}
// Use the functionality of XOR to swap values.
void swapNumbers(int *x, int *y, int *z){
    *x ^= *y;
    *y ^= *x;
    *x ^= *y;
    *x ^= *z;
    *z ^= *x;
    *x ^= *z;
}
