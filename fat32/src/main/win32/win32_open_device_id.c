#include <win32/api.h>

/*
   openes the hdd device as file and returns handle to it
   parameters:
     input:
       deviceId >=0 && <=99
     output:
       handle - handle to be used to read/write device
   return values:
       false if not success
       true if success, handle in 1-st parameter updated
*/
bool win32_open_device_id(HANDLE * handle, UINT8 deviceId) {
  char deviceName[32];
  bool result = 
    win32_get_hdd_device_name(deviceId, deviceName, sizeof(deviceName));
  result = result && win32_open_device_name(handle, deviceName);
  return result;
}
