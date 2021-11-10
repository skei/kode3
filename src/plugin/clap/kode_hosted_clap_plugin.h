#ifndef kode_hosted_clap_plugin_included
#define kode_hosted_clap_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_hosted_plugin.h"
#include "plugin/clap/kode_clap.h"
#include "plugin/clap/kode_clap_host.h"
#include "plugin/clap/kode_hosted_clap_instance.h"

//typedef AEffect* (*vst2_plugin_main)(audioMasterCallback audioMaster);

//----------------------------------------------------------------------

class KODE_HostedClapPlugin
: public KODE_HostedPlugin {

//------------------------------
private:
//------------------------------

  KODE_Descriptor*  MDescriptor                             = nullptr;
  KODE_ClapHost*    MHost                                   = nullptr;

//  void*                     MLibHandle        = nullptr;
//  clap_plugin*              MClapPlugin       = nullptr;
//  clap_plugin_descriptor*   MClapDescriptor   = nullptr;
//  struct clap_plugin_entry* MClapPluginEntry  = nullptr;

//------------------------------
public:
//------------------------------

// DEBUG.. just return 1 so that plugin loads :-)
// TODO: -> KODE_Vst2Host

//static
//VstIntPtr kode_audioMasterCallback(AEffect* effect, VstInt32 opcode, VstInt32 index, VstIntPtr value, void* ptr, float opt) {
//  KODE_PRINT;
//  return 1;
//}

//------------------------------
public:
//------------------------------

  KODE_HostedClapPlugin()
  : KODE_HostedPlugin() {
    KODE_PRINT;
//    MHost = new KODE_ClapHost(/*kode_audioMasterCallback*/);
  }

  //----------

  KODE_HostedClapPlugin(const char* AFile)
  : KODE_HostedPlugin(AFile) {
    loadPlugin(AFile);
    KODE_Print("MDescriptor %p\n",MDescriptor);
    MDescriptor->print();
    KODE_PRINT;

  }

  //----------

  virtual ~KODE_HostedClapPlugin() {
    //if (MDescriptor) delete MDescriptor;
    //if (MHost) delete MHost;
  }

//------------------------------
public:
//------------------------------

  void loadPlugin(const char* AFile) {
    MDescriptor = new KODE_Descriptor();
    KODE_DPrint("loading %s\n",CLAP_FILENAME);
    if (MLibHandle) {

      const struct clap_plugin_entry* clap_entry = (const struct clap_plugin_entry*)getSymbol("clap_plugin_entry");
      KODE_Print("clap_entry %p\n",clap_entry);

      if (clap_entry) {
        const clap_plugin_descriptor* clap_descriptor = clap_entry->get_plugin_descriptor(0);
        KODE_Print("clap_descriptor %p\n",clap_descriptor);
        //MDescriptor = initDescriptor();
        MDescriptor->name         = "name";//clap_descriptor->name;
        MDescriptor->author       = "vendor";//clap_descriptor->vendor;
        MDescriptor->version      = 0; // clap_descriptor->version
        MDescriptor->short_id     = 0;  // clap_descriptor->id;
        MDescriptor->email        = "";
        MDescriptor->url          = "url";//clap_descriptor->url;
        MDescriptor->description  = "description";//clap_descriptor->description;
        MDescriptor->keywords     = "keywords";//clap_descriptor->keywords;
        MDescriptor->license_text = "";
        MDescriptor->editorWidth  = 0;
        MDescriptor->editorHeight = 0;
//        for (int32_t i=0; i<MAEffect->numInputs; i++) MDescriptor->appendInput("input");
//        for (int32_t i=0; i<MAEffect->numOutputs; i++) MDescriptor->appendOutput("output");
//        for (int32_t i=0; i<MAEffect->numParams; i++) MDescriptor->appendParameter(new KODE_Parameter());
        if (clap_descriptor->plugin_type & CLAP_PLUGIN_INSTRUMENT) {
          MDescriptor->options.is_synth = true;
        }
        if (clap_descriptor->plugin_type & CLAP_PLUGIN_AUDIO_EFFECT) {
          MDescriptor->options.is_synth = false;
        }
        if (clap_descriptor->plugin_type & CLAP_PLUGIN_EVENT_EFFECT) {
          MDescriptor->options.can_send_midi = true;
          MDescriptor->options.can_receive_midi = true;
        }
        if (clap_descriptor->plugin_type & CLAP_PLUGIN_ANALYZER) {
        }
        //KODE_PRINT;
        //if (MAEffect->flags & effFlagsCanReplacing) {}
        //if (MAEffect->flags & effFlagsCanDoubleReplacing) {}
        //if (MAEffect->flags & effFlagsNoSoundInStop) {}
      }
    }
  }

//          MAEffect->dispatcher(MAEffect,effGetEffectName,0,0,MEffectName,0);
//          MAEffect->dispatcher(MAEffect,effGetVendorString,0,0,MVendorString,0);
//          MAEffect->dispatcher(MAEffect,effGetProductString,0,0,MProductString,0);
//          MVersion = MAEffect->dispatcher(MAEffect,effGetVendorVersion,0,0,0,0);
//          MUniqueId = MAEffect->uniqueID;
//        }
//      }
//    }

//------------------------------
public:
//------------------------------

  KODE_Descriptor* getDescriptor() final {
    return MDescriptor;
  }

  //----------

  KODE_HostedInstance* createInstance() final {
    KODE_HostedClapInstance* instance = new KODE_HostedClapInstance(MDescriptor);
    return instance;
  }



//------------------------------
public:
//------------------------------

//------------------------------
public:
//------------------------------

    /*
    struct clap_plugin_entry CLAP_ENTRY_STRUCT asm("clap_plugin_entry") = {
      CLAP_VERSION,
      clap_entry_init_callback,
      clap_entry_deinit_callback,
      clap_entry_get_plugin_count_callback,
      clap_entry_get_plugin_descriptor_callback,
      clap_entry_create_plugin_callback,
      clap_entry_get_invalidation_sources_count_callback,
      clap_entry_get_invalidation_sources_callback,
      clap_entry_refresh_callback
    };
    */

  bool clap_init(const char *plugin_path) { return false; }
  void clap_deinit() {}
  uint32_t clap_get_plugin_count() { return 0; }
  const clap_plugin_descriptor* clap_get_plugin_descriptor(uint32_t index) { return nullptr; }
  const clap_plugin* clap_create_plugin(const clap_host* host, const char* plugin_id) { return nullptr; }
  uint32_t clap_get_invalidation_sources_count() { return 0; }
  const clap_plugin_invalidation_source* clap_get_invalidation_sources(uint32_t index) { return nullptr; }
  void clap_refresh() {}

};

//----------------------------------------------------------------------
#endif
