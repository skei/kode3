#ifndef kode_vst3_included
#define kode_vst3_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/vst3/kode_vst3_base.h"

#ifndef KODE_DEBUG
  #undef KODE_DEBUG_VST3
#endif

#ifdef KODE_DEBUG_VST3
  #define KODE_VST3PRINT  KODE_PRINT
  #define KODE_Vst3Print  KODE_Print
  #define KODE_Vst3DPrint KODE_DPrint
#else
  #define KODE_VST3PRINT
  #define KODE_Vst3Print  KODE_NoPrint
  #define KODE_Vst3DPrint KODE_NoPrint
#endif

//----------------------------------------------------------------------
#endif
