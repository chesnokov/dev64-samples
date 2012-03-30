#include <fat32/api.h>

typedef struct {
  FAT32_CB_T * cb;
  ISPROC * isproc;
} READ_CLUSTER_PARMS;

bool read_cluster(void * iclusters, UINT cluster) {
  READ_CLUSTER_PARMS * parms =
    (READ_CLUSTER_PARMS*)(((ICLUSTERS *)iclusters)->ptr);

  if(cluster >= FAT32_BAD)
    return true;

  UINT32 sector = fat32_get_sector_by_cluster(parms->cb, cluster);
  return !fat32_read_sectors(parms->cb, sector,
      parms->cb->bootSector.bpb.BPB_SecPerClus, parms->isproc);
}

bool fat32_read_cluster_chain(FAT32_CB_T * cb,
  UINT32 cluster, ISPROC * proc) {

  READ_CLUSTER_PARMS read_cluster_parms;
  read_cluster_parms.cb = cb;
  read_cluster_parms.isproc = proc;

  ICLUSTERS ifc;
  ifc.proc = read_cluster;
  ifc.ptr = &read_cluster_parms;

  return fat32_get_cluster_chain(cb, cluster, &ifc);
}
