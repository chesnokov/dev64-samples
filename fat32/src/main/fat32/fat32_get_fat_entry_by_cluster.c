#include <fat32/api.h>

void
  fat32_get_fat_entry_by_cluster(const FAT32_CB_T * cb,
    UINT32 *entry_sector, UINT16 * entry_offset, UINT32 cluster) {

    UINT32 fatOffset = cluster << 2;

    *entry_sector =
      fatOffset / cb->bootSector.bpb.BPB_BytsPerSec +
        cb->bootSector.bpb.BPB_RsvdSecCnt + cb->bootSector.bpb.BPB_HiddSec;

    *entry_offset =
      fatOffset % cb->bootSector.bpb.BPB_BytsPerSec;
}
