#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ANIMALS 100

// Forward declarations
struct Animal;

// ---------- Animal Specific Structs ----------
typedef struct Dog   { void (*sound)(char* name); } Dog;
typedef struct Cat   { void (*sound)(char* name); } Cat;
typedef struct Chicken { void (*sound)(char* name); } Chicken;
typedef struct Parrot { void (*sound)(char* name); } Parrot;
typedef struct Crocodile { vo   id (*sound)(char* name); } Crocodile;
typedef struct Turtle { void (*sound)(char* name); } Turtle;
typedef struct Tuna { void (*sound)(char* name); } Tuna;
typedef struct Salmon { void (*sound)(char* name); } Salmon;

// ---------- Category Structs ----------
typedef struct Mammal {
    enum { DOG, CAT } kind;
    int hasFur;
    void* specific;  // points to Dog or Cat
} Mammal;

typedef struct Bird {
    enum { CHICKEN, PARROT } kind;
    int canFly;
    void* specific;  // points to Chicken or Parrot
} Bird;

typedef struct Reptile {
    enum { CROCODILE, TURTLE } kind;
    int isVenomous;
    void* specific;  // points to Crocodile or Turtle
} Reptile;

typedef struct Fish {
    enum { TUNA, SALMON } kind;
    int isSaltWater;
    void* specific;  // points to Tuna or Salmon
} Fish;

// ---------- Animal Type ----------
typedef struct AnimalType {
    enum { MAMMAL, BIRD, REPTILE, FISH } category;
    void* specificCategory;  // points to Mammal, Bird, Reptile or Fish
} AnimalType;

// ---------- Animal ----------
typedef struct Animal {
    char name[30];
    int age;
    AnimalType type;
    void (*speak)(struct Animal* self);
    void (*printInfo)(struct Animal* self);
} Animal;

// ---------- Global Ecosystem ----------
Animal* ecosystem[MAX_ANIMALS];
int count = 0;

// ---------- Helper Functions ----------
void toLowerCase(char* str) {
    for (int i = 0; str[i]; i++)
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] - 'A' + 'a';
}
int parseAnimalCategory(const char* typeStr) {
    char temp[30];
    strcpy(temp, typeStr);
    toLowerCase(temp);

    if (strcmp(temp, "mammal") == 0) return MAMMAL;
    if (strcmp(temp, "bird") == 0) return BIRD;
    if (strcmp(temp, "reptile") == 0) return REPTILE;
    if (strcmp(temp, "fish") == 0) return FISH;

    return -1;
}

// ---------- Sounds ----------
void dogSound(char* name) { printf("%s: Hop Hop!\n", name); }
void catSound(char* name) { printf("%s: Meow!\n", name); }
void chickenSound(char* name) { printf("%s: Ghod Ghod!\n", name); }
void parrotSound(char* name) { printf("%s: Squawk!\n", name); }
void crocodileSound(char* name) { printf("%s: Grrr!\n", name); }
void turtleSound(char* name) { printf("%s: ...\n", name); }
void tunaSound(char* name) { printf("%s: Blub!\n", name); }
void salmonSound(char* name) { printf("%s: Splash!\n", name); }

// ---------- Speak Function ----------
void animalSpeak(Animal* self) { ///Don't change this function
    switch (self->type.category) {
        case MAMMAL: {
            Mammal* m = (Mammal*)self->type.specificCategory;
            if (m->kind == DOG) ((Dog*)m->specific)->sound(self->name);
            else ((Cat*)m->specific)->sound(self->name);
            break;
        }
        case BIRD: {
            Bird* b = (Bird*)self->type.specificCategory;
            if (b->kind == CHICKEN) ((Chicken*)b->specific)->sound(self->name);
            else ((Parrot*)b->specific)->sound(self->name);
            break;
        }
        case REPTILE: {
            Reptile* r = (Reptile*)self->type.specificCategory;
            if (r->kind == CROCODILE) ((Crocodile*)r->specific)->sound(self->name);
            else ((Turtle*)r->specific)->sound(self->name);
            break;
        }
        case FISH: {
            Fish* f = (Fish*)self->type.specificCategory;
            if (f->kind == TUNA) ((Tuna*)f->specific)->sound(self->name);
            else ((Salmon*)f->specific)->sound(self->name);
            break;
        }
    }
}

