#include <stdio.h>

int length;
char text[1024];
char output[1024];


void clean_up(char text[], int size){
    int i = 0, j = 0;

    while (text[i]) {

        // Remove spaces before punctuation or another space
        // but do NOT remove a space directly after output punctuation.
        if (text[i] == ' ' && (text[i+1] == ' ' || text[i+1] == ',' || text[i+1] == '.' || text[i+1] == '!' || text[i+1] == '?') && !(j > 0 && (text[j-1] == ',' || text[j-1] == '.' || text[j-1] == '!' || text[j-1] == '?'))){
                i++;
                continue;
            }

        // if ((text[i] >= 'A' && text[i] <= 'Z') && !(j == 0 || (j >= 2 && ((output[j-2] == '.' || output[j-2] == '!' || output[j-2] == '?') || (output[j-1] == '.' || output[j-1] == '!' || output[j-1] == '?'))))) text[i] = text[i] + 32;

        // Write character to output
        output[j++] = text[i];

        // Add a space after punctuation unless one already exists
        if (text[i+1] != ' ' && (text[i] == ',' || text[i] == '.' || text[i] == '!' || text[i] == '?')) output[j++] = ' ';

        i++;
    }

    output[j] = 0;
    for(i = 0; text[i]; i++) text[i] = output[i];
    length = j;
}




int validate(char text[], int size){
    for(int i = 0; text[i]; i++){
        if(!(text[i] == '\n' || (text[i] >= '0' && text[i] <= '9') || (text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z') || text[i] == ' ' || text[i] == ',' || text[i] == '.' || text[i] == '!' || text[i] == '?' || text[i] == '+' || text[i] == '-' || text[i] == '*' || text[i] == '/' || text[i] == '=')) return 0;
    }
    return 1;
    }

int math_expression(int i){
    // Check left of number
    int L = i - 1;
    while(L >= 0 && text[L] == ' ' || (text[L] >= '0' && text[L] <= '9')) L--;
    if(L >= 0 && (text[L] == '+' || text[L] == '-' || text[L] == '=' || text[L] == '*' || text[L] == '/')) return 1;

    int R = i + 1;
    while(text[R] && (text[R] >= '0' && text[R] <= '9' || text[R] == ' ')) R++;
    if(text[R] == '+' || text[R] == '-' || text[R] == '=' || text[R] == '*' || text[R] == '/') return 1;

    return 0;
}

char ONES[20][10] = {
    "zero","one","two","three","four","five","six","seven","eight","nine",
    "ten","eleven","twelve","thirteen","fourteen","fifteen",
    "sixteen","seventeen","eighteen","nineteen"
};

char TENS[10][10] = {
    "", "", "twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"
};

int number_to_words(int n, int j) {

    if(n < 20){
        int k = 0;
        while (ONES[n][k]){
            output[j++] = ONES[n][k++];
        }
        return j;
    }

    if(n < 100){
        int k = 0;

        // tens
        while(TENS[n/10][k] != 0){
            output[j++] = TENS[n/10][k++];
        }

        // ones
        if(n % 10 != 0){
            output[j++] = ' ';
            k = 0;
            while(ONES[n%10][k] != 0){
                output[j++] = ONES[n%10][k++];
            }
        }

        return j;
    }

    // 100–999
    int k = 0;

    while (ONES[n/100][k] != 0) {
        output[j++] = ONES[n/100][k++];
    }
    output[j++] = ' ';
    output[j++] = 'h';
    output[j++] = 'u';
    output[j++] = 'n';
    output[j++] = 'd';
    output[j++] = 'r';
    output[j++] = 'e';
    output[j++] = 'd';

    if (n % 100 != 0) {
        output[j++] = ' ';
        j = number_to_words(n % 100, j);
    }

    return j;
}



char SCALE[][20] = {"", "thousand", "million", "billion"};

int number_to_words_large(long long n, int j) {
    if(n == 0){
        int k = 0;
        while(ONES[0][k]) output[j++] = ONES[0][k++];
        return j;
    }

    long long parts[10];
    int part_count = 0;

    while(n > 0){
        parts[part_count++] = n % 1000;
        n /= 1000;
    }

    for(int i = part_count - 1; i >= 0; i--){
        if(parts[i] != 0){
            j = number_to_words((int)parts[i], j);
            if(i > 0){
                output[j++] = ' ';
                int k = 0;
                while(SCALE[i][k]) output[j++] = SCALE[i][k++];
                output[j++] = ' ';
            } else {
                output[j++] = ' ';
            }
        }
    }

    if(j > 0 && output[j-1] == ' ') j--;
    return j;
}



void decoding(char text[], int size){
    int r = 0;   // reader
    int w = 0;   // writer

    while(text[r]){
        if((text[r] >= '0' && text[r] <= '9') && !math_expression(r)){
            int start = r;
            int end = r;

            // find full number, allow commas
            while(text[end+1] && ((text[end+1] >= '0' && text[end+1] <= '9') || text[end+1] == ',')) end++;

            // convert digits to int, skip commas
            long long n = 0;
            for(int k = start; k <= end; k++){
                if(text[k] != ',') n = n*10 + (text[k] - '0');
            }

            // write words
            w = number_to_words_large(n, w);

            r = end + 1;   // continue after number
        }
        else{
            output[w++] = text[r++];
        }
    }

    output[w] = 0;
}


int main(){
    fgets(text, 1024, stdin);
    if(validate(text, 1024)){
    clean_up(text, 1024);
    decoding(text, 1024);
    printf("%s", output);
    }
    else printf("The message may have been leaked!");
}

