#include <stdio.h>

int n;

int main(){
    scanf("%d", &n);
    while(n > 0){
        unsigned long long x;
        scanf("%llu", &x);

        // Check Vertical Symmetry
        int vertical = 1;
        for(int i = 0; i < 8; i++){
            unsigned long long row = (x >> (i*8)) & ((1ULL << 8) - 1);
            unsigned long long mirror = 0;
            for(int j = 0; j < 8; j++){
                mirror = mirror | (((row >> j) & 1ULL) << (7-j));
            }
            if(mirror != row){vertical = 0; break;}
        }

        // Check Horizontal Symmetry
        int horizontal = 1;
        for(int i = 0; i < 4; i++){
            unsigned long long row_top = (x >> (i+4)*8) & ((1ULL << 8) - 1);
            unsigned long long row_bottom = (x >> (3-i)*8) & ((1ULL << 8) - 1);
            if(row_bottom != row_top){horizontal = 0; break;}
        }

        // Check Diagonal Symmetry
        int main_diagonal = 1;
        for(int i = 0; i < 8; i++){
            for(int j = i+1; j < 8; j++){
                int bit1 = (x >> (i*8 + j)) & 1ULL; // row i, col j
                int bit2 = (x >> (j*8 + i)) & 1ULL; // row j, col i
                if(bit1 != bit2){main_diagonal = 0; break;}
            }
        }

        // Check Other Diagonal Symmetry
        int off_diagonal = 1;
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                int bit1 = (x >> (i*8 + j)) & 1ULL; // row i, col j
                int bit2 = (x >> ((7-j)*8 + 7-i)) & 1ULL; // row 7-j, col 7-i
                if(bit1 != bit2){off_diagonal = 0; break;}
            }
        }

        // Printing Output
        int count = vertical + horizontal + main_diagonal + off_diagonal;
        printf("%d ", count);
        if(count == 0) printf("-");
        if(vertical) printf("V");
        if(horizontal) printf("H");
        if(main_diagonal) printf("A");
        if(off_diagonal) printf("B");
        printf("\n");
        n--;
    }
}