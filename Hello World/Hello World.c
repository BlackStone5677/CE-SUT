// First file, to test out printing capabilities of C
#include <stdio.h>

int main() {

    char msg[50];

    printf("What do you want to tell the world? ");
    fgets(msg, 50, stdin);

    printf("Here's your message: %s \n", msg);
    

    int num;

    printf("Tell me a number to see in binary. ");
    scanf("%d", &num);

    printf("This is your number: %d \n", num);

    
    getchar(); getchar();
    return 0;
}