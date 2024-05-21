#include "fileWalk.h"


int fileWalk(unsigned char** page, off_t offset, const char* filename){
    int fd = open(filename, O_RDONLY);
    if (fd == -1){
        return 2;
    }

    struct stat fileStat;
    fstat(fd, &fileStat);
    long page_size = sysconf(_SC_PAGESIZE);
    off_t true_offset = offset - (offset % page_size);
    if (true_offset + page_size > fileStat.st_size){
        
    }
    /*if(lseek(fd, offset, SEEK_SET) == -1){
        close(fd);
        return 3;
    }
    ssize_t bytes_read = read(fd, *bytes, length);
    if (bytes_read == -1){
        close(fd);
        return 4;
    }*/

    void *mem = mmap(NULL, page_size, PROT_READ, MAP_SHARED, fd, true_offset);
    if (mem == MAP_FAILED){
        return 3;
    }

    memcpy(*page, mem, page_size);
    munmap(mem, page_size);

    close(fd);
    return 1;
}