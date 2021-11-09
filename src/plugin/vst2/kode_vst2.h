#ifndef kode_vst2_included
#define kode_vst2_included
//----------------------------------------------------------------------

#include "kode.h"

//#ifdef KODE_PLUGIN_VST2_VESTIGE
//  typedef int32_t   VstInt32;
//  typedef intptr_t  VstIntPtr;
//  struct  ERect { int16_t top, left, bottom, right; };
//  #include "extern/vst2/vestige.h"
//#else

  #define __cdecl
  #include "extern/vst2/aeffect.h"
  #include "extern/vst2/aeffectx.h"

//#endif

//----------------------------------------------------------------------

#ifndef KODE_DEBUG
  #undef KODE_DEBUG_VST2
#endif

#ifdef KODE_DEBUG_VST2
  #define KODE_VST2PRINT  KODE_PRINT
  #define KODE_Vst2Print  KODE_Print
  #define KODE_Vst2DPrint KODE_DPrint
#else
  #define KODE_VST2PRINT
  #define KODE_Vst2Print  KODE_NoPrint
  #define KODE_Vst2DPrint KODE_NoPrint
#endif

//----------------------------------------------------------------------
#endif




