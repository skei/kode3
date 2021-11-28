#ifndef kode_instance_included
#define kode_instance_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_descriptor.h"
#include "plugin/kode_editor.h"
#include "plugin/kode_process_context.h"


class KODE_Instance
: public KODE_EditorListener {

//------------------------------
private:
//------------------------------

  KODE_Descriptor* MDescriptor = nullptr;

//------------------------------
public:
//------------------------------

  KODE_Instance(KODE_Descriptor* ADescriptor) {
    //KODE_PRINT;
    MDescriptor = ADescriptor;
  }

  //----------

  virtual ~KODE_Instance() {
    //KODE_PRINT;
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

  virtual bool          on_plugin_init() { return false; }
  virtual void          on_plugin_destroy() {}
  virtual bool          on_plugin_activate() { return false; }
  virtual void          on_plugin_deactivate() {}
  virtual bool          on_plugin_startProcessing() { return false; }
  virtual void          on_plugin_stopProcessing() {}
  virtual uint32_t      on_plugin_process(KODE_ProcessContext* AContext) { return 0; }
  virtual void          on_plugin_parameter(uint32_t AIndex, float AValue) {}
  virtual void          on_plugin_midi(uint32_t AOffset, uint8_t AMsg1, uint8_t AMsg2, uint8_t AMsg3) {}
  virtual uint32_t      on_plugin_saveState(void** ABuffer, uint32_t AMode) { *ABuffer = nullptr; return 0; }
  virtual uint32_t      on_plugin_loadState(uint32_t ASize, void* ABuffer, uint32_t AMode) { return 0; }
  virtual KODE_Editor*  on_plugin_openEditor() { return nullptr; }
  virtual void          on_plugin_closeEditor() {}
  virtual uint32_t      on_plugin_updateEditor() { return 0; }

};

//----------------------------------------------------------------------
#endif
