
#include "stack.h"
void pushHead(node** head, pid_t pid){
    node* n = (node*)malloc(sizeof(node));
    n->next = *head;
    n->pid = pid;
    n->num = size(*head) + 1;
    *head = n;
}

void popHead(node** head){
    if(*head != NULL){
        node *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

void clearQueue(node** head){
    while(*head != NULL){
        node* temp = *head;
        (*head) = (*head)->next;
        free(temp);
    }
}

void show(node* head){
    node* temp = head;
    while (temp != NULL){
        printf("C_%d with pid %d\n", temp->num, temp->pid);
        temp = temp->next;
    }
}

int size(node* head){
    int size = 0;
    node* temp = head;
    while(temp != NULL){
        size++;
        temp = temp->next;
    }
    return size;
}
