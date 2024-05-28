#pragma once

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include "blockPanel.h"

int readFile(unsigned char** page, const char* filename);