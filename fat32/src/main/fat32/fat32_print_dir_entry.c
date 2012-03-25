#include <stdio.h>
#include <fat32/api.h>

bool fat32_print_dir_entry(FAT32_DIR_ENTRY_T * entry) {
  int i;
  char * c = entry->DIR_Name;
  if (*c == 0)
    return false;
  printf("\nDIR_Name=");
  for(i=0; i<sizeof(entry->DIR_Name); i++,c++) putchar(*c);
  printf("\nDIR_Attr=%02x\n", entry->DIR_Attr);
  printf("DIR_NTRes=%02x\n", entry->DIR_NTRes);
  printf("DIR_CrtTime_Tenth=%02x\n", entry->DIR_CrtTime_Tenth);
  printf("DIR_CrtTime=%04x\n", entry->DIR_CrtTime);
  printf("DIR_CrtDate=%04x\n", entry->DIR_CrtDate);
  printf("DIR_LstAccDate=%04x\n", entry->DIR_LstAccDate);
  printf("DIR_FstClusHI=%04x\n", entry->DIR_FstClusHI);
  printf("DIR_WrtTime=%04x\n", entry->DIR_WrtTime);
  printf("DIR_WrtDate=%04x\n", entry->DIR_WrtDate);
  printf("DIR_FstClusLO=%04x\n", entry->DIR_FstClusLO);
  printf("DIR_FileSize=%08x\n", entry->DIR_FileSize);
  return true;
}
