#include "normalPanel.h"

void print_normal(WINDOW *normal_win){
    box(normal_win, 0, 0);
    wattron(normal_win, COLOR_PAIR(MENU_GREEN));
    mvwprintw(normal_win, 0, 1, "%s", NORMAL_VALUE);
    wattroff(normal_win, COLOR_PAIR(MENU_GREEN));
    wrefresh(normal_win);
}