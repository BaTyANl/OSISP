#pragma once
#include <ncurses.h>
#include "colors.h"
                            //Панель с байтами
#define WIDTH_HEX 46
#define HEIGHT_HEX 21

#define HEX_VALUE "01 02 03 04 05 06 07 08 09 0A 0B 0C 0D OE OF"    //Строка для вывода

void print_hex(WINDOW *hex_win, unsigned char *bytes);            //Вывод