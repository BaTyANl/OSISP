#include "blockPanel.h"
                                //Нижняя панель с информацией о блоках
static char *block_info[5] = {  //Сообщения с информацией
    "Offset(h): ",
    "Block(h): ",
    "Block size: ",
    "Sector: ",
    "Sector size: "
};

block block_stats;

void print_block(WINDOW *block_win, off_t off){  //Вывод панельки
    werase(block_win);
    wbkgd(block_win, COLOR_PAIR(TOP_PANEL_COLOR));          //Устанавливанем цвет
    mvwprintw(block_win, 0, 2, "%s", block_info[0]);
    mvwprintw(block_win, 1, 2, "%08X", block_stats.offset + off - 1);

    block_stats.block = (block_stats.offset + off - 1)/4096;
    mvwprintw(block_win, 0, 17, "%s", block_info[1]);
    mvwprintw(block_win, 1, 17, "%04X", block_stats.block);

    mvwprintw(block_win, 0, 33, "%s", block_info[2]);
    mvwprintw(block_win, 1, 33, "%d", block_stats.block_size);

    block_stats.sector = ((block_stats.offset + off - 1)/256)%16;
    mvwprintw(block_win, 0, 51, "%s", block_info[3]);
    mvwprintw(block_win, 1, 51, "%02d", block_stats.sector); 

    mvwprintw(block_win, 0, 64, "%s", block_info[4]);
    mvwprintw(block_win, 1, 64, "%d", block_stats.sector_size);  //Выводим все

    wrefresh(block_win);                                    //Обновление окна
}   