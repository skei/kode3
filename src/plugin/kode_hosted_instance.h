#ifndef kode_hosted_instance_included
#define kode_hosted_instance_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_instance.h"

//----------------------------------------------------------------------

class KODE_HostedInstance
: public KODE_Instance {

//------------------------------
private:
//------------------------------

  //const char* MFilepath = "";

//------------------------------
public:
//------------------------------

  KODE_HostedInstance(KODE_Descriptor* ADescriptor)
  : KODE_Instance(ADescriptor) {
    KODE_PRINT;
  }

  //----------

  virtual ~KODE_HostedInstance() {
    KODE_PRINT;
  }

//------------------------------
public:
//------------------------------


};

//----------------------------------------------------------------------
#endif
