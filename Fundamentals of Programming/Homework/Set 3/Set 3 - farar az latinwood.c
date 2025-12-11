#include <stdio.h>

int n;
int square[18][18], row_has[18][18], column_has[18][18];

int solve(int row, int column){
    if(row == n) return 1;
    if(column == n) return solve(row + 1, 0);

    if(square[row][column] != 0) return solve(row, column + 1);

    for(int k = 1; k <= n; k++){
        if(!row_has[row][k-1] && !column_has[column][k-1]){
            square[row][column] = k;
            row_has[row][k-1] = column_has[column][k-1] = 1;
            if(solve(row, column + 1)) return 1;
            square[row][column] = 0;
            row_has[row][k-1] = column_has[column][k-1] = 0;
        }
    }
    return 0;
}

int main(){
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &square[i][j]);
            row_has[i][j] = column_has[i][j] = 0;
        }
    }

    // mark pre-filled numbers
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(square[i][j] != 0){
                row_has[i][square[i][j]-1] = 1;
                column_has[j][square[i][j]-1] = 1;
            }
        }
    }

    if(solve(0, 0)){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++) printf("%d ", square[i][j]);
            printf("\n");
        }
    } else {
        printf("Escape is impossible!!\n");
    }
}
