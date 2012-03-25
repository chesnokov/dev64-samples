#include <hdd/api.h>

/*
  search for active partition in the partition table
  Parameters:
    input:
      mbr - pointer to buffer with MBR
    output:
      partition - pointer to active partition structure
  Return:
    false  if no active partition in MBR
    true   if success, assign partition pointer
 */
bool
  hdd_get_active_partition(
  const HDD_MBR_T * mbr, const HDD_PARTITION_T ** partition) {

  bool result = false;
  const HDD_PARTITION_T * p = mbr->partition;
  int i;
  for(i = 0; i<4; i++,p++) {
    if(p->active == 0x80) {
      *partition = p;
      result = true;
      break;
    }
  }
  return result;
}
