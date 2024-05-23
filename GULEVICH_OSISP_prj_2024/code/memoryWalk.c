#include "memoryWalk.h"


int readOffset(unsigned char** bytes, off_t offset){
    int fd = open("/proc/kcore", O_RDONLY);
    if (fd == -1){
        return 2;
    }

    if(lseek(fd, offset, SEEK_SET) == -1){
        close(fd);
        return 3;
    }
    ssize_t bytes_read = read(fd, *bytes, 304);
    if (bytes_read == -1){
        close(fd);
        return 4;
    }
    close(fd);
    return 1;
}