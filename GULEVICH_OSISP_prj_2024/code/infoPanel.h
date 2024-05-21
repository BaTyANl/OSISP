#pragma once
#include <ncurses.h>
#include <string.h>
#include "colors.h"
                        //Панель с информацией
#define WIDTH_INFO 13
#define HEIGHT_INFO 21

typedef struct info     //Структура с информацией
{
    char* name;         //Имя
    char* type;
    char* path;         //Полный путь
    int size;           //Размер

    enum access{        //Тип доступа
        READ_ONLY = 1,
        READ_WRITE,
        NO_DATA
    }access;

}info;

//extern info infoStats;

extern const char* info_fld[];  

void print_info(WINDOW *info_win, info stats);  //Вывод окна
