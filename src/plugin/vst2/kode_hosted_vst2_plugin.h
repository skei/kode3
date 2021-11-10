#ifndef kode_hosted_vst2_plugin_included
#define kode_hosted_vst2_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_hosted_plugin.h"
#include "plugin/vst2/kode_vst2.h"
#include "plugin/vst2/kode_vst2_host.h"
#include "plugin/vst2/kode_hosted_vst2_instance.h"

typedef AEffect* (*vst2_plugin_main)(audioMasterCallback audioMaster);

//----------------------------------------------------------------------

class KODE_HostedVst2Plugin
: public KODE_HostedPlugin {

//------------------------------
private:
//------------------------------

  AEffect*          MAEffect                                = nullptr;
  KODE_Descriptor*  MDescriptor                             = nullptr;
  KODE_Vst2Host*    MHost                                   = nullptr;
  char              MEffectName[kVstMaxEffectNameLen+1]     = {0};
  char              MVendorString[kVstMaxVendorStrLen+1]    = {0};
  char              MProductString[kVstMaxProductStrLen+1]  = {0};
  uint32_t          MVersion                                = 0;
  uint32_t          MUniqueId                               = 0;

//------------------------------
public:
//------------------------------

// DEBUG.. just return 1 so that plugin loads :-)
// TODO: -> KODE_Vst2Host

static
VstIntPtr kode_audioMasterCallback(AEffect* effect, VstInt32 opcode, VstInt32 index, VstIntPtr value, void* ptr, float opt) {
  KODE_PRINT;//    KODE_DPrint("loading %s\n",CLAP_FILENAME);

  return 1;
}

//------------------------------
public:
//------------------------------

  KODE_HostedVst2Plugin()
  : KODE_HostedPlugin() {
    KODE_PRINT;
    MHost = new KODE_Vst2Host(kode_audioMasterCallback);
  }

  //----------

  KODE_HostedVst2Plugin(const char* AFile)
  : KODE_HostedPlugin(AFile) {
    KODE_PRINT;
    loadPlugin(AFile);
    KODE_PRINT;
    MDescriptor->print();
  }

  //----------

  virtual ~KODE_HostedVst2Plugin() {
    //if (MDescriptor) delete MDescriptor;
    //if (MHost) delete MHost;
  }

//------------------------------
public:
//------------------------------

  void loadPlugin(const char* AFile) {
    MDescriptor = new KODE_Descriptor();
    if (MLibHandle) {
      vst2_plugin_main plugin_main = (vst2_plugin_main)dlsym(MLibHandle,"VSTPluginMain");
      if (plugin_main) {
        MAEffect = plugin_main(kode_audioMasterCallback);
        if (MAEffect) {
          //MDescriptor = initDescriptor();
          MAEffect->dispatcher(MAEffect,effGetEffectName,0,0,MEffectName,0);
          MAEffect->dispatcher(MAEffect,effGetVendorString,0,0,MVendorString,0);
          MAEffect->dispatcher(MAEffect,effGetProductString,0,0,MProductString,0);
          MVersion = MAEffect->dispatcher(MAEffect,effGetVendorVersion,0,0,0,0);
          MUniqueId = MAEffect->uniqueID;
          MDescriptor->name          = MEffectName;           //"hosted_vst2_plugin";
          MDescriptor->author        = MVendorString;         //"skei.audio";
          MDescriptor->version       = MVersion;              //MAEffect->version;
          MDescriptor->short_id      = MUniqueId;             //MAEffect->uniqueID;
          MDescriptor->email         = "";
          MDescriptor->url           = "";
          MDescriptor->description   = MProductString;
          MDescriptor->keywords      = "";
          MDescriptor->license_text  = "";
          MDescriptor->editorWidth   = 0;
          MDescriptor->editorHeight  = 0;
          for (int32_t i=0; i<MAEffect->numInputs; i++) MDescriptor->appendInput("input");
          for (int32_t i=0; i<MAEffect->numOutputs; i++) MDescriptor->appendOutput("output");
          for (int32_t i=0; i<MAEffect->numParams; i++) MDescriptor->appendParameter(new KODE_Parameter());
          if (MAEffect->flags & effFlagsHasEditor) {
            MDescriptor->options.has_editor = true;
            MDescriptor->editorWidth = 640;
            MDescriptor->editorHeight = 480;
          }
          if (MAEffect->flags & effFlagsIsSynth) {
            MDescriptor->options.is_synth = true;
          }
          //if (MAEffect->flags & effFlagsCanReplacing) {}
          //if (MAEffect->flags & effFlagsCanDoubleReplacing) {}
          //if (MAEffect->flags & effFlagsNoSoundInStop) {}
        }
      }
    }
  }

//------------------------------
public:
//------------------------------

  KODE_Descriptor* getDescriptor() final {
    return MDescriptor;
  }

  //----------

  KODE_HostedInstance* createInstance() final {
    KODE_HostedVst2Instance* instance = new KODE_HostedVst2Instance(MDescriptor);
    return instance;
  }

};

//----------------------------------------------------------------------
#endif
