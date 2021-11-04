#ifndef kode_instance_included
#define kode_instance_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_descriptor.h"


class KODE_Instance {

//------------------------------
protected:
//------------------------------

  KODE_Descriptor* MDescriptor = nullptr;

//------------------------------
public:
//------------------------------

  KODE_Instance(KODE_Descriptor* ADescriptor) {
    MDescriptor = ADescriptor;
  }

  //----------

  virtual ~KODE_Instance() {
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

  virtual void      on_plugin_init() {}
  virtual void      on_plugin_destroy() {}
  virtual void      on_plugin_activate() {}
  virtual void      on_plugin_deactivate() {}
  virtual void      on_plugin_start_processing() {}
  virtual void      on_plugin_stop_processing() {}
  virtual void      on_plugin_process() {}
  virtual void      on_plugin_parameter() {}
  virtual void      on_plugin_midi() {}
  virtual uint32_t  on_plugin_save_state(void** buffer, uint32_t mode) { *buffer = nullptr; return 0; }
  virtual void      on_plugin_load_state() {}
  virtual void      on_plugin_open_editor() {}
  virtual void      on_plugin_close_editor() {}
  virtual void      on_plugin_update_editor() {}

};

//----------------------------------------------------------------------
#endif
