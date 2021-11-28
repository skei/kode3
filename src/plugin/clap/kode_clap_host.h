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

  const clap_host*  MClapHost     = nullptr;
  void*             MHostData     = nullptr;
  const char*       MHostName     = "";
  const char*       MHostVendor   = "";
  const char*       MHostUrl      = "";
  const char*       MHostVersion  = "";

  // extensions
  clap_host_audio_ports_config* MHostAudioPortsConfig = nullptr;
  clap_host_audio_ports*        MHostAudioPorts       = nullptr;
  clap_host_event_filter*       MHostEventFilter      = nullptr;
  clap_host_fd_support*         MHostFdSupport        = nullptr;
  clap_host_gui*                MHostGui              = nullptr;
  clap_host_latency*            MHostLatency          = nullptr;
  clap_host_log*                MHostLog              = nullptr;
  clap_host_note_name*          MHostNoteName         = nullptr;
  clap_host_params*             MHostParams           = nullptr;
  clap_host_state*              MHostState            = nullptr;
  clap_host_thread_check*       MHostThreadCheck      = nullptr;
  clap_host_timer_support*      MHostTimerSupport     = nullptr;

//------------------------------
public:
//------------------------------

  KODE_ClapHost(const clap_host* AHost) {
    MClapHost     = AHost;
    MHostData     = AHost->host_data;
    MHostName     = AHost->name;
    MHostVendor   = AHost->vendor;
    MHostUrl      = AHost->url;
    MHostVersion  = AHost->version;
    init_extensions();
  }

//------------------------------
public:
//------------------------------

  void init_extensions() {
    MHostAudioPortsConfig = (clap_host_audio_ports_config*)get_extension(CLAP_EXT_AUDIO_PORTS_CONFIG);
    MHostAudioPorts       = (clap_host_audio_ports*)get_extension(CLAP_EXT_AUDIO_PORTS);
    MHostEventFilter      = (clap_host_event_filter*)get_extension(CLAP_EXT_EVENT_FILTER);
    MHostFdSupport        = (clap_host_fd_support*)get_extension(CLAP_EXT_FD_SUPPORT);
    MHostGui              = (clap_host_gui*)get_extension(CLAP_EXT_GUI);
    MHostLatency          = (clap_host_latency*)get_extension(CLAP_EXT_LATENCY);
    MHostLog              = (clap_host_log*)get_extension(CLAP_EXT_LOG);
    MHostNoteName         = (clap_host_note_name*)get_extension(CLAP_EXT_NOTE_NAME);
    MHostParams           = (clap_host_params*)get_extension(CLAP_EXT_PARAMS);
    MHostState            = (clap_host_state*)get_extension(CLAP_EXT_STATE);
    MHostThreadCheck      = (clap_host_thread_check*)get_extension(CLAP_EXT_THREAD_CHECK);
    MHostTimerSupport     = (clap_host_timer_support*)get_extension(CLAP_EXT_TIMER_SUPPORT);
  }

//------------------------------
public:
//------------------------------

  // Query an extension.
  // [thread-safe]

  const void* get_extension(const char *extension_id) {
    KODE_ClapPrint("%s\n",extension_id);
    return MClapHost->get_extension(MClapHost,extension_id);
  }

  //----------

  // Request the host to deactivate and then reactivate the plugin.
  // The operation may be delayed by the host.
  // [thread-safe]

  void request_restart() {
    KODE_CLAPPRINT;
    MClapHost->request_restart(MClapHost);
  }

  //----------

  // Request the host to activate and start processing the plugin.
  // This is useful if you have external IO and need to wake up the plugin from "sleep".
  // [thread-safe]

  void request_process() {
    KODE_CLAPPRINT;
    MClapHost->request_process(MClapHost);
  }

  //----------

  // Request the host to schedule a call to plugin->on_main_thread(plugin) on the main thread.
  // [thread-safe]

  void request_callback() {
    KODE_CLAPPRINT;
    MClapHost->request_callback(MClapHost);
  }

//------------------------------

};

//----------------------------------------------------------------------
#endif
