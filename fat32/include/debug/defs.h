/*
  This include file defines set of debug macroses
  
  _IFDEB(op) - run operation in debug version only
  _TRACE(op) - print trace in debug mode and perform operation
  _FMT(fmt) - adds file, line to debug format in debug mode
  _DEB(op) - prints file, line then executes operation. Usially used 
    for debug print. Operation usially debug print.
  ASSERT(a, b) - checks condition a. If condition false then print
    assertion failed message and execute operation b.
*/
#ifndef _DEBUG_DEFS_H_
#define _DEBUG_DEFS_H_

#if DEBUG_VERSION == 1
  #define ASSERT(a,b)\
    do { if(!(a)) {\
      printf("Assertion failed in %s(%d)\n", __FILE__, __LINE__); b; }\
    } while(0)
  
  #define _IFDEB(op)\
    do { op; } while(0)
  
  #define _DEB(op) do {\
    printf("%s(%d):",__FILE__,__LINE__);\
    op;\
  } while(0)
  
  #define _TRACE(op) do {\
    printf("%s(%d) %s\n",__FILE__,__LINE__,#op);\
    x;\
  } while(0)
  
  #define FMT(fmt) "%s(%d) " fmt ,__FILE__,__LINE__
  
#else
	#define _IFDEB(x)
	#define _DEB(x)
	#define _TRACE(x) { x; }
	#define FMT(a) a
	#define ASSERT(a,b)
#endif

#endif
