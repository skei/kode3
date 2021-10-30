
#define KODE_DEBUG

#include "kode.h"
#include "plugin/kode_plugin.h"

//----------------------------------------------------------------------

/*

lv2:

  - host calls lv2_descriptor()
  - plugin returns ptr to LV2_Descriptor
  - host calls LV2_Descriptor.instantiate()
  - plugin creates 'real' plugin instance class,
    and returns ptr to this as the 'handle'

  - host calls various callback functions given in the LV2_Descriptor
    the plugin returned earlier
  - callback functions typecast the handle argument as ptr to 'real'
    plugin instance class, and calls proper method

*/

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




