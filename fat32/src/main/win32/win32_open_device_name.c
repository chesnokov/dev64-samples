#include <win32/api.h>

/*
   openes the hdd device as file and returns handle to it
   parameters:
     input:
       deviceName - name of device file
     output:
       handle - handle to be used to read/write device
   return values:
       false if not success
       true if success, handle in 1-st parameter updated
*/
bool win32_open_device_name(HANDLE * handle, const char * deviceName) {
  bool result = (deviceName != 0);
  if (result) {
    *handle = CreateFile(deviceName, GENERIC_READ, 
      FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL); 
    
    result = *handle != INVALID_HANDLE_VALUE;
  }
  return result;
}
