
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
    name    = "myPlugin";
    author  = "skei.audio";
  }

};

//----------------------------------------------------------------------

class myInstance
: public KODE_Instance {

public:

  myInstance(KODE_Descriptor* ADescriptor)
  : KODE_Instance(ADescriptor) {
    KODE_HostedClapPlugin plugin;
  }

  void on_plugin_init() final {}
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
