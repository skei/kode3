
//#define KODE_PLUGIN_EXE
#define KODE_PLUGIN_ALL

//----------

#include "kode.h"
#include "plugin/kode_plugin.h"

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
