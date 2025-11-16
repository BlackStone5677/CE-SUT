#include <stdio.h>

int m;
long long n;

int main(){
    scanf("%d", &m);

    while(m > 0){
        int mirror = 0;
        int digit = 0;
        scanf("%lld", &n);
        long long original = n;
        while(n > 0){
            digit = n % 10;
            mirror = mirror * 10 + digit;
            n = n / 10;
        }
        if(mirror == original) printf("Yes \n");
        else printf("No \n");
        m--;
    }
}