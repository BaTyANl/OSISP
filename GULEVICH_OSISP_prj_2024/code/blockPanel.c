#include "blockPanel.h"
                                //Нижняя панель с информацией о блоках
static char *block_info[4] = {  //Сообщения с информацией
    "Offset(h): ",
    "Block(h): ",
    "Block size: ",
    "Sector: "
};

static void print_block(WINDOW *block_win, block block_stats){  //Вывод панельки

    block_stats.offset = 23235983;                          //Тестовая структура
    block_stats.block = 2343;
    block_stats.block_size = 12345;
    block_stats.sector = 20;

    wbkgd(block_win, COLOR_PAIR(TOP_PANEL_COLOR));          //Устанавливанем цвет
    mvwprintw(block_win, 0, 2, "%s", block_info[0]);
    mvwprintw(block_win, 1, 2, "%x", block_stats.offset);

    mvwprintw(block_win, 0, 23, "%s", block_info[1]);
    mvwprintw(block_win, 1, 23, "%x", block_stats.block);

    mvwprintw(block_win, 0, 42, "%s", block_info[2]);
    mvwprintw(block_win, 1, 42, "%d", block_stats.block_size);

    mvwprintw(block_win, 0, 66, "%s", block_info[3]);
    mvwprintw(block_win, 1, 66, "%d", block_stats.sector);  //Выводим все

    wrefresh(block_win);                                    //Обновление окна
}   