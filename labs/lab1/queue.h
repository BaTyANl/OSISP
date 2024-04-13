#ifndef LAB1_LIST_H
#define LAB1_LIST_H
#endif //LAB1_LIST_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef struct node{
    char* data;
    struct node* next;
} node;
void pushQueue(node** head, node** tail, char* str);
void sortQueue(node* head);
void showQueue(node* head);
void clearQueue(node** head, node** tail);