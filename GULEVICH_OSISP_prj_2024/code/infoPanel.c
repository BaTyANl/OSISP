#include "infoPanel.h"

info info_stats;

const char* info_fld[] = {  //Сообщения для вывода
    "Type: ",
    "Name: ",
    "Path: ",
    "Size: ",
    "Access type"
};


void print_stats(WINDOW* info_win){ //Вывод информации
    int y = 2;
    int x = 1;


    wattron(info_win, COLOR_PAIR(INFO_PANEL));          //Цвет
    mvwprintw(info_win, y, 1, "%s", info_fld[0]);       //Вывод 
    wattroff(info_win, COLOR_PAIR(INFO_PANEL));
    mvwprintw(info_win, ++y, 1, "%s", info_stats.type);
    y++;

    wattron(info_win, COLOR_PAIR(INFO_PANEL));          //Цвет
    mvwprintw(info_win, ++y, 1, "%s", info_fld[1]);     //Вывод 
    wattroff(info_win, COLOR_PAIR(INFO_PANEL));
    mvwprintw(info_win, ++y, 1, "%s", info_stats.name);      //Вывод 
    y++;

    wattron(info_win, COLOR_PAIR(INFO_PANEL));          //Цвет
    mvwprintw(info_win, ++y, 1, "%s", info_fld[2]);     //Вывод 
    wattroff(info_win, COLOR_PAIR(INFO_PANEL));
    if(strlen(info_stats.path) > 13){
        y++;
        for(int i = 0, j = 0; i < strlen(info_stats.path); i++, j++){    //Вывод с переносом
            mvwaddch(info_win, y, j + x, info_stats.path[i]);
            if(info_stats.path[i] == '/'){
                y++;
                j = 0;
                x = 1;
            }
        }
    } else{
        mvwprintw(info_win, ++y, 1, "%s", info_stats.path);
    }
    y++;
    wattron(info_win, COLOR_PAIR(INFO_PANEL));          //Цвет
    mvwprintw(info_win, ++y, 1, "%s", info_fld[3]);     //Вывод 
    wattroff(info_win, COLOR_PAIR(INFO_PANEL));

    mvwprintw(info_win, ++y, 1, "%d B", info_stats.size);       //Вывод 
    y++;

    wattron(info_win, COLOR_PAIR(INFO_PANEL));              //Цвет
    mvwprintw(info_win, ++y, 1, "%s", info_fld[4]);        //Вывод 
    wattroff(info_win, COLOR_PAIR(INFO_PANEL));
    if(info_stats.access == NO_DATA){
        mvwprintw(info_win, ++y, 1, "%s", "N/D");
    } else{
        if(info_stats.access == READ_ONLY)                           //Вывод 
            mvwprintw(info_win, ++y, 1, "%s", "Read-Only");
        else
            mvwprintw(info_win, ++y, 1, "%s", "Read-Write");
    }
}

void print_info(WINDOW *info_win){              //Создание окна
    box(info_win, 0, 0);                                    //Обводка окна
    wattron(info_win, COLOR_PAIR(MENU_GREEN));              //Цвет
    mvwprintw(info_win, 0, 1, "%s", "Info panel");          //Вывод 
    wattroff(info_win, COLOR_PAIR(MENU_GREEN));
    print_stats(info_win);                           //Вывод информации

    wrefresh(info_win);                                     //Обновление экрана
}