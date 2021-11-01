#ifndef kode_vst3_plugin_included
#define kode_vst3_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
//#include "plugin/vst3/kode_vst3.h"

//----------------------------------------------------------------------

#define VST3_PLUGIN_API
class VST3_IPluginFactory {
};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

template <class DESCRIPTOR, class INSTANCE, class EDITOR>
class KODE_Vst3Plugin
: public VST3_IPluginFactory {

//------------------------------
private:
//------------------------------

  DESCRIPTOR* MDescriptor = nullptr;

//------------------------------
public:
//------------------------------

  KODE_Vst3Plugin()
  : VST3_IPluginFactory() {
    KODE_PRINT;
    MDescriptor = new DESCRIPTOR();
  }

  //----------

  ~KODE_Vst3Plugin() {
    KODE_PRINT;
    delete MDescriptor;
  }

};



//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#define VST3_ENTRYPOINT_SYMBOL    asm ("GetPluginFactory");
#define VST3_MODULE_ENTRY_SYMBOL  asm ("ModuleEntry");
#define VST3_MODULE_EXIT_SYMBOL   asm ("ModuleExit");

VST3_IPluginFactory*  VST3_PLUGIN_API vst3_entrypoint()                             VST3_ENTRYPOINT_SYMBOL;
bool                                  vst3_module_entry(void* sharedLibraryHandle)  VST3_MODULE_ENTRY_SYMBOL;
bool                                  vst3_module_exit(void)                        VST3_MODULE_EXIT_SYMBOL;

//----------

#define KODE_VST3_PLUGIN_ENTRYPOINT(D,I,E)                  \
                                                            \
  /*__KODE_DLLEXPORT*/                                      \
  __attribute__ ((visibility ("default")))                  \
  VST3_IPluginFactory* VST3_PLUGIN_API vst3_entrypoint() {  \
    KODE_Print("\n");                                       \
    return new KODE_Vst3Plugin<D,I,E>();                    \
  }                                                         \
                                                            \
/*  void* moduleHandle = nullptr;              */           \
/*  static int counter {0};                    */           \
                                                            \
  /*__KODE_DLLEXPORT*/                                      \
  __attribute__ ((visibility ("default")))                  \
  bool vst3_module_entry(void* sharedLibraryHandle) {       \
/*  KODE_Vst3Print("\n");                      */           \
/*    if (++counter == 1) {                    */           \
/*      moduleHandle = sharedLibraryHandle;    */           \
/*      return true;                           */           \
/*    }                                        */           \
    return true;                                            \
  }                                                         \
                                                            \
  /*__KODE_DLLEXPORT*/                                      \
  __attribute__ ((visibility ("default")))                  \
  bool vst3_module_exit(void) {                             \
/*    KODE_Vst3Print("\n");                    */           \
/*    if (--counter == 0) {                    */           \
/*      moduleHandle = nullptr;                */           \
/*      return true;                           */           \
/*    }                                        */           \
    return true;                                            \
  }

//----------------------------------------------------------------------
#endif


