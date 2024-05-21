#include "errorWindow.h"


void printErrorPanel(WINDOW* e_win, const char* table_name, const char* error_type, const char *error){
    wbkgd(e_win, COLOR_PAIR(EXCEPTION_COLOR));   //Установка цвета для окна
    box(e_win, 0, 0);                            //Обозначение границ окна
    mvwprintw(e_win, 0, 8 , "%s", table_name); //Вывод строк
    mvwprintw(e_win, 3, 1 , "%s", error_type);
    mvwprintw(e_win, 4, 1 , "%s", error);
    wattron(e_win, COLOR_PAIR(SLCTD_EXCEPTION_COLOR));
    mvwprintw(e_win, 9, 11, "%s", "[  OK  ]");
    wattroff(e_win, COLOR_PAIR(SLCTD_EXCEPTION_COLOR));
    wrefresh(e_win);                             //Обновление окна
}

void printError(const char* table_name, const char* error_type, const char *error){
    WINDOW* e_win;                            //Окно
    int maxx, maxy;
    getmaxyx(stdscr, maxy, maxx);
    e_win = newwin(10, 30, (maxy - 10)/2, (maxx - 30)/2);    //Создание окна
    printErrorPanel(e_win, table_name, error_type, error);   //Вывод окна
    keypad(e_win, true);                                     //Выключение обработки нажатий
    while(1){
        int c = wgetch(e_win);
        if(c == '\n'){                                          //F1 - Выход
            delwin(e_win);
            return;
        }
    }
}