#ifndef kode_vst2_plugin_included
#define kode_vst2_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/vst2/kode_vst2.h"

//----------------------------------------------------------------------

#define VST2_PLUGIN_API
//struct AEffect {
//};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

template <class DESCRIPTOR, class INSTANCE, class EDITOR>
class KODE_Vst2Plugin
/*: public VST2_IPluginFactory*/ {

//------------------------------
private:
//------------------------------

  DESCRIPTOR MDescriptor = {};

//------------------------------
public:
//------------------------------

  KODE_Vst2Plugin()
  /*: VST3_IPluginFactory()*/ {
    KODE_PRINT;
  }

  //----------

  ~KODE_Vst2Plugin() {
    KODE_PRINT;
  }

//------------------------------
public:
//------------------------------

  AEffect* entrypoint(audioMasterCallback audioMaster) {
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

#define VST2_ENTRYPOINT_SYMBOL asm ("VSTPluginMain");
AEffect* VST2_PLUGIN_API vst2_entrypoint(audioMasterCallback audioMaster) VST2_ENTRYPOINT_SYMBOL;

//#define VST3_MODULE_ENTRY_SYMBOL  asm ("ModuleEntry");
//#define VST3_MODULE_EXIT_SYMBOL   asm ("ModuleExit");


//bool vst3_module_entry(void* sharedLibraryHandle)  VST3_MODULE_ENTRY_SYMBOL;
//bool vst3_module_exit(void)                        VST3_MODULE_EXIT_SYMBOL;

//----------

#define KODE_VST2_PLUGIN_ENTRYPOINT(D,I,E)                                    \
                                                                              \
  KODE_Vst2Plugin<D,I,E> VST2_PLUGIN;                                         \
                                                                              \
  __attribute__ ((visibility ("default")))                                    \
  AEffect* VST2_PLUGIN_API vst2_entrypoint(audioMasterCallback audioMaster) { \
    KODE_Print("\n");                                                         \
    return VST2_PLUGIN.entrypoint(audioMaster);                               \
  }                                                                           \
                                                                              \
/*  void* moduleHandle = nullptr;                       */                    \
/*  static int counter {0};                             */                    \
                                                                              \
/*  __attribute__ ((visibility ("default")))            */                    \
/*  bool vst3_module_entry(void* sharedLibraryHandle) { */                    \
/*    KODE_Vst3Print("\n");                             */                    \
/*    if (++counter == 1) {                             */                    \
/*      moduleHandle = sharedLibraryHandle;             */                    \
/*      return true;                                    */                    \
/*    }                                                 */                    \
/*    return true;                                      */                    \
/*  }                                                   */                    \
                                                                              \
/*  __attribute__ ((visibility ("default")))            */                    \
/*  bool vst3_module_exit(void) {                       */                    \
/*    KODE_Vst3Print("\n");                             */                    \
/*    if (--counter == 0) {                             */                    \
/*      moduleHandle = nullptr;                         */                    \
/*      return true;                                    */                    \
/*    }                                                 */                    \
/*    return true;                                      */                    \
/*  }                                                   */                    \

//----------------------------------------------------------------------
#endif


