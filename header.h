#ifndef LABA4A_HEADER_H
#define LABA4A_HEADER_H

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>

#define msg "0. Quit \n1. Add \n2. Show \n3. Find \n4. Delete \n5. Find next \n6. Timing \n7. Load file\n8. Save file\n"

typedef struct Node {
    char *key;
    struct Node *right;
    struct Node *left;
    struct Node *parent;
    char *Info;
} Node;

void getInt(int* a);
char* getstr();
void getKey(Node *root);
Node* createNode(char* value, char* key, Node *parent);
int addNode(Node** root, char* key, char* Info);
Node* findNode(Node *root, char* key);
void printTree(Node *root, char *name, int lvl);
void printNode(Node *root);
void deleteTree(Node *root);
void deleteNode(Node *root);
Node* getMin(Node *root);
Node* getNext(Node *root);
void removeNode(Node *root);
void nextNode(Node *root);
int timing_func();
void getInfo(Node **root);
char* random_string();
int load(Node **trp);
void save_tree(Node* ptr, FILE* fd);
int save(Node** root);

#endif //LABA4A_HEADER_H
