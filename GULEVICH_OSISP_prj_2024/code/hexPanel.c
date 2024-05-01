#include "hexPanel.h"

void print_hex(WINDOW *hex_win, unsigned char* bytes){                        //Вывод панели с байтами
    box(hex_win, 0, 0);                                 //Обводка окна
    wattron(hex_win, COLOR_PAIR(MENU_GREEN));           //Цвет
    mvwprintw(hex_win, 0, 1, "%s", HEX_VALUE);          //Вывод строки
    wattroff(hex_win, COLOR_PAIR(MENU_GREEN));          
    if (bytes != NULL){
        for (int i = 0; i < 19; i++){
            for (int j = 0; j < 16; j++){
                mvwprintw(hex_win, i+1, 1 + (j * 3), "%02X", bytes[16*i + j]);
            }  
        }
    }
    wrefresh(hex_win);                                  //Обновление окна
}