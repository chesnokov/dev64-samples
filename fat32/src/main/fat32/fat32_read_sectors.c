#include <win32/api.h>
#include <fat32/api.h>

/*
   reads several sectors starting from specified
   function to be used to read cluster

   TODO: now this function assumes
 */
bool fat32_read_sectors(const FAT32_CB_T * cb,
  void * buffer, UINT32 start_sector, UINT32 sectors) {

  UINT32 sector=start_sector;
  UINT32 end_sector=sector+sectors;
  UINT32 sector_size=cb->bootSector.bpb.BPB_BytsPerSec;
  bool result;


  for(; sector<end_sector && result; sector++,buffer+=sector_size) {
    result = win32_read_sector(cb->hdd_cb->handle, buffer, sector);
  }
  return result;
}
