#include <stdio.h>
#include <string.h>

double power(double x, int p) {
    double res = 1.0;
    for (int i = 0; i < p; i++)
        res *= x;
    return res;
}

double factorial(int n) {
    double res = 1.0;
    for (int i = 1; i <= n; i++)
        res *= i;
    return res;
}

double sin_t(double x, int n){
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
    double term = power(x, 2*i + 1) / factorial(2*i + 1);
    if (i % 2) term = -term;
    sum += term;
    }
    return sum;
}

double cos_t(double x, int n){
    double sum = 0.0;
    for(int i = 0; i < n; i++){
        double term = power(x, 2*i) / factorial(2*i);
        if(i % 2) term = -term;
        sum += term;
    }
    return sum;
}

double exp_t(double x, int n){
    double sum = 0.0;
    for(int i = 0; i < n; i++){
        double term = power(x, i) / factorial(i);
        sum += term;
    }
    return sum;
}

int main(){
    int n = 0;
    scanf("%d", &n);
    double regs[n]; for(int i = 0; i < n; i++) regs[i] = 0.0;

    #define VALID(r) ((r) >= 0 && (r) < n)

    char operation[100];
    while(scanf("%s", operation) == 1 && strcmp(operation, "end")){
        if(!strcmp(operation, "load")){int reg; scanf("%d", &reg); if(VALID(reg)){scanf("%lf", &regs[reg]);} else printf("INVALID REGISTER NUMBER\n");}
        else if(!strcmp(operation, "print")){int reg; scanf("%d", &reg); if(VALID(reg)){printf("%.4f\n", regs[reg]);} else printf("INVALID REGISTER NUMBER\n");}
        else if(!strcmp(operation, "add")){int reg1, reg2, reg3; scanf("%d %d %d", &reg1, &reg2, &reg3); if(VALID(reg1) && VALID(reg2) && VALID(reg3)){regs[reg3] = regs[reg1] + regs[reg2];} else printf("INVALID REGISTER NUMBER\n");}
        else if(!strcmp(operation, "sub")){int reg1, reg2, reg3; scanf("%d %d %d", &reg1, &reg2, &reg3); if(VALID(reg1) && VALID(reg2) && VALID(reg3)){regs[reg3] = regs[reg1] - regs[reg2];} else printf("INVALID REGISTER NUMBER\n");}
        else if(!strcmp(operation, "mul")){int reg1, reg2, reg3; scanf("%d %d %d", &reg1, &reg2, &reg3); if(VALID(reg1) && VALID(reg2) && VALID(reg3)){regs[reg3] = regs[reg1] * regs[reg2];} else printf("INVALID REGISTER NUMBER\n");}
        else if(!strcmp(operation, "div")){int reg1, reg2, reg3; scanf("%d %d %d", &reg1, &reg2, &reg3); if(VALID(reg1) && VALID(reg2) && VALID(reg3)){if(regs[reg2] != 0.0){regs[reg3] = regs[reg1] / regs[reg2];}} else printf("INVALID REGISTER NUMBER\n");}

        else if(!strcmp(operation, "sin")){int reg1, reg2, m; scanf("%d %d %d", &reg1, &reg2, &m); if(VALID(reg2) && VALID(reg1)){regs[reg2] = sin_t(regs[reg1], m);} else printf("INVALID REGISTER NUMBER\n");}
        else if(!strcmp(operation, "cos")){int reg1, reg2, m; scanf("%d %d %d", &reg1, &reg2, &m); if(VALID(reg2) && VALID(reg1)){regs[reg2] = cos_t(regs[reg1], m);} else printf("INVALID REGISTER NUMBER\n");}
        else if(!strcmp(operation, "exp")){int reg1, reg2, m; scanf("%d %d %d", &reg1, &reg2, &m); if(VALID(reg2) && VALID(reg1)){regs[reg2] = exp_t(regs[reg1], m);} else printf("INVALID REGISTER NUMBER\n");}
        }
    return 0;
}