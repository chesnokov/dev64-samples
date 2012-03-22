/*
   This file contains helper types and constant definitions
   related to Win32
 */
#ifndef _WIN32_TYPES_H_
#define _WIN32_TYPES_H_

#ifdef _WIN32
  #include <windows.h>
#else
  typedef unsigned long UINT32;
#endif

typedef unsigned char UINT8;
typedef unsigned short UINT16;

#ifndef __cplusplus
  #define bool UINT32
  #define true 1
  #define false 0
#endif

#define HDD_DEVICE_STRING "\\\\.\\PhysicalDrive"
#define HDD_DEVICE_STRING_LEN (sizeof(HDD_DEVICE_STRING) - 1)
#define HDD_DEVICE_STRING_SIZE (sizeof(HDD_DEVICE_STRING"XX"))

#endif
