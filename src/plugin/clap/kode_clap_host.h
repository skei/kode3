#ifndef kode_clap_host_cinluded
#define kode_clap_host_cinluded
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/clap/kode_clap.h"

//----------------------------------------------------------------------

class KODE_ClapHost {

//------------------------------
private:
//------------------------------

  clap_host* MClapHost = nullptr;

  void*       MHostData     = nullptr;
  const char* MHostName     = "";
  const char* MHostVendor   = "";
  const char* MHostUrl      = "";
  const char* MHostVersion  = "";

//------------------------------
public:
//------------------------------

  KODE_ClapHost(clap_host* AHost) {
    MClapHost     = AHost;
    MHostData     = AHost->host_data;
    MHostName     = AHost->name;
    MHostVendor   = AHost->vendor;
    MHostUrl      = AHost->url;
    MHostVersion  = AHost->version;


  }

//------------------------------
public:
//------------------------------

  // Query an extension.
  // [thread-safe]

  const void* get_extension(const char *extension_id) {
    return MClapHost->get_extension(MClapHost,extension_id);
  }

  //----------

  // Request the host to deactivate and then reactivate the plugin.
  // The operation may be delayed by the host.
  // [thread-safe]

  void request_restart() {
    MClapHost->request_restart(MClapHost);
  }

  //----------

  // Request the host to activate and start processing the plugin.
  // This is useful if you have external IO and need to wake up the plugin from "sleep".
  // [thread-safe]

  void request_process() {
    MClapHost->request_process(MClapHost);
  }

  //----------

  // Request the host to schedule a call to plugin->on_main_thread(plugin) on the main thread.
  // [thread-safe]

  void request_callback() {
    MClapHost->request_callback(MClapHost);
  }

//------------------------------

};

//----------------------------------------------------------------------
#endif
