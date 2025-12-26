#include <stdio.h>

int f(int*p,int x){return p[x]==x?x:(p[x]=f(p,p[x]));}

int main(){
    int n,c;scanf("%d",&n);int p[n];
    for(int i=0;i<n;i++) p[i]=i;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) scanf("%d",&c),c&&(p[f(p,j)]=f(p,i));
    for(int i=0;i<n;i++) printf("%d ",f(p,i));
}