#include <stdio.h>

int count = 0;

int is_prime(int k) {
    return (k == 2 || k == 3 || k == 5 || k == 7 || k == 11 || k == 13 || k == 17 || k == 19 || k == 23 || k == 29 || k == 31);
}

void backtrack(int arr[], int pos, int used, int n) {
    if (pos == n) {
        if (is_prime(arr[n - 1] + arr[0]))
            count++;
        return;
    }

    for(int num = 2; num <= n; num++){
        if(!(used & (1 << num))){
            if(is_prime(arr[pos - 1] + num)){ 
                arr[pos] = num;
                backtrack(arr, pos + 1, used | (1 << num), n);
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    arr[0] = 1;

    backtrack(arr, 1, 1 << 1, n);
    printf("%d\n", count);
}
