#include <fat32/api.h>

/*
   This function calculates the first data sector number
   relative to Boot Sector using following formula
   (taken from Microsoft Documentation):
            
   FirstDataSector = 
      BPB_ResvdSecCnt + 
      (BPB_NumFATs * BPB_FATSz32) + RootDirSectors;   
      
   RootDirSectors for FAT32 volume are alwais 0. So
   formula made slightly less complicated:
           
   FirstDataSector = BPB_ResvdSecCnt + 
      (BPB_NumFATs * BPB_FATSz32);
 */
UINT32 fat32_get_first_data_sector(const FAT32_CB_T * cb) {
    const FAT32_BPB_T * bpb = &(cb->bootSector.bpb);       
    return bpb->BPB_FATSz32 * (UINT32)bpb->BPB_NumFATs + 
      (UINT32)bpb->BPB_RsvdSecCnt;
}
