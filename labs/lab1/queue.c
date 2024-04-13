
#include "queue.h"
void pushQueue(node** head, node** tail, char* str){
    node* n = (node*)malloc(sizeof(node));
    n->next = NULL;
    n->data = str;
    if(*head == NULL){
        *head = n;
        *tail = n;
    }else{
        (*tail)->next = n;
        *tail = n;
    }
}

void sortQueue(node* head){
    node* ptr1 = head;
    node* ptr2 = head;
    char* temp = (char*)malloc(80 * sizeof(char));
    while(ptr1 != NULL){
        while(ptr2 != NULL){
            if(ptr2->data < ptr1->data){
                temp = ptr2->data;
                ptr2->data = ptr1->data;
                ptr1->data = temp;
            }
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
        ptr2 = ptr1;
    }
}

void clearQueue(node** head, node** tail){
    while(*head != NULL){
        node* temp = *head;
        (*head) = (*head)->next;
        free(temp);
    }
    *tail = NULL;
}

void showQueue(node* head){
    node* temp = head;
    while (temp != NULL){
        printf("%s\n", temp->data);
        temp = temp->next;
    }
}
