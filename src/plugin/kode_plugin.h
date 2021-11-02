#ifndef kode_plugin_included
#define kode_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_descriptor.h"
#include "plugin/kode_instance.h"
#include "plugin/kode_editor.h"
#include "plugin/kode_host.h"

//----------------------------------------------------------------------

//class KODE_BasePlugin {
//public:
//  virtual KODE_Descriptor*  getDescriptor() { return nullptr; }
//  virtual KODE_Instance*    createInstance(KODE_Descriptor* ADescriptor) { return nullptr; }
//  virtual KODE_Editor*      createEditor(KODE_Instance* AInstance) { return nullptr; }
//};

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

#undef KODE_PLUGIN_DEFINED

//----------

#ifdef KODE_PLUGIN_NONE
  #define KODE_PLUGIN_DEFINED
#endif

#ifdef KODE_PLUGIN_CLAP
  #define KODE_PLUGIN_DEFINED
  #include "plugin/clap/kode_clap_plugin.h"
  #define _KODE_CLAP_ENTRYPOINT(D,I,E)  KODE_CLAP_PLUGIN_ENTRYPOINT(D,I,E)
#else
  #define _KODE_CLAP_ENTRYPOINT(D,I,E)
#endif

#ifdef KODE_PLUGIN_DSSI
  #define KODE_PLUGIN_DEFINED
  #include "plugin/dssi/kode_dssi_plugin.h"
  #define _KODE_DSSI_ENTRYPOINT(D,I,E)  KODE_DSSI_PLUGIN_ENTRYPOINT(D,I,E)
#else
  #define _KODE_DSSI_ENTRYPOINT(D,I,E)
#endif

#ifdef KODE_PLUGIN_EXE
  #define KODE_PLUGIN_DEFINED
  #include "plugin/exe/kode_exe_plugin.h"
  #define _KODE_EXE_ENTRYPOINT(D,I,E)  KODE_EXE_PLUGIN_ENTRYPOINT(D,I,E)
#else
  #define _KODE_EXE_ENTRYPOINT(D,I,E)
#endif

#ifdef KODE_PLUGIN_LADSPA
  #define KODE_PLUGIN_DEFINED
  #include "plugin/ladspa/kode_ladspa_plugin.h"
  #define _KODE_LADSPA_ENTRYPOINT(D,I,E)  KODE_LADSPA_PLUGIN_ENTRYPOINT(D,I,E)
#else
  #define _KODE_LADSPA_ENTRYPOINT(D,I,E)
#endif

#ifdef KODE_PLUGIN_LV2
  #define KODE_PLUGIN_DEFINED
  #include "plugin/lv2/kode_lv2_plugin.h"
  #define _KODE_LV2_ENTRYPOINT(D,I,E)  KODE_LV2_PLUGIN_ENTRYPOINT(D,I,E)
#else
  #define _KODE_LV2_ENTRYPOINT(D,I,E)
#endif

#ifdef KODE_PLUGIN_VST2
  #define KODE_PLUGIN_DEFINED
  #include "plugin/vst2/kode_vst2_plugin.h"
  #define _KODE_VST2_ENTRYPOINT(D,I,E)  KODE_VST2_PLUGIN_ENTRYPOINT(D,I,E)
#else
  #define _KODE_VST2_ENTRYPOINT(D,I,E)
#endif

#ifdef KODE_PLUGIN_VST3
  #define KODE_PLUGIN_DEFINED
  #include "plugin/vst3/kode_vst3_plugin.h"
  #define _KODE_VST3_ENTRYPOINT(D,I,E)  KODE_VST3_PLUGIN_ENTRYPOINT(D,I,E)
#else
  #define _KODE_VST3_ENTRYPOINT(D,I,E)
#endif

//----------

#ifndef KODE_PLUGIN_DEFINED
  #error NO PLUGIN FORMAT DEFINED
#endif


//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#define KODE_PLUGIN_ENTRYPOINT(D,I,E)     \
                                          \
  _KODE_CLAP_ENTRYPOINT(D,I,E);           \
  _KODE_DSSI_ENTRYPOINT(D,I,E);           \
  _KODE_EXE_ENTRYPOINT(D,I,E);            \
  _KODE_LADSPA_ENTRYPOINT(D,I,E);         \
  _KODE_LV2_ENTRYPOINT(D,I,E);            \
  _KODE_VST2_ENTRYPOINT(D,I,E);           \
  _KODE_VST3_ENTRYPOINT(D,I,E);           \



//----------------------------------------------------------------------
#endif
