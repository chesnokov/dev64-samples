#include <fat32/api.h>

/*
  Calculate first sector of cluster
  using formula:
  FirstSectorofCluster = 
    ((N - 2) * BPB_SecPerClus) + FirstDataSector + BPB_HiddSec
*/
UINT32 fat32_get_sector_by_cluster(const FAT32_CB_T * cb, UINT32 cluster) {
  return ((cluster - 2) * 
    cb->bootSector.bpb.BPB_SecPerClus) +
    cb->firstDataSector + cb->bootSector.bpb.BPB_HiddSec;
}
