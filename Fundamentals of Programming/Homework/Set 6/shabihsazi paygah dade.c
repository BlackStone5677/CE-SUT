#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct { int id, age; char name[51], field[51]; } Student;

int getNextID() {
    FILE *f=fopen("database.dat","rb"); Student s; int id=0;
    if(f){ while(fread(&s,sizeof(Student),1,f)) id=s.id; fclose(f);}
    return id+1;
}

void insert(char *n,int a,char *f){ FILE *file=fopen("database.dat","ab"); Student s={getNextID(),a}; strcpy(s.name,n); strcpy(s.field,f); fwrite(&s,sizeof(Student),1,file); fclose(file);}
void selectAll(){ FILE *file=fopen("database.dat","rb"); Student s; printf("----------\nID / name / age / field\n"); if(file){ while(fread(&s,sizeof(Student),1,file)) printf("%d %s %d %s\n",s.id,s.name,s.age,s.field); fclose(file);} printf("----------\n");}
void update(int id,char *n,int a,char *f){ FILE *file=fopen("database.dat","rb"); FILE *temp=fopen("temp.dat","wb"); Student s; int found=0; while(fread(&s,sizeof(Student),1,file)){ if(s.id==id){ strcpy(s.name,n); s.age=a; strcpy(s.field,f); found=1;} fwrite(&s,sizeof(Student),1,temp);} fclose(file); fclose(temp); rename("temp.dat","database.dat"); printf(found?"Record updated.\n":"ID not found!\n");}
void deleteID(int id){ FILE *file=fopen("database.dat","rb"); FILE *temp=fopen("temp.dat","wb"); Student s; int found=0; while(fread(&s,sizeof(Student),1,file)){ if(s.id==id){found=1; continue;} fwrite(&s,sizeof(Student),1,temp);} fclose(file); fclose(temp); rename("temp.dat","database.dat"); printf(found?"Record deleted.\n":"ID not found!\n");}

int main(){
    char cmd[10],n[51],f[51]; int a,id;
    while(1){
        scanf("%s",cmd);
        if(strcmp(cmd,"INSERT")==0){ scanf(" student(%50[^,], %d, %50[^)])",n,&a,f); insert(n,a,f);}
        else if(strcmp(cmd,"SELECT")==0) selectAll();
        else if(strcmp(cmd,"UPDATE")==0){ scanf(" ID: %d student(%50[^,], %d, %50[^)])",&id,n,&a,f); update(id,n,a,f);}
        else if(strcmp(cmd,"DELETE")==0){ scanf(" ID: %d",&id); deleteID(id);}
        else if(strcmp(cmd,"exit")==0) break;
    }
}