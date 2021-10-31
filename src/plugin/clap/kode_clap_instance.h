#ifndef kode_clap_instance_included
#define kode_clap_instance_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/clap/kode_clap.h"

//----------------------------------------------------------------------

class KODE_ClapInstance {

//------------------------------
private:
//------------------------------

  const clap_host*  MClapHost = nullptr;
  KODE_Instance*    MInstance = nullptr;

//------------------------------
public:
//------------------------------

  /*
    struct clap_host {
      clap_version  clap_version  = CLAP_VERSION
      void*         host_data     = nullptr
      const char*   name          = "Bitwig Studio"
      const char*   vendor        = "Bitwig GmbH"
      const char*   url           = "https://bitwig.com"
      const char*   version       = "3.3.8"
      const void*   (*get_extension)(const struct clap_host *host, const char *extension_id);
      void          (*request_restart)(const struct clap_host *host);
      void          (*request_process)(const struct clap_host *host);
      void          (*request_callback)(const struct clap_host *host);
    };
  */

  KODE_ClapInstance(const clap_host *host, KODE_Instance* AInstance) {
    MClapHost = host;
    MInstance = AInstance;
  }

  //----------

  ~KODE_ClapInstance() {
  }

//------------------------------
public:
//------------------------------

  //const clap_plugin* getClapPlugin() {
  //  return &MClapPlugin;
  //}

//------------------------------
public:
//------------------------------

  /*
    Must be called after creating the plugin.
    If init returns false, the host must destroy the plugin instance.
  */

  bool clap_instance_init() {
    return false;
  }

  //----------

  /*
    Free the plugin and its resources.
    It is not required to deactivate the plugin prior to this call.
  */

  void clap_instance_destroy() {
  }

  //----------

  /*
    activation
    [main-thread]
  */

  bool clap_instance_activate(double sample_rate) {
    return false;
  }

  //----------

  /*
    deactivation
    [main-thread]
  */

  void clap_instance_deactivate() {
  }

  //----------

  /*
    Set to true before processing
    (and to false before sending the plugin to sleep)
    [audio-thread]

    NOTE: clarify documentation/comments
  */

  bool clap_instance_start_processing() {
    return false;
  }

  //----------

  /*
    (Set to true before processing)
    and to false before sending the plugin to sleep.
    [audio-thread]
  */

  void clap_instance_stop_processing() {
  }


  //----------

  /*
    process audio, events, ...
    [audio-thread]
  */

  /*
    struct clap_process {
      uint64_t                    steady_time;
      uint32_t                    frames_count;
      const clap_event_transport* transport;
      const clap_audio_buffer*    audio_inputs;
      const clap_audio_buffer*    audio_outputs;
      uint32_t                    audio_inputs_count;
      uint32_t                    audio_outputs_count;
      const clap_event_list*      in_events;
      const clap_event_list*      out_events;
    };
  */

  clap_process_status clap_instance_process(const clap_process *process) {
    return CLAP_PROCESS_ERROR;
  }

  //----------

  /*
    Query an extension.
    The returned pointer is owned by the plugin.
    [thread-safe]
  */

  const void* clap_instance_get_extension(const char *id) {
    return nullptr;
  }

  //----------

  /*
    Called by the host on the main thread in response to a previous call to:
    host->request_callback(host);
    [main-thread]
  */

  void clap_instance_on_main_thread() {
  }

//------------------------------
public:
//------------------------------

};

//----------------------------------------------------------------------
#endif
