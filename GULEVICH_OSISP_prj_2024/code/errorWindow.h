#pragma once
#include <ncurses.h>
#include <fcntl.h>
#include <string.h>
#include "colors.h"
#include "hexPanel.h"
#include "memoryWalk.h"

void printError(const char* table_name, const char* error_type, const char *error);