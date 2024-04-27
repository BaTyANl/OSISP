#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define MAX_MES_COUNT 20

typedef struct {
    u_int8_t type;
    u_int16_t hash;
    u_int8_t size;
    u_int8_t data[256];
} mes;

typedef struct ringNode {
    uintptr_t message;
    uintptr_t next;
    uintptr_t prev;
} ringNode;

typedef struct {
    int countAdded;
    int countDeleted;
    uintptr_t ringHead;
    uintptr_t ringTail;
    uintptr_t currentPlaceToWrite;
} queue;

#define START_PLACE_TO_WRITE sizeof(queue)
#define END_PLACE_TO_WRITE (sizeof(queue)+MAX_MES_COUNT*sizeof(ringNode)+MAX_MES_COUNT*sizeof(mes))
#define STEP_TO_WRITE (sizeof(ringNode) + sizeof(mes))

void push(queue*);
void pop(queue*);

void initMes(mes*);
void printMes(mes*);