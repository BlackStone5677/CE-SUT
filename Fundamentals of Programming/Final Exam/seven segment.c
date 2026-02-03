#include <stdio.h>

int seg[10][7] = {
{1,1,1,1,1,1,0}, //0
{0,1,1,0,0,0,0}, //1
{1,1,0,1,1,0,1}, //2
{1,1,1,1,0,0,1}, //3
{0,1,1,0,0,1,1}, //4
{1,0,1,1,0,1,1}, //5
{1,0,1,1,1,1,1}, //6
{1,1,1,0,0,0,0}, //7
{1,1,1,1,1,1,1}, //8
{1,1,1,1,0,1,1}  //9
};

void print_digit(int d, int row){
    int *s = seg[d];
    if(row==0){
        printf(" ");
        for(int i=0;i<5;i++) printf("%c", s[0]?'*':' ');
        printf(" ");
    }else if(row>=1 && row<=3){
        printf("%c", s[5]?'*':' ');
        for(int i=0;i<5;i++) printf(" ");
        printf("%c", s[1]?'*':' ');
    }else if(row==4){
        printf(" ");
        for(int i=0;i<5;i++) printf("%c", s[6]?'*':' ');
        printf(" ");
    }else if(row>=5 && row<=7){
        printf("%c", s[4]?'*':' ');
        for(int i=0;i<5;i++) printf(" ");
        printf("%c", s[2]?'*':' ');
    }else if(row==8){
        printf(" ");
        for(int i=0;i<5;i++) printf("%c", s[3]?'*':' ');
        printf(" ");
    }
}

int main(){
    char str[1001];
    scanf("%s", str);
    int len = 0;
    while(str[len]) len++;
    for(int r=0;r<9;r++){
        for(int i=0;i<len;i++){
            print_digit(str[i]-'0', r);
            if(i<len-1) printf("   ");
        }
        printf("\n");
    }
    return 0;
}