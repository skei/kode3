#ifndef kode_vst3_plugin_included
#define kode_vst3_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/vst3/kode_vst3.h"
#include "plugin/vst3/kode_vst3_instance.h"
#include "plugin/vst3/kode_vst3_utils.h"

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
  DESCRIPTOR*     MDescriptor;

//------------------------------
public:
//------------------------------

  KODE_Vst3Plugin() {
    KODE_VST3PRINT;
    MDescriptor = new DESCRIPTOR();
    MRefCount = 1;
  }

  //----------

  virtual ~KODE_Vst3Plugin() {
    KODE_VST3PRINT;
    delete MDescriptor;
  }

//------------------------------
public: // FUnknown
//------------------------------

  uint32_t VST3_API addRef() final {
    MRefCount++;
    KODE_Vst3Print("-> %i\n",MRefCount);
    return MRefCount;
  }

  //----------

  uint32_t VST3_API release() final {
    //const uint32_t r = --MRefCount;
    MRefCount--;
    KODE_Vst3Print("-> %i %s",MRefCount, (MRefCount==0) ? "(delete)\n" : "\n" );
    if (MRefCount == 0) delete this;
    return MRefCount;
  }

  //----------

  int32_t VST3_API queryInterface(const VST3_Id _iid, void** obj) final {
    KODE_Vst3Print("iid: ");
    //VST3_PrintIID(_iid);
    if (VST3_iidEqual(VST3_IPluginFactory2_iid,_iid)) {
      *obj = (VST3_IPluginFactory2*)this;
      KODE_Vst3DPrint(" (IPluginFactory2) -> Ok\n");
      addRef();
      return vst3_ResultOk;
    }
    if (VST3_iidEqual(VST3_IPluginFactory3_iid,_iid)) {
      *obj = (VST3_IPluginFactory3*)this;
      KODE_Vst3DPrint(" (IPluginFactory3) -> Ok\n");
      addRef();
      return vst3_ResultOk;
    }
    *obj = nullptr;
    KODE_Vst3DPrint(" (unknown) -> NoInterface\n");
    return vst3_NoInterface;
  }

//------------------------------
public:
//------------------------------

  //--------------------
  // IPluginFactory
  //--------------------

  int32_t VST3_API getFactoryInfo(VST3_PFactoryInfo* info) final {
    KODE_Vst3Print(" -> Ok\n");
    strcpy(info->vendor,MDescriptor->author);
    strcpy(info->url,MDescriptor->url);
    strcpy(info->email,MDescriptor->email);
    info->flags = VST3_PFactoryInfo::vst3_NoFlags;
    //KODE_Vst3DPrint(". author: '%s'\n",info->vendor);
    //KODE_Vst3DPrint(". url: '%s'\n",info->url);
    //KODE_Vst3DPrint(". email: '%s'\n",info->email);
    //KODE_Vst3DPrint(". flags: %i\n",info->flags);
    return vst3_ResultOk;
  }

  //----------

  int32_t VST3_API countClasses() final {
    KODE_Vst3Print(" -> 1\n");
    return 1;
  }

  //----------

  int32_t VST3_API getClassInfo(int32_t index, VST3_PClassInfo* info) final {
    KODE_Vst3Print("index: %i",index);
    switch (index) {
      case 0:
        KODE_Vst3DPrint(" -> Ok\n");
        memcpy(info->cid,MDescriptor->getLongId(),16);
        info->cardinality = VST3_PClassInfo::vst3_ManyInstances;
        strncpy(info->category,vst3_VstAudioEffectClass,VST3_PClassInfo::vst3_CategorySize);
        strncpy(info->name,MDescriptor->name,VST3_PClassInfo::vst3_NameSize);
        //KODE_Vst3DPrint(". cid: ");   VST3_PrintIID(info->cid);   KODE_Vst3DPrint("\n");
        //KODE_Vst3DPrint(". cardinality: %i (%s)\n",info->cardinality,info->cardinality?"ManyInstances":"");
        //KODE_Vst3DPrint(". category: '%s'\n",info->category);
        //KODE_Vst3DPrint(". name: '%s'\n",info->name);
        return vst3_ResultOk;
    }
    KODE_Vst3DPrint(" -> False\n");
    return vst3_ResultFalse;
  }

  //----------

  int32_t VST3_API createInstance(const char* cid, const char* _iid, void** obj) final {
    KODE_Vst3Print("cid: ");
    //KODE_Vst3DPrint(cid);
    //VST3_PrintIID(cid);
    if (VST3_iidEqual(MDescriptor->getLongId(),cid)) {
      KODE_Vst3DPrint(" (%s) -> Ok\n",MDescriptor->name);

      //INSTANCE* instance = new INSTANCE(MDescriptor);

      KODE_Instance* instance = _kode_create_instance(MDescriptor);
      KODE_Vst3Instance* vst3_instance = new KODE_Vst3Instance(instance);

      instance->on_plugin_init(); //  ->on_plugin_destroy called in vst3_instance.release()

//      instance->setDefaultParameterValues();
//      instance->updateAllParameters();

      //*obj = (VST3_IComponent*)instance;
      *obj = (VST3_IComponent*)vst3_instance;
      return vst3_ResultOk;
    }
    *obj = nullptr;
    KODE_Vst3DPrint(" (unknown) -> False\n");
    return vst3_NotImplemented;
  }

