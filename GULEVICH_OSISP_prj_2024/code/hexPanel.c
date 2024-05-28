#include "hexPanel.h"

int hex_menu(WINDOW *hex_win, unsigned char* bytes, off_t highlight_bumber, WINDOW* normal_win, WINDOW* block_win){
    int choise;
    int c;
    keypad(hex_win, true);
    print_hex(hex_win, bytes, 1, normal_win, block_win);            //Вывод меню
    print_block(block_win, highlight_bumber);
    while(1) {
        c = wgetch(hex_win);                       //Считывание нажатий
        switch(c) {
        case KEY_LEFT:                              // <-
            if(highlight_bumber % 16 == 1)
                highlight_bumber += 15;
            else
                --(highlight_bumber);
            print_hex(hex_win, bytes, highlight_bumber, normal_win, block_win);            //Вывод меню
            print_block(block_win, highlight_bumber);
        break;
        case KEY_RIGHT:                             // ->
            if(highlight_bumber % 16 == 0)
                highlight_bumber -= 15;
            else
                ++(highlight_bumber);
            print_hex(hex_win, bytes, highlight_bumber, normal_win, block_win);            //Вывод меню
            print_block(block_win, highlight_bumber);
        break;
        case KEY_UP:
            if (highlight_bumber / 16 == 0){
                //вызвать чтение системы заново
                if (block_stats.offset <= 15){
                    block_stats.offset = 0;
                } else {
                    if (highlight_bumber <= 15 && block_stats.offset > 15){
                        block_stats.offset -= 16;
                        if (strcmp(info_stats.type, "Memory file") == 0){
                            readOffset(&bytes);
                        } else {
                            readFile(&bytes, info_stats.path);
                        }
                    }
                }
            } else {
                highlight_bumber -= 16;
            }
            print_hex(hex_win, bytes, highlight_bumber, normal_win, block_win);            //Вывод меню
            print_block(block_win, highlight_bumber);
            break;
        case KEY_DOWN:
            if (highlight_bumber / 16 == 18){
                block_stats.offset += 16;
                if (strcmp(info_stats.type, "Memory file") == 0){
                    readOffset(&bytes);
                } else {
                    readFile(&bytes, info_stats.path);
                }
            } else {
                highlight_bumber += 16;
            }
            print_hex(hex_win, bytes, highlight_bumber, normal_win, block_win);            //Вывод меню
            print_block(block_win, highlight_bumber);
            break;
        case KEY_F(2):
            print_hex(hex_win, bytes, 0, normal_win, block_win);
            print_block(block_win, highlight_bumber);
            return 0;
        }
        //case 10:                                    //Enter
        //    choise = highlight_bumber;
        //    break;
        //}
        print_hex(hex_win, bytes, highlight_bumber, normal_win, block_win);            //Вывод меню
        print_block(block_win, highlight_bumber);
    }
    return choise;
}

void print_hex(WINDOW *hex_win, unsigned char* bytes, off_t highlight_number, WINDOW* normal_win, WINDOW* block_win){                        //Вывод панели с байтами
    box(hex_win, 0, 0);                                 //Обводка окна
    wattron(hex_win, COLOR_PAIR(MENU_GREEN));           //Цвет
    mvwprintw(hex_win, 0, 1, "%s", HEX_VALUE);          //Вывод строки
    wattroff(hex_win, COLOR_PAIR(MENU_GREEN));          
    if (bytes != NULL){
        for (int i = 0; i < 19; i++){
            for (int j = 0; j < 16; j++){
                if (highlight_number == 16*i + j + 1) {
                    wattron(hex_win, COLOR_PAIR(MENU_SLCTD_ITEM));
                }
                mvwprintw(hex_win, i+1, 1 + (j * 3), "%02X", bytes[16*i + j]);
                if (highlight_number == 16*i + j + 1) {
                    wattroff(hex_win, COLOR_PAIR(MENU_SLCTD_ITEM));
                }
            }  
        }
    }
    print_normal(normal_win, bytes, highlight_number);
    wrefresh(hex_win);                                  //Обновление окна
}