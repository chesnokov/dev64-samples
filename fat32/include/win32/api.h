#ifndef _WIN32_API_H_
#define _WIN32_API_H_

#include <win32/types.h>

#ifdef __cplusplus
  extern "C" {
#endif

bool win32_get_hdd_device_name(
  UINT8 deviceId, char * deviceName, UINT32 length);

bool win32_open_device(HANDLE * handle, const char * deviceName);

#ifdef __cplusplus
  }
#endif

#endif
