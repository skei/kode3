#ifndef kode_ladspa_plugin_included
#define kode_ladspa_plugin_included
//----------------------------------------------------------------------

// in progress

#include "kode.h"
#include "plugin/kode_descriptor.h"
//#include "plugin/kode_instance_listener.h"
#include "plugin/ladspa/kode_ladspa.h"
#include "plugin/ladspa/kode_ladspa_instance.h"
#include "plugin/ladspa/kode_ladspa_utils.h"

/*
#include "base/kode.h"
#include "plugin/ladspa/kode_ladspa.h"
#include "plugin/ladspa/kode_ladspa_host.h"
#include "plugin/ladspa/kode_ladspa_instance.h"
*/

//----------------------------------------------------------------------


template<class DESCRIPTOR, class INSTANCE, class EDITOR>
class KODE_LadspaPlugin
/*: public KODE_InstanceListener*/ {

//------------------------------
private:
//------------------------------

  KODE_Descriptor*      MDescriptor       = nullptr;
  LADSPA_Descriptor*    MLadspaDescriptor = {0};
//LADSPA_Descriptor*    MLadspaDescriptor = KODE_NULL;

  //int*                  MPortDescriptors  = KODE_NULL;
  //char**                MPortNames        = KODE_NULL;
  //char*                 MPortNamesBuffer  = KODE_NULL;
  //LADSPA_PortRangeHint* MPortRangeHints   = KODE_NULL;

  KODE_LadspaPorts   MPorts;

  char*                 MNameBuffer       = nullptr;
  char*                 MLabelBuffer      = nullptr;
  char*                 MMakerBuffer      = nullptr;
  char*                 MCopyrightBuffer  = nullptr;

//------------------------------
public:
//------------------------------

  KODE_LadspaPlugin() {
    //KODE_TRACE;
  }

  //----------

  ~KODE_LadspaPlugin() {
    //KODE_TRACE;
    if (MDescriptor)        delete MDescriptor;
    if (MNameBuffer)        free(MNameBuffer);
    if (MLabelBuffer)       free(MLabelBuffer);
    if (MMakerBuffer)       free(MMakerBuffer);
    if (MCopyrightBuffer)   free(MCopyrightBuffer);
    KODE_LadspaCleanupPorts(&MPorts);
    if (MLadspaDescriptor)  free(MLadspaDescriptor);
  }

//------------------------------
public:
//------------------------------

  /*
    - at the moment, we only support index == 0
    - carla calles ladspa_descriptor a second time before deleting the first..
  */

  const LADSPA_Descriptor* entrypoint(unsigned long Index) {
    if (Index > 0) return nullptr;
    if (MLadspaDescriptor) return MLadspaDescriptor;
    MDescriptor = new DESCRIPTOR();
    MLadspaDescriptor = (LADSPA_Descriptor*)malloc(sizeof(LADSPA_Descriptor));
    memset(MLadspaDescriptor,0,sizeof(LADSPA_Descriptor));
    //setDefaultParamValues();

    MNameBuffer       = (char*)malloc(KODE_PLUGIN_LADSPA_MAX_NAME_LENGTH-1);
    MLabelBuffer      = (char*)malloc(KODE_PLUGIN_LADSPA_MAX_NAME_LENGTH-1);
    MMakerBuffer      = (char*)malloc(KODE_PLUGIN_LADSPA_MAX_NAME_LENGTH-1);
    MCopyrightBuffer  = (char*)malloc(KODE_PLUGIN_LADSPA_MAX_NAME_LENGTH-1);

    strncpy(MNameBuffer,      MDescriptor->name,        KODE_PLUGIN_LADSPA_MAX_NAME_LENGTH-1);
    strncpy(MLabelBuffer,     MDescriptor->name,        KODE_PLUGIN_LADSPA_MAX_NAME_LENGTH-1); // todo: make valid c symbol (see lv2)
    strncpy(MMakerBuffer,     MDescriptor->author,      KODE_PLUGIN_LADSPA_MAX_NAME_LENGTH-1);
    strncpy(MCopyrightBuffer, MDescriptor->license_text, KODE_PLUGIN_LADSPA_MAX_NAME_LENGTH-1);

    uint32_t numports = KODE_LadspaSetupPorts(MDescriptor,&MPorts);
    //KODE_Assert(port == numports);

    MLadspaDescriptor->UniqueID            = MDescriptor->short_id;
    MLadspaDescriptor->Label               = MLabelBuffer;
    MLadspaDescriptor->Properties          = LADSPA_PROPERTY_HARD_RT_CAPABLE; // LADSPA_PROPERTY_REALTIME, LADSPA_PROPERTY_INPLACE_BROKEN
    MLadspaDescriptor->Name                = MNameBuffer;
    MLadspaDescriptor->Maker               = MMakerBuffer;
    MLadspaDescriptor->Copyright           = MCopyrightBuffer;
    MLadspaDescriptor->PortCount           = numports;
    MLadspaDescriptor->PortDescriptors     = MPorts.descriptors;
    MLadspaDescriptor->PortNames           = (const char* const*)MPorts.names;
    MLadspaDescriptor->PortRangeHints      = MPorts.rangeHints;
    MLadspaDescriptor->ImplementationData  = this;//KODE_NULL;
    MLadspaDescriptor->instantiate         = ladspa_instantiate_callback;
    MLadspaDescriptor->connect_port        = ladspa_connect_port_callback;
    MLadspaDescriptor->activate            = ladspa_activate_callback;
    MLadspaDescriptor->run                 = ladspa_run_callback;
    MLadspaDescriptor->run_adding          = ladspa_run_adding_callback;
    MLadspaDescriptor->set_run_adding_gain = ladspa_set_run_adding_gain_callback;
    MLadspaDescriptor->deactivate          = ladspa_deactivate_callback;
    MLadspaDescriptor->cleanup             = ladspa_cleanup_callback;

    return MLadspaDescriptor;

  }

  //----------

  LADSPA_Handle instantiate(unsigned long SampleRate) {
    // instance deleted in ~KODE_LadspaInstance()
    KODE_Instance* instance = new INSTANCE(MDescriptor);
//    instance->on_open();
    // ladspa_instance deleted in ladspa_cleanup_callback()
    KODE_LadspaInstance* ladspa_instance = new KODE_LadspaInstance(instance,SampleRate);
    return (LADSPA_Handle)ladspa_instance;
  }

//------------------------------
private: // ladspa callbacks
//------------------------------

  static
  LADSPA_Handle ladspa_instantiate_callback(const struct _LADSPA_Descriptor* Descriptor, unsigned long SampleRate) {
    KODE_LadspaPlugin* plugin = (KODE_LadspaPlugin*)Descriptor->ImplementationData;
    LADSPA_Handle instance = nullptr;
    if (plugin) instance = plugin->instantiate(SampleRate);
    return (LADSPA_Handle)instance;
  }

  //----------

  static
  void ladspa_connect_port_callback(LADSPA_Handle Instance, unsigned long Port, LADSPA_Data * DataLocation) {
    //LADSPA_Trace("ladspa: ladspa_connect_port_callback\n");
    KODE_LadspaInstance* ladspa_instance = (KODE_LadspaInstance*)Instance;
    if (ladspa_instance) ladspa_instance->ladspa_connect_port(Port,DataLocation);
  }

  //----------

  static
  void ladspa_activate_callback(LADSPA_Handle Instance) {
    //LADSPA_Trace("ladspa: ladspa_activate_callback\n");
    KODE_LadspaInstance* ladspa_instance = (KODE_LadspaInstance*)Instance;
    if (ladspa_instance) ladspa_instance->ladspa_activate();
  }

  //----------

  static
  void ladspa_run_callback(LADSPA_Handle Instance, unsigned long SampleCount) {
    //LADSPA_Trace("ladspa: ladspa_run_callback\n");
    KODE_LadspaInstance* ladspa_instance = (KODE_LadspaInstance*)Instance;
    if (ladspa_instance) ladspa_instance->ladspa_run(SampleCount);
  }

  //----------

  static
  void ladspa_run_adding_callback(LADSPA_Handle Instance, unsigned long SampleCount) {
    //LADSPA_Trace("ladspa: ladspa_run_adding_callback\n");
    KODE_LadspaInstance* ladspa_instance = (KODE_LadspaInstance*)Instance;
    if (ladspa_instance) ladspa_instance->ladspa_run_adding(SampleCount);
  }

  //----------

  static
  void ladspa_set_run_adding_gain_callback(LADSPA_Handle Instance, LADSPA_Data Gain) {
    //LADSPA_Trace("ladspa: ladspa_set_run_adding_gain_callback\n");
    KODE_LadspaInstance* ladspa_instance = (KODE_LadspaInstance*)Instance;
    if (ladspa_instance) ladspa_instance->ladspa_set_run_adding_gain(Gain);
  }

  //----------

  static
  void ladspa_deactivate_callback(LADSPA_Handle Instance) {
    //LADSPA_Trace("ladspa: ladspa_deactivate_callback\n");
    KODE_LadspaInstance* ladspa_instance = (KODE_LadspaInstance*)Instance;
    if (ladspa_instance) ladspa_instance->ladspa_deactivate();
  }

  //----------

  static
  void ladspa_cleanup_callback(LADSPA_Handle Instance) {
    //LADSPA_Trace("ladspa: ladspa_cleanup_callback\n");
    KODE_LadspaInstance* ladspa_instance = (KODE_LadspaInstance*)Instance;
    if (ladspa_instance) ladspa_instance->ladspa_cleanup();
    //LADSPA_Trace("ladspa: cleanup -> deleting instance\n");
    delete ladspa_instance;
  }

//------------------------------

};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#define KODE_LADSPA_MAIN_SYMBOL asm ("ladspa_descriptor");
const LADSPA_Descriptor* kode_ladspa_entrypoint(unsigned long Index) KODE_LADSPA_MAIN_SYMBOL

//----------

#define KODE_LADSPA_MAIN(D,I,E)                                           \
                                                                          \
  KODE_LadspaPlugin<D,I,E> _LADSPA_PLUGIN;                                \
                                                                          \
  __attribute__((visibility("default")))                                  \
  const LADSPA_Descriptor* kode_ladspa_entrypoint(unsigned long Index) {  \
    return _LADSPA_PLUGIN.entrypoint(Index);                              \
  }

//----------------------------------------------------------------------
#endif
