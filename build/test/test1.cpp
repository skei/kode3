
//#define KODE_PLUGIN_EXE
#define KODE_PLUGIN_VST3
#define KODE_PLUGIN_CLAP

//#define KODE_DEBUG_CLAP

//#define SKIP_STATE_SAVE

#define KODE_GUI_XCB
#define KODE_DEBUG_PRINT_SOCKET
// nc -U -l -k /tmp/kode.socket

//----------

#include "kode.h"
#include "plugin/kode_plugin.h"
#include "plugin/kode_voice_manager.h"
#include "gui/kode_widgets.h"

//----------------------------------------------------------------------

//class myVoice {
//public:
//  void strike(float note, float vel) {}
//  void lift(float vel) {}
//  void bend(float v) {}
//  void press(float v) {}
//  void slide(float v) {}
//  void ctrl(uint32_t i, uint32_t v) {}
//  void master_bend(float mb) {}
//  void master_press(float mp) {}
//  void master_ctrl(uint32_t i, uint32_t v) {}
//  void parameter(uint32_t i, float v) {}
//  void process(KODE_VoiceContext* AContext) {}
//};

//----------------------------------------------------------------------
//
// voice
//
//----------------------------------------------------------------------

class myVoice {

//------------------------------
private:
//------------------------------

  KODE_VoiceContext*  MContext      = KODE_NULL;
  float               MNote         = 0.0f;
  float               MBend         = 0.0f;
  float               MMasterBend   = 0.0f;
  float               MMasterPress  = 0.0f;

  float srate = 0.0f; // sample rate
  float ph    = 0.0f; // phase
  float phadd = 0.0f; // phase add

//------------------------------
public:
//------------------------------

  // content of AContext not valid yet..
  // just keep track of the ptr..

  void prepare(KODE_VoiceContext* AContext, float ASampleRate/*, uint32_t ABlockSize*/) {
    MContext = AContext;
    srate = ASampleRate;
  }

  //----------

  uint32_t strike(float note, float vel) {
    MNote = note;
    MBend = 0.0f;
    float hz = KODE_NoteToHz(MNote + (MMasterBend * 2.0f) + (MBend*48.0f));
    ph = 0.0f;
    phadd = hz / srate;
    return KODE_VOICE_PLAYING;
  }

  //----------

  uint32_t lift(float vel) {
    return KODE_VOICE_FINISHED;
  }

  //----------

  void bend(float b) {
    MBend = b;
    float hz = KODE_NoteToHz(MNote + (MMasterBend * 2.0f) + (MBend*48.0f));
    phadd = hz / srate;
  }

  //----------

  void press(float p) {
  }

  //----------

  void slide(float s) {
  }

  //----------

  void ctrl(uint32_t i, uint32_t v) {
  }

  //----------

  void master_bend(float mb) {
    MMasterBend = mb;
    float hz = KODE_NoteToHz(MNote + (MMasterBend * 2.0f) + (MBend*48.0f));
    phadd = hz / srate;
  }

  //----------

  void master_press(float mp) {
    MMasterPress = mp;
  }

  //----------

  void master_ctrl(uint32_t i, float mc) {
  }

  //----------

  void parameter(uint32_t i, float c) {
  }

  //----------

  uint32_t process(uint32_t AMode) {
    uint32_t num = MContext->processContext->numsamples;
    float*out0 = MContext->processContext->outputs[0];
    float*out1 = MContext->processContext->outputs[1];
    for (uint32_t i=0; i<num; i++) {
      float v = (ph * 2.0f) - 1.0f;
      ph += phadd;
      ph = KODE_Fract(ph);
      *out0++ += v * 0.1f;
      *out1++ += v * 0.1f;
    }
    return AMode;
  }

  //----------

};


//----------------------------------------------------------------------

