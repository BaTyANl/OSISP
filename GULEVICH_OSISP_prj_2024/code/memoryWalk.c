#include "memoryWalk.h"


int readOffset(unsigned char** bytes, off_t offset){
    int fd = open("/dev/mem", O_RDONLY);
    if (fd == -1){
        //ошибка открытия памяти

        return 2;
    }
    size_t length = 304;
    if(lseek(fd, offset, SEEK_SET) == -1){
        close(fd);
        return 3;
    }
    ssize_t bytes_read = read(fd, *bytes, length);
    if (bytes_read == -1){
        close(fd);
        return 4;
    }

    close(fd);
    return 1;
}