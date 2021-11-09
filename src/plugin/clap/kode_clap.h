#ifndef kode_clap_included
#define kode_clap_included
//----------------------------------------------------------------------

#include "kode.h"

//#include "../../clap/include/clap/all.h"
#include "extern/clap/all.h"

#ifndef KODE_DEBUG
  #undef KODE_DEBUG_CLAP
#endif

#ifdef KODE_DEBUG_CLAP
  #define KODE_CLAPPRINT  KODE_PRINT
  #define KODE_ClapPrint  KODE_Print
  #define KODE_ClapDPrint KODE_DPrint
#else
  #define KODE_CLAPPRINT
  #define KODE_ClapPrint  KODE_NoPrint
  #define KODE_ClapDPrint KODE_NoPrint
#endif


//----------------------------------------------------------------------
#endif
