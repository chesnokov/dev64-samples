#include <stdio.h>
#include <stdlib.h>
#include <hdd/mbr.h>
#include <win32/api.h>

int main(int argc, char *argv[])
{
  HDD_MBR_T mbr;
  HANDLE handle;
  HDD_PARTITION_T * partition; 
  bool result = win32_open_device_id(&handle, 1);
  result = result && win32_read_sector(handle, &mbr, 0);
  result = result && hdd_get_active_partition(&mbr, &partition);
  printf( result ? 
    "active partition start sector %x" : "false" , partition->lba_start );
  return 0;
}
