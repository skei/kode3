
//#define KODE_PLUGIN_EXE
#define KODE_PLUGIN_ALL

//#define KODE_DEBUG_PRINT_SOCKET
// nc -U -l -k /tmp/kode.socket

//----------

#include "kode.h"
#include "plugin/kode_plugin.h"

#include "plugin/clap/kode_hosted_clap_plugin.h"

//----------------------------------------------------------------------

class myDescriptor
: public KODE_Descriptor {

public:

  myDescriptor() {
    name = "myPlugin";
    author = "skei.audio";
    appendInput("input 1");
    appendInput("input 2");
    appendOutput("output 1");
    appendOutput("output 2");
    appendParameter( new KODE_Parameter() );
  }

};

//----------------------------------------------------------------------

class myInstance
: public KODE_Instance {

public:

  myInstance(KODE_Descriptor* ADescriptor)
  : KODE_Instance(ADescriptor) {
  }

  bool on_plugin_init() final { return true; }
  void on_plugin_destroy() final {}

};

//----------------------------------------------------------------------

class myEditor
: public KODE_Editor {

public:

  myEditor(KODE_Instance* AInstance)
  : KODE_Editor(AInstance) {
  }

};

//----------------------------------------------------------------------

KODE_MAIN(myDescriptor,myInstance,myEditor)
