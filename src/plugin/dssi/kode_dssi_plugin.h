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

  DESCRIPTOR MDescriptor = {};

//------------------------------
public:
//------------------------------

  KODE_DssiPlugin() {
    KODE_PRINT;
  }

  //----------

  ~KODE_DssiPlugin() {
    KODE_PRINT;
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

//#ifdef __cplusplus
//extern "C" {
//#endif

//----------

#define DSSI_ENTRYPOINT_SYMBOL asm ("dssi_descriptor");
const DSSI_Descriptor* dssi_entrypoint(uint32_t index) DSSI_ENTRYPOINT_SYMBOL;

//#define VST3_MODULE_ENTRY_SYMBOL  asm ("ModuleEntry");
//#define VST3_MODULE_EXIT_SYMBOL   asm ("ModuleExit");

//bool vst3_module_entry(void* sharedLibraryHandle)  VST3_MODULE_ENTRY_SYMBOL;
//bool vst3_module_exit(void)                        VST3_MODULE_EXIT_SYMBOL;

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

//#ifdef __cplusplus
//}
//#endif

//----------------------------------------------------------------------
#endif


