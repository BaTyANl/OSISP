#pragma once
#include <ncurses.h>
#include <string.h>
#include "colors.h"
                        //Панель с информацией
#define WIDTH_INFO 16
#define HEIGHT_INFO 21

#define FOLDER_TYPE "folder"
#define FILE_TYPE "file"
#define SYMBOLIC_LINK_TYPE "symbolic link"

typedef struct info     //Структура с информацией
{
    char* name;         //Имя

    enum types{         //Тип
       folder = 1,
       file,
       symLink
    }types;

    char* path;         //Полный путь
    int size;           //Размер

    enum access{        //Тип доступа
        READ_ONLY = 1,
        READ_WRITE
    }access;

}info;

extern const char* info_fld[];  

void print_info(WINDOW *info_win, info stats);  //Вывод окна
