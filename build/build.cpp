
#define KODE_PLUGIN_ALL

//#define KODE_DEBUG_PRINT_TIME
//#define KODE_DEBUG_PRINT_THREAD
//#define KODE_DEBUG_PRINT_SOCKET
// nc -U -l -k /tmp/kode.socket

#include "kode.h"
#include "plugin/kode_plugin.h"

//----------------------------------------------------------------------

//----------------------------------------------------------------------

class myDescriptor
: public KODE_Descriptor {
public:
  myDescriptor() {
    KODE_PRINT;
    name = "kode_debug";
    author = "skei.audio";
  }
  virtual ~myDescriptor() { KODE_PRINT; }
};

//----------

class myInstance
: public KODE_Instance {
public:
  myInstance(KODE_Descriptor* ADescriptor) : KODE_Instance(ADescriptor) { KODE_PRINT; }
  virtual ~myInstance() { KODE_PRINT; }
};

//----------------------------------------------------------------------

KODE_PLUGIN_ENTRYPOINT(myDescriptor,myInstance);
