#include "stack.h"

void pushStack(stackNode** head, pthread_t threadId) {
    stackNode *new = (stackNode *) malloc(sizeof(stackNode));
    new->next = *head;
    new->threadId = threadId;
    *head = new;
}
void popStack(stackNode** head) {
    if(*head!=NULL) {
        stackNode *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}