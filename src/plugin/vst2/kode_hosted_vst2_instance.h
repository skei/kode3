#ifndef kode_hosted_vst2_instance_included
#define kode_hosted_vst2_instance_included
//----------------------------------------------------------------------

//#include <dlfcn.h>

#include "kode.h"
#include "plugin/kode_hosted_instance.h"
#include "plugin/vst2/kode_vst2.h"

//----------------------------------------------------------------------

class KODE_HostedVst2Instance
: public KODE_HostedInstance {

//------------------------------
private:
//------------------------------


//------------------------------
public:
//------------------------------

  KODE_HostedVst2Instance(KODE_Descriptor* ADescriptor)
  : KODE_HostedInstance(ADescriptor) {
    //KODE_PRINT;
  }

  //----------

  virtual ~KODE_HostedVst2Instance() {
    //KODE_PRINT;
  }


//------------------------------
public:
//------------------------------

  /*
  bool      on_plugin_init() final { return false; }
  void      on_plugin_destroy() final {}
  bool      on_plugin_activate() final { return false; }
  void      on_plugin_deactivate() final {}
  bool      on_plugin_start_processing() final { return false; }
  void      on_plugin_stop_processing() final {}
  uint32_t  on_plugin_process(KODE_ProcessContext* AContext) final { return 0; }
  void      on_plugin_parameter(uint32_t AIndex, float AValue) final {}
  void      on_plugin_midi(uint32_t AOffset, uint8_t AMsg1, uint8_t AMsg2, uint8_t AMsg3) final {}
  uint32_t  on_plugin_save_state(void** ABuffer, uint32_t AMode) final { *ABuffer = nullptr; return 0; }
  uint32_t  on_plugin_load_state(uint32_t ASize, void* ABuffer, uint32_t AMode) final { return 0; }
  void*     on_plugin_create_editor(void* AParent) final { return nullptr; }
  bool      on_plugin_open_editor() final { return false; }
  void      on_plugin_close_editor() final {}
  uint32_t  on_plugin_update_editor() final { return 0; }
  */

};

//----------------------------------------------------------------------
#endif
