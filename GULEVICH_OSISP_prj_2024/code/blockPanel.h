#pragma once

#include <ncurses.h>
#include <string.h>
#include "colors.h"

#define WIDTH_BLOCK 80  //Ширина окна
#define HEIGHT_BLOCK 2  //Высота окна

typedef struct block{   //Структура о блочной инфе
    off_t offset;         //Смещение
    int block;          //Номер блока
    long block_size;     //Размер блока
    int sector;         //Номер сектора в блоке
    int sector_size;
}block;

extern block block_stats;

void print_block(WINDOW *block_win, off_t off);  //Вывод панельки
