
//#define KODE_PLUGIN_EXE
//#define KODE_PLUGIN_LADSPA
//#define KODE_PLUGIN_DSSI
//#define KODE_PLUGIN_LV2
//#define KODE_PLUGIN_VST2
//#define KODE_PLUGIN_VST3
//#define KODE_PLUGIN_CLAP
#define KODE_PLUGIN_ALL

#define KODE_GUI_XCB

//#define KODE_DEBUG_PRINT_SOCKET
// nc -U -l -k /tmp/kode.socket

//----------

#include "kode.h"
#include "plugin/kode_plugin.h"
#include "gui/kode_widgets.h"

//----------------------------------------------------------------------
//
// descriptor
//
//----------------------------------------------------------------------

class myDescriptor
: public KODE_Descriptor {

//------------------------------
private:
//------------------------------

//------------------------------
public:
//------------------------------

  myDescriptor() {
    //KODE_PRINT;
    #ifdef KODE_DEBUG
      MName  = "kode_debug";
    #else
      name  = "kode";
    #endif
    MAuthor  = "skei.audio";
    appendInput("input 1");
    appendInput("input 2");
    appendOutput("output 1");
    appendOutput("output 2");
    appendParameter(new KODE_Parameter( "slider", 1.0,  -2.0, 2.0 ));
    appendParameter(new KODE_Parameter( "knob",   0.25,  0.0, 1.0 ));
    MOptions.has_editor = true;
    MEditorWidth = 400;
    MEditorHeight = 300;
  }

  //----------

  virtual ~myDescriptor() {
    //KODE_PRINT;
  }

};

//----------------------------------------------------------------------
//
// editor
//
//----------------------------------------------------------------------

class myEditor
: public KODE_Editor {

//------------------------------
private:
//------------------------------

  KODE_SliderWidget*  MSlider1      = nullptr;
  KODE_KnobWidget*    MKnob1        = nullptr;

//------------------------------
public:
//------------------------------

  myEditor(KODE_EditorListener* AListener, KODE_Descriptor* ADescriptor)
  : KODE_Editor(AListener,ADescriptor) {
    //KODE_PRINT;
  }

  //----------

  virtual ~myEditor() {
    //KODE_PRINT;
  }

  //----------

  void show() override {
    KODE_PRINT;
    if (MWindow) {
      KODE_PRINT;
      MSlider1  = new KODE_SliderWidget( KODE_FRect(10,10,150,20) );
      MKnob1    = new KODE_KnobWidget( KODE_FRect(10,40,50,50) );
      MWindow->appendWidget(MSlider1);
      MWindow->appendWidget(MKnob1);
      connect( MSlider1, 0 );
      connect( MKnob1,   1 );
    }
    KODE_Editor::show();
  }

};

//----------------------------------------------------------------------
//
// instance
//
//----------------------------------------------------------------------

class myInstance
: public KODE_Instance
/*, public KODE_EditorListener*/ {

//------------------------------
private:
//------------------------------

  KODE_Descriptor*  MDescriptor = nullptr;
  KODE_Editor*      MEditor     = nullptr;

//------------------------------
public:
//------------------------------

  myInstance(KODE_Descriptor* ADescriptor)
  : KODE_Instance(ADescriptor) {
    //KODE_PRINT;
    MDescriptor = ADescriptor;
  }

  //----------

  virtual ~myInstance() {
    //KODE_PRINT;
  }

//------------------------------
public:
//------------------------------

  bool on_plugin_init() final {
    KODE_PRINT;
    return true;
  }

  //----------

  void on_plugin_destroy() final {
    KODE_PRINT;
  }

  //----------

  bool on_plugin_activate(float ASampleRate, uint32_t AMinFrames, uint32_t AMaxFrames) final {
    KODE_PRINT;
    return false;
  }

  //----------

  void on_plugin_deactivate() final {
    KODE_PRINT;
  }

  //----------

  bool on_plugin_startProcessing() final {
    KODE_PRINT;
    return false;
  }

  //----------

  void on_plugin_stopProcessing() final {
    KODE_PRINT;
  }

  //----------

  //void on_plugin_expression() final {
  //  KODE_PRINT;
  //}

  //----------

  void on_plugin_modulation(uint32_t AIndex, float AValue) final {
    KODE_PRINT;
  }

  //----------

  void on_plugin_parameter(uint32_t AIndex, float AValue) final {
    KODE_PRINT;
  }

  //----------

  void on_plugin_midi(uint32_t AOffset, uint8_t AMsg1, uint8_t AMsg2, uint8_t AMsg3) final {
    //KODE_Print("%i : %02x %02x %02x\n",AOffset,AMsg1,AMsg2,AMsg3);
  }

  //----------

  uint32_t on_plugin_saveState(void** ABuffer, uint32_t AMode) final {
    KODE_PRINT;
    *ABuffer = nullptr; return 0;
  }

  //----------

  uint32_t on_plugin_loadState(uint32_t ASize, void* ABuffer, uint32_t AMode) final {
    KODE_PRINT;
    return 0;
  }

  //----------

  uint32_t on_plugin_process(KODE_ProcessContext* AContext) final {
    //float* out0 = AContext->outputs[0];
    //float* out1 = AContext->outputs[1];
    //for (uint32_t i=0; i<AContext->numsamples; i++) {
    //  *out0++ = KODE_RandomSigned() * 0.5;
    //  *out1++ = KODE_RandomSigned() * 0.5;
    //}
    return 0;
  }

  //----------

  // we don't have a window yet
  bool on_plugin_createEditor(KODE_Editor* AEditor) final {
    KODE_PRINT;
    return true;
  }

  //----------

  void on_plugin_destroyEditor(KODE_Editor* AEditor) final {
    KODE_PRINT;
  }

  //----------

  bool on_plugin_openEditor(KODE_Editor* AEditor) final {
    KODE_PRINT;
    KODE_Window* window = AEditor->getWindow();
    if (window) {
      return true;
    }
    return false;
  }

  //----------

  void on_plugin_closeEditor(KODE_Editor* AEditor) final {
    KODE_PRINT;
  }

  //----------

  void on_plugin_updateEditor(KODE_Editor* AEditor) final {
    //KODE_PRINT;
  }

  //----------

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

KODE_MAIN(myDescriptor,myInstance,myEditor)
