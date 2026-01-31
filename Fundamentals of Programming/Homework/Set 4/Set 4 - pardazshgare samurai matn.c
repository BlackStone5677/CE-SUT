#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 600
#define ISL(c) (((c)>='a'&&(c)<='z')||((c)>='A'&&(c)<='Z'))
#define VOW(c) ((c|32)=='a'||(c|32)=='e'||(c|32)=='i'||(c|32)=='o'||(c|32)=='u')

const char *roots[]={"go","run","play","right","light","happy","quick","art","rat","star"};

void rooting(char t[],int *c){
    for(int i=0,n=strlen(t);i<n;){
        if(!ISL(t[i])){i++;continue;}
        int l=i; while(ISL(t[i])) i++; int r=i;
        for(int k=0;k<10;k++)
            for(int s=l,rl=strlen(roots[k]);s+rl<=r;s++)
                if(!strncmp(t+s,roots[k],rl)){
                    memmove(t+l+rl,t+r,n-r+1);
                    memcpy(t+l,roots[k],rl);
                    if(*c>=strlen(t)) *c=strlen(t)-1;
                    i=l+rl; goto next;
                }
        next:;
    }
}

void move(char t[],int a,int *c){
    int n=strlen(t);
    if(*c+a<0||*c+a>=n) puts("Not enough characters.");
    else *c+=a;
}

void add(char t[],char *w,int *c){
    int n=strlen(t),p=*c,l=strlen(w);
    if(ISL(t[p])) while(ISL(t[p])) p++;
    memmove(t+p+l+1,t+p,n-p+1);
    t[p]=' '; memcpy(t+p+1,w,l);
}

void reverse(char t[],int *c){
    if(!ISL(t[*c])) return;
    int l=*c,r=*c;
    while(l&&ISL(t[l-1])) l--;
    while(ISL(t[r+1])) r++;
    for(;l<r;l++,r--){ char x=t[l];t[l]=t[r];t[r]=x; }
}

void wow(char t[]){
    for(int i=0,n=strlen(t);i<n;){
        if(!ISL(t[i])){i++;continue;}
        int v=0,l=0;
        while(ISL(t[i])){v+=VOW(t[i]);l++;i++;}
        if(l>=5&&v>=2){ memmove(t+i+1,t+i,n-i+1); t[i++]='!'; n++; }
    }
}

void uler(char t[],int *c,int u){
    for(int i=*c;ISL(t[i]);i++)
        t[i]+=u?(t[i]>='a'&&t[i]<='z'?-32:0):(t[i]>='A'&&t[i]<='Z'?32:0);
}

void change(char t[],int *c,int a){
    int n=strlen(t);
    if(*c+a>n){ puts("Not enough characters."); return; }
    while(a--){
        char *x=&t[(*c)++];
        if(*x>='a'&&*x<='z') *x=(*x-'a'+1)%26+'a';
        else if(*x>='A'&&*x<='Z') *x=(*x-'A'+1)%26+'A';
    }
}

int main(){
    char t[MAX],cmd[20],arg[40]; int c=0;
    fgets(t,MAX,stdin); t[strcspn(t,"\n")]=0;

    while(scanf("%s",cmd) && strcmp(cmd,"###")){
        if(!strcmp(cmd,"move")||!strcmp(cmd,"add")||!strcmp(cmd,"change")) scanf("%s",arg);
        
        if(!strcmp(cmd,"rooting")) rooting(t,&c);
        else if(!strcmp(cmd,"location")) printf("%d\n",c);
        else if(!strcmp(cmd,"move")) move(t,atoi(arg),&c);
        else if(!strcmp(cmd,"add")) add(t,arg,&c);
        else if(!strcmp(cmd,"reverse")) reverse(t,&c);
        else if(!strcmp(cmd,"WOW")) wow(t);
        else if(!strcmp(cmd,"upper")) uler(t,&c,1);
        else if(!strcmp(cmd,"lower")) uler(t,&c,0);
        else if(!strcmp(cmd,"change")) change(t,&c,atoi(arg));
    }
    puts(t);
}