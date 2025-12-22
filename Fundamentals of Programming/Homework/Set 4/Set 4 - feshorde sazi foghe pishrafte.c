#include <stdio.h>
#include <string.h>

#define MAX_WORDS 20000
#define MAX_LEN 200

int main() {
    char text[50000];
    fgets(text, sizeof(text), stdin);
    
    text[strcspn(text, "\n")] = '\0';
    
    if(strlen(text) == 0){
        printf("\n");
        return 0;
    }
    text[strcspn(text, "\n")] = 0;

    char words[MAX_WORDS][MAX_LEN];
    int word_count = 0;

    int i = 0;
    while(text[i]){
        while(text[i] == ' ' && text[i] != 0) i++;
        if(text[i] == 0) break;

        char word[MAX_LEN];
        int w = 0;
        while(text[i] != ' ' && text[i] != 0 && w < MAX_LEN-1) word[w++] = text[i++];
        word[w] = 0;

        strcpy(words[word_count++], word);
    }

    char dictionary[MAX_WORDS][MAX_LEN];
    int dict_size = 0;
    int dict_indices[MAX_WORDS];

    for(i = 0; i < word_count; i++){
        int count = 0;
        for (int j = 0; j < word_count; j++) if(strcmp(words[i], words[j]) == 0) count++;

        if(count > 1){
            int found = -1;
            for (int j = 0; j < dict_size; j++) if (strcmp(dictionary[j], words[i]) == 0){
                found = j;
                break;
            }
            if (found == -1){
                strcpy(dictionary[dict_size], words[i]);
                found = dict_size;
                dict_size++;
            }
            dict_indices[i] = found;
        }
        else dict_indices[i] = -1;
    }

    for(i = 0; i < dict_size; i++) printf("%d: %s\n", i, dictionary[i]);

    char prev_word[MAX_LEN] = "";
    int prev_index = -2;
    int run_count = 0;
    int first_output = 1;

    for(i = 0; i <= word_count; i++){
        int idx = (i < word_count) ? dict_indices[i] : -3;
        char* curr_word = (i < word_count) ? words[i] : "";

        if(i < word_count && strcmp(curr_word, prev_word) == 0) run_count++;
        else{
            if(prev_word[0] != '\0'){
                if(!first_output) printf(" ");
                if(prev_index >= 0){
                    if (run_count == 1) printf("%d", prev_index);
                    else printf("%d[%d]", prev_index, run_count);
                }
                else printf("%s", prev_word);
                first_output = 0;
            }

            if(i < word_count){
                strcpy(prev_word, curr_word);
                prev_index = idx;
                run_count = 1;
            }
        }
    }

    printf("\n");
    return 0;
}
