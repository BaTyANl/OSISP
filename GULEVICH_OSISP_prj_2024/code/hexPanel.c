#include "hexPanel.h"

void newBytePanel(WINDOW* win_byte){              //Вывод панели с вводом пути к файлу

    wbkgd(win_byte, COLOR_PAIR(TOP_PANEL_COLOR));   //Установка цвета для окна
    box(win_byte, 0, 0);                            //Обозначение границ окна
    mvwprintw(win_byte, 0, 9 , "%s", "Byte changing"); //Вывод строк
    mvwprintw(win_byte, 2, 1 , "%s", "Input new value of byte.");
    mvwprintw(win_byte, 3, 1 , "%s", "Press F1 to cancel.");
    wrefresh(win_byte);                             //Обновление окна
}

void newByteInput(size_t index){                               //Ввод пути к файлу
    WINDOW* win_byte;                               //Окно
    int maxx, maxy;
    getmaxyx(stdscr, maxy, maxx);
    int errFl = 1;
    int newValue;
    while(errFl){
        win_byte = newwin(10, 30, (maxy - 10)/2, (maxx - 30)/2);    //Создание окна
        errFl = 0;
        newBytePanel(win_byte);                       //Вывод окна
        keypad(win_byte, true);                         //Выключение обработки нажатий
        int c = wgetch(win_byte);
        if(c == KEY_F(1)){                              //F1 - Выход
            delwin(win_byte);
            return;
        }   
        curs_set(1);                                    //Включение отображения курсора
        echo();           
        mvwscanw(win_byte, 4, 13, "%d", &newValue);        
        noecho();
        curs_set(0);
        mvwprintw(win_byte, 5, 1, "Input preview: ");
        if ((newValue > 0 && newValue < 32) || (newValue > 126 && newValue < 160)){
            mvwprintw(win_byte, 5, 18, "%lc", newValue + 0x028E);
        } else {
            if (newValue == 0){
                mvwprintw(win_byte, 5, 18, "%c", '.');
            } else {
                mvwprintw(win_byte, 5, 18, "%lc", newValue);
            }
        }
        c = wgetch(win_byte);
        if(c == KEY_F(1)){                              //F1 - Выход
            delwin(win_byte);
            return;
        }
        int error = changeByte(index-1, newValue);

        if (error == 2){
            printError("Changing error", "Invalid value", "Value is 0-255");
            errFl = 1;
        }
    }
    delwin(win_byte);                       //Освобождение памяти
}

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
            if ((highlight_bumber-1) / 16 == 0){
                //вызвать чтение системы заново
                if (block_stats.offset <= 16){
                    block_stats.offset = 0;
                } else {
                    if (highlight_bumber <= 16 && block_stats.offset > 15){
                        block_stats.offset -= 16;
                        if (strcmp(info_stats.type, "Memory file") == 0){
                            readOffset(&bytes);
                        } else {
                            if (block_stats.offset%4096 < 16){
                               highlight_bumber += 288;
                               block_stats.offset -= 304;
                            }
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
            if ((highlight_bumber-1) / 16 == 18){
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
        case 10:
            if (info_stats.access == READ_WRITE){
                newByteInput(highlight_bumber);
                readFile(&bytes, info_stats.path);
            }
            break;
        }

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