#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "blockPanel.h"
#include "infoPanel.h"

int changeByte(size_t index, int value);
