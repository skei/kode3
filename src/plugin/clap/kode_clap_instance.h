#ifndef kode_clap_instance_included
#define kode_clap_instance_included
//----------------------------------------------------------------------

#include "kode_clap.h"
#include "plugin/kode_descriptor.h"
#include "plugin/kode_instance.h"
#include "plugin/kode_editor.h"

//----------------------------------------------------------------------

class KODE_ClapInstance {

//------------------------------
private:
//------------------------------

  KODE_Instance* MInstance = nullptr;

//------------------------------
public:
//------------------------------

  KODE_ClapInstance(KODE_Instance* AInstance) {
    MInstance = AInstance;
  }

  //----------

  ~KODE_ClapInstance() {
    if (MInstance) delete MInstance;
  }

//------------------------------
public:
//------------------------------

  /*
    Must be called after creating the plugin.
    If init returns false, the host must destroy the plugin instance.
  */

  bool clap_instance_init() {
    MInstance->on_plugin_init();
    return false;
  }

  /*
    Free the plugin and its resources.
    It is not required to deactivate the plugin prior to this call.
  */

  void clap_instance_destroy() {
    MInstance->on_plugin_destroy();
  }

  /*
    activation/deactivation
    [main-thread]
  */

  bool clap_instance_activate(double sample_rate) {
    MInstance->on_plugin_activate();
    return true;
  }

  void clap_instance_deactivate() {
    MInstance->on_plugin_deactivate();
  }

  /*
    Set to true before processing,
    and to false before sending the plugin to sleep.
    [audio-thread]
  */

  bool clap_instance_start_processing() {
    MInstance->on_plugin_start_processing();
    return true;
  }

  void clap_instance_stop_processing() {
    MInstance->on_plugin_stop_processing();
  }

  /*
    process audio, events, ...
    [audio-thread]
  */

  clap_process_status clap_instance_process(const clap_process *process) {
    MInstance->on_plugin_process();
    return CLAP_PROCESS_CONTINUE;
  }

  /*
    Query an extension.
    The returned pointer is owned by the plugin.
    [thread-safe]
  */


  const void *clap_instance_get_extension(const char *id) {
    return nullptr;
  }

  /*
    Called by the host on the main thread in response to a previous call to:
      host->request_callback(host);
    [main-thread]
  */

  void clap_instance_on_main_thread() {
  }

};

//----------------------------------------------------------------------
#endif
