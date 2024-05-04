#include "normalPanel.h"

void print_normal(WINDOW *normal_win, unsigned char* bytes, int highlight_number){                  //Панель с выводом байт в ASCII
    werase(normal_win);
    box(normal_win, 0, 0);                              //Обводка
    wattron(normal_win, COLOR_PAIR(MENU_GREEN));        //Цвет
    mvwprintw(normal_win, 0, 1, "%s", NORMAL_VALUE);    //Вывод
    wattroff(normal_win, COLOR_PAIR(MENU_GREEN));
    if (bytes != NULL){
        for (int i = 0; i < 19; i++){
            for (int j = 0; j < 16; j++){
                if (highlight_number == 16*i + j + 1) {
                    wattron(normal_win, COLOR_PAIR(MENU_SLCTD_ITEM));
                }
                if ((bytes[16*i + j] > 0 && bytes[16*i + j] < 32) || (bytes[16*i + j] > 126 && bytes[16*i + j] < 160)){
                    mvwprintw(normal_win, i+1, 1 + j, "%lc", bytes[16*i + j] + 0x2654);
                } else {
                    if (bytes[16*i + j] == 0){
                        mvwprintw(normal_win, i+1, 1 + j, "%c", '.');
                    } else {
                        mvwprintw(normal_win, i+1, 1 + j, "%lc", bytes[16*i + j]);
                    }
                }
                if (highlight_number == 16*i + j + 1) {
                    wattroff(normal_win, COLOR_PAIR(MENU_SLCTD_ITEM));
                }
            }  
        }
    }
    wrefresh(normal_win);                               //Обновление
}