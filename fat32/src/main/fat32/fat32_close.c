#include <fat32/api.h>

bool fat32_close(FAT32_CB_T *cb) {
  bool result = cb != 0;
  if (result) {
    result = CloseHandle(cb->deviceHandle);
    cb->deviceHandle = INVALID_HANDLE_VALUE;
  }
  return result;
}
