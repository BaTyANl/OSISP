#include "normalPanel.h"

void print_normal(WINDOW *normal_win){                  //Панель с выводом байт в ASCII
    box(normal_win, 0, 0);                              //Обводка
    wattron(normal_win, COLOR_PAIR(MENU_GREEN));        //Цвет
    mvwprintw(normal_win, 0, 1, "%s", NORMAL_VALUE);    //Вывод
    wattroff(normal_win, COLOR_PAIR(MENU_GREEN));
    wrefresh(normal_win);                               //Обновление
}