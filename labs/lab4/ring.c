#include "ring.h"

void push(queue* Queue) {
    if(Queue->currentPlaceToWrite > END_PLACE_TO_WRITE)                        // Установка места добавления.
        Queue->currentPlaceToWrite = START_PLACE_TO_WRITE;
    ringNode *temp = (ringNode *)((uintptr_t)Queue + Queue->currentPlaceToWrite);      // Инициализация памяти.
    temp->message = ((uintptr_t)Queue + Queue->currentPlaceToWrite + sizeof(ringNode));
    initMes((mes*)temp->message);                                          // Инициализация сообщения.
    if (Queue->ringHead != 0) {
        temp->next = Queue->ringHead;                                          // Добавление в кольцо.
        temp->prev = Queue->ringTail;
        ((ringNode*)(Queue->ringHead+(uintptr_t)Queue))->prev = (uintptr_t)temp - (uintptr_t)Queue;
        ((ringNode*)(Queue->ringTail+(uintptr_t)Queue))->next = (uintptr_t)temp - (uintptr_t)Queue;
        Queue->ringTail = (uintptr_t)temp - (uintptr_t)Queue;
    } else {
        Queue->ringHead = (uintptr_t)temp - (uintptr_t)Queue;
        Queue->ringTail = (uintptr_t)temp - (uintptr_t)Queue;
        temp->next = (uintptr_t)temp - (uintptr_t)Queue;
        temp->prev = (uintptr_t)temp - (uintptr_t)Queue;
    }
    Queue->currentPlaceToWrite += STEP_TO_WRITE;                                   
}
void pop(queue* Queue) {
    if (Queue->ringHead != 0) {
        if (Queue->ringHead != Queue->ringTail) {
            ringNode *temp = (ringNode *) (Queue->ringHead + (uintptr_t) Queue);      // Удаление.
            ((ringNode *) (Queue->ringTail + (uintptr_t) Queue))->next = temp->next;
            ((ringNode *) (temp->next + (uintptr_t) Queue))->prev = Queue->ringTail;
            Queue->ringHead = temp->next;
        } else {
            Queue->ringHead = 0;
            Queue->ringTail = 0;
        }
    }
}

void initMes(mes* message) {
    message->type = 0;                                    
    message->hash = 0;
    message->size = rand() % 257;
    for (size_t i = 0; i < message->size; i++) {
        message->data[i] = rand() % 256;
        message->hash += message->data[i];                // Для хэша.
    }
    message->hash = ~message->hash;                       // Метод дополнения.
}

void printMes(mes* mes) {
    printf("Message type: %d, hash: %d, size: %d, data: ", mes->type, mes->hash, mes->size);
    for(size_t i = 0; i<mes->size; i++)
        printf("%d", mes->data[i]);
    printf("\n");
}