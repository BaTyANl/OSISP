#include "hexPanel.h"

int hex_menu(WINDOW *hex_win, unsigned char* bytes, int highlight_bumber, off_t offset, WINDOW* normal_win){
    int choise;
    int c;
    keypad(hex_win, true);
    print_hex(hex_win, bytes, 1, offset, normal_win);            //Вывод меню
    while(1) {
        c = wgetch(hex_win);                       //Считывание нажатий
        switch(c) {
        case KEY_LEFT:                              // <-
            if(highlight_bumber % 16 == 1)
                highlight_bumber += 15;
            else
                --(highlight_bumber);
            print_hex(hex_win, bytes, highlight_bumber, offset, normal_win);            //Вывод меню
        break;
        case KEY_RIGHT:                             // ->
            if(highlight_bumber % 16 == 0)
                highlight_bumber -= 15;
            else
                ++(highlight_bumber);
            print_hex(hex_win, bytes, highlight_bumber, offset, normal_win);            //Вывод меню
        break;
        case KEY_UP:
            if (highlight_bumber / 16 == 0){
                //вызвать чтение системы заново
                if (offset <= 15){
                    offset = 0;
                } else {
                    if (highlight_bumber <= 15 && offset > 15){
                        offset -= 16;
                        readOffset(&bytes, offset);
                    }
                }
            } else {
                highlight_bumber -= 16;
            }
            print_hex(hex_win, bytes, highlight_bumber, offset, normal_win);            //Вывод меню
            break;
        case KEY_DOWN:
            if (highlight_bumber / 16 == 18){
                offset += 16;
                readOffset(&bytes, offset);
            } else {
                highlight_bumber += 16;
            }
            print_hex(hex_win, bytes, highlight_bumber, offset, normal_win);            //Вывод меню
            break;
        case KEY_F(2):
            print_hex(hex_win, bytes, 0, offset, normal_win);
            return 0;
        }
        //case 10:                                    //Enter
        //    choise = highlight_bumber;
        //    break;
        //}
        print_hex(hex_win, bytes, highlight_bumber, offset, normal_win);            //Вывод меню
        //if(choise != 0)
        //    break;
    }
    return choise;
}

void print_hex(WINDOW *hex_win, unsigned char* bytes, int highlight_number, off_t offset, WINDOW* normal_win){                        //Вывод панели с байтами
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