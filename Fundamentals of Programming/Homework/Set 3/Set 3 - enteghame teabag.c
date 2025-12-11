#include <stdio.h>

int gcd(int a, int b){
    if(b == 0) return a;
    else return gcd(b, a % b);
}

int main(){
    int n;
    scanf("%d", &n);
    getchar();
    char expression[1024];
    fgets(expression, 1024, stdin);
    int num[n];
    for(int i = 0; i < n; i++) scanf("%d", &num[i]);

    int stack[1024];
    int top = -1;
    int len = 0;
    while(expression[len]) len++;
    // total length of expression is always n+2
    for(int i = len - 1; i>=0; i--){
        if(expression[i] == 'X') stack[++top] = num[--n];
        else{
            int a = stack[top--];
            int b = stack[top--];
            if      (expression[i] == '&') stack[++top] = gcd(a,b);
            else if (expression[i] == '@') stack[++top] = a * b / gcd(a,b);
        }
    }
    printf("%d", stack[top]);
    
}