#ifndef kode_debug_included
#define kode_debug_included
//----------------------------------------------------------------------

#define KODE_DEBUG_PRINT
//#define KODE_DEBUG_STACKTRACE
//#define KODE_DEBUG_MEMORY

//----------------------------------------------------------------------

#ifndef KODE_DEBUG
  #undef KODE_DEBUG_PRINT
  #undef KODE_DEBUG_STACKTRACE
  #undef KODE_DEBUG_MEMORY
#endif

//----------


//----------

#ifdef KODE_DEBUG

  const char* _kode_debug_strip_path(const char* buffer) {
    const char *slash;
    slash = strrchr(buffer,'/');
    if (slash) {
      return slash + 1;
    }
    return buffer;
  }

  #ifdef KODE_DEBUG_PRINT
    #include "base/kode_debug_print.h"
  #endif

  #ifdef KODE_DEBUG_STACKTRACE
    #include "base/kode_debug_stacktrace.h"
  #endif

  #ifdef KODE_DEBUG_MEMORY
    #include "base/kode_debug_memory.h"
  #endif

#else // KODE_DEBUG

    void KODE_NoPrint(const char*,...) {}
    #define KODE_Print  KODE_NoPrint
    #define KODE_DPrint KODE_NoPrint
    #define KODE_PRINT  {}

#endif // KODE_DEBUG

//----------------------------------------------------------------------
#endif
