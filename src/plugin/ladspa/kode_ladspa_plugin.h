#ifndef kode_ladspa_plugin_included
#define kode_ladspa_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/ladspa/kode_ladspa.h"

//----------------------------------------------------------------------

#define LADSPA_PLUGIN_API

struct LADSPA_Descriptor {
};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

template <class DESCRIPTOR, class INSTANCE, class EDITOR>
class KODE_LadspaPlugin {

//------------------------------
private:
//------------------------------

  DESCRIPTOR MDescriptor = {};

//------------------------------
public:
//------------------------------

  KODE_LadspaPlugin() {
    KODE_PRINT;
  }

  //----------

  ~KODE_LadspaPlugin() {
    KODE_PRINT;
  }

//------------------------------
public:
//------------------------------

  LADSPA_Descriptor* entrypoint(uint32_t AIndex) {
    return nullptr;
  }

};



//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#define LADSPA_ENTRYPOINT_SYMBOL asm ("ladspa_descriptor");
const LADSPA_Descriptor* ladspa_entrypoint() LADSPA_ENTRYPOINT_SYMBOL;

//----------

#define KODE_LADSPA_PLUGIN_ENTRYPOINT(D,I,E)                                      \
                                                                                  \
  KODE_LadspaPlugin<D,I,E> LADSPA_PLUGIN;                                         \
                                                                                  \
  __attribute__ ((visibility ("default")))                                        \
  const LADSPA_Descriptor* LADSPA_PLUGIN_API ladspa_entrypoint(uint32_t index) {  \
    KODE_Print("\n");                                                             \
    return LADSPA_PLUGIN.entrypoint(index);                                       \
  }

//----------------------------------------------------------------------
#endif


