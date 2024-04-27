#include "ring.h"
#include <sys/types.h>

void push(ringNode** head, ringNode** tail) {
    if (*head != NULL) {
        ringNode *temp = (ringNode *) malloc(sizeof(ringNode));
        temp->message = (mes*)malloc(sizeof(mes));
        initMes(temp->message);
        temp->next = *head;
        temp->prev = *tail;
        (*tail)->next = temp;
        (*head)->prev = temp;
        *tail = temp;
    } else {
        *head = (ringNode *) malloc(sizeof(ringNode));
        (*head)->message = (mes*)malloc(sizeof(mes));
        initMes((*head)->message);
        (*head)->prev = *head;
        (*head)->next = *head;
        *tail = *head;
    }
}
void pop(ringNode** head, ringNode** tail) {
    if (*head != NULL) {
        if (*head != *tail) {
            ringNode *temp = *head;
            (*tail)->next = (*head)->next;
            *head = (*head)->next;
            (*head)->prev = *tail;
            free(temp);
        } else {
            free(*head);
            *head = NULL;
            *tail = NULL;
        }
    }
}

void initMes(mes* message) {
    message->type = 0;
    message->hash = 0;
    message->size = rand() % 257;
    message->data = (u_int8_t*)malloc(message->size*sizeof(u_int8_t));
    for (size_t i = 0; i < message->size; i++) {
        message->data[i] = rand() % 256;
        message->hash += message->data[i];
    }
    message->hash = ~message->hash;
}

void printMes(mes* mes) {
    printf("Message type: %d, hash: %d, size: %d, data: ", mes->type, mes->hash, mes->size);
    for(size_t i = 0; i<mes->size; i++)
        printf("%d", mes->data[i]);
    printf("\n");
}