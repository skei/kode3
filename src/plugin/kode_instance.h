#ifndef kode_instance_included
#define kode_instance_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_descriptor.h"
#include "plugin/kode_editor.h"
#include "plugin/kode_process_context.h"


class KODE_Instance
/*: public KODE_EditorListener*/ {

//------------------------------
private:
//------------------------------

  KODE_Descriptor*  MDescriptor       = nullptr;
  float*            MParameterValues  = nullptr;

//------------------------------
public:
//------------------------------

  KODE_Instance(KODE_Descriptor* ADescriptor) {
    //KODE_PRINT;
    MDescriptor = ADescriptor;
    MParameterValues = (float*)malloc(MDescriptor->parameters.size() * sizeof(float));
  }

  //----------

  virtual ~KODE_Instance() {
    //KODE_PRINT;
    if (MParameterValues) free(MParameterValues);
    if (MDescriptor) delete MDescriptor;
  }

//------------------------------
public:
//------------------------------

  KODE_Descriptor* getDescriptor() {
    return MDescriptor;
  }

  float* getParameterValueBuffer() {
    return MParameterValues;
  }

  void setParameterValue(uint32_t AIndex, float AValue) {
    MParameterValues[AIndex] = AValue;
  }

  float getParameterValue(uint32_t AIndex) {
    return MParameterValues[AIndex];
  }

////------------------------------
//public: // editor listener
////------------------------------
//
//  void on_editor_updateParameter(uint32_t AIndex, float AValue) override {
//    KODE_Print("index %i value %.3f\n",AIndex,AValue);
//  }
//
//  void on_editor_resize(uint32_t AWidth, uint32_t AHeight) override {
//    KODE_Print("width %i height %i\n",AWidth,AHeight);
//  }

//------------------------------
public:
//------------------------------

  virtual bool          on_plugin_init() { return false; }
  virtual void          on_plugin_destroy() {}
  virtual bool          on_plugin_activate(float ASampleRate, uint32_t AMinFrames, uint32_t AMaxFrames) { return false; }
  virtual void          on_plugin_deactivate() {}
  virtual bool          on_plugin_startProcessing() { return false; }
  virtual void          on_plugin_stopProcessing() {}
  virtual uint32_t      on_plugin_process(KODE_ProcessContext* AContext) { return 0; }
  virtual void          on_plugin_parameter(uint32_t AIndex, float AValue) {}
  virtual void          on_plugin_midi(uint32_t AOffset, uint8_t AMsg1, uint8_t AMsg2, uint8_t AMsg3) {}
  virtual uint32_t      on_plugin_saveState(void** ABuffer, uint32_t AMode) { *ABuffer = nullptr; return 0; }
  virtual uint32_t      on_plugin_loadState(uint32_t ASize, void* ABuffer, uint32_t AMode) { return 0; }

  virtual bool          on_plugin_createEditor(KODE_Editor* AEditor) { return false; }
  virtual void          on_plugin_destroyEditor(KODE_Editor* AEditor) {}
  virtual bool          on_plugin_openEditor(KODE_Editor* AEditor) { return false; }
  virtual void          on_plugin_closeEditor(KODE_Editor* AEditor) {}
  virtual void          on_plugin_updateEditor(KODE_Editor* AEditor) {}

//  virtual bool          on_plugin_openEditor(KODE_Editor* AEditor) { return false; }
//  virtual void          on_plugin_closeEditor(KODE_Editor* AEditor) {}
//  virtual uint32_t      on_plugin_updateEditor(KODE_Editor* AEditor) { return 0; }

};

//----------------------------------------------------------------------
#endif
