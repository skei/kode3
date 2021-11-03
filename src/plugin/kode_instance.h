#ifndef kode_instance_included
#define kode_instance_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_editor.h"
#include "plugin/kode_process.h"

class KODE_Instance {

private:

  KODE_Descriptor*  MDescriptor = nullptr;

public:

  KODE_Instance(KODE_Descriptor* ADescriptor) {
    KODE_PRINT;
    MDescriptor = ADescriptor;
  }

  virtual ~KODE_Instance() {
    KODE_PRINT;
  }

//------------------------------
public:
//------------------------------

  virtual void  on_plugin_init() {}
  virtual void  on_plugin_exit() {}
  virtual void  on_plugin_activate() {}
  virtual void  on_plugin_deactivate() {}
  virtual void  on_plugin_prepare() {}
  virtual void  on_plugin_process(KODE_ProcessContext* AContext) {}
  virtual void  on_plugin_parameter(uint32_t AOffset, uint32_t AIndex, float AValue) {}
  virtual void  on_plugin_midi(uint32_t AOffset, uint8_t AMsg1, uint8_t AMsg2, uint8_t AMsg3) {}
  virtual void* on_plugin_open_editor(void* AParent) { return nullptr; }
  virtual void  on_plugin_close_editor() {}
  virtual void  on_plugin_refresh_editor() {}

//------------------------------
public:
//------------------------------

  //virtual KODE_Editor* createEditor(void* ptr) {
  //  KODE_PRINT;
  //  return nullptr;
  //}

  //virtual void deleteEditor() {
  //  KODE_PRINT;
  //}

  //void setDescriptor(KODE_Descriptor* ADescriptor) {
  //  MDescriptor = ADescriptor;
  //}

  //KODE_Descriptor* getDescriptor() {
  //  return MDescriptor;
  //}

  //virtual bool openEditor() { return false; }
  //virtual void closeEditor() { }
  //virtual void updateEditor() { }

};

//----------------------------------------------------------------------
#endif
