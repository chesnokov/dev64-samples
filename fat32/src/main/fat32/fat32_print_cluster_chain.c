#include <stdio.h>
#include <fat32/api.h>

bool print_cluster(void * ifc, UINT32 cluster) {
  bool result = false;
  printf("%08x\n", cluster);
  if (cluster >= FAT32_BAD)
    result = true;

  return result;
}

bool fat32_print_cluster_chain(FAT32_CB_T *cb, UINT32 cluster) {
  ICLUSTERS ifc;
  ifc.proc = print_cluster;
  ifc.ptr = 0;

  return fat32_get_cluster_chain(cb, cluster, &ifc);
}
