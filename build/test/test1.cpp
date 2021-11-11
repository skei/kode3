
#define KODE_PLUGIN_ALL
#define KODE_GUI_XCB

#define KODE_DEBUG_PRINT
#define KODE_DEBUG_PRINT_SOCKET
// nc -U -l -k /tmp/kode.socket

//----------

#include "kode.h"
#include "plugin/kode_plugin.h"

//----------------------------------------------------------------------

class myDescriptor
: public KODE_Descriptor {

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
    //options.has_editor = true;
    //editorWidth= 400;
    //editorWidth= 300;
  }

};

//----------------------------------------------------------------------

class myInstance
: public KODE_Instance {

public:

  myInstance(KODE_Descriptor* ADescriptor)
  : KODE_Instance(ADescriptor) {
    KODE_PRINT;
  }

  virtual ~myInstance() {
    KODE_PRINT;
  }

  bool on_plugin_init() final {
    KODE_PRINT;
    return true;
  }

  void on_plugin_destroy() final {
    KODE_PRINT;
  }

};

//----------------------------------------------------------------------

class myEditor
: public KODE_Editor {

public:

  myEditor(KODE_Instance* AInstance)
  : KODE_Editor(AInstance) {
    KODE_PRINT;
  }

};

//----------------------------------------------------------------------

KODE_MAIN(myDescriptor,myInstance,myEditor)
