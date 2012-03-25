#include <windows.h>
#include <test/api.h>

bool
  writeBufferToFile(const char *filename,
  const void * buffer, UINT32 bufferSize) {
    DWORD dwBytesWritten;
    HANDLE handle = openOutputFile(filename);
    bool result = handle != INVALID_HANDLE_VALUE;
    if (result) {
      result = WriteFile (handle, buffer,
        bufferSize, &dwBytesWritten, NULL);
      CloseHandle(handle);
    }
    return result;
}
