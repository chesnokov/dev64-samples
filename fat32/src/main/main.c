#include <stdio.h>
#include <stdlib.h>
#include <hdd/api.h>
#include <fat32/api.h>
#include <test/api.h>

int main(int argc, char *argv[])
{
  HDD_CB_T hdd_cb;
  FAT32_CB_T cb;
  UINT32 bytesInCluster ;
  UINT8 * clusterBuffer;
  UINT32 rootDirSector;
  int i;
  FAT32_DIR_ENTRY_T * dirEntry;

  bool result = hdd_open_device(&hdd_cb, 1);
  printf( result ?
    "active partition start sector %x\n" : "false" , hdd_cb.lbaStart );

  result = result && fat32_open_device(&cb, &hdd_cb);
  if (result) {
    fat32_print_control_block(&cb);

    bytesInCluster = fat32_get_cluster_size(&cb);
    printf("bytes in cluster = %d\n", bytesInCluster);
    clusterBuffer = (UINT8 *)malloc(bytesInCluster);
    rootDirSector =
      fat32_get_sector_by_cluster(&cb, cb.bootSector.bpb.BPB_RootClus);
    printf("root dir sector =%x\n", rootDirSector);
    rootDirSector+= cb.bootSector.bpb.BPB_HiddSec;
    printf("root dir sector =%x\n", rootDirSector);

    result = fat32_read_sectors(&cb, clusterBuffer,
      rootDirSector, cb.bootSector.bpb.BPB_SecPerClus);
    result = result &&
      writeBufferToFile("rootdir.dat", clusterBuffer, bytesInCluster);

    dirEntry = (FAT32_DIR_ENTRY_T *)clusterBuffer;
    if (result) {
      for(i=0;
        i<bytesInCluster/sizeof(FAT32_DIR_ENTRY_T) && result;
        i++,dirEntry++) {
        result=fat32_print_dir_entry(dirEntry);
      }
    }

    free(clusterBuffer);
  }
  return 0;
}

