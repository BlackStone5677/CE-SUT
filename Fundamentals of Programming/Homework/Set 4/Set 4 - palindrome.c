#include <stdio.h>
#include <string.h>

int dp[500][500];

int winner(char s[],int l,int r){
    if(l>r) return 0;
    if(l==r) return 1;
    if(dp[l][r]!=-1) return dp[l][r];

    int i=l,j=r,ok=1;
    while(i<j) if(s[i++]!=s[j--]){ok=0; break;}
    if(ok) return 1;

    i=l+1;j=r;ok=1;
    while(i<j) if(s[i++]!=s[j--]){ok=0; break;}
    if(ok || !winner(s,l+1,r)) return dp[l][r]=1;
    
    i=l;j=r-1;ok=1;
    while(i<j) if(s[i++]!=s[j--]){ok=0; break;}
    if(ok || !winner(s,l,r-1)) return dp[l][r]=1;

    return dp[l][r]=0;
}

int main(){
    int n; scanf("%d",&n); getchar();
    while(n--){
        char s[500]; fgets(s,500,stdin); s[strcspn(s,"\n")]=0;
        int len=strlen(s);
        for(int i=0;i<len;i++) for(int j=0;j<len;j++) dp[i][j]=-1;
        printf("%s\n",winner(s,0,len-1)?"First":"Second");
    }
}