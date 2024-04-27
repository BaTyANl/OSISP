#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

typedef struct stackNode {
    pid_t pid;
    struct stackNode* next;
} stackNode;

void pushStack(stackNode**, pid_t);
void popStack(stackNode**);