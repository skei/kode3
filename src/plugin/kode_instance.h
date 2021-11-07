#ifndef kode_instance_included
#define kode_instance_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_descriptor.h"
#include "plugin/kode_process_context.h"


class KODE_Instance {

//------------------------------
private:
//------------------------------

  KODE_Descriptor* MDescriptor = nullptr;

//------------------------------
public:
//------------------------------

  KODE_Instance(KODE_Descriptor* ADescriptor) {
    KODE_PRINT;
    MDescriptor = ADescriptor;
  }

  //----------

  virtual ~KODE_Instance() {
    KODE_PRINT;
    if (MDescriptor) delete MDescriptor;
  }

//------------------------------
public:
//------------------------------

  KODE_Descriptor* getDescriptor() {
    return MDescriptor;
  }

  float* getParameterValueBuffer() {
    return nullptr;
  }

  void setParameterValue(uint32_t AIndex, float AValue) {
  }

  float getParameterValue(uint32_t AIndex) {
    return 0.0;
  }

//------------------------------
public:
//------------------------------

  virtual bool      on_plugin_init() { return false; }
  virtual void      on_plugin_destroy() {}
  virtual bool      on_plugin_activate() { return false; }
  virtual void      on_plugin_deactivate() {}
  virtual bool      on_plugin_start_processing() { return false; }
  virtual void      on_plugin_stop_processing() {}
  virtual uint32_t  on_plugin_process(KODE_ProcessContext* AContext) { return 0; }
  virtual void      on_plugin_parameter(uint32_t AIndex, float AValue) {}
  virtual void      on_plugin_midi(uint32_t AOffset, uint8_t AMsg1, uint8_t AMsg2, uint8_t AMsg3) {}
  virtual uint32_t  on_plugin_save_state(void** ABuffer, uint32_t AMode) { *ABuffer = nullptr; return 0; }
  virtual uint32_t  on_plugin_load_state(uint32_t ASize, void* ABuffer, uint32_t AMode) { return 0; }
  virtual void*     on_plugin_create_editor(void* AParent) { return nullptr; }
  virtual bool      on_plugin_open_editor() { return false; }
  virtual void      on_plugin_close_editor() {}
  virtual uint32_t  on_plugin_update_editor() { return 0; }

};

//----------------------------------------------------------------------
#endif
