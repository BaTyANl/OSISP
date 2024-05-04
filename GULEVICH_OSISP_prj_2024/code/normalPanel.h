#pragma once
#include <ncurses.h>
#include "colors.h"
#include <locale.h>
#include <wchar.h>
#define WIDTH_NORMAL 18
#define HEIGHT_NORMAL 21
#define NORMAL_VALUE "0123456789ABCDEF"     //Строка для читаемого вывода

void print_normal(WINDOW *normal_win, unsigned char* bytes, int highlight_number);      //Вывод панели с байтами в ASCII