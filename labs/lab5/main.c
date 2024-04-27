#include "ring.h"
#include "stack.h"
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>


#define FILL_SEM_NAME "/fill_sem"
#define EXTRACT_SEM_NAME "/extract_sem"
#define QUEUE_ACCESS_SEM_NAME "/queue_sem"

int continuing = 1;
int MAX_MES_COUNT = 20;

stackNode* stackFiller = NULL;
stackNode* stackExtractor = NULL;

queue* Queue;

void *fillingMessages();
void *extractingMessages();
void changeContinuingStatus();

int main() {
    srand(time(NULL));

    sem_unlink(FILL_SEM_NAME);                        // Очистка семафоров, если существуют.
    sem_unlink(EXTRACT_SEM_NAME);
    sem_unlink(QUEUE_ACCESS_SEM_NAME);

    signal(SIGUSR1, changeContinuingStatus);          // Сигнал остановки.

    Queue = (queue*)malloc(sizeof(queue));            // Очередь.
    Queue->ringHead = 0;
    Queue->ringTail = 0;
    Queue->countDeleted = 0;
    Queue->countAdded = 0;

    sem_t* fillSem;                                   // Инициализация семафоров.
    if((fillSem = sem_open(FILL_SEM_NAME, O_CREAT | O_EXCL, 0666, 1)) == SEM_FAILED) {
        printf("Error while open filling semaphore, code %d.\n", errno);
        exit(errno);
    }
    sem_t* extractSem;
    if((extractSem = sem_open(EXTRACT_SEM_NAME, O_CREAT | O_EXCL, 0666, 1)) == SEM_FAILED) {
        printf("Error while open extracting semaphore, code %d.\n", errno);
        exit(errno);
    }
    sem_t* queueAccess;
    if((queueAccess = sem_open(QUEUE_ACCESS_SEM_NAME, O_CREAT | O_EXCL, 0666, 1)) == SEM_FAILED) {
        printf("Error while open queue semaphore, code %d.\n", errno);
        exit(errno);
    }

    while(continuing) {
        char ch = getchar();
        switch (ch) {
            case 'w': { // Создать заполнитель.
                pthread_t threadId;
                //Функция создания потока и запуска в нем нужной функции: 1 - идентификатор потока, 2 - аттрибуты потока, 3 - нужная функция, 4 - передача аргемента в функцию
                if(pthread_create(&threadId, NULL, fillingMessages, NULL) != 0) {
                    printf("Error while creating filling thread.");
                    continuing = 0;
                } else
                    pushStack(&stackFiller, threadId);
                break;
            }
            case 's':   // Удалить заполнитель.
                if(stackFiller!=NULL) {
                    pthread_kill(stackFiller->threadId, SIGUSR1);
                    //Ожидает завершения потока
                    pthread_join(stackFiller->threadId, NULL);
                    popStack(&stackFiller);
                    continuing = 1;
                } else
                    printf("There is no fillers.\n");
                break;
            case 'e': { // Создать изыматель.
                pthread_t threadId;
                if(pthread_create(&threadId, NULL, extractingMessages, NULL) != 0) {
                    printf("Error while creating extracting thread.");
                    continuing = 0;
                } else
                    pushStack(&stackExtractor, threadId);
                break;
            }
            case 'd':  // Удалить изыматель.
                if(stackExtractor!=NULL) {
                    pthread_kill(stackExtractor->threadId, SIGUSR1);
                    pthread_join(stackExtractor->threadId, NULL);
                    popStack(&stackExtractor);
                    continuing = 1;
                } else
                    printf("There is no extractors.\n");
                break;
            case '+':  // Изменить размер очереди.
                MAX_MES_COUNT++;
                break;
            case '-':
                if(Queue->countAdded - Queue->countDeleted < MAX_MES_COUNT)
                    MAX_MES_COUNT--;
                break;
            case 'q':  // Конец.
                while(stackFiller != NULL) {
                    pthread_kill(stackFiller->threadId, SIGUSR1);
                    pthread_join(stackFiller->threadId, NULL);
                    popStack(&stackFiller);
                    continuing = 1;
                }
                while(stackExtractor != NULL) {
                    pthread_kill(stackExtractor->threadId, SIGUSR1);
                    pthread_join(stackExtractor->threadId, NULL);
                    popStack(&stackExtractor);
                    continuing = 1;
                }
                printf("All fillers are extractors are killed. End of program.\n");
                continuing = 0;
                break;
        }
    }
                                          // Закрыть семафоры и отсоединить их.
    sem_close(fillSem);
    sem_unlink(FILL_SEM_NAME);
    sem_close(extractSem);
    sem_unlink(EXTRACT_SEM_NAME);
    sem_close(queueAccess);
    sem_unlink(QUEUE_ACCESS_SEM_NAME);

    return 0;
}

void *fillingMessages() {
    sem_t* queueAccess = sem_open(QUEUE_ACCESS_SEM_NAME, 0);       // Открыть семафоры.
    if(queueAccess == SEM_FAILED) {
        printf("Error while opening queue access semaphore.\n");
        exit(EXIT_FAILURE);
    }

    sem_t* fillSem = sem_open(FILL_SEM_NAME, 0);
    if(fillSem == SEM_FAILED) {
        printf("Error while opening filling semaphore.\n");
        exit(EXIT_FAILURE);
    }
    while (continuing) {
        sem_wait(queueAccess);                                   // Ожидание доступа.
        sem_wait(fillSem);

        if (Queue->countAdded - Queue->countDeleted < MAX_MES_COUNT) {  // Добавить, если есть место.
            push(&Queue->ringHead, &Queue->ringTail);
            Queue->countAdded++;
            printf("Added %d message:\n", Queue->countAdded);
            printMes(Queue->ringTail->message);
        } else
            printf("Queue is full!\n");

        sem_post(fillSem);                                       // Отпустить семафор.
        sem_post(queueAccess);
        sleep(3);
    }

    sem_close(queueAccess);                                      // Отсоединить семафор.
    sem_close(fillSem);
}

void *extractingMessages() {
    sem_t* queueAccess = sem_open(QUEUE_ACCESS_SEM_NAME, 0);     // Подключить семафор.
    if(queueAccess == SEM_FAILED) {
        printf("Error while opening queue access semaphore.\n");
        exit(EXIT_FAILURE);
    }

    sem_t* extractSem = sem_open(EXTRACT_SEM_NAME, 0);
    if(extractSem == SEM_FAILED) {
        printf("Error while opening extracting semaphore.\n");
        exit(EXIT_FAILURE);
    }

    while(continuing) {
        sem_wait(queueAccess);                                    // Ожидание доступа.
        sem_wait(extractSem);

        if(Queue->countAdded - Queue->countDeleted > 0) {         // Извлечь, если есть что.
            mes* temp = Queue->ringHead->message;
            pop(&Queue->ringHead, &Queue->ringTail);
            Queue->countDeleted++;
            printf("Delete %d message:\n", Queue->countDeleted);
            printMes(temp);
            free(temp->data);
            free(temp);
        } else
            printf("Queue is empty!\n");

        sem_post(extractSem);                                     // Отпустить семафор.
        sem_post(queueAccess);
        sleep(3);
    } 

    sem_close(queueAccess);                                       // Отсоединить семафор.
    sem_close(extractSem);
}

void changeContinuingStatus() {
    continuing ^= 1;
}