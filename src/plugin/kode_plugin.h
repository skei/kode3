#ifndef kode_plugin_included
#define kode_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_descriptor.h"
#include "plugin/kode_instance.h"
#include "plugin/kode_editor.h"
#include "plugin/kode_host.h"

//----------------------------------------------------------------------

#ifdef KODE_PLUGIN_ALL
  #define KODE_PLUGIN_CLAP
  #define KODE_PLUGIN_DSSI
  #define KODE_PLUGIN_EXE
  #define KODE_PLUGIN_LADSPA
  #define KODE_PLUGIN_LV2
  #define KODE_PLUGIN_VST2
  #define KODE_PLUGIN_VST3
#endif

//----------------------------------------------------------------------

#ifdef KODE_PLUGIN_CLAP
  #include "plugin/clap/kode_clap_plugin.h"
  #define _KODE_CLAP_ENTRYPOINT(D,I)  KODE_CLAP_PLUGIN_ENTRYPOINT(D,I)
#else
  #define _KODE_CLAP_ENTRYPOINT(D,I)
#endif

#ifdef KODE_PLUGIN_DSSI
  #include "plugin/dssi/kode_dssi_plugin.h"
  #define _KODE_DSSI_ENTRYPOINT(D,I)  KODE_DSSI_PLUGIN_ENTRYPOINT(D,I)
#else
  #define _KODE_DSSI_ENTRYPOINT(D,I)
#endif

#ifdef KODE_PLUGIN_EXE
  #include "plugin/exe/kode_exe_plugin.h"
  #define _KODE_EXE_ENTRYPOINT(D,I)  KODE_EXE_PLUGIN_ENTRYPOINT(D,I)
#else
  #define _KODE_EXE_ENTRYPOINT(D,I)
#endif

#ifdef KODE_PLUGIN_LADSPA
  #include "plugin/ladspa/kode_ladspa_plugin.h"
  #define _KODE_LADSPA_ENTRYPOINT(D,I)  KODE_LADSPA_PLUGIN_ENTRYPOINT(D,I)
#else
  #define _KODE_LADSPA_ENTRYPOINT(D,I)
#endif

#ifdef KODE_PLUGIN_LV2
  #include "plugin/lv2/kode_lv2_plugin.h"
  #define _KODE_LV2_ENTRYPOINT(D,I)  KODE_LV2_PLUGIN_ENTRYPOINT(D,I)
#else
  #define _KODE_LV2_ENTRYPOINT(D,I)
#endif

#ifdef KODE_PLUGIN_VST2
  #include "plugin/vst2/kode_vst2_plugin.h"
  #define _KODE_VST2_ENTRYPOINT(D,I)  KODE_VST2_PLUGIN_ENTRYPOINT(D,I)
#else
  #define _KODE_VST2_ENTRYPOINT(D,I)
#endif

#ifdef KODE_PLUGIN_VST3
  #include "plugin/vst3/kode_vst3_plugin.h"
  #define _KODE_VST3_ENTRYPOINT(D,I)  KODE_VST3_PLUGIN_ENTRYPOINT(D,I)
#else
  #define _KODE_VST3_ENTRYPOINT(D,I)
#endif

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#define KODE_PLUGIN_ENTRYPOINT(D,I)   \
                                      \
  _KODE_CLAP_ENTRYPOINT(D,I);         \
  _KODE_DSSI_ENTRYPOINT(D,I);         \
  _KODE_EXE_ENTRYPOINT(D,I);          \
  _KODE_LADSPA_ENTRYPOINT(D,I);       \
  _KODE_LV2_ENTRYPOINT(D,I);          \
  _KODE_VST2_ENTRYPOINT(D,I);         \
  _KODE_VST3_ENTRYPOINT(D,I);         \



//----------------------------------------------------------------------
#endif
