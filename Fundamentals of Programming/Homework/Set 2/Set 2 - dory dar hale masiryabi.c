#include <stdio.h>

int n;
unsigned long long k;

int main(){
    scanf("%d", &n);

    if (n == -1) {
        printf("Congrats, Dory is home.");
        return 0;
    }

    scanf("%llu", &k);

    if(n <= 2) {
        printf("No");
        return 0;
    }

    int found = 0;

    // Check rows for 3 consecutive 1's
    for(int i = n; i > 0; i--){
        unsigned long long row = (k >> ((i-1)*n)) & ((1ULL << n) - 1);
        if((row & (row >> 1) & (row >> 2)) != 0) found = 1;
    }

    // Check columns for 3 consecutive 1's
    for(int j = n; j > 0; j--){
        unsigned long long column = 0;
        for(int i = n; i > 0; i--){
            column |= ((k >> ((i-1)*n + j - 1)) & 1ULL) << (n - i);
        }
        if((column & (column >> 1) & (column >> 2)) != 0) found = 1;
    }

    // Check all diagonals of length >= 3
    // '\' diagonals (top-left to bottom-right)
    for(int startRow = 0; startRow <= n - 3; startRow++){
        for(int startCol = 0; startCol <= n - 3; startCol++){
            unsigned long long diag = 0;
            for(int i = 0; i < n - startRow && i < n - startCol; i++){
                diag |= ((k >> ((n - 1 - (startRow + i))*n + (n - 1 - (startCol + i)))) & 1ULL) << (n - 1 - i);
            }
            if((diag & (diag >> 1) & (diag >> 2)) != 0) found = 1;
        }
    }

    // '/' diagonals (top-right to bottom-left)
    for(int startRow = 0; startRow <= n - 3; startRow++){
        for(int startCol = 2; startCol < n; startCol++){
            unsigned long long diag = 0;
            for(int i = 0; i < n - startRow && i <= startCol; i++){
                diag |= ((k >> ((n - 1 - (startRow + i))*n + (n - 1 - (startCol - i)))) & 1ULL) << (n - 1 - i);
            }
            if((diag & (diag >> 1) & (diag >> 2)) != 0) found = 1;
        }
    }

    if(found) printf("Yes");
    else printf("No");

    return 0;
}
