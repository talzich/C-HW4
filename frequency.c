#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_LEN ((int)10)

void init(char *str, int length){
    int word_flag = 0;
    int i =0;
    char c; 

    while((c = getchar())!= EOF){
        if (i >= length-1)
            str = realloc(str, (length += 10)*sizeof(char));
        
        if (c >= 65 && c <= 90){
            c += 32;
            str[i++] = c;
        }
        else if (c >= 97 && c <= 122){
            str[i++] = c;
        }
        else if (c == ' ' || c == '\n' || c == '\r' || c == '\v' || c == '\t'){
            str[i++] = c;
        }
    }
}

int main(void){

    //Dynamically allocate memory for our string
    char *text = (char *)calloc(INIT_LEN, sizeof(char));

    //Check if allocation was successful
    if (text == NULL){
        perror("Error in calloc:");
        exit(1);
    }
    else{
        init(text, INIT_LEN);
    }
    printf("%s\n", text);

}
