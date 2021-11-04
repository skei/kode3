
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

    //setName("myPlugin");
    //setAuthor("skei.audio");

    name = "myPlugin";
    author = "skei.audio";

    //appendInput(  new KODE_PluginPort("input 1", KODE_PORT_AUDIO,1,KODE_PORT_INPUT) );
    //appendInput(  new KODE_PluginPort("input 2", KODE_PORT_AUDIO,1,KODE_PORT_INPUT) );
    //appendOutput( new KODE_PluginPort("output 1",KODE_PORT_AUDIO,1,KODE_PORT_OUTPUT) );
    //appendOutput( new KODE_PluginPort("output 2",KODE_PORT_AUDIO,1,KODE_PORT_OUTPUT) );

    appendInput("input 1");
    appendInput("input 2");
    appendOutput("output 1");
    appendOutput("output 2");

    //KODE_Parameter* param1 = new KODE_Parameter();
    appendParameter( new KODE_Parameter() );
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
