#include <fat32/api.h>

bool fat32_read_sector(FAT32_CB_T * cb, char * buffer, UINT32 sector) {
    UINT32 bytesPerSector = cb->bootSector.bpb.BPB_BytsPerSec;

    // Setting the pointer to the start of the sector we want to read ...
    SetFilePointer (cb->hdd_cb->handle,
      (sector*bytesPerSector), NULL, FILE_BEGIN);

    DWORD dwBytesRead;
    return ReadFile (cb->hdd_cb->handle,
      buffer, bytesPerSector, &dwBytesRead, NULL);
}
