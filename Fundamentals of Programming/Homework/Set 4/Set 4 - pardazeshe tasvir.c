#include <stdio.h>

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    int matrix[m][n];
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++) scanf("%d", &matrix[i][j]);
    }
    int k, p;
    scanf("%d %d", &k, &p);
    int kernel[k][p];
    for(int i = 0; i < k; i++){
        for(int j = 0; j < p; j++) scanf("%d", &kernel[i][j]);
    }
    int padding, stride;
    scanf("%d %d", &padding, &stride);

    for(int i = -padding; i < m + padding - k + 1; i += stride){
        for(int j = -padding; j < n + padding - p + 1; j += stride){
            int sum = 0;
            for(int r = 0; r < k; r++){
                for(int s = 0; s < p; s++) if(i+r >= 0 && i+r < m && j+s >= 0 && j+s < n) sum += matrix[i+r][j+s] * kernel[r][s];
            }
            printf("%d ", sum);
        }
        printf("\n");
    }
}