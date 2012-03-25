#include <win32/api.h>
#include <hdd/api.h>

/*
  Openes device specified by deviceId
  Parameters:
    Input:
      deviceId >=0 && <=99
    Output:
      cb - hdd control block with active partition info
           and handle to opened device
    Return:
      false if error
      true if success and fills cb structure with data
 */
bool hdd_open_device(HDD_CB_T * cb, UINT8 deviceId) {
  HDD_MBR_T mbr;
  const HDD_PARTITION_T * partition;
  cb->handle = INVALID_HANDLE_VALUE;
  bool result = win32_open_device_id(&cb->handle, 1);
  result = result && win32_read_sector(cb->handle, &mbr, 0);
  result = result && hdd_get_active_partition(&mbr, &partition);
  if (result) {
     cb->lbaStart = partition->lba_start;
     cb->lbaEnd = partition->lba_end;
     cb->deviceId = deviceId;
  } else {
     if (cb->handle != INVALID_HANDLE_VALUE) {
        CloseHandle(cb->handle);
        cb->handle = INVALID_HANDLE_VALUE;
     }
  }
  return result;
}
