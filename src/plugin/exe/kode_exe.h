#ifndef kode_exe_included
#define kode_exe_included
//----------------------------------------------------------------------

#ifndef KODE_DEBUG
  #undef KODE_DEBUG_EXE
#endif

#ifdef KODE_DEBUG_EXE
  #define KODE_EXEPRINT  KODE_PRINT
  #define KODE_ExePrint  KODE_Print
  #define KODE_ExeDPrint KODE_DPrint
#else
  #define KODE_EXEPRINT
  #define KODE_ExePrint  KODE_NoPrint
  #define KODE_ExeDPrint KODE_NoPrint
#endif

//----------------------------------------------------------------------
#endif
