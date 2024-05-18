#include "infoPanel.h"

info infoStats;

const char* info_fld[] = {  //Сообщения для вывода
    "Type: ",
    "Name: ",
    "Path: ",
    "Size: ",
    "Access type"
};


void print_stats(WINDOW* info_win, info stats){ //Вывод информации
    int y = 2;
    int x = 1;
    stats.type = ".png";                         //Тестовая структура
    stats.name = "testPhoto";
    stats.path = "home/batyanl/osisp/";
    stats.size = 23357;
    stats.access = READ_ONLY;

    wattron(info_win, COLOR_PAIR(INFO_PANEL));          //Цвет
    mvwprintw(info_win, y, 1, "%s", info_fld[0]);       //Вывод 
    wattroff(info_win, COLOR_PAIR(INFO_PANEL));
    mvwprintw(info_win, ++y, 1, "%s", stats.type);
    y++;

    wattron(info_win, COLOR_PAIR(INFO_PANEL));          //Цвет
    mvwprintw(info_win, ++y, 1, "%s", info_fld[1]);     //Вывод 
    wattroff(info_win, COLOR_PAIR(INFO_PANEL));
    mvwprintw(info_win, ++y, 1, "%s", stats.name);      //Вывод 
    y++;

    wattron(info_win, COLOR_PAIR(INFO_PANEL));          //Цвет
    mvwprintw(info_win, ++y, 1, "%s", info_fld[2]);     //Вывод 
    wattroff(info_win, COLOR_PAIR(INFO_PANEL));
    if(strlen(stats.path) > 13){
        y++;
        for(int i = 0, j = 0; i < strlen(stats.path); i++, j++){    //Вывод с переносом
            mvwaddch(info_win, y, j + x, stats.path[i]);
            if(stats.path[i] == '/'){
                y++;
                j = 0;
                x = 1;
            }
        }
    } else{
        mvwprintw(info_win, ++y, 1, "%s", stats.path);
    }
    y++;
    wattron(info_win, COLOR_PAIR(INFO_PANEL));          //Цвет
    mvwprintw(info_win, ++y, 1, "%s", info_fld[3]);     //Вывод 
    wattroff(info_win, COLOR_PAIR(INFO_PANEL));

    mvwprintw(info_win, ++y, 1, "%d B", stats.size);       //Вывод 
    y++;

    wattron(info_win, COLOR_PAIR(INFO_PANEL));              //Цвет
    mvwprintw(info_win, ++y, 1, "%s", info_fld[4]);        //Вывод 
    wattroff(info_win, COLOR_PAIR(INFO_PANEL));
    if(stats.access == NO_DATA){
        mvwprintw(info_win, ++y, 1, "%s", "N/D");
    } else{
        if(stats.access == READ_ONLY)                           //Вывод 
            mvwprintw(info_win, ++y, 1, "%s", "Read-Only");
        else
            mvwprintw(info_win, ++y, 1, "%s", "Read-Write");
    }
}

void print_info(WINDOW *info_win, info stats){              //Создание окна
    box(info_win, 0, 0);                                    //Обводка окна
    wattron(info_win, COLOR_PAIR(MENU_GREEN));              //Цвет
    mvwprintw(info_win, 0, 1, "%s", "Info panel");          //Вывод 
    wattroff(info_win, COLOR_PAIR(MENU_GREEN));
    print_stats(info_win, stats);                           //Вывод информации

    wrefresh(info_win);                                     //Обновление экрана
}