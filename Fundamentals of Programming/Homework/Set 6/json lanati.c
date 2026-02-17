#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { INT, STR, OBJ } T;

typedef struct J {
    char* k;
    T t;
    union {
        int i;
        char* s;
        struct J** c;
    };
    int n;
} J;

char* skip(char* s) { while(*s==' '||*s=='\n'||*s=='\t'||*s=='\r') s++; return s; }
int isdigit_c(char c) { return c>='0' && c<='9'; }

char* pstr(char* s, char** out) {
    s++;
    char* t=s;
    while(*s!='"') s++;
    *out=strndup(t,s-t);
    return s+1;
}

char* pint(char* s,int* out) {
    *out=0;
    while(isdigit_c(*s)) *out = *out*10 + (*s++-'0');
    return s;
}

char* pval(char* s,J* j); // forward

char* pobj(char* s,J** out) {
    s++;
    J* j = calloc(1,sizeof(J));
    j->c=NULL; j->n=0;
    while(*s) {
        s=skip(s);
        if(*s=='}'){ s++; break; }
        char* key;
        s=pstr(s,&key);
        s=skip(s); s++; // skip ':'
        j->c=realloc(j->c,sizeof(J*)*(j->n+1));
        J* child=calloc(1,sizeof(J));
        child->k=key;
        s=pval(s,child);
        j->c[j->n++]=child;
        s=skip(s);
        if(*s==',') s++;
    }
    j->t=OBJ;
    *out=j;
    return s;
}

char* pval(char* s,J* j) {
    s=skip(s);
    if(*s=='{') {
        J* obj=NULL;
        s=pobj(s,&obj);
        j->t=OBJ;
        j->c=obj->c;
        j->n=obj->n;
        free(obj); // free temporary wrapper
        return s;
    } else if(*s=='"') { j->t=STR; return pstr(s,&j->s); }
    else { j->t=INT; return pint(s,&j->i); }
}

int depth(J* j) {
    if(j->t!=OBJ) return 1;
    int m=0;
    for(int i=0;i<j->n;i++){
        int d=depth(j->c[i]);
        if(d>m) m=d;
    }
    return m+1;
}

J* find(J* j,char* path) {
    for(char* t=path;;){
        char* dot=strchr(t,'.');
        int len = dot ? dot-t : strlen(t);
        if(j->t!=OBJ) return NULL;
        J* f=NULL;
        for(int i=0;i<j->n;i++)
            if(strlen(j->c[i]->k)==len && strncmp(j->c[i]->k,t,len)==0){ f=j->c[i]; break; }
        if(!f) return NULL;
        if(!dot) return f;
        j=f; t=dot+1;
    }
}

int main(){
    char fn[128]; scanf("%s",fn);
    FILE* f=fopen(fn,"r"); fseek(f,0,SEEK_END); long sz=ftell(f); fseek(f,0,SEEK_SET);
    char* js=malloc(sz+1); fread(js,1,sz,f); fclose(f); js[sz]=0;

    J* root=NULL;
    pobj(js,&root);

    char q[128];
    while(scanf(" %[^\n]",q)==1){
        if(!strcmp(q,"exit")) break;
        else if(!strcmp(q,"depth")) printf("%d\n",depth(root)-1);
        else if(!strncmp(q,"typeof ",7)){
            J* n=find(root,q+7);
            if(!n) printf("No value found for this address!!\n");
            else if(n->t==INT) printf("INT\n");
            else if(n->t==STR) printf("STRING\n");
            else printf("OBJECT\n");
        } else if(!strncmp(q,"valueof ",8)){
            J* n=find(root,q+8);
            if(!n) printf("No value found for this address!!\n");
            else if(n->t==INT) printf("%d\n",n->i);
            else if(n->t==STR) printf("%s\n",n->s);
            else printf("I can not print objects!\n");
        }
    }
}
