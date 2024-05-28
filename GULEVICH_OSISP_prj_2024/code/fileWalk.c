#include "fileWalk.h"

int readFile(unsigned char** bytes, const char* filename){
    int fd = open(filename, O_RDONLY);
    if (fd == -1){
        return 2;
    }
    struct stat fileStat;
    fstat(fd, &fileStat);
    getch();
    long page_size = sysconf(_SC_PAGESIZE);
    int block_count = (block_stats.offset) / page_size;
    off_t block_offset = (block_stats.offset) % page_size;
    getch();
    if (block_offset + 304 > page_size){
        block_offset = 0;
        (block_stats.offset) = page_size * (block_count + 1);
    }   
    getch();
    off_t true_offset = (block_stats.offset) - (block_offset);
    if (true_offset + page_size < fileStat.st_size){
        void *mem = mmap(NULL, page_size, PROT_READ, MAP_SHARED, fd, true_offset);
        if (mem == MAP_FAILED){
            return 3;
        }
        getch();
        memcpy(*bytes, (char*)mem + (block_offset), 304);
        getch();
        munmap(mem, page_size);
    }
    close(fd);
    getch();
    return 1;
}