#ifndef _HDD_API_H_
#define _HDD_API_H_

#include <hdd/mbr.h>

bool
  hdd_get_active_partition(
  const HDD_MBR_T * mbr, const HDD_PARTITION_T ** partition);

bool hdd_open_device(HDD_CB_T * cb, UINT8 deviceId);

#endif
