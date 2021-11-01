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
class KODE_Vst2Plugin {

//------------------------------
private:
//------------------------------

  DESCRIPTOR* MDescriptor = nullptr;
  AEffect*    MAEffect    = nullptr;

//------------------------------
public:
//------------------------------

  KODE_Vst2Plugin() {
    KODE_PRINT;
    MDescriptor = new DESCRIPTOR();
    MAEffect = (AEffect*)malloc(sizeof(AEffect));
    memset(MAEffect,0,sizeof(AEffect));
  }

  //----------

  ~KODE_Vst2Plugin() {
    KODE_PRINT;
    free(MAEffect);
    delete MDescriptor;
  }

//------------------------------
private:
//------------------------------

  void vst2_set_parameter(int index, float value) {
  }

  //----------

  float vst2_get_parameter(int index) {
    return 0.0f;
  }

  //----------

  intptr_t vst2_dispatcher(int opcode, int index, intptr_t ip, void* ptr, float f) {
    switch(opcode) {
    }
    return 0;
  }

  //----------

  void vst2_process(float** inputs, float** outputs, int length) {
  }

  //----------

  void vst2_process_replacing(float** inputs, float** outouts, int length) {
  }

//------------------------------
private:
//------------------------------

  static
  void vst2_set_parameter_callback(struct _AEffect* aeffect, int i, float f) {
    KODE_Vst2Plugin* vst2_plugin = (KODE_Vst2Plugin*)aeffect->user;
    //KODE_Vst2Instance* vst2_instance = (KODE_Vst2Instance*)aeffect->object;
    vst2_plugin->vst2_set_parameter(i,f);
  }

  static
  float vst2_get_parameter_callback(struct _AEffect* aeffect, int i) {
    KODE_Vst2Plugin* vst2_plugin = (KODE_Vst2Plugin*)aeffect->user;
    return vst2_plugin->vst2_get_parameter(i);
  }

  static
  intptr_t vst2_dispatcher_callback(struct _AEffect* aeffect, int i1, int i2, intptr_t ip, void* p, float f) {
    KODE_Vst2Plugin* vst2_plugin = (KODE_Vst2Plugin*)aeffect->user;
    return vst2_plugin->vst2_dispatcher(i1,i2,ip,p,f);
  }

  static
  void vst2_process_callback(struct _AEffect* aeffect, float** f1, float** f2, int i) {
    KODE_Vst2Plugin* vst2_plugin = (KODE_Vst2Plugin*)aeffect->user;
    vst2_plugin->vst2_process(f1,f2,i);
  }

  static
  void vst2_process_replacing_callback(struct _AEffect* aeffect, float** f1, float** f2, int i) {
    KODE_Vst2Plugin* vst2_plugin = (KODE_Vst2Plugin*)aeffect->user;
    vst2_plugin->vst2_process_replacing(f1,f2,i);
  }


//------------------------------
public:
//------------------------------

  AEffect* entrypoint(audioMasterCallback audioMaster) {
    //KODE_Vst2Instance* vst2_instance = new KODE_Vst2Instance();
    //memset(&MAEffect,0,sizeof(AEffect));
    MAEffect->magic            = 0;
    MAEffect->flags            = 0;
    MAEffect->numPrograms      = 0;
    MAEffect->numParams        = 0;
    MAEffect->numInputs        = 0;
    MAEffect->numOutputs       = 0;
    MAEffect->initialDelay     = 0;
    MAEffect->object           = 0; //this;
    MAEffect->user             = 0; //instance;
    MAEffect->uniqueID         = 0;
    MAEffect->version          = 0;
    MAEffect->setParameter     = vst2_set_parameter_callback;
    MAEffect->getParameter     = vst2_get_parameter_callback;
    MAEffect->dispatcher       = vst2_dispatcher_callback;
    MAEffect->process          = vst2_process_callback;
    MAEffect->processReplacing = vst2_process_replacing_callback;
    return MAEffect;
  }

};



//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#define VST2_ENTRYPOINT_SYMBOL asm ("VSTPluginMain");
AEffect* VST2_PLUGIN_API vst2_entrypoint(audioMasterCallback audioMaster) VST2_ENTRYPOINT_SYMBOL;

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


//----------------------------------------------------------------------
#endif


