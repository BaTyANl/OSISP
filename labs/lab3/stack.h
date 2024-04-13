#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <errno.h>

typedef struct node{
    int num;
    pid_t pid;
    struct node* next;
} node;

void pushHead(node** head, pid_t pid);
void popHead(node** head);
void show(node* head);
void clear(node** head);
int size(node* head);
