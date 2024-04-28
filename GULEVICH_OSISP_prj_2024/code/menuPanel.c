#include "menuPanel.h"

const char *helpMessage[] = {                   //Cоощение помощи
    "This app is intended for editing ",
    "sector level block devices. You can",
    "see 5 panels in the terminal.",
    "The upper one gives you option to",
    "open file or folder, change the bytes",
    "of memory and save changes. The left", 
    "one gives you information about your", 
    "file, like type, name, real path,", 
    "size in bytes and access type. Access", 
    "type could be read-only and ead-write.", 
    "The bottom panel provides more", 
    "in-depth information, like offset,",
    "block number and size and sector number", 
    "in the block. The central and the right", 
    "panels are the most important on this", 
    "app. The central one shows you the flow",
    "of bytes of your memory in hexadecimal.",
    "Right panel translates hexadecimal", 
    "form into usual ASCII. After pressing", 
    "change bytes button in the upper panel.",
    "you will be able to edit bytes of memry.", 
    "Then press save changes to save changes)",
    "Be careful with that app and try not",
    "to break your system. Good luck)))"
};

const char *choices[] = {                       //Текст менюшки
    "Open file",
    "Change bytes",
    "Save Changes",
    "Help",
    "Exit programm"
};


void print_menu(WINDOW *menu_win, int highlight){   //Функция вывода меню
    int x, y, i;
    keypad(menu_win, TRUE);                         //Выключение обработки спец клавиш в этом окне
    y = 0, x = 0;
    wbkgd(menu_win, COLOR_PAIR(TOP_PANEL_COLOR));   //Установка цвета для окна
    for(i = 0; i < 5; ++i)
        {
            if(highlight == i + 1) //Подсветка выбранного пункта меню
            {
                wattron(menu_win, COLOR_PAIR(SLCTD_TOP_PANEL)); //Включение аттрибута цвета
                mvwprintw(menu_win, y, x, "%s", choices[i]);    //Вывод выбранного пункта
                wattroff(menu_win, COLOR_PAIR(SLCTD_TOP_PANEL)); //Включение аттрибута цвета
            }
            else{
                mvwprintw(menu_win, y, x, "%s", choices[i]);    //Вывод остальных пунктов меню
            }
            if(i == 0) x+=15;
            if(i == 1) x+=18;
            if(i == 2) x+=18;
            if(i == 3) x+=9;    //x для позиционирования
        }
    wrefresh(menu_win);         //Обновление окна, чтобы увидеть результат
}

int menu_choise(WINDOW *menu_win, int highlight){   //Выбор в меню
    int choise;
    int c;
    while(1) {
        c = wgetch(menu_win);                       //Считывание нажатий
        switch(c) {
        case KEY_LEFT:                              // <-
            if(highlight == 1)
                highlight = 5;
            else
                --(highlight);
        break;
        case KEY_RIGHT:                             // ->
            if(highlight == 5)
                highlight = 1;
            else
                ++(highlight);
        break;
        case 10:                                    //Enter
            choise = highlight;
            break;
        }
        print_menu(menu_win, highlight);            //Вывод меню
        if(choise != 0)
            break;
    }
    return choise;
}

void printFilePanel(WINDOW* win_open){              //Вывод панели с вводом пути к файлу

    wbkgd(win_open, COLOR_PAIR(TOP_PANEL_COLOR));   //Установка цвета для окна
    box(win_open, 0, 0);                            //Обозначение границ окна
    mvwprintw(win_open, 0, 9 , "%s", "File opening"); //Вывод строк
    mvwprintw(win_open, 2, 1 , "%s", "Input path of your file.");
    mvwprintw(win_open, 3, 1 , "%s", "Press F1 to cancel.");
    wrefresh(win_open);                             //Обновление окна
}

