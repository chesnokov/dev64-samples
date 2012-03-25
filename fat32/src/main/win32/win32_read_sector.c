#include <win32/api.h>

/*
  read specified sector to buffer
  Parameters:
    input:
      device - device handle
      sector - LBA sector address
    output:
      buffer - buffer for for sector data
  return
    false if error
    true if success and fill buffer with sector data
 */
bool win32_read_sector(HANDLE device, void * buffer, DWORD sector) {
    // Setting the pointer to point to the start of the sector we want to read ..
    SetFilePointer (device, (sector*512), NULL, FILE_BEGIN);

    DWORD dwBytesRead;
    return ReadFile (device, buffer, 512, &dwBytesRead, NULL);
}
