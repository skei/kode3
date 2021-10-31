
#include "kode.h"
#include "plugin/kode_plugin.h"

//----------------------------------------------------------------------

//----------------------------------------------------------------------

class myDescriptor
: public KODE_Descriptor {
public:
  myDescriptor() { KODE_PRINT; }
  virtual ~myDescriptor() { KODE_PRINT; }
};

//----------

class myInstance
: public KODE_Instance {
public:
  myInstance() { KODE_PRINT; }
  virtual ~myInstance() { KODE_PRINT; }
};

//----------------------------------------------------------------------

KODE_PLUGIN_ENTRYPOINT(myDescriptor,myInstance);




