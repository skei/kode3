
#define KODE_PLUGIN_CLAP
#define KODE_DEBUG_CLAP

#define KODE_GUI_XCB
#define KODE_DEBUG_PRINT_SOCKET
// nc -U -l -k /tmp/kode.socket

//----------

#include "kode.h"
#include "plugin/kode_plugin.h"
#include "gui/kode_widgets.h"

//----------------------------------------------------------------------

class myDescriptor
: public KODE_Descriptor {

private:

public:

  myDescriptor() {
    KODE_PRINT;
    #ifdef KODE_DEBUG
      name  = "kode_debug";
    #else
      name  = "kode";
    #endif
    author  = "skei.audio";
    appendInput("input 1");
    appendInput("input 2");
    appendOutput("output 1");
    appendOutput("output 2");
    appendParameter( new KODE_Parameter() );
    options.is_synth = true;
    options.has_editor = true;
    editorWidth = 400;
    editorHeight = 300;
  }

  virtual ~myDescriptor() {
    KODE_PRINT;
  }

};

//----------------------------------------------------------------------

class myInstance
: public KODE_Instance
/*, public KODE_EditorListener*/ {

private:

  KODE_Descriptor*  MDescriptor = nullptr;
  KODE_Editor*      MEditor     = nullptr;

public:

  myInstance(KODE_Descriptor* ADescriptor)
  : KODE_Instance(ADescriptor) {
    KODE_PRINT;
    MDescriptor = ADescriptor;
  }

  virtual ~myInstance() {
    KODE_PRINT;
  }

  bool on_plugin_init() final { return true; }
  void on_plugin_destroy() final {}
  bool on_plugin_activate() final { return false; }
  void on_plugin_deactivate() final {}
  bool on_plugin_startProcessing() final { return false; }
  void on_plugin_stopProcessing() final {}

  uint32_t on_plugin_process(KODE_ProcessContext* AContext) final {
    float* out0 = AContext->outputs[0];
    float* out1 = AContext->outputs[1];
    for (uint32_t i=0; i<AContext->numsamples; i++) {
      *out0++ = KODE_RandomSigned() * 0.5;
      *out1++ = KODE_RandomSigned() * 0.5;
    }
    return 0;
  }

  void on_plugin_parameter(uint32_t AIndex, float AValue) final {}
  void on_plugin_midi(uint32_t AOffset, uint8_t AMsg1, uint8_t AMsg2, uint8_t AMsg3) final {}
  uint32_t on_plugin_saveState(void** ABuffer, uint32_t AMode) final { *ABuffer = nullptr; return 0; }
  uint32_t on_plugin_loadState(uint32_t ASize, void* ABuffer, uint32_t AMode) final { return 0; }

  //KODE_Editor* on_plugin_openEditor() final {
  //  MEditor = new KODE_Editor(this,MDescriptor);
  //  return MEditor;
  //}

  //void on_plugin_closeEditor() final {
  //  delete MEditor;
  //  MEditor = nullptr;
  //}

  //uint32_t on_plugin_updateEditor() final {
  //  return 0;
  //}

  bool on_plugin_createEditor(KODE_Editor* AEditor) final {
    KODE_PRINT;
    return true;
  }

  void on_plugin_destroyEditor(KODE_Editor* AEditor) final {
    KODE_PRINT;
  }

  bool on_plugin_openEditor(KODE_Editor* AEditor) final {
    KODE_PRINT;
    KODE_Window* window = AEditor->getWindow();
    if (window) {
      KODE_SliderWidget* slider = new KODE_SliderWidget( KODE_FRect(10,10,150,20) );
      KODE_KnobWidget*    knob  = new KODE_KnobWidget( KODE_FRect(10,40,50,50) );
      window->appendWidget(slider);
      window->appendWidget(knob);
      AEditor->connect(slider,0);
      return true;
    }
    return false;
  }

  void on_plugin_closeEditor(KODE_Editor* AEditor) final {
    KODE_PRINT;
  }

  void on_plugin_updateEditor(KODE_Editor* AEditor) final {
    KODE_PRINT;
  }

};

//----------------------------------------------------------------------

class myEditor
: public KODE_Editor {

public:

  myEditor(KODE_EditorListener* AListener, KODE_Descriptor* ADescriptor)
  : KODE_Editor(AListener,ADescriptor) {
    KODE_PRINT;
  }

  virtual ~myEditor() {
    KODE_PRINT;
  }

};

//----------------------------------------------------------------------

KODE_MAIN(myDescriptor,myInstance,myEditor)
