#include "stack.h"

void pushStack(stackNode** head, pid_t pid) {
    stackNode *new = (stackNode*) malloc(sizeof(stackNode));
    new->next = *head;
    new->pid = pid;
    *head = new;
}

void popStack(stackNode** head) {
    if(*head!=NULL) {
        stackNode *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}