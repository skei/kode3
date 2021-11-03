#ifndef kode_instance_included
#define kode_instance_included
//----------------------------------------------------------------------

#include "kode.h"
#include "kode_descriptor.h"


class KODE_Instance {

public:

  KODE_Instance(KODE_Descriptor* ADescriptor) {
  }

  virtual ~KODE_Instance() {
  }

public:

  virtual void  on_plugin_init() {}
  virtual void  on_plugin_destroy() {}
  virtual void  on_plugin_activate() {}
  virtual void  on_plugin_deactivate() {}
  virtual void  on_plugin_start_processing() {}
  virtual void  on_plugin_stop_processing() {}
  virtual void  on_plugin_process() {}

};

//----------------------------------------------------------------------
#endif
