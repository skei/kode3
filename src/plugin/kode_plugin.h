#ifndef kode_plugin_included
#define kode_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_descriptor.h"

#include "plugin/kode_instance.h"
#include "plugin/kode_editor.h"

#include "plugin/clap/kode_clap_plugin.h"
#include "plugin/dssi/kode_dssi_plugin.h"
#include "plugin/exe/kode_exe_plugin.h"
#include "plugin/ladspa/kode_ladspa_plugin.h"
#include "plugin/lv2/kode_lv2_plugin.h"
#include "plugin/vst2/kode_vst2_plugin.h"
#include "plugin/vst3/kode_vst3_plugin.h"

//----------------------------------------------------------------------

#define KODE_PLUGIN_ENTRYPOINT(D,I)   \
                                      \
  KODE_CLAP_PLUGIN_ENTRYPOINT(D,I);   \
  KODE_DSSI_PLUGIN_ENTRYPOINT(D,I);   \
  KODE_EXE_PLUGIN_ENTRYPOINT(D,I);    \
  KODE_LADSPA_PLUGIN_ENTRYPOINT(D,I); \
  KODE_LV2_PLUGIN_ENTRYPOINT(D,I);    \
  KODE_VST2_PLUGIN_ENTRYPOINT(D,I);   \
  KODE_VST3_PLUGIN_ENTRYPOINT(D,I);   \


//----------------------------------------------------------------------
#endif
