#ifndef kode_debug_included
#define kode_debug_included
//----------------------------------------------------------------------

#define KODE_DEBUG_PRINT
#define KODE_DEBUG_CALLSTACK
#define KODE_DEBUG_CRASH_HANDLER
//#define KODE_DEBUG_MEMORY

//----------------------------------------------------------------------

void KODE_NoPrint(const char*,...) {}

#ifndef KODE_DEBUG
  #undef KODE_DEBUG_PRINT
  #undef KODE_DEBUG_CALLSTACK
  #undef KODE_DEBUG_CRASH_HANDLER
  #undef KODE_DEBUG_STACKTRACE
  #undef KODE_DEBUG_MEMORY
#endif

//----------

#ifdef KODE_DEBUG_CRASH_HANDLER
  #define KODE_DEBUG_CALLSTACK
#endif

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
    #include "base/debug/kode_debug_print.h"
  #endif

  #ifdef KODE_DEBUG_CALLSTACK
    #include "base/debug/kode_debug_callstack.h"
  #endif

  #ifdef KODE_DEBUG_CRASH_HANDLER
    #include "base/debug/kode_debug_crash_handler.h"
  #endif

  #ifdef KODE_DEBUG_MEMORY
    #include "base/debug/kode_debug_memory.h"
  #endif

  #ifdef KODE_DEBUG_STACKTRACE
    #include "base/debug/kode_debug_stacktrace.h"
  #endif

#else // KODE_DEBUG

  //void KODE_NoPrint(const char*,...) {}
  #define KODE_Print  KODE_NoPrint
  #define KODE_DPrint KODE_NoPrint
  #define KODE_PRINT  {}

  //

//  struct KODE_CallStackSymbol {};
//  struct KODE_CallStackStringBuffer {};
//  /*_KODE_ALWAYS_INLINE*/ int kode_callstack(int skip_frames, void** addresses, int num_addresses) { return 0; }
//  /*_KODE_ALWAYS_INLINE*/ int KODE_CallStackSymbols(void** addresses, KODE_CallStackSymbol* out_syms, int num_addresses, char* memory, int mem_size) { return 0; }
//  /*_KODE_ALWAYS_INLINE*/ void KODE_PrintCallStack(void** AAddresses=nullptr, int ANumAddresses=0) {}
//  #define KODE_DumpCallStack {}
//  #define KODE_DumpCallStackSkip(s) {}

#endif // KODE_DEBUG

//----------------------------------------------------------------------
#endif
