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
   Callback interface for sector data processing
   Parameters:
     ifc - pointer to ISPROC interface itself
     buf - buffer with sector data for processing
     bufsz - buffer size
   Return:
     true - if processing should be stopped
     false - if processing should be continued

     true means that function has done what it
     wanted to do
 */
typedef struct {
  void * ptr;
  bool (*proc) (void * ifc, void * buf, UINT32 bufsz);
} ISPROC;

typedef struct {
  void * ptr;
  bool (*proc) (void * ifc, UINT32 cluster);
} ICLUSTERS;


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
  fat32_search_root_dir(FAT32_CB_T * cb,
    FAT32_DIR_ENTRY_T * entry);

/*
  Calculate cluster size in bytes
 */
UINT32 fat32_get_cluster_size(const FAT32_CB_T * cb);

/*
  Reads several sectors
 */
bool fat32_read_sectors(const FAT32_CB_T * cb,
  UINT32 start_sector, UINT32 sectors, ISPROC * proc );

bool fat32_print_dir_entry(FAT32_DIR_ENTRY_T * entry);

/*
  Reads cluster chain starting from specified
  Calls call back interface specified by ISPROC
 */
bool fat32_read_cluster_chain(FAT32_CB_T * cb,
  UINT32 cluster, ISPROC * proc);


/*
  Gets cluster numbers for the cluster chain and
  pass them for processing in ICLUSTERS interface
 */
bool fat32_get_cluster_chain(FAT32_CB_T * cb,
  UINT32 cluster, ICLUSTERS * proc);

/*
  Printing values of file clusters starting from specified
*/
bool fat32_print_cluster_chain(FAT32_CB_T *cb, UINT32 cluster);

/*
  Reads specified sector to buffer
  This function takes into account sector size specified in
  Partition BPB - BPB_BytsPerSec
 */
bool fat32_read_sector(FAT32_CB_T * cb, char * buffer, UINT32 sector);


#ifdef __cplusplus
  }
#endif

#endif
