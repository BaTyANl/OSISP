#pragma once

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>

int readOffset(unsigned char** page, off_t offset);