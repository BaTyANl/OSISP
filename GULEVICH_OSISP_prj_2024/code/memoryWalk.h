#pragma once

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "blockPanel.h"

int readOffset(unsigned char** bytes);