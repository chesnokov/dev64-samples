/*
  This file contains function definitions for test FAT32 API. 
  This API is to be used for experiments with FAT32 flash drive
  in Windows.
*/
#ifndef _FAT32API_H_
#define _FAT32API_H_

#include <win32/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
  FAT32 Control Block 
  This structure to be passed to each API function
*/
typedef struct {
  char deviceName[32];     // device Windows file name
  HANDLE deviceHandle;     // device handle (for read/write functions)
  UINT8  deviceId;         // the windows device id for open function
} FAT32_CB_T;

/*
  Function openes the specified device volume. The devices are specified 
  by number:
     0 is device  C:
     1 is next device
     ...
     
  Function fills control block passed by the first parameter with data 
  and returns true if success. 
*/
bool fat32_open_device(FAT32_CB_T * cb, UINT8 deviceId);

/*
  Close device
*/
bool fat32_close(FAT32_CB_T *cb);

#ifdef __cplusplus
  }
#endif

#endif
