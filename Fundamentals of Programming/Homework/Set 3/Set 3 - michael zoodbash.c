#include <stdio.h>

unsigned long long mask(int i, int j, int n){
    unsigned long long mask = 0ULL;
    mask |= 1ULL << (i * n + j);
    if(i>0) mask |= 1ULL << ((i - 1) * n + j);
    if(i<n-1) mask |= 1ULL << ((i + 1) * n + j);
    if(j>0) mask |= 1ULL << (i * n + (j - 1));
    if(j<n-1) mask |= 1ULL << (i * n + (j + 1));
    return mask;
}

int main(){
    int n;
    scanf("%d\n", &n);
    unsigned long long board = 0ULL;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            char c;
            scanf("%c", &c);
            board |= ((c == '+' || c == '*' || c == '#') ? 1ULL : 0ULL) << ((i * n) + j);
        }
        getchar();
    }
    
    for(int top = 0; top < (1<<n); top++){
        unsigned long long temp = board;
        for(int j = 0; j<n; j++){
            if((top >> j) & 1ULL) temp ^= mask(0,j,n);
        }
        for(int i = 0; i<n-1; i++){
            for(int j = 0; j<n; j++){
                if((temp >> (i*n+j)) & 1ULL) temp ^= mask(i+1,j,n);
            }
        }
        if(temp == 0){
            board = 0ULL;
            break;
    }
    }
    if(board) printf("Micheal can't escape today, he has at most 26 days left!");
    else printf("Finally, Micheal can escape from Iran :)");
}
