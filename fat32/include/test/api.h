#ifndef _TEST_API_H_
#define _TEST_API_H_

#include <windows.h>
#include <win32/api.h>

HANDLE openOutputFile(const char * filename);

bool writeBufferToFile(const char *filename,
  const void * buffer, UINT32 bufferSize);

#endif
