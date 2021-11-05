#ifndef kode_vst3_plugin_included
#define kode_vst3_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/vst3/kode_vst3.h"
#include "plugin/vst3/kode_vst3_instance.h"
#include "plugin/vst3/kode_vst3_utils.h"

//----------------------------------------------------------------------

//#define KODE_VST3_MAIN(D,I,E)

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

template <class DESCRIPTOR, class INSTANCE, class EDITOR>
class KODE_Vst3Plugin
: public VST3_IPluginFactory3 {

//------------------------------
private:
//------------------------------

  uint32_t        MRefCount     = 1;
  VST3_FUnknown*  MHostContext  = nullptr;
  DESCRIPTOR      MDescriptor;

//------------------------------
public:
//------------------------------

  KODE_Vst3Plugin() {
    KODE_Print("1\n");
    MRefCount = 1;
  }

  //----------

  virtual ~KODE_Vst3Plugin() {
    KODE_PRINT;
  }

//------------------------------
public: // FUnknown
//------------------------------

  uint32_t VST3_API addRef() final {
    MRefCount++;
    KODE_Print("-> %i\n",MRefCount);
    return MRefCount;
  }

  //----------

  uint32_t VST3_API release() final {
    const uint32_t r = --MRefCount;
    KODE_Print("-> %i %s",r, (r==0) ? "(delete)\n" : "\n" );
    if (r == 0) delete this;
    return r;
  }

  //----------

  int32_t VST3_API queryInterface(const VST3_Id _iid, void** obj) final {
    KODE_Print("iid: ");
    VST3_PrintIID(_iid);
    if (VST3_iidEqual(VST3_IPluginFactory2_iid,_iid)) {
      *obj = (VST3_IPluginFactory2*)this;
      KODE_DPrint(" (IPluginFactory2) -> Ok\n");
      addRef();
      return vst3_ResultOk;
    }
    if (VST3_iidEqual(VST3_IPluginFactory3_iid,_iid)) {
      *obj = (VST3_IPluginFactory3*)this;
      KODE_DPrint(" (IPluginFactory3) -> Ok\n");
      addRef();
      return vst3_ResultOk;
    }
    *obj = nullptr;
    KODE_DPrint(" (unknown) -> NoInterface\n");
    return vst3_NoInterface;
  }

//------------------------------
public:
//------------------------------

  //--------------------
  // IPluginFactory
  //--------------------

  int32_t VST3_API getFactoryInfo(VST3_PFactoryInfo* info) final {
    KODE_Print(" -> Ok\n");
    strcpy(info->vendor,MDescriptor.author);
    strcpy(info->url,MDescriptor.url);
    strcpy(info->email,MDescriptor.email);
    info->flags = VST3_PFactoryInfo::vst3_NoFlags;
    KODE_DPrint(". author: '%s'\n",info->vendor);
    KODE_DPrint(". url: '%s'\n",info->url);
    KODE_DPrint(". email: '%s'\n",info->email);
    KODE_DPrint(". flags: %i\n",info->flags);
    return vst3_ResultOk;
  }

  //----------

  int32_t VST3_API countClasses() final {
    KODE_Print(" -> 1\n");
    return 1;
  }

  //----------

  int32_t VST3_API getClassInfo(int32_t index, VST3_PClassInfo* info) final {
    KODE_Print("index: %i",index);
    switch (index) {
      case 0:
        KODE_DPrint(" -> Ok\n");
        memcpy(info->cid,MDescriptor.getLongId(),16);
        info->cardinality = VST3_PClassInfo::vst3_ManyInstances;
        strncpy(info->category,vst3_VstAudioEffectClass,VST3_PClassInfo::vst3_CategorySize);
        strncpy(info->name,MDescriptor.name,VST3_PClassInfo::vst3_NameSize);
        KODE_DPrint(". cid: ");   VST3_PrintIID(info->cid);   KODE_DPrint("\n");
        KODE_DPrint(". cardinality: %i (%s)\n",info->cardinality,info->cardinality?"ManyInstances":"");
        KODE_DPrint(". category: '%s'\n",info->category);
        KODE_DPrint(". name: '%s'\n",info->name);
        return vst3_ResultOk;
    }
    KODE_DPrint(" -> False\n");
    return vst3_ResultFalse;
  }

  //----------

  int32_t VST3_API createInstance(const char* cid, const char* _iid, void** obj) final {
    KODE_Print("cid: ");
    //KODE_DPrint(cid);
    VST3_PrintIID(cid);
    if (VST3_iidEqual(MDescriptor.getLongId(),cid)) {
      KODE_DPrint(" (%s) -> Ok\n",MDescriptor.name);
      INSTANCE* instance = new INSTANCE(&MDescriptor);
//      instance->on_plugin_open();
//      instance->setDefaultParameterValues();
//      instance->updateAllParameters();
      *obj = (VST3_IComponent*)instance;
      return vst3_ResultOk;
    }
    *obj = nullptr;
    KODE_DPrint(" (unknown) -> False\n");
    return vst3_NotImplemented;
  }

//------------------------------
public: // IPluginFactory2
//------------------------------

  int32_t VST3_API getClassInfo2(int32_t index, VST3_PClassInfo2* info) final {
    KODE_Print("index: %i",index);
    switch (index) {
      case 0:
        memcpy(info->cid,MDescriptor.getLongId(),16);
        info->cardinality = VST3_PClassInfo::vst3_ManyInstances;
        strcpy(info->category,vst3_VstAudioEffectClass);
        strcpy(info->name,MDescriptor.name);
        info->classFlags = 0;
        if (MDescriptor.options.is_synth) {
          strcpy(info->subCategories,vst3_Instrument);
        }
        else {
          strcpy(info->subCategories,vst3_Fx);
        }
        strcpy(info->vendor,MDescriptor.author);
        strcpy(info->version,MDescriptor.getVersionString());
        strcpy(info->sdkVersion,vst3_VstVersionString);
        KODE_DPrint(" -> Ok\n");
        KODE_DPrint(". cid: ");   VST3_PrintIID(info->cid);   KODE_DPrint("\n");
        KODE_DPrint(". cardinality: %i (%s)\n",info->cardinality,info->cardinality?"ManyInstances":"");
        KODE_DPrint(". category: '%s'\n",info->category);
        KODE_DPrint(". name: '%s'\n",info->name);
        KODE_DPrint(". classFlags: %i\n",info->classFlags);
        KODE_DPrint(". subCategories: '%s'\n",info->subCategories);
        return vst3_ResultOk;
    }
    KODE_DPrint(" -> False\n");
    return vst3_ResultFalse;
  }

//------------------------------
public: // IPluginFactory3
//------------------------------

  int32_t VST3_API getClassInfoUnicode(int32_t index, VST3_PClassInfoW* info) final {
    KODE_Print("index: %i -> False\n",index);
    return vst3_ResultFalse;
  }

  //----------

  int32_t VST3_API setHostContext(VST3_FUnknown* context) final {
    KODE_Print("context: %p -> Ok\n",context);
    MHostContext = context;
    return vst3_ResultOk;
  }

};