class myDescriptor
: public KODE_Descriptor {

private:

public:

  myDescriptor() {
    //KODE_PRINT;
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
    appendParameter(new KODE_Parameter( "slider", 1, -2, 2 ));
    appendParameter(new KODE_Parameter( "knob",   0,  0, 1 ));
    options.is_synth = true;
    options.has_editor = true;
    editorWidth = 400;
    editorHeight = 300;
  }

  virtual ~myDescriptor() {
    //KODE_PRINT;
  }

};

//----------------------------------------------------------------------

class myInstance
: public KODE_Instance
/*, public KODE_EditorListener*/ {

private:

  KODE_Descriptor*              MDescriptor = nullptr;
  KODE_Editor*                  MEditor     = nullptr;
  KODE_VoiceManager<myVoice,16> MVoices     = {};

public:

  myInstance(KODE_Descriptor* ADescriptor)
  : KODE_Instance(ADescriptor) {
    //KODE_PRINT;
    MDescriptor = ADescriptor;
  }

  virtual ~myInstance() {
    //KODE_PRINT;
  }

public:

  bool on_plugin_init() final {
    return true;
  }

  void on_plugin_destroy() final {
  }

  bool on_plugin_activate(float ASampleRate, uint32_t AMinFrames, uint32_t AMaxFrames) final {
    MVoices.prepare(ASampleRate/*,ABlocksize*/);
    return false;
  }

  void on_plugin_deactivate() final {
  }

  bool on_plugin_startProcessing() final {
    return false;
  }

  void on_plugin_stopProcessing() final {
  }

  uint32_t on_plugin_process(KODE_ProcessContext* AContext) final {
    //float* out0 = AContext->outputs[0];
    //float* out1 = AContext->outputs[1];
    //for (uint32_t i=0; i<AContext->numsamples; i++) {
    //  *out0++ = KODE_RandomSigned() * 0.5;
    //  *out1++ = KODE_RandomSigned() * 0.5;
    //}
    MVoices.processBlock(AContext);
    return 0;
  }

  void on_plugin_parameter(uint32_t AIndex, float AValue) final {
    uint32_t AOffset = 0;
    uint32_t AMode = 0;
    MVoices.parameter(AOffset,AIndex,AValue,AMode);
  }

  void on_plugin_midi(uint32_t AOffset, uint8_t AMsg1, uint8_t AMsg2, uint8_t AMsg3) final {
    uint32_t AMode = 0;
    MVoices.midi(AOffset,AMsg1,AMsg2,AMsg3,AMode);
  }

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

  // we don't have a window yet
  bool on_plugin_createEditor(KODE_Editor* AEditor) final {
    //KODE_PRINT;
    return true;
  }

  void on_plugin_destroyEditor(KODE_Editor* AEditor) final {
    //KODE_PRINT;
  }

  bool on_plugin_openEditor(KODE_Editor* AEditor) final {
    //KODE_PRINT;
    KODE_Window* window = AEditor->getWindow();
    if (window) {
      KODE_SliderWidget* slider = new KODE_SliderWidget( KODE_FRect(10,10,150,20) );
      KODE_KnobWidget*    knob  = new KODE_KnobWidget( KODE_FRect(10,40,50,50) );
      window->appendWidget(slider);
      window->appendWidget(knob);
      AEditor->connect(slider,0);
      AEditor->connect(knob,1);
      return true;
    }
    return false;
  }

  void on_plugin_closeEditor(KODE_Editor* AEditor) final {
    //KODE_PRINT;
  }

  void on_plugin_updateEditor(KODE_Editor* AEditor) final {
    //KODE_PRINT;
  }

};

//----------------------------------------------------------------------

class myEditor
: public KODE_Editor {

public:

  myEditor(KODE_EditorListener* AListener, KODE_Descriptor* ADescriptor)
  : KODE_Editor(AListener,ADescriptor) {
    //KODE_PRINT;
  }

  virtual ~myEditor() {
    //KODE_PRINT;
  }

};

//----------------------------------------------------------------------

KODE_MAIN(myDescriptor,myInstance,myEditor)
