#include <stdio.h>

int m, n;
unsigned long long k;

int main(){
    scanf("%d %d", &m, &n);
    scanf("%llu", &k);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++) printf("%d", (k >> i*n + j) & 1);
        printf("\n");
    }

}