//----------------------------------------------------------------------
//
// entrypoint
//
//----------------------------------------------------------------------

#define VST3_MAIN_SYMBOL asm ("GetPluginFactory");
VST3_IPluginFactory* VST3_API vst3_entrypoint() VST3_MAIN_SYMBOL;

#define VST3_MODULE_ENTRY_SYMBOL asm ("ModuleEntry");
bool vst3_module_entry(void* sharedLibraryHandle) VST3_MODULE_ENTRY_SYMBOL;

#define VST3_MODULE_EXIT_SYMBOL asm ("ModuleExit");
bool vst3_module_exit(void) VST3_MODULE_EXIT_SYMBOL;

//----------

#define KODE_VST3_MAIN(D,I,E)                           \
                                                        \
  __attribute__((visibility("default")))                \
  VST3_IPluginFactory* VST3_API vst3_entrypoint() {     \
    KODE_Print("\n");                                   \
    return new KODE_Vst3Plugin<D,I,E>();                \
  }                                                     \
                                                        \
/*  void* moduleHandle = nullptr;              */       \
/*  static int counter {0};                    */       \
                                                        \
  __attribute__((visibility("default")))                \
  bool vst3_module_entry(void* sharedLibraryHandle) {   \
/*  KODE_Print("\n");                      */           \
/*    if (++counter == 1) {                    */       \
/*      moduleHandle = sharedLibraryHandle;    */       \
/*      return true;                           */       \
/*    }                                        */       \
    return true;                                        \
  }                                                     \
                                                        \
  __attribute__((visibility("default")))                \
  bool vst3_module_exit(void) {                         \
/*    KODE_Print("\n");                    */           \
/*    if (--counter == 0) {                    */       \
/*      moduleHandle = nullptr;                */       \
/*      return true;                           */       \
/*    }                                        */       \
    return true;                                        \
  }


//----------------------------------------------------------------------
#endif
