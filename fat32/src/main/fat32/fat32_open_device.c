#include <fat32/api.h>
#include <win32/api.h>

/*
  opens fat32 filesystem
  in fact reads filesystem bootsector
    returns:
       false if error
       true if success and fills cb with data
 */
bool fat32_open_device(FAT32_CB_T * cb, HDD_CB_T * hdd) {
  cb->hdd_cb = hdd;
  bool result =
    win32_read_sector(hdd->handle, &cb->bootSector , hdd->lbaStart);
  if (result) {
     cb->firstDataSector = fat32_get_first_data_sector(cb);
  }
  return result;
}
