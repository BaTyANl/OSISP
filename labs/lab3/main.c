
#include "stack.h"



#define REPEAT_COUNT 101

typedef struct {
    int firstVal;
    int secondVal;
} PAIR;

node* head = NULL;

PAIR pair = {0, 0};
int makeValues = 1;
int zeroZeroCount = 0;
int zeroOneCount = 0;
int oneZeroCount = 0;
int oneOneCount = 0;
int canShow = 1;

void takeStatistics() {
    if (pair.firstVal == 0 && pair.secondVal == 0)
        zeroZeroCount++;
    else if (pair.firstVal == 0 && pair.secondVal == 1)
        zeroOneCount++;
    else if (pair.firstVal == 1 && pair.secondVal == 0)
        oneZeroCount++;
    else
        oneOneCount++;
    makeValues = 0;
}


void forbid() {
    canShow = 0;
}

void allow() {
    canShow = 1;
}

void allowAfterP() {
    sendAllow(-1);
}

void printStat() {
    printf("Process pid = %d, ppid = %d, {0,0} - %d, {0,1} - %d, {1,0} - %d, {1,1} - %d\n",
           getpid(), getppid(), zeroZeroCount, zeroOneCount, oneZeroCount, oneOneCount);
}

void cycle() {
    int currentRepeat = 0;
    while(1) {
        if(currentRepeat == REPEAT_COUNT) {
            currentRepeat = 0;
            if (canShow)
                printStat();
        }
        alarm(1);
        while (makeValues) {
            if (pair.firstVal == 0 && pair.secondVal == 0)
                pair.secondVal = 1;
            else if (pair.firstVal == 0 && pair.secondVal == 1) {
                pair.firstVal = 1;
                pair.secondVal = 0;
            } else if (pair.firstVal == 1 && pair.secondVal == 0)
                pair.secondVal = 1;
            else {
                pair.firstVal = 0;
                pair.secondVal = 0;
            }
        }
        makeValues = 1;
        currentRepeat++;
    }
}

void makeFork() {
    pid_t chpid = fork();                                      // Создание процесса.
    if(chpid == 0) {
        signal(SIGALRM, takeStatistics);                       // Обработчик сигнала будильника.
        cycle();
    } else if (chpid == -1) {
        printf("Error occured, error code - %d\n", errno);     // Ошибка.
        exit(errno);
    } else {
        pushHead(&head, chpid);                                    // Сохранение ид процесса.
        printf("Process with pid %d created.\n", chpid);
    }
}

void delLastFork() {
    kill(head->pid, SIGKILL);                                  // Сигнал завершения процессу.
    printf("Process C_%d with pid %d deleted.\n", head->num, head->pid);
    popHead(&head);
}

void sendForbid(int procNum) {
    if (procNum == -1) {
        node *temp = head;
        while (temp) {
            kill(temp->pid, SIGUSR2);                          // Сигнал запрщения вывода всем.
            temp = temp->next;
        }
    } else {
        node *temp = head;
        while (temp && temp->num != procNum)
            temp = temp->next;
        if (temp)
            kill(temp->pid, SIGUSR2);                          // Сигнал запрещения вывода одному.
    }
}

void sendAllow(int procNum) {
    if (procNum == -1) {
        node *temp = head;
        while (temp) {
            kill(temp->pid, SIGUSR1);                          // Сигнал разрешения вывода всем.
            temp = temp->next;
        }
    } else {
        node *temp = head;
        while (temp && temp->num != procNum)
            temp = temp->next;
        if (temp)
            kill(temp->pid, SIGUSR1);                          // Сигнал разрешения вывода одному.
    }
}

void forbidAndShow(int procNum) { 
    sendForbid(-1);                                            // Запретить всем.
    node *temp = head;
    while (temp && temp->num != procNum)
        temp = temp->next;
    if (temp)
        kill(temp->pid, SIGINT);                               // Вывести данные указанного процесса.
    signal(SIGALRM, allowAfterP);
    alarm(5);                                                  // Таймер чтобы вернуть всё назад.
}

int main() {
    signal(SIGINT, printStat);                                                  // Сигнал вывода информации.
    signal(SIGUSR1, allow);                                                     // Сигнал разрешения вывода данных.
    signal(SIGUSR2, forbid);                                                    // Сигнал запрещения вывода данных.

    int cont = 1;
    while(cont) {
        char ch = getchar(), n;
        int num = -1;
        while((n=getchar())!='\n') {
            if (num == -1) num++;
            num *= 10;
            num += n - '0';
        }
        switch(ch) {
            case '+':
                makeFork();                                                    // Создать процесс.
                break;
            case '-':
                delLastFork();                                                 // Удалить процесс.
                break;
            case 'l':
                printf("Process P with pid = %d\n", getpid());                 // Вывести все процессы.
                show(head);
                break;
            case 'k':
                while(head)
                    delLastFork();                                             // Удалить все.
                break;
            case 's':
                sendForbid(num);                                               // Запретить.
                break;
            case 'g':
                sendAllow(num);                                                // Разрешить.
                break;
            case 'p':
                forbidAndShow(num);                                            // Вывести данные одним процессом, запретив другим.
                break;
            case 'q':
                while(head)
                    delLastFork();                                             // Конец.
                printf("All processes are deleted. Program ends.\n");
                cont = 0;
                break;
        }
    }

    return 0;
}
