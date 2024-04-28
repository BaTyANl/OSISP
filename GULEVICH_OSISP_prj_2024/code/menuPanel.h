#pragma once
#include <ncurses.h>
#include <string.h>
#include "colors.h"
#include "hexPanel.h"


#define WIDTH_MENU 80
#define HEIGHT_MENU 1

extern const char *choises[];

void print_menu(WINDOW* menu_win, int highlight);
int menu_choise(WINDOW* menu_win, int highlight);
void filePathInput();
void helpPanel();

