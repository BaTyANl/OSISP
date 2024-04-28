#include "hexPanel.h"

void print_hex(WINDOW *hex_win){                        //Вывод панели с байтами
    box(hex_win, 0, 0);                                 //Обводка окна
    wattron(hex_win, COLOR_PAIR(MENU_GREEN));           //Цвет
    mvwprintw(hex_win, 0, 1, "%s", HEX_VALUE);          //Вывод строки
    wattroff(hex_win, COLOR_PAIR(MENU_GREEN));          
    wrefresh(hex_win);                                  //Обновление окна
}