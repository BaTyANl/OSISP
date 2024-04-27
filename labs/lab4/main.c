
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
#define SHARED_MEMORY_NAME "/queue_messages"

int continuing = 1;

void fillingMessages();          // Заполнять.
void extractingMessages();       // Извлекать.
void changeContinuingStatus();   // Инвертировать значение переменной продолжения.

stackNode* stackFiller = NULL;             // Процессы добавления.
stackNode* stackExtractor = NULL;          // Процессы удаления.
 
int main() {
    srand(time(NULL));

    shm_unlink(SHARED_MEMORY_NAME);             // Удаление, если созданы, семафоров и совместной памяти.
    sem_unlink(FILL_SEM_NAME);
    sem_unlink(EXTRACT_SEM_NAME);
    sem_unlink(QUEUE_ACCESS_SEM_NAME);

    signal(SIGUSR1, changeContinuingStatus);    // Сигнал остановки работы.
    //Параметры shm_open: 1 - название, 2 - флаги(если существует, то ошибка).
    int shm_fd = shm_open(SHARED_MEMORY_NAME, O_CREAT | O_RDWR, 0666);     // Открыть совместо используемую память для чтения и записи всем.
    if(shm_fd == -1) {
        printf("Error while creating shared memory.\n");
        exit(EXIT_FAILURE);
    }                                                                      // Выделить место под заданное количество элементов очереди.
    //Параметры функции: 1 - дескриптор, 2 - размер.
    ftruncate(shm_fd, sizeof(queue)+MAX_MES_COUNT*sizeof(ringNode)+MAX_MES_COUNT*sizeof(mes));
    //Функция отображает файл в память, 1 - адрес памяти, 2 - длина, 3 - флаги, определяющие режимы доступа к памяти(чтение и запись), 
    //4 - флаги доп параметров отображения памяти(общее с другими процессами), 5 - дескриптор открытого файла, 6 - смещение. 
    queue* Queue = mmap(NULL, sizeof(queue)+MAX_MES_COUNT*sizeof(ringNode)+MAX_MES_COUNT*sizeof(mes), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(Queue == MAP_FAILED) {
        printf("Error while mapping shared data.\n");
        exit(EXIT_FAILURE);
    }
    Queue->ringHead = 0;                                                   // Значение указателей по умолчанию.
    Queue->ringTail = 0;
    Queue->countDeleted = 0;
    Queue->countAdded = 0;
    Queue->currentPlaceToWrite = (uintptr_t)Queue + sizeof(queue);         // Место для записи.

    sem_t* fillSem;                                                        // Инициализация семафоров.
    //Параметры sem_open: 1 - имя, 2 - флаги(если существует, то выдается ошибка), 3 - режим(доступен для всех процессов), 4 - начальное значение семафора.
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
            case 'w': { 
                pid_t pid = fork();                                       // Создание процесса заполнения.
                if(pid == -1) {
                    printf("Error occurred while creating new filler, error code %d.\n", errno);
                    exit(errno);
                } else if(pid == 0) {
                    fillingMessages();                                    //Само заполнение.
                    exit(0);
                } else
                    pushStack(&stackFiller, pid);
                break;
            }
            case 's': 
                if(stackFiller!=NULL) {                                   // Удаление процесса заполнения.
                    kill(stackFiller->pid, SIGUSR1);
                    waitpid(stackFiller->pid, NULL, 0);
                    popStack(&stackFiller);
                } else
                    printf("There is no fillers.\n");
                break;
            case 'e': { 
                pid_t pid = fork();                                       // Создание процесса извлечения.
                if(pid == -1) {
                    printf("Error occurred while creating new extractor, error code %d.\n", errno);
                    exit(errno);
                } else if(pid == 0) {
                    extractingMessages();                                 //Само извлечение.
                    exit(0);
                } else
                    pushStack(&stackExtractor, pid);
                break;
            }
            case 'd':
                if(stackExtractor!=NULL) {                                // Удаление процесса извлечения.
                    kill(stackExtractor->pid, SIGUSR1);
                    waitpid(stackExtractor->pid, NULL, 0);
                    popStack(&stackExtractor);
                } else
                    printf("There is no extractors.\n");
                break;
            case 'q':
                while(stackFiller != NULL) {                              // Конец с завершением всех процессов.
                    kill(stackFiller->pid, SIGUSR1);
                    waitpid(stackFiller->pid, NULL, 0);
                    popStack(&stackFiller);
                }
                while(stackExtractor != NULL) {
                    kill(stackExtractor->pid, SIGUSR1);
                    waitpid(stackExtractor->pid, NULL, 0);
                    popStack(&stackExtractor);
                }
                printf("All fillers are extractors are killed. End of program.\n");
                continuing = 0;
                break;
        }
    }
    //Освобождение памяти: 1 - указатель на начало отображенной памяти, 2 - размер памяти.
    munmap(Queue, sizeof(queue)+MAX_MES_COUNT*sizeof(ringNode)+MAX_MES_COUNT*sizeof(mes));
    close(shm_fd);
    shm_unlink(SHARED_MEMORY_NAME);

    sem_close(fillSem);                                                    // Освобождение семафоров.
    sem_unlink(FILL_SEM_NAME);
    sem_close(extractSem);
    sem_unlink(EXTRACT_SEM_NAME);
    sem_close(queueAccess);
    sem_unlink(QUEUE_ACCESS_SEM_NAME);

    return 0;
}

