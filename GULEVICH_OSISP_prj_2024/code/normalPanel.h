#pragma once
#include <ncurses.h>
#include "colors.h"

#define WIDTH_NORMAL 18
#define HEIGHT_NORMAL 21
#define NORMAL_VALUE "0123456789ABCDEF"

void print_normal(WINDOW *normal_win);