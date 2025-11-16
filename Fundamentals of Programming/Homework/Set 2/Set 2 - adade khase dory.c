#include <stdio.h>

int m;
long long n;
long long output = 0;

int main(){


    scanf("%d", &m);
    while(m > 0){
        
        scanf("%d", &n);
        int sum = 0;
        long long original = n;
        int digit = 0;
        if(n<0) n = -1*n;
        while(n != 0){
            digit = n % 10;
            sum += digit;
            n = n / 10;
        }
        long long power = sum;
        for(int i = 1; i <= 5; i++){
            if(original == power){
                output = (output + (1 << (m - 1)));
                break;}
            power = power * sum;
        }
        m--;
    }
    printf("%lld", output);
}