void fillingMessages() {
    int shm_fd = shm_open(SHARED_MEMORY_NAME, O_RDWR, 0666);     // Открыть совместно используемую память.
    if(shm_fd == -1) {
        printf("Error while opening shared memory.\n");
        exit(EXIT_FAILURE);
    }
                                                                 // Отобразить её.
    queue* Queue = mmap(NULL, sizeof(queue)+MAX_MES_COUNT*sizeof(ringNode)+MAX_MES_COUNT*sizeof(mes), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(Queue == MAP_FAILED) {
        printf("Error while mapping shared memory.\n");
        exit(EXIT_FAILURE);
    }
                                                                 // Открыть семафоры.
    sem_t* queueAccess = sem_open(QUEUE_ACCESS_SEM_NAME, 0);
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
        sem_wait(queueAccess);                                   // Ожидание доступа к памяти и заполнению.
        sem_wait(fillSem);

        if (Queue->countAdded - Queue->countDeleted < MAX_MES_COUNT) {    // Добавить, если есть место.
            push(Queue);
            Queue->countAdded++;
            printf("Added %d message:\n", Queue->countAdded);
            printMes((mes*)(((ringNode*)(Queue->ringTail + (uintptr_t)Queue))->message));
        } else
            printf("Queue is full!\n");

        sem_post(fillSem);                                       // Освободить семафоры.
        sem_post(queueAccess);
        sleep(3);
    }
                                                                 // Отсоединить память.
    munmap(Queue, sizeof(Queue)+MAX_MES_COUNT*sizeof(ringNode)+MAX_MES_COUNT*sizeof(mes));
    close(shm_fd);

    sem_close(queueAccess);                                      // Закрыть семафоры.
    sem_close(fillSem);
}
void extractingMessages() {
    int shm_fd = shm_open(SHARED_MEMORY_NAME, O_RDWR, 0666);     // Открыть совместо используемую память.
    if(shm_fd == -1) {
        printf("Error while opening shared memory. Code: %d\n", errno);
        exit(EXIT_FAILURE);
    }
                                                                 // Отобразить совместо используемую память.
    queue* Queue = mmap(NULL, sizeof(queue)+MAX_MES_COUNT*sizeof(ringNode)+MAX_MES_COUNT*sizeof(mes), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(Queue == MAP_FAILED) {
        printf("Error while mapping shared memory.\n");
        exit(EXIT_FAILURE);
    }
                                                                 // Открыть семафоры.
    sem_t* queueAccess = sem_open(QUEUE_ACCESS_SEM_NAME, 0);
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
        sem_wait(queueAccess);                                   // Ожидание доступа к памяти и чтению.
        sem_wait(extractSem);

        if(Queue->countAdded - Queue->countDeleted > 0) {        // Чтение, если есть что читать.
            printf("Delete %d message:\n", Queue->countDeleted+1);
            printMes((mes*)(((ringNode*)(Queue->ringHead + (uintptr_t)Queue))->message));
            pop(Queue);
            Queue->countDeleted++;
        } else
            printf("Queue is empty!\n");

        sem_post(extractSem);                                    // Разблокировать семафоры.
        sem_post(queueAccess);
        sleep(3);
    }
                                                                 // Отсоединить память.
    munmap(Queue, sizeof(queue)+MAX_MES_COUNT*sizeof(ringNode)+MAX_MES_COUNT*sizeof(mes));
    close(shm_fd);

    sem_close(queueAccess);                                      // Закрыть семафоры.
    sem_close(extractSem);
}

void changeContinuingStatus() {
    continuing ^= 1;
}