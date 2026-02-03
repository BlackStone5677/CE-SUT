#include <stdlib.h>

int* aggregator(int* a, int* b) {
    int len_a = 1; long long sum_a = 0;
    int* p_a = a;
    while(*p_a != sum_a){sum_a += *p_a; p_a++; len_a++;}
    
    int len_b = 1; long long sum_b =0;
    int* p_b = b;
    while(*p_b != sum_b){sum_b += *p_b; p_b++; len_b++;}

    int *arr = (int*)malloc(sizeof(int)*(len_a+len_b));
    p_a = a; p_b = b; int* p = arr;
    int i = 0, j = 0;
    while(i < len_a || j < len_b){
        if(i < len_a){*p = *p_a; p++; p_a++; i++;}
        if(j < len_b){*p = *p_b; p++; p_b++; j++;}
    }
    return arr;
}