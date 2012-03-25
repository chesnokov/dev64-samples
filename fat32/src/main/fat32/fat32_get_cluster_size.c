#include <fat32/api.h>

UINT32 fat32_get_cluster_size(const FAT32_CB_T * cb) {
  return
    cb->bootSector.bpb.BPB_BytsPerSec *
      cb->bootSector.bpb.BPB_SecPerClus;
}
