#include <fat32/api.h>
#include <win32/api.h>

bool fat32_open_device(FAT32_CB_T * cb, UINT8 deviceId) {
  bool result = cb != 0;
  if (result) {
    cb->deviceId = deviceId;
    result = result && 
      win32_get_hdd_device_name(deviceId, 
        cb->deviceName, sizeof(cb->deviceId));
    result = result &&
      win32_open_device(&cb->deviceHandle, cb->deviceName);
  }
  return result;
}
