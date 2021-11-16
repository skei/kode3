
#define KODE_PLUGIN_ALL
#define KODE_GUI_XCB
#define KODE_DEBUG_PRINT_SOCKET
// nc -U -l -k /tmp/kode.socket

//----------

#include "kode.h"
#include "plugin/kode_plugin.h"

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
    appendParameter( new KODE_Parameter() );
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
, public KODE_EditorListener {

private:

  KODE_Descriptor*  MDescriptor = nullptr;
  KODE_Editor*      MEditor     = nullptr;

public:

  myInstance(KODE_Descriptor* ADescriptor)
  : KODE_Instance(ADescriptor) {
    //KODE_PRINT;
    MDescriptor = ADescriptor;
  }

  virtual ~myInstance() {
    //KODE_PRINT;
  }

  bool on_plugin_init() final { return true; }
  void on_plugin_destroy() final {}
  bool on_plugin_activate() final { return false; }
  void on_plugin_deactivate() final {}
  bool on_plugin_startProcessing() final { return false; }
  void on_plugin_stopProcessing() final {}
  uint32_t on_plugin_process(KODE_ProcessContext* AContext) final { return 0; }
  void on_plugin_parameter(uint32_t AIndex, float AValue) final {}
  void on_plugin_midi(uint32_t AOffset, uint8_t AMsg1, uint8_t AMsg2, uint8_t AMsg3) final {}
  uint32_t on_plugin_saveState(void** ABuffer, uint32_t AMode) final { *ABuffer = nullptr; return 0; }
  uint32_t on_plugin_loadState(uint32_t ASize, void* ABuffer, uint32_t AMode) final { return 0; }

  KODE_Editor* on_plugin_openEditor() final {
    MEditor = new KODE_Editor(this);
    return MEditor;
  }

  void on_plugin_closeEditor() final {
    delete MEditor;
    MEditor = nullptr;
  }

  uint32_t on_plugin_updateEditor() final { return 0; }


};

//----------------------------------------------------------------------

class myEditor
: public KODE_Editor {

public:

  myEditor(KODE_EditorListener* AListener)
  : KODE_Editor(AListener) {
    //KODE_PRINT;
  }

  virtual ~myEditor() {
    //KODE_PRINT;
  }

};

//----------------------------------------------------------------------

KODE_MAIN(myDescriptor,myInstance,myEditor)
