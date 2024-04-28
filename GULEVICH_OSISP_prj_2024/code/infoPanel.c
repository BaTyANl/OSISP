#include "infoPanel.h"

const char* info_fld[] = {  //Сообщения для вывода
    "Type: ",
    "Name: ",
    "Path: ",
    "Size: ",
    "Access type: "
};


void print_stats(WINDOW* info_win, info stats){ //Вывод информации
    int y = 2;
    int x = 1;
    stats.types = file;                         //Тестовая структура
    stats.name = "file.txt";
    stats.path = "D/papka/papka2/papka3/";
    stats.size = 12345;
    stats.access = READ_ONLY;

    wattron(info_win, COLOR_PAIR(INFO_PANEL));          //Цвет
    mvwprintw(info_win, y, 1, "%s", info_fld[0]);       //Вывод 
    wattroff(info_win, COLOR_PAIR(INFO_PANEL));

    if(stats.types == file)                             //Вывод 
        mvwprintw(info_win, ++y, 1, "%s", "File");
    else
        if(stats.types == folder)
            mvwprintw(info_win, ++y, 1, "%s", "Folder");
        else
            mvwprintw(info_win, ++y, 1, "%s", "Link");
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
    wattron(info_win, COLOR_PAIR(INFO_PANEL));          //Цвет
    mvwprintw(info_win, ++y, 1, "%s", info_fld[3]);     //Вывод 
    wattroff(info_win, COLOR_PAIR(INFO_PANEL));

    mvwprintw(info_win, ++y, 1, "%d B", stats.size);       //Вывод 
    y++;

    wattron(info_win, COLOR_PAIR(INFO_PANEL));              //Цвет
    mvwprintw(info_win, ++y, 1, "%s", info_fld[4]);        //Вывод 
    wattroff(info_win, COLOR_PAIR(INFO_PANEL));
    if(stats.access == READ_ONLY)                           //Вывод 
        mvwprintw(info_win, ++y, 1, "%s", "Read-Only");
    else
        mvwprintw(info_win, ++y, 1, "%s", "Read-Write");
}

void print_info(WINDOW *info_win, info stats){              //Создание окна
    box(info_win, 0, 0);                                    //Обводка окна
    wattron(info_win, COLOR_PAIR(MENU_GREEN));              //Цвет
    mvwprintw(info_win, 0, 1, "%s", "Info panel");          //Вывод 
    wattroff(info_win, COLOR_PAIR(MENU_GREEN));
    print_stats(info_win, stats);                           //Вывод информации

    wrefresh(info_win);                                     //Обновление экрана
}