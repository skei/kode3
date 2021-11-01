
#define KODE_PLUGIN_ALL

//#define KODE_DEBUG_PRINT_TIME
//#define KODE_DEBUG_PRINT_THREAD
//#define KODE_DEBUG_PRINT_SOCKET
// nc -U -l -k /tmp/kode.socket

#include "kode.h"
#include "plugin/kode_plugin.h"
#include "plugin/kode_editor.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class myDescriptor
: public KODE_Descriptor {

public:

  myDescriptor()
  : KODE_Descriptor() {

    KODE_PRINT;
    #ifdef KODE_DEBUG
    name    = "kode_plugin_debug";
    #else
    name    = "kode_plugin";
    #endif
    author  = "skei.audio";

  }

  //----------

  virtual ~myDescriptor() {
    KODE_PRINT;
  }

};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class myEditor
: public KODE_Editor {
};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class myInstance
: public KODE_Instance {

public:

  myInstance(KODE_Descriptor* ADescriptor)
  : KODE_Instance(ADescriptor) {
    KODE_PRINT;
  }

  //----------

  virtual ~myInstance() {
    KODE_PRINT;
  }

};

//----------------------------------------------------------------------

KODE_PLUGIN_ENTRYPOINT(myDescriptor,myInstance,myEditor);
