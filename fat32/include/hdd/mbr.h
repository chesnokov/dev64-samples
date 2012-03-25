#ifndef _HDD_MBR_H_
#define _HDD_MBR_H_

#include <win32/types.h>

#ifdef __cplusplus
  extern "C" {
#endif

#pragma pack(push,1)

typedef struct {
  UINT8 active;
  UINT8 chs_first[3];
  UINT8 type;
  UINT8 chs_last[3];
  UINT32 lba_start;
  UINT32 lba_end;
} HDD_PARTITION_T;

typedef struct {
  char code[446];                 // MBR boot code
  HDD_PARTITION_T partition[4];   // partition table
  UINT16 signature;               // MBR signature
} HDD_MBR_T;

typedef struct {
  HANDLE handle;             // device handle (for read/write functions)
  UINT32 lbaStart;           // boot sector lba start address
  UINT32 lbaEnd;             // boot sector lba end address
  UINT8  deviceId;           // the windows device id for open function
} HDD_CB_T;

#pragma pack(pop)

#ifdef __cplusplus
  }
#endif


#endif
