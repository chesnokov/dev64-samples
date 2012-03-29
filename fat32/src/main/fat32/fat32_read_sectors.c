#include <malloc.h>
#include <win32/api.h>
#include <fat32/api.h>

/*
   reads several sectors starting from specified
   function to be used to read cluster

 */
bool fat32_read_sectors(const FAT32_CB_T * cb,
  UINT32 start_sector, UINT32 sectors, ISPROC * spf) {

  UINT32 sector=start_sector;
  UINT32 end_sector=sector+sectors;
  bool result=true;
  char *buffer = alloca(cb->bootSector.bpb.BPB_BytsPerSec);

  for(; sector<end_sector && result; sector++) {
    result = win32_read_sector(cb->hdd_cb->handle, buffer, sector);
    if (spf->proc(spf, buffer, cb->bootSector.bpb.BPB_BytsPerSec))
      break;
  }
  return result;
}
