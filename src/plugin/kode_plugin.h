#ifndef kode_plugin_included
#define kode_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_descriptor.h"
#include "plugin/kode_instance.h"
#include "plugin/kode_editor.h"

KODE_Descriptor*  _kode_create_descriptor();
KODE_Instance*    _kode_create_instance(KODE_Descriptor* ADescriptor);
KODE_Editor*      _kode_create_editor(KODE_Instance* AInstance);

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#undef KODE_PLUGIN_DEFINED

#ifdef KODE_NO_PLUGIN
  #define KODE_PLUGIN_DEFINED
#endif

//----------

//#ifdef KODE_PLUGIN_ALL
//  #define KODE_PLUGIN_CLAP
//  #define KODE_PLUGIN_DSSI
//  #define KODE_PLUGIN_EXE
//  #define KODE_PLUGIN_LADSPA
//  #define KODE_PLUGIN_LV2
//  #define KODE_PLUGIN_VST2
//  #define KODE_PLUGIN_VST3
//#endif

//----------

#ifdef KODE_PLUGIN_CLAP
  #define KODE_PLUGIN_DEFINED
  #include "plugin/clap/kode_clap_plugin.h"
#else
  #define KODE_CLAP_MAIN(D,I,E)
#endif

#ifdef KODE_PLUGIN_DSSI
  #define KODE_PLUGIN_DEFINED
  #include "plugin/dssi/kode_dssi_plugin.h"
#else
  #define KODE_DSSI_MAIN(D,I,E)
#endif

#ifdef KODE_PLUGIN_EXE
  #define KODE_PLUGIN_DEFINED
  #include "plugin/exe/kode_exe_plugin.h"
#else
  #define KODE_EXE_MAIN(D,I,E)
#endif

#ifdef KODE_PLUGIN_LADSPA
  #define KODE_PLUGIN_DEFINED
  #include "plugin/ladspa/kode_ladspa_plugin.h"
#else
  #define KODE_LADSPA_MAIN(D,I,E)
#endif

#ifdef KODE_PLUGIN_LV2
  #define KODE_PLUGIN_DEFINED
  #include "plugin/lv2/kode_lv2_plugin.h"
#else
  #define KODE_LV2_MAIN(D,I,E)
#endif

#ifdef KODE_PLUGIN_VST2
  #define KODE_PLUGIN_DEFINED
  #include "plugin/vst2/kode_vst2_plugin.h"
#else
  #define KODE_VST2_MAIN(D,I,E)
#endif

#ifdef KODE_PLUGIN_VST3
  #define KODE_PLUGIN_DEFINED
  #include "plugin/vst3/kode_vst3_plugin.h"
#else
  #define KODE_VST3_MAIN(D,I,E)
#endif

//----------

#ifndef KODE_PLUGIN_DEFINED
  #warning NO PLUGIN FORMAT DEFINED
#endif

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#define KODE_MAIN(D,I,E)                                                                    \
                                                                                            \
  KODE_Descriptor*  _kode_create_descriptor()                     { return new D();      }  \
  KODE_Instance*    _kode_create_instance(KODE_Descriptor* ADesc) { return new I(ADesc); }  \
  KODE_Editor*      _kode_create_editor(KODE_Instance* AInst)     { return new E(AInst); }  \
                                                                                            \
  KODE_CLAP_MAIN(D,I,E);                                                                    \
  KODE_DSSI_MAIN(D,I,E);                                                                    \
  KODE_EXE_MAIN(D,I,E);                                                                     \
  KODE_LADSPA_MAIN(D,I,E);                                                                  \
  KODE_LV2_MAIN(D,I,E);                                                                     \
  KODE_VST2_MAIN(D,I,E);                                                                    \
  KODE_VST3_MAIN(D,I,E);                                                                    \


//----------------------------------------------------------------------
#endif
