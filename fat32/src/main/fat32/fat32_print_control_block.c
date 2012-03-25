#include <stdio.h>
#include <fat32/api.h>

void fat32_print_control_block(const FAT32_CB_T * cb) {
  printf("BPB_BytsPerSec %x\n",cb->bootSector.bpb.BPB_BytsPerSec);
  printf("BPB_SecPerClus %x\n",cb->bootSector.bpb.BPB_SecPerClus);
  printf("BPB_RsvdSecCnt %x\n",cb->bootSector.bpb.BPB_RsvdSecCnt);
  printf("BPB_NumFATs %x\n",cb->bootSector.bpb.BPB_NumFATs);
  printf("BPB_RootEntCnt %x\n",cb->bootSector.bpb.BPB_RootEntCnt);
  printf("BPB_TotSec16 %x\n",cb->bootSector.bpb.BPB_TotSec16);
  printf("BPB_Media %x\n",cb->bootSector.bpb.BPB_Media);
  printf("BPB_FATSz16 %x\n",cb->bootSector.bpb.BPB_FATSz16);
  printf("BPB_SecPerTrk %x\n",cb->bootSector.bpb.BPB_SecPerTrk);
  printf("BPB_NumHeads %x\n",cb->bootSector.bpb.BPB_NumHeads);
  printf("BPB_HiddSec %x\n",cb->bootSector.bpb.BPB_HiddSec);
  printf("BPB_TotSec32 %x\n",cb->bootSector.bpb.BPB_TotSec32);
  printf("BPB_FATSz32 %x\n",cb->bootSector.bpb.BPB_FATSz32);
  printf("BPB_ExtFlags %x\n",cb->bootSector.bpb.BPB_ExtFlags);
  printf("BPB_FSVer %x\n",cb->bootSector.bpb.BPB_FSVer);
  printf("BPB_RootClus %x\n",cb->bootSector.bpb.BPB_RootClus);
  printf("BPB_FSInfo %x\n",cb->bootSector.bpb.BPB_FSInfo);
  printf("BPB_BkBootSec %x\n",cb->bootSector.bpb.BPB_BkBootSec);
  printf("BS_DrvNum %x\n",cb->bootSector.bpb.BS_DrvNum);
  printf("BS_BootSig %x\n",cb->bootSector.bpb.BS_BootSig);
  printf("BS_VolID %x\n",cb->bootSector.bpb.BS_VolID);

  printf("firstDataSector = %x\n", cb->firstDataSector);
}
