
#include "colors.h"
#include "blockPanel.c"
#include "menuPanel.h"
#include "infoPanel.h"
#include "hexPanel.h"
#include "normalPanel.h"


void init_app();
void init_menu_panel();
void init_block_panel();
void init_info_panel();
void init_hex_panel();
void init_normal_panel();


int main() {
    WINDOW *menu_win;
    WINDOW *info_win;
    WINDOW *hex_win;
    WINDOW *normal_win;
    WINDOW *block_win;

    int highlight = 1;

    info stats;
    block block_stats;

    initscr();
    clear();
    noecho();
    ext_start_color();
    cbreak();
    curs_set(false);

    menu_win = newwin(HEIGHT_MENU, WIDTH_MENU, 0, 0);
    info_win = newwin(HEIGHT_INFO, WIDTH_INFO, 1, 0);
    hex_win = newwin(HEIGHT_HEX, WIDTH_HEX, 1, WIDTH_INFO);
    normal_win = newwin(HEIGHT_NORMAL, WIDTH_NORMAL, 1, WIDTH_INFO + WIDTH_HEX);
    block_win = newwin(HEIGHT_BLOCK, WIDTH_BLOCK, 1 + HEIGHT_INFO, 0);

    refresh();

    print_menu(menu_win, highlight);
    print_info(info_win, stats);
    print_hex(hex_win);
    print_normal(normal_win);
    print_block(block_win, block_stats);
    while(1){
        int choise = menu_choise(menu_win, highlight);

        switch (choise){
            case 1:{
                filePathInput();
                print_hex(hex_win);
                break;
            }
            case 2:{
                getch();
                break;
            }
            case 3:{
                getch();
                break;
            }
            case 4:{
                helpPanel();
                print_hex(hex_win);
                break;
            }
            case 5:{
                goto end;
            }
        }
    }
    end:
    clrtoeol();
    refresh();
    endwin();
    return 0;
}


