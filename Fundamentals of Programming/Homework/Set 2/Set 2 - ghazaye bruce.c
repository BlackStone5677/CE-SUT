#include <stdio.h>

int m;
long long n;

int main(){
    scanf("%d", &m);

    while(m > 0){
        scanf("%lld", &n);
        while(n != 0){
        if(n % 3 == 0){
            printf("Oooh that’s good! \n");
            break;
        }
        n = n / 10;
        }
        if(n == 0) printf("Oooh delom shikast! \n");
        m--;
        
    }
}