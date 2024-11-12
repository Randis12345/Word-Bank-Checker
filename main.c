#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>


#define ALPHSIZE 26

int hashy(int c){
    if (c < 'a' || c > 'z') return 0;
    return (int) c-'a';
};

struct Node{
    bool end;   
    char c;
    struct Node** connections;
};

bool searchforword(char* lookingfor, struct Node* head){
    int ind = hashy((int) lookingfor[0]);
    if (head->connections[ind]){ 
        head = head->connections[ind];
        if (!lookingfor[1] && head->end) {
            return true;
        }
        return searchforword(lookingfor+1,head);
    }
    return false;
}


struct Node* createNode(char c) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->end = false;
    newNode->c = c;
    newNode->connections = malloc(ALPHSIZE*sizeof(struct Node*));
    for (int i = 0; i < ALPHSIZE; i++) {
        newNode->connections[i] = NULL;
    }
    return newNode;
}


struct Node* gentree(const char* wordbankname){
    FILE* wordbank = fopen(wordbankname,"r");
    struct Node*root = createNode((char)1);
    
    struct Node* head = root;
    int nextchar = getc(wordbank);
    
  
    while(nextchar != EOF){
        if (!nextchar) {
            nextchar = getc(wordbank);
            continue;
        }
        if (nextchar == '\n'){
            head->end = true; 
            head = root;
            nextchar = getc(wordbank);
            continue;
        }
        int cindex = hashy(nextchar);
        if (!head->connections[cindex]) head->connections[cindex] = createNode(nextchar);
        head = head->connections[cindex];
        nextchar = getc(wordbank);
    }

    fclose(wordbank);
    return root;
}

int main(int argc, char* argv[]){
    
    if (argc <= 1){
        printf("file path for wordbank not provided");
        return 1;
    }
    
    struct Node* root = gentree(argv[1]);
    for(int i = 2; i < argc; i++){
        printf("%s: %s", argv[i], searchforword(argv[i],root) ? "True" : "False");
        printf("\n");
    }

    return 0;
};