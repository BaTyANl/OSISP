#include "memoryWalk.h"


#define MAP_MASK 255
int readOffset(unsigned char** bytes, off_t offset){
    int fd = open("/proc/kcore", O_RDONLY);
    if (fd == -1){
        //ошибка открытия памяти

        return 2;
    }
    off_t target = 0x100000;
    size_t length = 256;
    if(lseek(fd, target, SEEK_SET) == -1){
        close(fd);
        return 3;
    }
    ssize_t bytes_read = read(fd, bytes, length);
    if (bytes_read == -1){
        close(fd);
        return 4;
    }

    close(fd);
    return 1;
}