//------------------------------
public: // IPluginFactory2
//------------------------------

  int32_t VST3_API getClassInfo2(int32_t index, VST3_PClassInfo2* info) final {
    KODE_Vst3Print("index: %i",index);
    switch (index) {
      case 0:
        memcpy(info->cid,MDescriptor->getLongId(),16);
        info->cardinality = VST3_PClassInfo::vst3_ManyInstances;
        strcpy(info->category,vst3_VstAudioEffectClass);
        strcpy(info->name,MDescriptor->name);
        info->classFlags = 0;
        if (MDescriptor->options.is_synth) {
          strcpy(info->subCategories,vst3_Instrument);
        }
        else {
          strcpy(info->subCategories,vst3_Fx);
        }
        strcpy(info->vendor,MDescriptor->author);
        strcpy(info->version,MDescriptor->getVersionString());
        strcpy(info->sdkVersion,vst3_VstVersionString);
        KODE_Vst3DPrint(" -> Ok\n");
        //KODE_Vst3DPrint(". cid: ");   VST3_PrintIID(info->cid);   KODE_Vst3DPrint("\n");
        //KODE_Vst3DPrint(". cardinality: %i (%s)\n",info->cardinality,info->cardinality?"ManyInstances":"");
        //KODE_Vst3DPrint(". category: '%s'\n",info->category);
        //KODE_Vst3DPrint(". name: '%s'\n",info->name);
        //KODE_Vst3DPrint(". classFlags: %i\n",info->classFlags);
        //KODE_Vst3DPrint(". subCategories: '%s'\n",info->subCategories);
        return vst3_ResultOk;
    }
    KODE_Vst3DPrint(" -> False\n");
    return vst3_ResultFalse;
  }

//------------------------------
public: // IPluginFactory3
//------------------------------

  int32_t VST3_API getClassInfoUnicode(int32_t index, VST3_PClassInfoW* info) final {
    KODE_Vst3Print("index: %i -> False\n",index);
    return vst3_ResultFalse;
  }

  //----------

  int32_t VST3_API setHostContext(VST3_FUnknown* context) final {
    KODE_Vst3Print("context: %p -> Ok\n",context);
    MHostContext = context;
    return vst3_ResultOk;
  }

};

//----------------------------------------------------------------------
//
// entrypoint
//
//----------------------------------------------------------------------

//#define VST3_MAIN_SYMBOL asm ("GetPluginFactory");
//#define VST3_MODULE_ENTRY_SYMBOL asm ("ModuleEntry");
//#define VST3_MODULE_EXIT_SYMBOL asm ("ModuleExit");

VST3_IPluginFactory* VST3_API vst3_entrypoint()                             asm ("GetPluginFactory"); // VST3_MAIN_SYMBOL;
bool                          vst3_module_entry(void* sharedLibraryHandle)  asm ("ModuleEntry");      // VST3_MODULE_ENTRY_SYMBOL;
bool                          vst3_module_exit(void)                        asm ("ModuleExit");       // VST3_MODULE_EXIT_SYMBOL;

//----------

#define KODE_VST3_MAIN(D,I,E)                           \
                                                        \
  /*__attribute__((visibility("default")))*/            \
  __KODE_DLLEXPORT                                      \
  VST3_IPluginFactory* VST3_API vst3_entrypoint() {     \
    KODE_VST3PRINT;                                     \
    return new KODE_Vst3Plugin<D,I,E>();                \
  }                                                     \
                                                        \
/*  void* moduleHandle = nullptr;              */       \
/*  static int counter {0};                    */       \
                                                        \
  /*__attribute__((visibility("default")))*/            \
  __KODE_DLLEXPORT                                      \
  bool vst3_module_entry(void* sharedLibraryHandle)  {  \
    KODE_VST3PRINT;                                     \
/*    if (++counter == 1) {                    */       \
/*      moduleHandle = sharedLibraryHandle;    */       \
/*      return true;                           */       \
/*    }                                        */       \
    return true;                                        \
  }                                                     \
                                                        \
  /*__attribute__((visibility("default")))*/            \
  __KODE_DLLEXPORT                                      \
  bool vst3_module_exit(void) {                         \
    KODE_VST3PRINT;                                     \
/*    if (--counter == 0) {                    */       \
/*      moduleHandle = nullptr;                */       \
/*      return true;                           */       \
/*    }                                        */       \
    return true;                                        \
  }


//----------------------------------------------------------------------
#endif
