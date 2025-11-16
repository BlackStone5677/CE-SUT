#include <stdio.h>

unsigned long long x;

int main(){
    unsigned long long left =   0x0101010101010101ULL;
    unsigned long long right =  0x8080808080808080ULL;
    unsigned long long border = 0xFF818181818181FFULL;

    scanf("%llu", &x);

    // Unvisited Cells during Flood-Fill
    unsigned long long unvisited = ~x;

    int count = 0;

    while(unvisited){
        
        // The cell where Flood-Fill begins at(the first 0 bit of x)
        unsigned long long seed = unvisited & (-unvisited);
        // All the cells near seed which are to be Flood-Filled
        unsigned long long region = seed;

        while(seed){
            region |= seed;
            seed = (((seed << 1) & ~left) | ((seed >> 1) & ~right) | (seed << 8) | (seed >> 8)) & unvisited & ~region;
            
        // To see the progression of the region in each step

        // printf("\n");
        // for(int i = 0; i < 8; i++){
        //     for(int j = 0; j < 8; j++) printf("%d", (region >> i*8 + j) & 1);
        // printf("\n");
        // }

        }

        unvisited ^= region;

        // To see the progression of unvisited

        // printf("\n");
        // for(int i = 0; i < 8; i++){
        //     for(int j = 0; j < 8; j++) printf("%d", (unvisited >> i*8 + j) & 1);
        // printf("\n");
        // }
        
        if (!(region & border)) count++;

    }

    printf("%d\n", count);
    return 0;
}