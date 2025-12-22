#include <stdio.h>
#include <string.h>

int top_letter(char text[]){
    int frequency[26] = {0};
    for(int i = 0; text[i]; i++){
        if(text[i] >= 'A' && text[i] <= 'Z') frequency[text[i] - 'A']++;
        else if(text[i] >= 'a' && text[i] <= 'z') frequency[text[i] - 'a']++;
    }
    int max = 0;
    for(int i = 0; i < 26; i++){
        if(frequency[i] > frequency[max]) max = i;
    }
    int letters = 0;
    for(int i = 0; text[i]; i++) if((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z')) letters++;
    if((((float)frequency[max] / letters) < 0.10) || (((float)frequency[max] / letters) > 0.14)) max = -1;
    return max;
}

int main(){
    char text[1024];
    fgets(text, 1024, stdin);
    text[strcspn(text, "\n")] = 0;
    int top = top_letter(text);
    if(top == -1) printf("Ciphertext is either too short or not a Caesar cipher!");
    else{
    int shift = (top - 4 + 26) % 26;
    for(int i = 0; text[i]; i++){
        if(text[i] >= 'A' && text[i] <= 'Z') text[i] = 'A' + (text[i] - 'A' - shift + 52) % 26;
        else if(text[i] >= 'a' && text[i] <= 'z') text[i] = 'a' + (text[i] - 'a' - shift + 52) % 26;
    }
    printf("%d\n", shift);
    printf("%s", text);
    }
}

