#include <win32/api.h>

#define MAX_DEVICE_ID 99
#define DEVICE_NAME_LEN sizeof(HDD_DEVICE_STRING"XX")

/*
  gets windows hdd device name
  parameters:
    input:
      deviceId - numeric device id > 0 && <= MAX_DEVICE_ID
      deviceName - character buffer for output
      length - character buffer length
    output:
       deviceName - 0 terminated character string with device name
    return
       false if incorrect parameters or not enougth space in the 
         specified output buffer
       true if success, deviceName is assigned the valid deviceName
*/
bool win32_get_hdd_device_name(
  UINT8 deviceId, char * deviceName, UINT32 length) {
        
  bool result = false;
  result = deviceId <= MAX_DEVICE_ID && length >= HDD_DEVICE_STRING_SIZE;
    
  if (result) {
    strncpy(deviceName, HDD_DEVICE_STRING, length);
    itoa(deviceId, deviceName + HDD_DEVICE_STRING_LEN, 10);
  }
  return result;
}
