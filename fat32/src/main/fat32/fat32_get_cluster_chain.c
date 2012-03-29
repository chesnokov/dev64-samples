#include <malloc.h>
#include <fat32/api.h>

bool fat32_get_cluster_chain(FAT32_CB_T * cb,
  UINT32 cluster, ICLUSTERS * proc) {
  bool result = true;
  UINT32 current_sector = 0;
  UINT8 * buf = (UINT8 *)alloca(cb->bootSector.bpb.BPB_BytsPerSec);
  UINT32 entry_sector;
  UINT16 entry_offset;

  while(result && !proc->proc(proc, cluster)) {
    fat32_get_fat_entry_by_cluster(cb,
      &entry_sector, &entry_offset,cluster);

    if (current_sector != entry_sector) {
      result = fat32_read_sector(cb, buf, entry_sector);
      current_sector = entry_sector;
    }
    if (result) {
      cluster = *((UINT32 *)((UINT8 *)(buf+entry_offset))) & FAT32_MASK;
    }
  }
  return result;
}
