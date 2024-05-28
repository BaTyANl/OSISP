#pragma once
#include <ncurses.h>
#include "colors.h"
#include "normalPanel.h"
#include "memoryWalk.h"
#include "blockPanel.h"
#include "hexPanel.h"
#include "infoPanel.h"
#include "fileWalk.h"
#include "newByte.h"
#include "errorWindow.h"
                            //Панель с байтами
#define WIDTH_HEX 49
#define HEIGHT_HEX 21

#define HEX_VALUE "00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D OE OF"    //Строка для вывода

void print_hex(WINDOW *hex_win, unsigned char *bytes, off_t highlight_bumber, WINDOW* normal_win, WINDOW* block_win);            //Вывод
int hex_menu(WINDOW *hex_win, unsigned char* bytes, off_t highlight_bumber, WINDOW* normal_win, WINDOW* block_win);