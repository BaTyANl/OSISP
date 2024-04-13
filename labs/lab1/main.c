#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include "queue.h"
#define STANDART_DIR "."

const char* newPath(const char* olddir, const char* newdir){
    char* resdir = (char*)malloc((strlen(olddir)+ strlen(newdir) + 2) * sizeof(char));
    for (int i = 0; i < strlen(olddir); i++){
        resdir[i] = olddir[i];
    }
    resdir[strlen(olddir)] = '/';
    for(int i = 0; i < strlen(newdir); i++){
        resdir[strlen(olddir) + 1 + i] = newdir[i];
    }
    resdir[strlen(olddir) + strlen(newdir) + 1] = '\0';
    return resdir;
}

void printDir(const char* path, int l, int d, int f, int s, node** head, node** tail){
    DIR *dir = opendir(path);
    if(!dir) {
        perror("opendir error");
        exit(errno);
    }
    struct dirent *curdir;
    while(1){
        curdir = readdir(dir);
        if (curdir == NULL){
            if(errno) {
                perror("readdir error");
                exit(errno);
            }
            break;
        }
        switch (curdir->d_type) {
            case DT_DIR:{
                if(strcmp(curdir->d_name, ".") != 0 && strcmp(curdir->d_name, "..") != 0){
                    if(d == 1){
                        pushQueue(head, tail, newPath(path, curdir->d_name));
                    }
                    printDir(newPath(path, curdir->d_name), l, d, f, s, head, tail);
                }
                break;
            }
            case DT_LNK:{
                if(l == 1){
                    pushQueue(head, tail, newPath(path, curdir->d_name));
                }
                break;
            }
            case DT_REG:{
                if (f == 1){
                    pushQueue(head, tail, newPath(path, curdir->d_name));
                }
                break;
            }
        }
    }
    closedir(dir);
}
int main(int argc, char* argv[]) {
    struct stat bufStat;
    node* head = NULL;
    node* tail = NULL;
    int opt;
    int l = 0;
    int d = 0;
    int f = 0;
    int s = 0;
    while ((opt = getopt(argc, argv, "ldfs")) != -1){
        switch(opt){
            case 'l':{
                l = 1;
                break;
            }
            case 'd':{
                d = 1;
                break;
            }
            case 'f':{
                f = 1;
                break;
            }
            case 's':{
                s = 1;
                break;
            }
            default:{
                perror("Unknown option");
                exit(1);
            }
        }
    }
    if (!l && !d && !f){
        l = 1;
        d = 1;
        f = 1;
    }
    if (optind < argc){
        if(stat(argv[optind], &bufStat) == 0 && S_ISDIR(bufStat.st_mode)){
            printDir(argv[optind], l, d, f, s, &head, &tail);
        }else{
            printDir(STANDART_DIR, l, d, f, s, &head, &tail);
        }
    }else{
        printDir(STANDART_DIR, l, d, f, s, &head, &tail);
    }
    if (s == 1){
        sortQueue(head);
    }
    showQueue(head);
    clearQueue(&head, &tail);
    return 0;
}
