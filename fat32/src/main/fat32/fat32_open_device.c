#include <fat32/api.h>
#include <win32/api.h>

/*
  openes fat32 filesystem at specified device
  parameters:
    input:
      deviceId - device Id number >=0 && <=99
    output:
       cb - structure that contains data required for subsequent
          read function calls
    return:
       false if error
       true if success and fills cb with data
 */
bool fat32_open_device(FAT32_CB_T * cb, UINT8 deviceId) {
  bool result = cb != 0;
  if (result) {
    cb->deviceId = deviceId;
    result = result && 
      win32_get_hdd_device_name(deviceId, 
        cb->deviceName, sizeof(cb->deviceId));
    result = result &&
      win32_open_device_name(&cb->deviceHandle, cb->deviceName);
  }
  return result;
}
