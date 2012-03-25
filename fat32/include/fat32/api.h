/*
  This file contains function definitions for test FAT32 API.
  This API is to be used for experiments with FAT32 flash drive
  in Windows.
*/
#ifndef _FAT32_API_H_
#define _FAT32_API_H_

#include <fat32/types.h>
#include <hdd/mbr.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
  FAT32 Control Block
  This structure to be passed to each API function
*/
typedef struct {
  FAT32_BS_T bootSector;     // bootSector
  HDD_CB_T * hdd_cb;
  UINT32 firstDataSector;
} FAT32_CB_T;

/*
*/
bool fat32_open_device(FAT32_CB_T * cb, HDD_CB_T * hdd);

/*
  Close device
*/
bool fat32_close(FAT32_CB_T *cb);

/*
  Prints FAT32 BPB
 */
void fat32_print_control_block(const FAT32_CB_T * cb);

/*
  Calculate first data sector by BPB data
 */
UINT32 fat32_get_first_data_sector(const FAT32_CB_T * cb);

/*
  Calculate cluster start sector
 */
UINT32 fat32_get_sector_by_cluster(const FAT32_CB_T * cb, UINT32 cluster);

/*
  Calculate FAT entry parameters by cluster number
 */
void
  fat32_get_fat_entry_by_cluster(const FAT32_CB_T * cb,
    UINT32 *entry_sector, UINT16 * entry_offset, UINT32 cluster);

/*
  Search file in root directory
 */
bool
  fat32_search_root_dir(const FAT32_CB_T * cb,
    FAT32_DIR_ENTRY_T * entry);

/*
  Calculate cluster size in bytes
 */
UINT32 fat32_get_cluster_size(const FAT32_CB_T * cb);

/*
  Reads several sectors
 */
bool fat32_read_sectors(const FAT32_CB_T * cb,
  void * buffer, UINT32 start_sector, UINT32 sectors);


bool fat32_print_dir_entry(FAT32_DIR_ENTRY_T * entry);

#ifdef __cplusplus
  }
#endif

#endif
