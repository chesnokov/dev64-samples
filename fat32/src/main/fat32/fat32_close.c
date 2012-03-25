#include <fat32/api.h>

bool fat32_close(FAT32_CB_T *cb) {
  bool result = (cb != 0 && cb->hdd_cb != 0);
  if (result) {
    if (cb->hdd_cb->handle != INVALID_HANDLE_VALUE) {
      result = CloseHandle(cb->hdd_cb->handle);
      cb->hdd_cb->handle = INVALID_HANDLE_VALUE;
    }
  }
  return result;
}
