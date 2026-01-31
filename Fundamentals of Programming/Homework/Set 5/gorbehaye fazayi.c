#include <stdio.h>
#include <string.h>

void transpose(int n, int matrix[n][n]){
    for(int i = 0; i < n; i++)
        for(int j = 0; j < i; j++){
            int t = matrix[i][j]; matrix[i][j] = matrix[j][i]; matrix[j][i] = t;
        }
}

// dir = 1: ccw, dir = 0: cw
void rotate(int dir, int n, int matrix[n][n]){
    transpose(n, matrix);
    if(!dir)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n/2; j++){int t = matrix[i][j]; matrix[i][j] = matrix[i][n-1-j]; matrix[i][n-1-j] = t;}
    else
        for(int j = 0; j < n; j++)
            for(int i = 0; i < n/2; i++){int t = matrix[i][j]; matrix[i][j] = matrix[n-1-i][j]; matrix[n-1-i][j] = t;}
}

void saddle(int n, int matrix[n][n]){
    for(int i=0;i<n;i++){
        int min_val=matrix[i][0];
        for(int j=1;j<n;j++) if(matrix[i][j]<min_val) min_val=matrix[i][j];
        for(int j=0;j<n;j++) if(matrix[i][j]==min_val){
            int k; for(k=0;k<n;k++) if(matrix[k][j]>min_val) break;
            if(k==n) printf("(%d, %d)", i+1, j+1);
        }
    }
    printf("\n");
}

void swap(int cols, int a, int b, int n, int matrix[n][n]){
    if(a < 1 || b < 1 || a > n || b > n){ printf("invalid numbers for swapping.\n"); return; }
    for(int k = 0; k < n; k++){
        if(cols){ int t = matrix[k][a-1]; matrix[k][a-1] = matrix[k][b-1]; matrix[k][b-1] = t; }
        else{int t = matrix[a-1][k]; matrix[a-1][k] = matrix[b-1][k]; matrix[b-1][k] = t;}
    }
}

int main(){
    int n; scanf("%d", &n);
    int matrix[n][n], visited[100][100] = {0};
    int i = 0, j = 0, di = 0, dj = 1;

    for(int k = 0; k < n*n; k++){
        scanf("%d", &matrix[i][j]); visited[i][j] = 1;
        if(i+di<0 || i+di>=n || j+dj<0 || j+dj>=n || visited[i+di][j+dj]){int t = di; di = dj; dj = -t;}
        i += di; j += dj;
    }

    char operation[20];
    while(scanf("%s", operation) && strcmp(operation, "end")){
        if(!strcmp(operation, "transpose")) transpose(n, matrix);
        else if(!strcmp(operation, "rotate")){char arg[20]; scanf("%s", arg); rotate(strcmp(arg, "clockwise"), n, matrix);}
        else if(!strcmp(operation, "saddle")) saddle(n, matrix);
        else if(!strcmp(operation, "swap")){char arg[20]; int a, b; scanf("%s %d and %d", arg, &a, &b); swap(strcmp(arg, "rows"), a, b, n, matrix);}
    }

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++) printf("%d ", matrix[i][j]);
        printf("\n");
    }
}