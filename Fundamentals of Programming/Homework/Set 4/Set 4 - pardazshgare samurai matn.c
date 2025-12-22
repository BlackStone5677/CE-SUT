#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *roots[] = {"go","run","play","right","light","happy","quick","art","rat","star"};
const char *delims = "0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ \t\n\r\v\f";

int is_delim(char c){
    for(int i=0; delims[i]; i++)
        if(c == delims[i]) return 1;
    return 0;
}

int is_letter(char c){
    return (c>='a'&&c<='z') || (c>='A'&&c<='Z');
}

int is_vowel(char c){
    c |= 32;
    return c=='a'||c=='e'||c=='i'||c=='o'||c=='u';
}

void rooting(char text[], int *cursor){
    int i=0;
    while(text[i]){
        if(!is_letter(text[i])){ i++; continue; }

        int l=i;
        while(text[i] && is_letter(text[i])) i++;
        int r=i;

        for(int k=0;k<10;k++){
            int rl = strlen(roots[k]);
            for(int s=l; s+rl<=r; s++){
                if(!strncmp(text+s, roots[k], rl)){
                    memmove(text+l+rl, text+r, strlen(text+r)+1);
                    memcpy(text+l, roots[k], rl);
                    if(*cursor > strlen(text)-1)
                        *cursor = strlen(text)-1;
                    i = l + rl;
                    goto done;
                }
            }
        }
        done:;
    }
}

void move(char text[], int amount, int *cursor){
    int n = strlen(text);
    if(*cursor + amount < 0 || *cursor + amount > n-1){
        printf("Not enough characters.\n");
        return;
    }
    *cursor += amount;
}

void add(char text[], char *word, int *cursor){
    int n = strlen(text), w = strlen(word), p = *cursor;

    if(is_letter(text[p])){
        int end=p;
        while(end<n && is_letter(text[end])) end++;

        memmove(text+end+w+1, text+end, n-end+1);
        text[end]=' ';
        memcpy(text+end+1, word, w);

        if(end+w+1 < strlen(text) && is_letter(text[end+w+1])){
            memmove(text+end+w+2, text+end+w+1, strlen(text)-(end+w));
            text[end+w+1]=' ';
        }
    }else{
        memmove(text+p+1+w, text+p+1, n-p);
        memcpy(text+p+1, word, w);

        if(p+1+w < strlen(text) && is_letter(text[p+1+w])){
            memmove(text+p+2+w, text+p+1+w, strlen(text)-(p+w));
            text[p+1+w]=' ';
        }
    }
}

void reverse(char text[], int *cursor){
    if(!is_letter(text[*cursor])) return;

    int l=*cursor, r=*cursor;
    while(l>0 && is_letter(text[l-1])) l--;
    while(text[r+1] && is_letter(text[r+1])) r++;

    while(l<r){
        char t=text[l];
        text[l++]=text[r];
        text[r--]=t;
    }
}

void wow(char text[]){
    int i=0;
    while(text[i]){
        if(!is_letter(text[i])){ i++; continue; }

        int l=i, v=0, len=0;
        while(text[i] && is_letter(text[i])){
            v += is_vowel(text[i]);
            len++;
            i++;
        }

        if(len>=5 && v>=2){
            memmove(text+i+1, text+i, strlen(text+i)+1);
            text[i]='!';
            i++;
        }
    }
}

void uler(char text[], int *cursor, int upper){
    int i=*cursor;
    while(text[i] && is_letter(text[i])){
        if(upper && text[i]>='a'&&text[i]<='z') text[i]-=32;
        if(!upper && text[i]>='A'&&text[i]<='Z') text[i]+=32;
        i++;
    }
}

void change(char text[], int *cursor, int amount){
    int n=strlen(text);
    if(*cursor + amount > n-1){
        printf("Not enough characters.\n");
        return;
    }
    for(int i=0;i<amount;i++){
        char *c=&text[*cursor];
        if(*c>='a'&&*c<='z') *c=(*c-'a'+1)%26+'a';
        else if(*c>='A'&&*c<='Z') *c=(*c-'A'+1)%26+'A';
        (*cursor)++;
    }
}

int main(){
    char text[600];
    int cursor=0;
    fgets(text,600,stdin);
    text[strcspn(text,"\n")]=0;

    char cmd[20], arg[40];
    while(scanf("%s",cmd) && strcmp(cmd,"###")){
        if(!strcmp(cmd,"move")||!strcmp(cmd,"change")||!strcmp(cmd,"add"))
            scanf("%s",arg);

        if(!strcmp(cmd,"rooting")) rooting(text,&cursor);
        else if(!strcmp(cmd,"location")) printf("%d\n",cursor);
        else if(!strcmp(cmd,"move")) move(text,atoi(arg),&cursor);
        else if(!strcmp(cmd,"add")) add(text,arg,&cursor);
        else if(!strcmp(cmd,"reverse")) reverse(text,&cursor);
        else if(!strcmp(cmd,"WOW")) wow(text);
        else if(!strcmp(cmd,"upper")) uler(text,&cursor,1);
        else if(!strcmp(cmd,"lower")) uler(text,&cursor,0);
        else if(!strcmp(cmd,"change")) change(text,&cursor,atoi(arg));
    }

    printf("%s",text);
}
