#include <fat32/api.h>

typedef struct {
  FAT32_DIR_ENTRY_T * entry;
  bool result;                  // true if found
} SEARCH_ENTRY;

bool search_file(void * ifc, void * buf, UINT32 bufsz) {
  ISPROC * iface = (ISPROC *)ifc;
  SEARCH_ENTRY * search_entry = (SEARCH_ENTRY *)iface->ptr;
  FAT32_DIR_ENTRY_T * entry = search_entry->entry;
  FAT32_DIR_ENTRY_T * dirEntry = (FAT32_DIR_ENTRY_T *)buf;
  bool result = false;
  UINT32 i;

  for(i=0; i<bufsz/sizeof(FAT32_DIR_ENTRY_T);
        i++,dirEntry++ ) {
    fat32_print_dir_entry(dirEntry);
    result = !memcmp(dirEntry->DIR_Name,
      entry->DIR_Name, sizeof(dirEntry->DIR_Name));
    if (result) {
      memcpy(entry, dirEntry, sizeof(FAT32_DIR_ENTRY_T));
      search_entry->result = result;
      break;
    }
  }
  return result;
}


bool
  fat32_search_root_dir(FAT32_CB_T * cb,
    FAT32_DIR_ENTRY_T * entry) {

  SEARCH_ENTRY search_entry;
  search_entry.entry = entry;
  search_entry.result = false;

  ISPROC ifc;
  ifc.ptr = &search_entry;
  ifc.proc = search_file;

  fat32_read_cluster_chain(cb, cb->bootSector.bpb.BPB_RootClus, &ifc );

  return search_entry.result;
}
