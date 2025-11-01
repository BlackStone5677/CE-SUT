// Takes a number and turns it to its two's complement binary representation.
#include <stdio.h>
#include <math.h>

int binarify(int num) {
    int bits = 8; // Can change later.
    char bit[bits];
    int binary = 0;
    for (int i = bits - 1; i >= 0, i--;) {
        bit[i] = (num >> i) & 1; // Shift right once and mask with 1(grab only the first bit)
        binary += bit[i] * pow(10,i);
    }

    return binary;

}

int main() {

    int num;
    int valid = 0;

    while(!valid) {
        printf("Please enter a number to turn it to its binary counterpart: ");
        valid = scanf("%d", &num);

        if (!valid) {
            printf("What you entered %d, was not a number. Please try again \n", num);
            while (getchar() != '\n'); // Clear invalid input from buffer
        }
        
    }

    printf("You entered: %d as your number. \n", num);

    int binary = binarify(num);

    printf("It is represented as %u in binary. \n", binary);

    return 0;
}