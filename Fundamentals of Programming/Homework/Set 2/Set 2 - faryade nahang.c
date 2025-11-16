#include <stdio.h>

int main() {
    
    long long int n;
    scanf("%lld", &n);

    long long int i = 2;
    short first = 1;

    while(i*i <= n){
        int power = 0;
           if(n % i == 0){
            while(n % i == 0){
                n = n / i;
                power++;
            }
            if(first == 0) printf(" * ");
            first = 0;
            if(power > 1) printf("%lld^%d", i, power);
            if(power == 1) printf("%lld", i);
            }
            else i++;
    }
        if (n > 1) {
        if (first == 0) printf(" * ");
        printf("%lld", n);
    }


}