#include <stdio.h>

void swapNumbers(int *x, int *y);

int main() {
    int e1, e2;

    scanf("%d %d", &e1, &e2);

    swapNumbers(&e1, &e2);

    printf("%d %d", e1, e2);

    return 0;
}

void swapNumbers(int *x, int *y){
    *x ^= *y;
    *y ^= *x;
    *x ^= *y;
}
