#ifndef kode_system_included
#define kode_system_included
//----------------------------------------------------------------------

#include "kode.h"

//----------------------------------------------------------------------

#ifdef __gnu_linux__

  #define __KODE_EXPORT __attribute__((visibility("default")))

#endif

//----------------------------------------------------------------------

#ifdef _WIN32
#endif

//----------------------------------------------------------------------
#endif
