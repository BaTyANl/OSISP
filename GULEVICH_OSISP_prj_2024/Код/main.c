#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define SECTOR_SIZE 512
//Максимально черновой кусок кода
void readSector(const char* diskPath, int sectorNumber, unsigned char* buffer) {
    FILE* disk = fopen(diskPath, "rb");
    fseek(disk, sectorNumber * SECTOR_SIZE, SEEK_SET);
    fread(buffer, SECTOR_SIZE, 1, disk);
    fclose(disk);
}

void writeSector(const char* diskPath, int sectorNumber, unsigned char* buffer) {
    FILE* disk = fopen(diskPath, "rb+");
    fseek(disk, sectorNumber * SECTOR_SIZE, SEEK_SET);
    fwrite(buffer, SECTOR_SIZE, 1, disk);
    fclose(disk);
}

int main() {
    DIR* directory;
    char diskPath[100];
    unsigned char* sectorBuffer;
    int sectorNumber;

    scanf("%s", diskPath);

    directory = opendir(diskPath);
    if (directory == NULL) {
        return 1;
    }

    sectorBuffer = (unsigned char*)malloc(SECTOR_SIZE);
    if (sectorBuffer == NULL) {
        closedir(directory);
        return 1;
    }

    scanf("%d", &sectorNumber);

    readSector(diskPath, sectorNumber, sectorBuffer);
    printf("Содержимое сектора %d:\n", sectorNumber);
    printf("%s\n", sectorBuffer);

    scanf(" %[^\n]s", sectorBuffer);
    writeSector(diskPath, sectorNumber, sectorBuffer);
    }
    free(sectorBuffer);
    closedir(directory);
    return 0;
}