// ---------- Print Info ----------
void printInfo(Animal* self) {
    char* categoryStr = "";
    char* specificStr = "";

    switch (self->type.category) {
        case MAMMAL: {
            categoryStr = "Mammal";
            Mammal* m = (Mammal*)self->type.specificCategory;
            specificStr = (m->kind == DOG) ? "Dog" : "Cat";
            break;
        }
        case BIRD: {
            categoryStr = "Bird";
            Bird* b = (Bird*)self->type.specificCategory;
            specificStr = (b->kind == CHICKEN) ? "Chicken" : "Parrot";
            break;
        }
        case REPTILE: {
            categoryStr = "Reptile";
            Reptile* r = (Reptile*)self->type.specificCategory;
            specificStr = (r->kind == CROCODILE) ? "Crocodile" : "Turtle";
            break;
        }
        case FISH: {
            categoryStr = "Fish";
            Fish* f = (Fish*)self->type.specificCategory;
            specificStr = (f->kind == TUNA) ? "Tuna" : "Salmon";
            break;
        }
    }

    printf("Type: %-10s | Specific: %-10s | Name: %-20s | Age: %d\n", categoryStr, specificStr, self->name, self->age);
}


// ---------- Constructors ----------
Animal* createAnimal(char* type, char* name, int age){
    Animal* animal = malloc(sizeof(Animal));
    if (!animal) {
        printf("Memory allocation failed for Animal.\n");
        exit(1);
    }

    strcpy(animal->name, name);
    animal->age = age;

    if (strcmp(type, "dog") == 0 || strcmp(type, "cat") == 0){
        Mammal* m = malloc(sizeof(Mammal));
        if(strcmp(type, "dog") == 0){
            Dog* dog = malloc(sizeof(Dog));
            dog->sound = dogSound;
            m->kind = DOG;
            m->hasFur = 1;
            m->specific = dog;
        } else{
            Cat* cat = malloc(sizeof(Cat));
            cat->sound = catSound;
            m->kind = CAT;
            m->hasFur = 1;
            m->specific = cat;
        }

        animal->type.category = MAMMAL;
        animal->type.specificCategory = m;
    }else if (strcmp(type, "chicken") == 0 || strcmp(type, "parrot") == 0){
        Bird* b = malloc(sizeof(Bird));
        if(strcmp(type, "chicken") == 0){
            Chicken* chicken = malloc(sizeof(Chicken));
            chicken->sound = chickenSound;
            b->kind = CHICKEN;
            b->canFly = 0;
            b->specific = chicken;
        } else{
            Parrot* parrot = malloc(sizeof(Parrot));
            parrot->sound = parrotSound;
            b->kind = PARROT;
            b->canFly = 1;
            b->specific = parrot;
        }

        animal->type.category = BIRD;
        animal->type.specificCategory = b;
    }else if (strcmp(type, "crocodile") == 0 || strcmp(type, "turtle") == 0){
        Reptile* r = malloc(sizeof(Reptile));
        if(strcmp(type, "crocodile") == 0){
            Crocodile* crocodile = malloc(sizeof(Crocodile));
            crocodile->sound = crocodileSound;
            r->kind = CROCODILE;
            r->isVenomous = 1;
            r->specific = crocodile;
        } else{
            Turtle* turtle = malloc(sizeof(Turtle));
            turtle->sound = turtleSound;
            r->kind = TURTLE;
            r->isVenomous = 0;
            r->specific = turtle;
        }

        animal->type.category = REPTILE;
        animal->type.specificCategory = r;
    }else if (strcmp(type, "tuna") == 0 || strcmp(type, "salmon") == 0){
        Fish* f = malloc(sizeof(Fish));
        if(strcmp(type, "tuna") == 0){
            Tuna* tuna = malloc(sizeof(Tuna));
            tuna->sound = tunaSound;
            f->kind = TUNA;
            f->isSaltWater = 1;
            f->specific = tuna;
        } else{
            Salmon* salmon = malloc(sizeof(Salmon));
            salmon->sound = salmonSound;
            f->kind = SALMON;
            f->isSaltWater = 0;
            f->specific = salmon;
        }

        animal->type.category = FISH;
        animal->type.specificCategory = f;
    } else {
        printf("Unknown animal type: %s\n", type);
        free(animal);
        return NULL;
    }
    
    animal->speak = animalSpeak;
    animal->printInfo = printInfo;

    return animal;

}

