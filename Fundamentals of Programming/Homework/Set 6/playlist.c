#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct{
    char name[100];
    char artist[100];
    int duration;
    int isFavorite;
} Song;

#define FILE_MAIN "playlist.dat"
#define FILE_OUT "output.txt"

void logg(const char*s){
    FILE *o=fopen(FILE_OUT,"a");
    if(o){fprintf(o,"%s\n",s); fclose(o);}
}

Song* load(int* n){
    FILE *f=fopen(FILE_MAIN,"rb");
    if(!f){*n=0; return NULL;}
    fseek(f,0,SEEK_END);
    long sz=ftell(f); rewind(f);
    *n=sz/sizeof(Song);
    if(*n==0){fclose(f); return NULL;}
    Song* arr=malloc(sz);
    fread(arr,sizeof(Song),*n,f);
    fclose(f);
    return arr;
}

void save(Song* arr,int n){
    FILE *f=fopen(FILE_MAIN,"wb");
    if(f){fwrite(arr,sizeof(Song),n,f); fclose(f);}
}

int timech(const char *s){
    if(!s || !*s) return -1;
    int min, sec;
    if(sscanf(s,"%d:%d",&min,&sec)==2){
        if(min<0||sec<0||sec>=60) return -1;
        return min*60+sec;
    }
    for(int i=0;s[i];i++) if(!isdigit((unsigned char)s[i])) return -1;
    if(sscanf(s,"%d",&min)!=1||min<0) return -1;
    return min;
}

void add(char* n,char* a,char* d){
    int t=timech(d);
    if(t<0){char b[256]; sprintf(b,"Invalid duration format: %s",d); logg(b); return;}
    int c; Song* s=load(&c);
    s=realloc(s,sizeof(Song)*(c+1));
    strcpy(s[c].name,n); strcpy(s[c].artist,a); s[c].duration=t; s[c].isFavorite=0;
    save(s,c+1);
    char b[256]; sprintf(b,"Song added: %s by %s",n,a); logg(b);
    free(s);
}

void delete_song(char* name){
    int c,nc=0,found=0;
    Song* s=load(&c);
    if(!s){char b[256]; sprintf(b,"Song not found: %s",name); logg(b); return;}
    for(int i=0;i<c;i++){
        if(strcmp(s[i].name,name)!=0) s[nc++]=s[i];
        else found=1;
    }
    if(found){save(s,nc); char b[256]; sprintf(b,"Deleted: %s",name); logg(b);}
    else {char b[256]; sprintf(b,"Song not found: %s",name); logg(b);}
    free(s);
}

void star(char* name,int fav){
    int c; Song* s=load(&c); if(!s) return;
    for(int i=0;i<c;i++) if(strcmp(s[i].name,name)==0){s[i].isFavorite=fav; save(s,c); char b[256]; sprintf(b,"%s: %s",fav?"Starred":"Unstarred",name); logg(b); break;}
    free(s);
}

void list(int fav){
    int c, found=0; Song* s=load(&c); if(!s){logg(fav?"No favorites found.":"Playlist is empty."); free(s); return;}
    FILE* o=fopen(FILE_OUT,"a");
    for(int i=0;i<c;i++) if(!fav||s[i].isFavorite){fprintf(o,"%s | %s | %d | %s\n",s[i].name,s[i].artist,s[i].duration,s[i].isFavorite?"Favorite":"Normal"); found=1;}
    if(!found) fprintf(o,"%s\n",fav?"No favorites found.":"Playlist is empty.");
    fclose(o); free(s);
}

static int sort_mode;
int cmp(const void* a,const void* b){
    const Song* x=a; const Song* y=b;
    if(sort_mode==0){int c=strcmp(x->name,y->name); return c?c:strcmp(x->artist,y->artist);}
    if(sort_mode==1){int c=strcmp(x->artist,y->artist); return c?c:strcmp(x->name,y->name);}
    if(x->duration!=y->duration) return x->duration - y->duration;
    int c=strcmp(x->artist,y->artist); return c?c:strcmp(x->name,y->name);
}

void sort_playlist(){
    int n; Song* arr=load(&n); if(!arr) return;
    qsort(arr,n,sizeof(Song),cmp); save(arr,n);
    logg(sort_mode==0?"Sorted by name.":sort_mode==1?"Sorted by artist.":"Sorted by duration.");
    free(arr);
}

void playlist_signature(){
    int c; Song* s=load(&c); unsigned int sig=0;
    for(int i=0;i<c;i++){
        unsigned int hn=0,ha=0;
        for(int j=0;s[i].name[j];j++) hn+=(unsigned char)s[i].name[j]*(j+1);
        for(int j=0;s[i].artist[j];j++) ha+=(unsigned char)s[i].artist[j]*(j+1);
        unsigned int h=31*hn+17*ha+13*s[i].duration+7*s[i].isFavorite;
        sig^=h<<(i%16);
    }
    char b[256]; sprintf(b,"Playlist signature: %u",sig); logg(b);
    free(s);
}

void playlist_entropy(){
    int c; Song* s=load(&c); if(!s){logg("Playlist entropy: 0.000"); free(s); return;}
    typedef struct{char artist[100]; int count;} A; A a[1024]; int k=0;
    for(int i=0;i<c;i++){
        int f=0; for(int j=0;j<k;j++) if(strcmp(a[j].artist,s[i].artist)==0){a[j].count++; f=1; break;}
        if(!f){strcpy(a[k].artist,s[i].artist); a[k].count=1; k++;}
    }
    double H=0; for(int i=0;i<k;i++){double p=(double)a[i].count/c; H-=p*log2(p);}
    char b[256]; sprintf(b,"Playlist entropy: %.3f",H); logg(b);
    free(s);
}

int main(){
    char cmd[256];
    while(fgets(cmd,sizeof(cmd),stdin)){
        cmd[strcspn(cmd,"\n")]=0;
        if(!strncmp(cmd,"add ",4)){char n[100],a[100],d[20]; if(sscanf(cmd+4,"%99s %99s %19s",n,a,d)==3) add(n,a,d); else logg("Invalid add command.");}
        else if(!strncmp(cmd,"delete ",7)){char n[100]; if(sscanf(cmd+7,"%99s",n)==1) delete_song(n);}
        else if(!strncmp(cmd,"star ",5)){char n[100]; if(sscanf(cmd+5,"%99s",n)==1) star(n,1);}
        else if(!strncmp(cmd,"unstar ",7)){char n[100]; if(sscanf(cmd+7,"%99s",n)==1) star(n,0);}
        else if(!strcmp(cmd,"list")) list(0);
        else if(!strcmp(cmd,"filter_favorites")) list(1);
        else if(!strcmp(cmd,"sort_name")){sort_mode=0; sort_playlist();}
        else if(!strcmp(cmd,"sort_artist")){sort_mode=1; sort_playlist();}
        else if(!strcmp(cmd,"sort_duration")){sort_mode=2; sort_playlist();}
        else if(!strcmp(cmd,"playlist_signature")) playlist_signature();
        else if(!strcmp(cmd,"playlist_entropy")) playlist_entropy();
        else if(!strcmp(cmd,"exit")) break;
    }
    return 0;
}