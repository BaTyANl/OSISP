#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

extern int MAX_MES_COUNT;

typedef struct mes{
    u_int8_t type;
    u_int16_t hash;
    u_int8_t size;
    u_int8_t* data;
} mes;

typedef struct ringNode{
    mes* message;
    struct ringNode* next;
    struct ringNode* prev;
} ringNode;

typedef struct queue{
    ringNode* ringHead;
    ringNode* ringTail;
    int countAdded;
    int countDeleted;
} queue;

void push(ringNode**, ringNode**);
void pop(ringNode**, ringNode**);

void initMes(mes*);
void printMes(mes*);