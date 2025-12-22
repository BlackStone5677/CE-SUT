#include <stdio.h>
int find(int p[],int x){return p[x]==x?x:(p[x]=find(p,p[x]));}
int main(){
    int n; scanf("%d",&n); int parent[n];
    for(int i=0;i<n;i++) parent[i]=i;
    for(int i=0;i<n;i++) for(int j=0,c;j<n;j++){scanf("%d",&c); if(c) parent[find(parent,j)]=find(parent,i);}
    int components = 0;
    for(int i=0;i<n;i++) components += (find(parent,i) == i);
    printf("%d", components);
}