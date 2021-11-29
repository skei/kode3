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

  /*
    Query an extension.
    [thread-safe]
  */

  const void* get_extension(const char *extension_id) {
    KODE_ClapPrint("%s\n",extension_id);
    return MClapHost->get_extension(MClapHost,extension_id);
  }

  /*
    Request the host to deactivate and then reactivate the plugin.
    The operation may be delayed by the host.
    [thread-safe]
  */

  void request_restart() {
    KODE_CLAPPRINT;
    MClapHost->request_restart(MClapHost);
  }

  //----------

  /*
    Request the host to activate and start processing the plugin.
    This is useful if you have external IO and need to wake up the plugin from
    "sleep".
    [thread-safe]
  */

  void request_process() {
    KODE_CLAPPRINT;
    MClapHost->request_process(MClapHost);
  }

  //----------

  /*
    Request the host to schedule a call to plugin->on_main_thread(plugin) on
    the main thread.
    [thread-safe]
  */

  void request_callback() {
    KODE_CLAPPRINT;
    MClapHost->request_callback(MClapHost);
  }

//------------------------------
public: // extensions
//------------------------------

  //--------------------
  // audio-ports-config
  //--------------------

  /*
    This extension provides a way for the plugin to describe possible ports
    configurations, for example mono, stereo, surround, ...
    and a way for the host to select a configuration.
    ...
    Plugin with very complex configuration possibilities should let the user
    configure the ports from the plugin GUI, and call
    clap_host_audio_ports.rescan(CLAP_AUDIO_PORTS_RESCAN_ALL).
  */

  //----------

  /*
    Rescan the full list of configs.
    [main-thread]
  */

  void audio_ports_config_rescan() {
    MHostAudioPortsConfig->rescan(MClapHost);
  }

  //--------------------
  // audio-ports
  //--------------------

  /*
    This extension provides a way for the plugin to describe its current audio
    ports.
    The plugin is only allowed to change its ports configuration while it is
    deactivated.
  */

  //----------

  /*
    [main-thread]
  */

  uint32_t audio_ports_get_preferred_sample_size() {
    return MHostAudioPorts->get_preferred_sample_size(MClapHost);
  }

  /*
    Rescan the full list of audio ports according to the flags.
    [main-thread]

    CLAP_AUDIO_PORTS_RESCAN_ALL
    CLAP_AUDIO_PORTS_RESCAN_NAMES

   The ports have changed, the host shall perform a full scan of the ports.
   This flag can only be used if the plugin is not active.
   If the plugin active, call host->request_restart() and then call rescan()
   when the host calls deactivate()
  */

  void audio_ports_rescan(uint32_t flags) {
    MHostAudioPorts->rescan(MClapHost,flags);
  }

  //--------------------
  // event-filter
  //--------------------

  /*
    This extension lets the host know which event types the plugin is
    interested in.
  */

  //----------

  /*
    [main-thread]
  */

  void event_filter_changed() {
    MHostEventFilter->changed(MClapHost);
  }

  //--------------------
  // fd-support
  //--------------------

  // [main-thread]

  bool fd_support_register_fd(clap_fd fd, clap_fd_flags flags) {
    return MHostFdSupport->register_fd(MClapHost,fd,flags);
  }

  // [main-thread]

  bool fd_support_modify_fd(clap_fd fd, clap_fd_flags flags) {
    return MHostFdSupport->modify_fd(MClapHost,fd,flags);
  }

  // [main-thread]

  bool fd_support_unregister_fd(clap_fd fd) {
    return MHostFdSupport->unregister_fd(MClapHost,fd);
  }

  //--------------------
  // gui
  //--------------------

  /*
    Request the host to resize the client area to width, height.
    Return true on success, false otherwise.
     [thread-safe]
  */

  bool gui_resize(uint32_t width, uint32_t height) {
    return MHostGui->resize(MClapHost,width,height);
  }

  //--------------------
  // latency
  //--------------------

  // Tell the host that the latency changed.
  // The latency is only allowed to change if the plugin is deactivated.
  // If the plugin is activated, call host->request_restart()
  // [main-thread]

  void latency_changed() {
    MHostLatency->changed(MClapHost);
  }

  //--------------------
  // log
  //--------------------

  // Log a message through the host.
  // [thread-safe]

  void log(clap_log_severity severity, const char *msg) {
    MHostLog->log(MClapHost,severity,msg);
  }

  //--------------------
  // note-name
  //--------------------

  // Informs the host that the note names has changed.
  // [main-thread]

  void note_name_changed() {
    MHostNoteName->changed(MClapHost);
  }

  //--------------------
  // params
  //--------------------

  /*
    Rescan the full list of parameters according to the flags.
    [main-thread]

    CLAP_PARAM_RESCAN_VALUES
    CLAP_PARAM_RESCAN_TEXT
    CLAP_PARAM_RESCAN_INFO
    CLAP_PARAM_RESCAN_ALL
  */

  void params_rescan(clap_param_rescan_flags flags) {
    MHostParams->rescan(MClapHost,flags);
  }

  /*
    Clears references to a parameter
    [main-thread]

    CLAP_PARAM_CLEAR_ALL
    CLAP_PARAM_CLEAR_AUTOMATIONS
    CLAP_PARAM_CLEAR_MODULATIONS
  */

  void params_clear(clap_id param_id, clap_param_clear_flags flags) {
    MHostParams->clear(MClapHost,param_id,flags);
  }

  /*
    Request the host to call clap_plugin_params->flush().
    This is useful if the plugin has parameters value changes to report to the
    host but the plugin is not processing.
    eg. the plugin has a USB socket to some hardware controllers and receives a
    parameter change while it is not processing.
    This must not be called on the [audio-thread].
    [thread-safe]
  */

  void params_request_flush() {
    MHostParams->request_flush(MClapHost);
  }

  //--------------------
  // state
  //--------------------

  /*
    Tell the host that the plugin state has changed and should be saved again.
    If a parameter value changes, then it is implicit that the state is dirty.
    [main-thread]
  */

  void state_mark_dirty() {
    MHostState->mark_dirty(MClapHost);
  }

  //--------------------
  // thread-check
  //--------------------

  /*
    This interface is useful to do runtime checks and make
    sure that the functions are called on the correct threads.
    It is highly recommended to implement this extension
  */

  //----------

  /*
    Returns true if "this" thread is the main thread.
    [thread-safe]
  */

  bool thread_check_is_main_thread() {
    return MHostThreadCheck->is_main_thread(MClapHost);
  }

  /*
    Returns true if "this" thread is one of the audio threads.
    [thread-safe]
  */

  bool thread_check_is_audio_thread() {
    return MHostThreadCheck->is_audio_thread(MClapHost);
  }

  //--------------------
  // timer-support
  //--------------------

  /*
    Registers a periodic timer.
    The host may adjust the period if it is under a certain threshold.
    30 Hz should be allowed.
    [main-thread]
  */

  bool timer_support_register_timer(uint32_t period_ms, clap_id *timer_id) {
    return MHostTimerSupport->register_timer(MClapHost,period_ms,timer_id);
  }

  /*
    [main-thread]
  */

  bool timer_support_unregister_timer(clap_id timer_id) {
    return MHostTimerSupport->unregister_timer(MClapHost,timer_id);
  }

};

//----------------------------------------------------------------------
#endif
