#ifndef kode_dssi_plugin_included
#define kode_dssi_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/dssi/kode_dssi.h"

//----------------------------------------------------------------------

#define DSSI_PLUGIN_API

struct DSSI_Descriptor {
};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

template <class DESCRIPTOR, class INSTANCE, class EDITOR>
class KODE_DssiPlugin {

//------------------------------
private:
//------------------------------

  DESCRIPTOR* MDescriptor = nullptr;

//------------------------------
public:
//------------------------------

  KODE_DssiPlugin() {
    KODE_PRINT;
    MDescriptor = new DESCRIPTOR();
  }

  //----------

  ~KODE_DssiPlugin() {
    KODE_PRINT;
    delete MDescriptor;
  }

//------------------------------
public:
//------------------------------

  DSSI_Descriptor* entrypoint(int32_t AIndex) {
    return nullptr;
  }

};



//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#define DSSI_ENTRYPOINT_SYMBOL asm ("dssi_descriptor");
const DSSI_Descriptor* dssi_entrypoint(uint32_t index) DSSI_ENTRYPOINT_SYMBOL;

//----------

#define KODE_DSSI_PLUGIN_ENTRYPOINT(D,I,E)                                  \
                                                                            \
  KODE_DssiPlugin<D,I,E> DSSI_PLUGIN;                                       \
                                                                            \
  __attribute__ ((visibility ("default")))                                  \
  const DSSI_Descriptor* DSSI_PLUGIN_API dssi_entrypoint(uint32_t index) {  \
    KODE_Print("\n");                                                       \
    return DSSI_PLUGIN.entrypoint(index);                                   \
  }

//----------------------------------------------------------------------
#endif