// ---------- Handle Add Command ----------
void handleAddCommand(char* args) {
    char type[11]; char name[21]; int age;
    sscanf(args, "-t %s -n %s -a %d", type, name, &age);
    ecosystem[count] = createAnimal(type, name, age);
    count++;
    printf("Added %s (%s) successfully!\n", name, type);
}

// ---------- Handle List ----------

//Remember to handle all errors :D

void handleListCommand() {
    if(count){
        printf("Animals in the ecosystem:\n");
        for(int i = 0; i < count; i++) printInfo(ecosystem[i]);
    }
    else printf("No animal in the ecosystem.\n");
}

// ---------- Handle Speak ----------
void handleSpeakAllCommand() {
    if(count == 0) {
        printf("No animal to speak.\n");
        return;
    }
    for(int i = 0; i < count; i++) ecosystem[i]->speak(ecosystem[i]);
}

void handleSpeakByCategoryCommand(char* category) {
    if(count == 0) {
        printf("No animal to speak.\n");
        return;
    }
    int cat = parseAnimalCategory(category);
    if(cat == -1) {
        printf("Unknown animal category: %s\n", category);
        return;
    }
    int none = 1;
    for(int i = 0; i < count; i++) if((ecosystem[i]->type.category) == cat) {ecosystem[i]->speak(ecosystem[i]); none = 0;}
    if(none) printf("No animal found in category: %s\n", category);
}

void handleSpeakByNameCommand(char* name) {
    if(count == 0){ printf("No animal to speak.\n"); return;}
    for(int i = 0; i < count; i++)
        if(strcmp(ecosystem[i]->name, name) == 0) {
            ecosystem[i]->speak(ecosystem[i]);
            return;
        }
    printf("No animal with that name.\n");
}

// ---------- Handle Change Age ----------
void handleChangeAgeCommand(char* args) {
    if(count==0){printf("No animal to change.\n"); return;}
    char name[21]; int newAge;
    sscanf(args, "-n %s -a %d", name, &newAge);
    for(int i = 0; i < count; i++)
        if(strcmp(ecosystem[i]->name, name) == 0){
            ecosystem[i]->age = newAge;
            printf("Changed %s age to %d successfully!\n", name, newAge);
            return;
        }
    printf("No animal with that name.\n");
}

// ---------- Main ----------
int main() {
    char input[200];

    while (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = '\0';

        if(!strcmp(input, "exit")){printf("Khodafez!"); break;}
        else if(!strncmp(input, "add animal", 10)) handleAddCommand(input + 11);
        else if(!strcmp(input, "list animals")) handleListCommand();
        else if(!strcmp(input, "speak all")) handleSpeakAllCommand();
        else if(!strncmp(input, "speak -c", 8)) handleSpeakByCategoryCommand(input + 9);
        else if(!strncmp(input, "speak -n", 8)) handleSpeakByNameCommand(input + 9);
        else if(!strncmp(input, "change age", 10)) handleChangeAgeCommand(input + 11);
    }

    // Free memory
    for (int i = 0; i < count; i++) {
        AnimalType* t = &ecosystem[i]->type;
        switch (t->category) {
            case MAMMAL: {
                Mammal* m = (Mammal*)t->specificCategory;
                free(m->specific); // Dog or Cat
                free(m);
                break;
            }
            case BIRD: {
                Bird* b = (Bird*)t->specificCategory;
                free(b->specific); // Chicken or Parrot
                free(b);
                break;
            }
            case REPTILE: {
                Reptile* r = (Reptile*)t->specificCategory;
                free(r->specific); // Crocodile or Turtle
                free(r);
                break;
            }
            case FISH: {
                Fish* f = (Fish*)t->specificCategory;
                free(f->specific); // Tuna or Salmon
                free(f);
                break;
            }
        }
        free(ecosystem[i]);
    }

    return 0;
}
 