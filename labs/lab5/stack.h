#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct stackNode{
    pthread_t threadId;
    struct stackNode* next;
} stackNode;

void pushStack(stackNode**, pthread_t);
void popStack(stackNode**);