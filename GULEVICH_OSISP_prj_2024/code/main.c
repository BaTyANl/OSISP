
#include "colors.h"
#include "blockPanel.h"
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
void init_structures();

int main() {
    setlocale(LC_ALL, "");
    WINDOW *menu_win;       //Окна
    WINDOW *info_win;
    WINDOW *hex_win;
    WINDOW *normal_win;
    WINDOW *block_win;  
    unsigned char *bytes;
    bytes = (unsigned char*)calloc(304, sizeof(unsigned char));
    int highlight = 1;      //Переменная подсветки выбранного элемента меню

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
    init_structures();

    print_info(info_win);
    print_hex(hex_win, bytes, 0, normal_win, block_win);
    print_block(block_win, 0);
    while(1){
        print_menu(menu_win, highlight);        //Вывод всех панелей 
        int choise = menu_choise(menu_win, highlight);  //Выбор меню

        switch (choise){
            case 1:{
                filePathInput(&bytes);        //Вызов панели с вводом файла
                print_hex(hex_win, bytes, 0, normal_win, block_win);
                print_info(info_win);
                break;
            }
            case 2:{
                offsetInput(&bytes);
                print_hex(hex_win, bytes, 0, normal_win, block_win);
                print_info(info_win);
                break;
            }
            case 3:{
                if (info_stats.access == READ_ONLY){
                    info_stats.access = READ_WRITE;
                } else {
                    if (info_stats.access == READ_WRITE){
                        info_stats.access = READ_ONLY;
                    }
                }
                werase(info_win);
                print_info(info_win);
                break;
            }
            case 4:{
                helpPanel();            //Вызов панели с помощью
                print_hex(hex_win, bytes, 0, normal_win, block_win);
                break;
            }
            case 11:{
                hex_menu(hex_win, bytes, 1, normal_win, block_win);
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

void init_structures(){
    long block_size = sysconf(_SC_PAGESIZE);
    block_stats.offset = 1;                          //Тестовая структура
    block_stats.block = 1;
    block_stats.block_size = block_size;
    block_stats.sector = 1;
    block_stats.sector_size = 256;

    strcpy(info_stats.type, "N/D");
    strcpy(info_stats.name, "N/D");
    strcpy(info_stats.path, "N/D");
    info_stats.size = 0;
    info_stats.access = NO_DATA;
}


