#pragma once
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
                                //Цвета
#define COLOR_VIOLET 9
#define COLOR_DEEP_BLUE 10
#define COLOR_ORANGE 11
#define COLOR_DEEP_PINK 12
#define COLOR_GRAY 13
#define COLOR_BEIGE 14
#define COLOR_EXC 46
#define COLOR_TEAL 47
#define MENU_GREEN 30
#define MENU_YELLOW 31
#define MENU_BLUE 32
#define MENU_RED 33
#define MENU_GRAY 34
#define MENU_WHITE 35
#define MENU_BEIGE 36
#define INFO_PANEL 45

#define MENU_SLCTD_ITEM 37

#define TOP_PANEL_COLOR 38
#define SLCTD_TOP_PANEL 39

#define BOTTOM_PANEL_ITEM 40
#define BOTTOM_PANEL_SLCTD_ITEM 41

#define EXCEPTION_COLOR 42
#define SLCTD_EXCEPTION_COLOR 43
#define WARNING_BOX_COLOR 44

#define U_ARROW_UP L"\u2191"
#define U_ARROW_DOWN L"\u2193"

#define CENTER_SCR(start_x, start_y) start_x = (LINES - 1) / 2; start_y = (COLS - 1) / 2

void clear_y_str(WINDOW* win, int y, int start_x, int len);
void ext_start_color();