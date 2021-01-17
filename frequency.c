#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INIT_LEN 10
#define AB_SIZE 26
#define INDEX(c) ((int)c - 97)
#define LETTER(i) (char)(i + 97)

typedef struct node{
    struct node *children[AB_SIZE]; // Will store all the children this node has
    bool is_end;    // Will store whether this node marks the end of a word
    long unsigned int count; // Will store how many times this word was entered
}Node;

Node *new_Node(void){ 

    Node *pNode = NULL; 
  
    pNode = (Node *)malloc(sizeof(Node)); 
    if(pNode == NULL){
        perror("Error in malloc:");
        exit(1);
    }
    else{
        pNode->is_end = false;
        pNode->count = 0;
        int i; 
        for (i = 0; i < AB_SIZE; i++) 
            pNode->children[i] = NULL; 
    } 
  
    return pNode; 
} 

void init(char *str, int length){
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

        else if (c == ' ' || c == '\n' || c == '\r' || c == '\v' || c == '\t' || c == '\f'){
            str[i++] = c;
        }
    }
}

void insert(Node *root, char *word){
    int c; 
    int length = strlen(word); 
    int index; 
  
    Node *pCrawl = root; 
  
    for (c = 0; c < length; c++) { 
        index = INDEX(word[c]); 

        if (pCrawl->children[index] == NULL) 
            pCrawl->children[index] = new_Node(); 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    pCrawl->is_end = true;
    pCrawl->count++;
}

void fill_trie(char *text, Node *root){

    char *copy = (char *)calloc(strlen(text), sizeof(char));
    if(copy == NULL){
        perror("Error in calloc:");
        exit(1);
    }
    strcpy(copy, text);

    char *word = strtok(copy, " \n\r\v\t\f");
    while(word != NULL){
        insert(root, word);
        word = strtok(NULL, " \n\r\v\t\f");
    }
    if(copy != NULL)
        free(copy);
}

void print_word(char *word, int n, int count){
    int i;
    for(i = 0; i < n; i++){
        printf("%c", word[i]);
    }
    printf(" %d\n", count);
}

void print_words(Node *root, char *word, int index, int length){
    if (root == NULL)
        return;
    if(root->is_end){
        print_word(word, index, root->count);
    }
    int i;
    for(i = 0; i < AB_SIZE; i++){
        if(root->children[i] != NULL){
            if (index>=length-1){
                word = realloc(word, (length+=10)*sizeof(char));
            }
            word[index] = LETTER(i);
            print_words(root->children[i], word, index+1, length);
        }
    }
}

void print_words_r(Node *root, char *word, int index, int length){
    if (root == NULL)
        return;
    int i;
    for(i = AB_SIZE-1; i >= 0; i--){
        if(root->children[i] != NULL){
            if (index>=length-1){
                word = realloc(word, (length+=10)*sizeof(char));
            }
            word[index] = LETTER(i);
            print_words_r(root->children[i], word, index+1, length);
        }
    }
    if(root->is_end){
        print_word(word, index, root->count);
    }
}

int main(int argc, char const *argv[]){


    //Dynamically allocate memory for our string
    char *text = (char *)malloc(INIT_LEN*sizeof(char));

    //Check if allocation was successful
    if (text == NULL){
        perror("Error in malloc:");
        exit(1);
    }

    // Insert input into the string
    else{
        init(text, INIT_LEN);
    }

    //Dynamically allocate memory for each word
    char *word = (char *)malloc(INIT_LEN*sizeof(char));

    //Check if allocation was successful
    if (word == NULL){
        perror("Error in malloc:");
        exit(1);
    }

    Node *root = new_Node();
    fill_trie(text, root);
    int pos = 0;

    if (argc > 1 && *(argv[1]) == 'r')
        print_words_r(root, word, pos, INIT_LEN);
    else
        print_words(root, word, pos, INIT_LEN);
    
    return 0;
}
