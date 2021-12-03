#ifndef kode_vst2_plugin_included
#define kode_vst2_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_descriptor.h"
//#include "plugin/kode_instance_listener.h"
#include "plugin/vst2/kode_vst2.h"
#include "plugin/vst2/kode_vst2_instance.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

template <class DESCRIPTOR, class INSTANCE, class EDITOR>
class KODE_Vst2Plugin {

//------------------------------
private:
//------------------------------

  KODE_Descriptor*  MDescriptor = nullptr;  // create in entrypoint, deleted in destructor

//------------------------------
public:
//------------------------------

  KODE_Vst2Plugin() {
    //KODE_Print("\n");
    //MDescriptor = KODE_New DESC();
  }

  //----------

  ~KODE_Vst2Plugin() {
    //KODE_Print("\n");
//    KODE_DPrint("deleting MDescriptor\n");
//    if (MDescriptor) delete MDescriptor;    // deleted in ~KODE_Descriptor()
//    KODE_DPrint("deleting MDescriptor OK\n");
  }

//------------------------------
private: // vst2 callbacks
//------------------------------

  static
  VstIntPtr vst2_dispatcher_callback(AEffect* effect, VstInt32 opcode, VstInt32 index, VstIntPtr value, void* ptr, float opt) {
    //KODE_Print("\n");
    VstIntPtr result = 0;
    KODE_Vst2Instance* vst2_instance = (KODE_Vst2Instance*)effect->object;
    result = vst2_instance->vst2_dispatcher(opcode,index,value,ptr,opt);
    if (opcode==effClose) {
      KODE_DPrint("deleting vst2_instance\n");
      delete (KODE_Vst2Instance*)vst2_instance;
      KODE_DPrint("deleting vst2_instance OK\n");
    }
    return result;
  }

  //----------

  static
  void vst2_setParameter_callback(AEffect* effect, VstInt32 index, float parameter) {
    //KODE_Print("\n");
    KODE_Vst2Instance* vst2_instance = (KODE_Vst2Instance*)effect->object;
    vst2_instance->vst2_setParameter(index,parameter);
  }

  //----------

  static
  float vst2_getParameter_callback(AEffect* effect, VstInt32 index) {
    //KODE_Print("\n");
    KODE_Vst2Instance* vst2_instance = (KODE_Vst2Instance*)effect->object;
    return vst2_instance->vst2_getParameter(index);
  }

  //----------

  static
  void vst2_process_callback(AEffect* effect, float** inputs, float** outputs, VstInt32 sampleFrames) {
    KODE_Vst2Instance* vst2_instance = (KODE_Vst2Instance*)effect->object;
    vst2_instance->vst2_process(inputs,outputs,sampleFrames);
  }

  //----------

  static
  void vst2_processDouble_callback(AEffect* effect, double** inputs, double** outputs, VstInt32 sampleFrames) {
    KODE_Vst2Instance* vst2_instance = (KODE_Vst2Instance*)effect->object;
    vst2_instance->vst2_processDouble(inputs,outputs,sampleFrames);
  }

//------------------------------
public:
//------------------------------

  AEffect* entrypoint(audioMasterCallback audioMaster) {
    //KODE_Print("\n");

    //if (!MDescriptor) MDescriptor = new DESCRIPTOR(); // deleted in: ~KODE_Instance()
    //KODE_Instance* instance = new INSTANCE(MDescriptor); // deleted in ~KODE_Vst2Instance()

    if (!MDescriptor) MDescriptor = _kode_create_descriptor(); // deleted in: ~KODE_Instance()

    KODE_Instance* instance = _kode_create_instance(MDescriptor); // deleted in ~KODE_Vst2Instance()
    instance->setPluginFormat(KODE_PLUGIN_FORMAT_VST2);

    KODE_Vst2Instance* vst2_instance  = new KODE_Vst2Instance(instance,audioMaster); // deleted in:
    AEffect* effect = vst2_instance->getAEffect();

//    instance->setListener(vst2_instance);

    instance->on_plugin_init();

//    instance->setDefaultParameterValues();
//    instance->updateAllParameters();

    int32_t flags = effFlagsCanReplacing;
    if (MDescriptor->options.is_synth)    flags |= effFlagsIsSynth;
    if (MDescriptor->options.has_editor)  flags |= effFlagsHasEditor;
    //if (MDescriptor->options.use_chunks)) flags |= effFlagsProgramChunks;
    //if (MPlugin->hasFlag(kpf_silentStop)) flags |= effFlagsNoSoundInStop;
    //#ifndef KODE_PLUGIN_VST2_VESTIGE
    //if (MDescriptor->options.can_process_double) flags |= effFlagsCanDoubleReplacing;
    //#endif
    memset(effect,0,sizeof(AEffect));
    effect->magic                     = kEffectMagic;
    effect->uniqueID                  = MDescriptor->short_id;
    effect->flags                     = flags;
    effect->numInputs                 = MDescriptor->inputs.size();
    effect->numOutputs                = MDescriptor->outputs.size();
    effect->numParams                 = MDescriptor->parameters.size();
    effect->numPrograms               = MDescriptor->presets.size();
    effect->version                   = MDescriptor->version;
    effect->initialDelay              = 0;
    effect->object                    = vst2_instance;
    effect->user                      = nullptr;//instance;
    effect->dispatcher                = vst2_dispatcher_callback;
    effect->setParameter              = vst2_setParameter_callback;
    effect->getParameter              = vst2_getParameter_callback;
    effect->processReplacing          = vst2_process_callback;
    effect->processDoubleReplacing    = vst2_processDouble_callback;
    return effect;
  }
};

//----------------------------------------------------------------------
//
// entrypoint
//
//----------------------------------------------------------------------

//#define KODE_VST2_MAIN_SYMBOL asm ("VSTPluginMain");
AEffect* kode_vst2_entrypoint(audioMasterCallback audioMaster) asm ("VSTPluginMain"); // KODE_VST2_MAIN_SYMBOL

#define KODE_VST2_MAIN(D,I,E)                                       \
                                                                    \
  KODE_Vst2Plugin<D,I,E> VST2_PLUGIN;                               \
                                                                    \
  /*__attribute__((visibility("default")))*/                        \
  __KODE_DLLEXPORT                                                     \
  AEffect* kode_vst2_entrypoint(audioMasterCallback audioMaster) {  \
    printf("VST2\n");                                               \
    if (!audioMaster(0,audioMasterVersion,0,0,0,0)) return 0;       \
    AEffect* effect = VST2_PLUGIN.entrypoint(audioMaster);          \
    return effect;                                                  \
  }

//----------------------------------------------------------------------
#endif
