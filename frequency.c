#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INIT_LEN 10
#define AB_SIZE 26
#define INDEX(c) ((int)c - 97)

typedef struct node{
    struct node *children[AB_SIZE]; // Will store all the children this node has
    bool is_end;    // Will store whether this node marks the end of a word
    long unsigned int count; // Will store how many times this word was entered
    char letter;    // Will store the letter that lead to this node
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

        else if (c == ' ' || c == '\n' || c == '\r' || c == '\v' || c == '\t'){
            str[i++] = c;
        }
    }
}

void fill_trie(Node *root, char *word){

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

int main(void){

    //Dynamically allocate memory for our string
    char *text = (char *)calloc(INIT_LEN, sizeof(char));

    //Check if allocation was successful
    if (text == NULL){
        perror("Error in calloc:");
        exit(1);
    }
    else{
        // Insert input into the string
        init(text, INIT_LEN);
    }
    
    Node *root = new_Node();

}
