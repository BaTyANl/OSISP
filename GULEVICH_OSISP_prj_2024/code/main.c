
#include "colors.h"
#include "blockPanel.c"
#include "menuPanel.h"
#include "infoPanel.h"
#include "hexPanel.h"
#include "normalPanel.h"

void init_app();            //Инициализация приложения
void init_menu_panel();     //Инициализация меню
void init_block_panel();    //Инициализация панели с блочной информацией
void init_info_panel();     //Инициализация панели информации
void init_hex_panel();      //Инициализация панели байт
void init_normal_panel();   //Инициализация панели байт в ASCII


int main() {
    setlocale(LC_ALL, "");
    WINDOW *menu_win;       //Окна
    WINDOW *info_win;
    WINDOW *hex_win;
    WINDOW *normal_win;
    WINDOW *block_win;  
    info infoStats;
    block blockStats;
    unsigned char *bytes;
    bytes = (unsigned char*)calloc(304, sizeof(unsigned char));
    int highlight = 1;      //Переменная подсветки выбранного элемента меню
    off_t offset;


    initscr();              //Инициализация ncurses
    clear();
    noecho();               //Отключение показа вводимых символов
    ext_start_color();      //Подключение цветов
    cbreak();               //Вводимые символы передаются программе сразу после ввода
    curs_set(false);        //Отключение курсора
                            //Инициализация окон
    menu_win = newwin(HEIGHT_MENU, WIDTH_MENU, 0, 0);
    info_win = newwin(HEIGHT_INFO, WIDTH_INFO, 1, 0);
    hex_win = newwin(HEIGHT_HEX, WIDTH_HEX, 1, WIDTH_INFO);
    normal_win = newwin(HEIGHT_NORMAL, WIDTH_NORMAL, 1, WIDTH_INFO + WIDTH_HEX);
    block_win = newwin(HEIGHT_BLOCK, WIDTH_BLOCK, 1 + HEIGHT_INFO, 0);

    refresh();                      //Обновление окна терминала

    print_menu(menu_win, highlight);        //Вывод всех панелей 
    print_info(info_win, infoStats);
    print_hex(hex_win, bytes, 0, offset, normal_win);
    print_block(block_win, blockStats);
    while(1){
        int choise = menu_choise(menu_win, highlight);  //Выбор меню

        switch (choise){
            case 1:{
                filePathInput();        //Вызов панели с вводом файла
                //print_hex(hex_win);
                break;
            }
            case 2:{
                offsetInput(&bytes, &offset);
                print_hex(hex_win, bytes, 0, offset, normal_win);
                break;
            }
            case 3:{
                getch();
                break;
            }
            case 4:{
                helpPanel();            //Вызов панели с помощью
                //print_hex(hex_win);
                break;
            }
            case 11:{
                hex_menu(hex_win, bytes, 1, offset, normal_win);
                break;
            }
            case 5:{
                goto end;
            }
        }
    }
    end:
    refresh();              //Обновление окна
    endwin();               //Закрыть все окна и закончить работу с ncurses
    return 0;
}


