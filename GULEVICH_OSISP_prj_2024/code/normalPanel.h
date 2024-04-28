#pragma once
#include <ncurses.h>
#include "colors.h"

#define WIDTH_NORMAL 18
#define HEIGHT_NORMAL 21
#define NORMAL_VALUE "0123456789ABCDEF"     //Строка для читаемого вывода

void print_normal(WINDOW *normal_win);      //Вывод панели с байтами в ASCII