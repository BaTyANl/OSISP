#include "infoPanel.h"

const char* info_fld[] = {  //Сообщения для вывода
    "Type: ",
    "Name: ",
    "Path: ",
    "Size: ",
    "Access type: "
};


void print_stats(WINDOW* info_win, info stats){
    int y = 2;
    int x = 1;
    stats.types = file;
    stats.name = "file.txt";
    stats.path = "D/papka/papka2/papka3/";
    stats.size = 12345;
    stats.access = READ_ONLY;

    wattron(info_win, COLOR_PAIR(INFO_PANEL));
    mvwprintw(info_win, y, 1, "%s", info_fld[0]);
    wattroff(info_win, COLOR_PAIR(INFO_PANEL));

    if(stats.types == file)
        mvwprintw(info_win, ++y, 1, "%s", "File");
    else
        if(stats.types == folder)
            mvwprintw(info_win, ++y, 1, "%s", "Folder");
        else
            mvwprintw(info_win, ++y, 1, "%s", "Link");
    y++;

    wattron(info_win, COLOR_PAIR(INFO_PANEL));
    mvwprintw(info_win, ++y, 1, "%s", info_fld[1]);
    wattroff(info_win, COLOR_PAIR(INFO_PANEL));
    mvwprintw(info_win, ++y, 1, "%s", stats.name);
    y++;

    wattron(info_win, COLOR_PAIR(INFO_PANEL));
    mvwprintw(info_win, ++y, 1, "%s", info_fld[2]);
    wattroff(info_win, COLOR_PAIR(INFO_PANEL));
    if(strlen(stats.path) > 13){
        y++;
        for(int i = 0, j = 0; i < strlen(stats.path); i++, j++){
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
    wattron(info_win, COLOR_PAIR(INFO_PANEL));
    mvwprintw(info_win, ++y, 1, "%s", info_fld[3]);
    wattroff(info_win, COLOR_PAIR(INFO_PANEL));

    mvwprintw(info_win, ++y, 1, "%d B", stats.size);
    y++;

    wattron(info_win, COLOR_PAIR(INFO_PANEL));
    mvwprintw(info_win, ++y, 1, "%s", info_fld[4]);
    wattroff(info_win, COLOR_PAIR(INFO_PANEL));
    if(stats.access == READ_ONLY)
        mvwprintw(info_win, ++y, 1, "%s", "Read-Only");
    else
        mvwprintw(info_win, ++y, 1, "%s", "Read-Write");
}

void print_info(WINDOW *info_win, info stats){
    box(info_win, 0, 0);
    wattron(info_win, COLOR_PAIR(MENU_GREEN));
    mvwprintw(info_win, 0, 1, "%s", "Info panel");
    wattroff(info_win, COLOR_PAIR(MENU_GREEN));
    print_stats(info_win, stats);

    wrefresh(info_win);
}