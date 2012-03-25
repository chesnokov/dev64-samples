#include <windows.h>

HANDLE openOutputFile(const char * filename) {
       return CreateFile ( filename,      // Open Two.txt.
            GENERIC_WRITE,          // Open for writing
            0,                      // Do not share
            NULL,                   // No security
            OPEN_ALWAYS,            // Open or create
            FILE_ATTRIBUTE_NORMAL,  // Normal file
            NULL);                  // No template file
}
