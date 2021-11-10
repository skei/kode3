#ifndef kode_hosted_vst2_plugin_included
#define kode_hosted_vst2_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_hosted_plugin.h"
#include "plugin/vst2/kode_vst2.h"
#include "plugin/vst2/kode_hosted_vst2_instance.h"

//----------------------------------------------------------------------

class KODE_HostedVst2Plugin
: public KODE_HostedPlugin {

//------------------------------
private:
//------------------------------

  KODE_Descriptor*  MDescriptor = nullptr;

//------------------------------
public:
//------------------------------

  KODE_HostedVst2Plugin()
  : KODE_HostedPlugin() {
    //KODE_PRINT;
  }

  //----------

  virtual ~KODE_HostedVst2Plugin() {
    //KODE_PRINT;
  }

//------------------------------
public:
//------------------------------

  KODE_HostedInstance* createInstance() final {
    KODE_HostedVst2Instance* instance = new KODE_HostedVst2Instance(MDescriptor);
    return instance;
  }



//------------------------------
public:
//------------------------------

//------------------------------
public:
//------------------------------

};

//----------------------------------------------------------------------
#endif
