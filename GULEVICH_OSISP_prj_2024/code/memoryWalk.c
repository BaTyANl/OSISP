#include "memoryWalk.h"


int readOffset(unsigned char** bytes){
    int fd = open("/proc/kcore", O_RDONLY);
    if (fd == -1){
        return 2;
    }
    struct sysinfo info;
    sysinfo(&info);
    if(lseek(fd, block_stats.offset, SEEK_SET) == -1){
        close(fd);
        return 3;
    }
    ssize_t bytes_read = read(fd, *bytes, 304);
    if (bytes_read == -1){
        close(fd);
        return 4;
    }
    info_stats.size = info.totalram/1024;
    close(fd);
    return 1;
}