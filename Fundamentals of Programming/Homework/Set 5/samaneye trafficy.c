#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int lane;
    int k;
    char plate[10];
    char color[10];
} car;

void add(car **cars, int *car_count, int lane_count[2]){
    int lane, k;
    char plate[10], color[10];
    scanf("%d %d %9s %9s", &lane, &k, plate, color);

    for(int i = 0; i < *car_count; i++) if(!strcmp((*cars)[i].plate, plate)){printf("this plate was already given\n"); return;}
    if(k < 1 || k > lane_count[lane] + 1){printf("an invalid number is given\n"); return;}

    *cars = realloc(*cars, (*car_count + 1) * sizeof(car));

    for(int i = 0; i < *car_count; i++) if((*cars)[i].lane == lane && (*cars)[i].k >= k) (*cars)[i].k++;

    (*cars)[*car_count].lane = lane;
    (*cars)[*car_count].k = k;
    memcpy((*cars)[*car_count].plate, plate, 10);
    memcpy((*cars)[*car_count].color, color, 10);

    (*car_count)++;
    lane_count[lane]++;
}

void delete(car **cars, int *car_count, int lane_count[2]){
    for(int i = 0; i < *car_count; i++) if(!strcmp((*cars)[i].color, "black")){
        int lane = (*cars)[i].lane;
        int k = (*cars)[i].k;
        lane_count[lane]--;

        for(int j = 0; j < *car_count; j++) if((*cars)[j].lane == lane && (*cars)[j].k > k) (*cars)[j].k--;
        (*cars)[i] = (*cars)[*car_count - 1];
        if((*cars)[i].lane == lane && (*cars)[i].k > lane_count[lane]) (*cars)[i].k = lane_count[lane];

        (*car_count)--; i--;
    }
    *cars = realloc(*cars, *car_count * sizeof(car));
}

void change(car **cars, int *car_count, int lane_count[2]){
    char plate[10]; scanf("%9s", plate);
    int idx = -1;

    for(int i = 0; i < *car_count; i++) if(!strcmp((*cars)[i].plate, plate)){idx = i; break;}
    if(idx == -1){printf("Car not found\n"); return;}

    int lane = (*cars)[idx].lane;
    int old_k = (*cars)[idx].k;
    int k = old_k;

    if(k > lane_count[!lane] + 1) k = lane_count[!lane] + 1;

    for(int i = 0; i < *car_count; i++){
        if((*cars)[i].lane == !lane && (*cars)[i].k >= k) (*cars)[i].k++;
        else if((*cars)[i].lane == lane && (*cars)[i].k > old_k) (*cars)[i].k--;
    }

    lane_count[!lane]++;
    lane_count[lane]--;

    (*cars)[idx].lane = !lane;
    (*cars)[idx].k = k;
}

void overtake(car **cars, int *car_count){
    char plate[10];
    int number;
    scanf("%9s %d", plate, &number);

    if(number < 1){printf("an invalid number is given\n"); return;}

    int idx = -1;
    for(int i = 0; i < *car_count; i++) if(!strcmp((*cars)[i].plate, plate)){idx = i; break;}
    if(idx == -1){printf("Car not found\n"); return;}

    if(number >= (*cars)[idx].k) number = (*cars)[idx].k - 1;

    for(int i = 0; i < *car_count; i++)
        if((*cars)[i].lane == (*cars)[idx].lane && (*cars)[i].k >= (*cars)[idx].k - number && (*cars)[i].k < (*cars)[idx].k) (*cars)[i].k++;

    (*cars)[idx].k -= number;
}

int main(){
    int car_count = 0;
    car *cars = malloc(sizeof(car));
    int lane_count[2] = {0, 0};
    char operation[50];

    while(scanf("%49s", operation) == 1 && strcmp(operation, "EXIT")){
        if(!strcmp(operation, "add")) add(&cars, &car_count, lane_count);
        else if(!strcmp(operation, "delete")) delete(&cars, &car_count, lane_count);
        else if(!strcmp(operation, "change")) change(&cars, &car_count, lane_count);
        else if(!strcmp(operation, "overtake")) overtake(&cars, &car_count);
    }

    printf("lane 0:\n");
    int k = lane_count[0];
    while(k--) for(int i = 0; i < car_count; i++) if(cars[i].lane == 0 && cars[i].k == lane_count[0] - k) printf("%s (%s)\n", cars[i].plate, cars[i].color);

    printf("**********\n");
    printf("lane 1:\n");
    k = lane_count[1];
    while(k--) for(int i = 0; i < car_count; i++) if(cars[i].lane == 1 && cars[i].k == lane_count[1] - k) printf("%s (%s)\n", cars[i].plate, cars[i].color);
}