void filePathInput(){                               //Ввод пути к файлу
    WINDOW* win_open;                               //Окно
    int maxx, maxy;
    getmaxyx(stdscr, maxy, maxx);
    win_open = newwin(10, 30, (maxy - 10)/2, (maxx - 30)/2);    //Создание окна
    printFilePanel(win_open);                       //Вывод окна
    keypad(win_open, true);                         //Выключение обработки нажатий
    int c = wgetch(win_open);
    if(c == KEY_F(1)){                              //F1 - Выход
        delwin(win_open);
        return;
    }
    char path[40];
    curs_set(1);                            //Включение отображения курсора
    mvwgetstr(win_open, 4, 1, path);        //Починить отображение ввода
    curs_set(0);
    mvwprintw(win_open, 5, 1 , "%s", path); 
    wrefresh(win_open);                     //Обновление окна
    getch();
    delwin(win_open);                       //Освобождение памяти
}

void printHelp(WINDOW* win_help, int page){ //Вывод окна помощи
    werase(win_help);                       //Очистка окна
    box(win_help, 0, 0);
    if (page == 1){                         //Выводим разную информацию для каждой страницы
        wattron(win_help ,COLOR_PAIR(INFO_PANEL));  //Включаем цвет
        mvwprintw(win_help, 0, 9 , "%s", "Help (Press F1 to exit)");
        wattroff(win_help ,COLOR_PAIR(INFO_PANEL));

        for(int i = 0; i < 8; i++){                 //Выводим помощь на эту страницу
            mvwprintw(win_help, i+1, 1 , "%s", helpMessage[(8*(page - 1)) + i]);
        }

        mvwprintw(win_help, 9, 16, "%s%d%s", "[   ", page, "/3 ->]");
    } else {    
        if(page == 2){                      //Страница 2
            wattron(win_help ,COLOR_PAIR(INFO_PANEL));
            mvwprintw(win_help, 0, 9 , "%s", "Help (Press F1 to exit)");
            wattroff(win_help ,COLOR_PAIR(INFO_PANEL));
            for(int i = 0; i < 8; i++){
                mvwprintw(win_help, i+1, 1 , "%s", helpMessage[(8*(page - 1)) + i]);
            }

            mvwprintw(win_help, 9, 16, "%s%d%s", "[<- ", page, "/3 ->]");
        } else{                             //Страница 3
            wattron(win_help ,COLOR_PAIR(INFO_PANEL));
            mvwprintw(win_help, 0, 9 , "%s", "Help (Press F1 to exit)");
            wattroff(win_help ,COLOR_PAIR(INFO_PANEL));

            for(int i = 0; i < 8; i++){
                mvwprintw(win_help, i+1, 1 , "%s", helpMessage[(8*(page - 1)) + i]);
            }

            mvwprintw(win_help, 9, 16, "%s%d%s", "[<- ", page, "/3   ]");
        }
    }

    wrefresh(win_help);             //Обновляем окно
}


void helpPanel(){                   //Панель помощи
    WINDOW* win_help;
    int maxx, maxy;
    int page = 1;
    int c;
    getmaxyx(stdscr, maxy, maxx);
    win_help = newwin(10, 42, (maxy - 10)/2, (maxx - 42)/2);    //Создаем окно
    wbkgd(win_help, COLOR_PAIR(TOP_PANEL_COLOR));               //Ставим цвет
    keypad(win_help, true);                                     //Включаем обработку нажатий
    printHelp(win_help, 1);                                     //Вывод окна с 1 страницей
    while(1){
        c = wgetch(win_help);
        switch (c)
        {
        case KEY_F(1):                                          //F1 - выход
            goto del;
            break;
        case KEY_LEFT:{
            if(page == 1) break;
            page--;
            printHelp(win_help, page);                          //Вывод окна с нужной страницей
            break;
        }
        case KEY_RIGHT:{
            if(page == 3) break;
            page++;
            printHelp(win_help, page);                          //Вывод окна с нужной страницей
            break;
        }
        }
    }
    del:
    delwin(win_help);                                           //Освобождение памяти от окна
}