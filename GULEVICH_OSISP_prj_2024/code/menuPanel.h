#pragma once
#include <ncurses.h>
#include <fcntl.h>
#include <string.h>
#include "colors.h"
#include "hexPanel.h"
#include "memoryWalk.h"
#include "errorWindow.h"
#include "blockPanel.h"
#include "infoPanel.h"

                            //Верхняя панель меню
#define WIDTH_MENU 80
#define HEIGHT_MENU 1

extern const char *choises[];

void print_menu(WINDOW* menu_win, int highlight);       //Вывод меню
int menu_choise(WINDOW* menu_win, int highlight);       //Выбор пункта меню
void filePathInput(unsigned char** bytes);                                   //Окно ввода пути файла
void helpPanel();                                       //Окно помощи
void offsetInput(unsigned char** bytes);

