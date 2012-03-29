#ifndef _FAT32_TYPES_H_
#define _FAT32_TYPES_H_

#include <win32/types.h>

#define FAT32_FREE   0x00000000L
#define FAT32_BAD    0x0ffffff7L
#define FAT32_MASK   0x0fffffffL

#ifdef __cplusplus
  extern "C" {
#endif

#pragma pack(push,1)

/*
  BPB stands BIOS parameter block
  It is placed at the beginning of Boot Sector
*/
typedef struct {
  char BS_jmpBoot[3];       // 0x00 jmp command to boot code
  char BS_OEMName[8];       // 0x03 OEM Name
  UINT16 BPB_BytsPerSec;    // 0x0b Bytes per sector 512,1024,2048 or 4096
  UINT8 BPB_SecPerClus;     // 0x0d Sectors per Cluster
  UINT16 BPB_RsvdSecCnt;    // 0x0e Reserved sectors count
  UINT8 BPB_NumFATs;        // 0x10 FATs number
  UINT16 BPB_RootEntCnt;    // 0x11 (not used for FAT32)
  UINT16 BPB_TotSec16;      // 0x13 (not used for FAT32)
  UINT8 BPB_Media;          // 0x15 (not used)
  UINT16 BPB_FATSz16;       // 0x16 (not used for FAT32)
  UINT16 BPB_SecPerTrk;     // 0x18 (SPT geometry for CHS)
  UINT16 BPB_NumHeads;      // 0x1a (HPC geometry for CHS)
  UINT32 BPB_HiddSec;       // 0x1c (Sectors before this partition)
  UINT32 BPB_TotSec32;      // 0x20 (Total sectors must be !=0 for FAT32)
  UINT32 BPB_FATSz32;       // 0x24 Sectors count in one FAT
  UINT16 BPB_ExtFlags;      // 0x28 See Microsoft document
  UINT16 BPB_FSVer;         // 0x2a Version of FAT32 filesystem
  UINT32 BPB_RootClus;      // 0x2c Root Directory cluster number
  UINT16 BPB_FSInfo;        // 0x30 Reserved = 1 usially see doc...
  UINT16 BPB_BkBootSec;     // 0x32 Sector in reserve area with Boot Sect Copy
  UINT8 BPB_Reserved[12];   // 0x34
  UINT8 BS_DrvNum;          // 0x40 Drive number for int 0x13
  UINT8 BS_Reserved1;       // 0x41
  UINT8 BS_BootSig;         // 0x42 0x29 means that next fields present
  UINT32 BS_VolID;          // 0x43 Volume ID 32 bit value
  char BS_VolLab[11];       // 0x47
  char BS_FilSysType[8];    // 0x52 "FAT32   "
} FAT32_BPB_T;

/*
  FAT32 Boot Sector
 */
typedef struct {
  FAT32_BPB_T bpb;          // FAT32 BPB
  UINT8 code[0x1a4];        // boot code
  UINT16 signature;         // 0xaa55
} FAT32_BS_T;

/*
  FAT32 Dir Entry
 */
typedef struct {
  char DIR_Name[11];
  UINT8 DIR_Attr;
  UINT8 DIR_NTRes;
  UINT8 DIR_CrtTime_Tenth;  // time in tenth of second
  UINT16 DIR_CrtTime;       // seconds
  UINT16 DIR_CrtDate;
  UINT16 DIR_LstAccDate;
  UINT16 DIR_FstClusHI;     // +20 first cluster Hi
  UINT16 DIR_WrtTime;
  UINT16 DIR_WrtDate;
  UINT16 DIR_FstClusLO;     // +26 first cluster Lo
  UINT32 DIR_FileSize;
} FAT32_DIR_ENTRY_T;

#pragma pack(pop)

#ifdef __cplusplus
  }
#endif

#endif
