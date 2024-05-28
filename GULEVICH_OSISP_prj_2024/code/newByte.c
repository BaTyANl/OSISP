#include "newByte.h"

int changeByte(size_t index, int value){
    int fd = open(info_stats.path, O_RDWR);
    char *addr = mmap(NULL, info_stats.size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    addr[block_stats.offset + index] = value;
    if (msync(addr, info_stats.size, MS_SYNC) == -1){
        munmap(addr, info_stats.size);
        close(fd);
        return 2;
    }
    munmap(addr, info_stats.size);
    close(fd);
    return 1;
}


