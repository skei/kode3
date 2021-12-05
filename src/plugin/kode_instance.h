#ifndef kode_instance_included
#define kode_instance_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_descriptor.h"
#include "plugin/kode_editor.h"
#include "plugin/kode_process_context.h"


class KODE_Instance {

//------------------------------
private:
//------------------------------

  uint32_t          MPluginFormat     = KODE_PLUGIN_FORMAT_NONE;
  KODE_Descriptor*  MDescriptor       = nullptr;
  float*            MParameterValues  = nullptr;
  float*            MModulationValues = nullptr;

//------------------------------
public:
//------------------------------

  KODE_Instance(KODE_Descriptor* ADescriptor) {
    MDescriptor = ADescriptor;
    MParameterValues = (float*)malloc(MDescriptor->parameters.size() * sizeof(float));
    MModulationValues = (float*)malloc(MDescriptor->parameters.size() * sizeof(float));
  }

  //----------

  virtual ~KODE_Instance() {
    if (MParameterValues) free(MParameterValues);
    if (MModulationValues) free(MModulationValues);
    if (MDescriptor) delete MDescriptor; // hmm.. :-/
  }

//------------------------------
public:
//------------------------------

  uint32_t          getPluginFormat()                     { return MPluginFormat; }
  KODE_Descriptor*  getDescriptor()                       { return MDescriptor; }
  float             getParameterValue(uint32_t AIndex)    { return MParameterValues[AIndex]; }
  float*            getParameterValueBuffer()             { return MParameterValues; }
  float             getModulationValue(uint32_t AIndex)   { return MModulationValues[AIndex]; }
  float*            getModulationValueBuffer()            { return MModulationValues; }

  void  setPluginFormat(uint32_t APluginFormat)           { MPluginFormat = APluginFormat; }
  void  setParameterValue(uint32_t AIndex, float AValue)  { MParameterValues[AIndex] = AValue; }
  void  setModulationValue(uint32_t AIndex, float AValue) { MModulationValues[AIndex] = AValue; }

//------------------------------
public:
//------------------------------

  virtual bool      on_plugin_init() { return false; }
  virtual void      on_plugin_destroy() {}
  virtual bool      on_plugin_activate(float ASampleRate, uint32_t AMinFrames, uint32_t AMaxFrames) { return false; }
  virtual void      on_plugin_deactivate() {}
  virtual bool      on_plugin_startProcessing() { return false; }
  virtual void      on_plugin_stopProcessing() {}

  //virtual void      on_plugin_expression() {}
  virtual void      on_plugin_modulation(uint32_t AIndex, float AValue) {}
  virtual void      on_plugin_parameter(uint32_t AIndex, float AValue) {}
  virtual void      on_plugin_midi(uint32_t AOffset, uint8_t AMsg1, uint8_t AMsg2, uint8_t AMsg3) {}
  virtual uint32_t  on_plugin_process(KODE_ProcessContext* AContext) { return 0; }

  virtual uint32_t  on_plugin_saveState(void** ABuffer, uint32_t AMode) { *ABuffer = nullptr; return 0; }
  virtual uint32_t  on_plugin_loadState(uint32_t ASize, void* ABuffer, uint32_t AMode) { return 0; }

  virtual bool      on_plugin_createEditor(KODE_Editor* AEditor) { return false; }
  virtual void      on_plugin_destroyEditor(KODE_Editor* AEditor) {}
  virtual bool      on_plugin_openEditor(KODE_Editor* AEditor) { return false; }
  virtual void      on_plugin_closeEditor(KODE_Editor* AEditor) {}
  virtual void      on_plugin_updateEditor(KODE_Editor* AEditor) {}

//------------------------------
public:
//------------------------------

  void setDefaultParameterValues() {
    uint32_t num = MDescriptor->parameters.size();
    for (uint32_t i=0; i<num; i++) {
      KODE_Parameter* parameter = MDescriptor->parameters[i];
      float value = parameter->def_value;
      MParameterValues[i] = value;
    }
  }

  //----------

  void updateAllParameters() {
    uint32_t num = MDescriptor->parameters.size();
    for (uint32_t i=0; i<num; i++) {
      float value = MParameterValues[i];
      if ((MPluginFormat == KODE_PLUGIN_FORMAT_VST2)
       || (MPluginFormat == KODE_PLUGIN_FORMAT_VST3)) {
        KODE_Parameter* parameter = MDescriptor->parameters[i];
        value = parameter->from01(value);
      }
      on_plugin_parameter(i,value);
    }
  }

  //----------

  #ifndef KODE_NO_GUI

  void updateEditorParameter(KODE_Editor* AEditor, uint32_t AIndex, bool ARedraw=true) {
    float value = MParameterValues[AIndex];
    if (MPluginFormat == KODE_PLUGIN_FORMAT_CLAP) {
      KODE_Parameter* parameter = MDescriptor->parameters[AIndex];
      value = parameter->to01(value);
    }
    AEditor->updateParameter(AIndex,value,ARedraw);
  }

  //----------

  void updateAllEditorParameters(KODE_Editor* AEditor, bool ARedraw=true) {
    uint32_t num = MDescriptor->parameters.size();
    for (uint32_t i=0; i<num; i++) {
      //float value = MParameterValues[i];
      //if (MPluginFormat == KODE_PLUGIN_FORMAT_CLAP) {
      //  KODE_Parameter* parameter = MDescriptor->parameters[i];
      //  value = parameter->to01(value);
      //}
      //AEditor->updateParameter(i,value,ARedraw);

      updateEditorParameter(AEditor,i,ARedraw);

    }
  }

  #endif

  //----------

};

//----------------------------------------------------------------------
#endif
