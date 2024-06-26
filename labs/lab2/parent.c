#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <locale.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;

int includeString(const char* str1, const char* str2) {     //Проверка вхождения одной строки в другую.
    for(size_t i = 0; i<strlen(str2); i++)
        if(str1[i]!=str2[i])
            return 0;
    return 1;
}

char* scanEnvp(char* envp[]) {                              
    int i = 0;
    while(envp[i]) {
        if(includeString(envp[i], "CHILD_PATH"))            // Обход всех параметров и проверка на совпадение.
            break;
        i++;
    }
    if(envp[i]==NULL)
        return NULL;
    char* result = (char*)calloc(strlen(envp[i]) - 10, sizeof(char));
    for(size_t j = 0; j<strlen(envp[i]); j++)                                 
        result[j] = envp[i][j+11];
    result[strlen(envp[i])-11] = '\0';
    return result;
}

int compare(const void *a, const void *b) {
    return strcoll(*(const char **)a, *(const char **)b);
}

void incName(char** name) {
    if ((*name)[7] == '9') {
        (*name)[6]++;
        (*name)[7] = 0;
    } else
        (*name)[7]++;
}

int main(int argc, char* argv[], char* envp[]) {

    setlocale(LC_COLLATE, "C");                                                      // Установить локаль.

    int i = 0;
    while (envp[i++]);                                                               // Узнать число параметров среды.
    qsort(envp, i-1, sizeof(char*), compare);                                        // Сортировка.
    i = 0;
    while(envp[i]) {
        printf("%s\n", envp[i++]);
    }

    char *childName = (char*)calloc(9, sizeof(char));
    strcpy(childName, "child_00");

    while(1) {
        char key = getchar();                                      
        while (getchar() != '\n')
            continue;
        if (key == 'q')
            break;
        else if (key == '+' || key == '*' || key == '&') {
            pid_t chpid = fork();                                                    // Новый процесс.
            if (chpid == 0) {
                char *childDir = NULL;
                switch (key) {                                                       // Получаем путь к программе сhild в соответствии с нажатой клавишей.
                    case '+':
                        childDir = getenv("CHILD_PATH");
                        break;
                    case '*':
                        childDir = scanEnvp(envp);
                        break;
                    case '&':
                        childDir = scanEnvp(environ);
                        break;
                }
                if (childDir) {
                    char *newArgv[] = {childName, argv[1], &key, NULL};
                    execve(childDir, newArgv, envp);                                // Вызов программы.
                } else {
                    printf("Error occured, path not find.\n");
                }
            } else if (chpid == -1) {
                printf("Error occured, error code - %d\n", errno);
                exit(errno);
            } else {
                incName(&childName);                                                // Увеличить номер процесса.
            }
        } else
            printf("Unknown key. Press '+', '*', '&' or q.\n");
        waitpid(-1, NULL, WNOHANG);                                                 // Ожидание завершения процесса.
    }

    free(childName);

    return 0;
}
