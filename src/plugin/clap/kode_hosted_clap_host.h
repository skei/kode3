

#if 0

#ifndef host_included
#define host_included
//----------------------------------------------------------------------

/*
  clap_host
  HostedPluginHost
*/

#include "clap/all.h"

//----------------------------------------------------------------------

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class Host {

//------------------------------
private:
//------------------------------

  struct clap_host MClapHost = {
    CLAP_VERSION,
    this,
    "clap-test",
    "Tor-Helge Skei",
    "https://torhelgeskei.com",
    "0.0.1",
    clap_host_get_extension_callback,
    clap_host_request_restart_callback,
    clap_host_request_process_callback,
    clap_host_request_callback_callback
  };

//------------------------------
public:
//------------------------------

  Host() {
  }

  //----------

  ~Host() {
  }

  //----------

  clap_host* getClapHost() {
    return &MClapHost;
  }

//------------------------------------------------------------
private: // extensions
//------------------------------------------------------------

/*
  TODO: implement (fill in) empty methods...
*/

//------------------------------------------------------------

  //--------------------
  // clap_host
  //--------------------

  const void* clap_host_get_extension(const char *extension_id) {
    printf("> clap_host_get_extension(%s)\n",extension_id);
    if (strcmp(extension_id,CLAP_EXT_AUDIO_PORTS) == 0)     { return &MClapHostAudioPorts; }
    if (strcmp(extension_id,CLAP_EXT_EVENT_FILTER) == 0)    { return &MClapHostEventFilter; }
    if (strcmp(extension_id,CLAP_EXT_FD_SUPPORT) == 0)      { return &MClapHostFdSupport; }
    if (strcmp(extension_id,CLAP_EXT_FILE_REFERENCE) == 0)  { return &MClapHostFileReference; }
    if (strcmp(extension_id,CLAP_EXT_GUI) == 0)             { return &MClapHostGui; }
    if (strcmp(extension_id,CLAP_EXT_LATENCY) == 0)         { return &MClapHostLatency; }
    if (strcmp(extension_id,CLAP_EXT_LOG) == 0)             { return &MClapHostLog; }
    if (strcmp(extension_id,CLAP_EXT_NOTE_NAME) == 0)       { return &MClapHostNoteName; }
    if (strcmp(extension_id,CLAP_EXT_PARAMS) == 0)          { return &MClapHostParams; }
    if (strcmp(extension_id,CLAP_EXT_QUICK_CONTROLS) == 0)  { return &MClapHostQuickControls; }
    if (strcmp(extension_id,CLAP_EXT_STATE) == 0)           { return &MClapHostState; }
    if (strcmp(extension_id,CLAP_EXT_THREAD_CHECK) == 0)    { return &MClapHostThreadCheck; }
    if (strcmp(extension_id,CLAP_EXT_THREAD_POOL) == 0)     { return &MClapHostThreadPool; }
    if (strcmp(extension_id,CLAP_EXT_TIMER_SUPPORT) == 0)   { return &MClapHostTimerSupport; }
    if (strcmp(extension_id,CLAP_EXT_TRACK_INFO) == 0)      { return &MClapHostTrackInfo; }
    return NULL;
  }

  //----------

  void clap_host_request_restart() {
    printf("> clap_host_request_restart()\n");
  }

  //----------

  void clap_host_request_process() {
    printf("> clap_host_request_process()\n");
  }

  //----------

  void clap_host_request_callback() {
    printf("> clap_host_request_callback()\n");
  }

  //--------------------
  // clap.audio-ports
  //--------------------

  uint32_t clap_host_audio_ports_get_preferred_sample_size() {
    printf("> audio-ports.getPreferredSampleSize() -> 32\n");
    return 32;
  }

  void clap_host_audio_ports_rescan(uint32_t flags) {
    printf("> audio-ports.rescan(%i)\n",flags);
  }

  //--------------------
  // clap.event_filter
  //--------------------

  void clap_host_event_filter_changed() {
    printf("> event-filter.changed()\n");
  }

  //--------------------
  // clap.fd-support
  //--------------------

  bool clap_host_fd_support_register_fd(clap_fd fd, clap_fd_flags flags) {
    printf("> fd-support.registerFd(%i)\n",flags);
    return false;
  }

  bool clap_host_fd_support_modify_fd(clap_fd fd, clap_fd_flags flags) {
    printf("> fd-support.modify(%i)\n",flags);
    return false;
  }

  bool clap_host_fd_support_unregister_fd(clap_fd fd) {
    printf("> fd-support.unregisterFd()\n");
    return false;
  }

  //--------------------
  // clap.file-reference.draft/0
  //--------------------

  void clap_host_file_reference_changed() {
    printf("> file-reference.changed()\n");
  }

  void clap_host_file_reference_set_dirty(clap_id resource_id) {
    printf("> file-reference.setDirty(%i)\n",resource_id);
  }

  //--------------------
  // clap.gui
  //--------------------

  bool clap_host_gui_resize(uint32_t width, uint32_t height) {
    printf("> gui.resize(%i,%i)\n",width,height);
    return false;
  }

  //--------------------
  // clap.latency
  //--------------------

  void clap_host_latency_changed() {
    printf("> latency.changed()\n");
  }

  //--------------------
  // clap.log
  //--------------------

  void clap_host_log_log(clap_log_severity severity, const char *msg) {
    printf("> log.log(%i,%s)\n",severity,msg);
  }

  //--------------------
  // clap.note-name
  //--------------------

  void clap_host_note_name_changed() {
    printf("> note-name.changed()\n");
  }

  //--------------------
  // clap.params
  //--------------------

  void clap_host_params_rescan(clap_param_rescan_flags flags) {
    printf("> params.rescan(%i)\n",flags);
  }

  void clap_host_params_clear(clap_id param_id, clap_param_clear_flags flags) {
    printf("> params.clear(%i,%i)\n",param_id,flags);
  }

  void clap_host_params_request_flush() {
    printf("> params.requestFlush()\n");
  }

  //--------------------
  // clap.quick-controls.draft/0
  //--------------------

  void clap_host_quick_controls_changed(clap_quick_controls_changed_flags flags) {
    printf("> quick-controls.changed(%i)\n",flags);
  }

  //--------------------
  // clap.state
  //--------------------

  void clap_host_state_mark_dirty() {
    printf("> state.markDirty()\n");
  }

  //--------------------
  // clap.thread-check
  //--------------------

  bool clap_host_thread_check_is_main_thread() {
    //printf("> thread-check.isMainThread() -> true\n");
    return true;
  }

  bool clap_host_thread_check_is_audio_thread() {
    //printf("> thread-check.isAudioThread() -> true\n");
    return true;
  }

  //--------------------
  // clap.thread-pool.draft/0
  //--------------------

  bool clap_host_thread_pool_request_exec(uint32_t num_tasks) {
    printf("> thread-pool.requestExec(%i)\n",num_tasks);
    return false;
  }

  //--------------------
  // clap.timer-support
  //--------------------

  bool clap_host_timer_support_register_timer(uint32_t period_ms, clap_id *timer_id) {
    printf("> timer-support.registerTimer(%i)\n",period_ms);
    return false;
  }

  bool clap_host_timer_support_unregister_timer(clap_id timer_id) {
    printf("> timer-support.unregisterTimer(%i)\n",timer_id);
    return false;
  }

  //--------------------
  // clap.track-info.draft/0
  //--------------------

  bool clap_host_track_info_get(clap_track_info *info) {
    printf("> track-info.get()\n");
    return false;
  }

//------------------------------------------------------------
private: // callbacks
//------------------------------------------------------------

/*
  callbacks
  trampoline into the Host class..
*/

//------------------------------------------------------------

  // clap_host

  static const void* clap_host_get_extension_callback(const struct clap_host* host, const char* extension_id) {
    Host* testhost = (Host*)host->host_data;
    return testhost->clap_host_get_extension(extension_id);
  }

  static void clap_host_request_restart_callback(const struct clap_host* host) {
    Host* testhost = (Host*)host->host_data;
    testhost->clap_host_request_restart();
  }

  static void clap_host_request_process_callback(const struct clap_host* host) {
    Host* testhost = (Host*)host->host_data;
    testhost->clap_host_request_process();
  }

  static void clap_host_request_callback_callback(const struct clap_host* host) {
    Host* testhost = (Host*)host->host_data;
    testhost->clap_host_request_callback();
  }

  // clap.audio-ports

  static uint32_t clap_host_audio_ports_get_preferred_sample_size_callback(const clap_host* host) {
    Host* testhost = (Host*)host->host_data;
    return testhost->clap_host_audio_ports_get_preferred_sample_size();
  }

  static void clap_host_audio_ports_rescan_callback(const clap_host* host, uint32_t flags) {
    Host* testhost = (Host*)host->host_data;
    testhost->clap_host_audio_ports_rescan(flags);
  }

  // clap.event_filter

  static void clap_host_event_filter_changed_callback(const clap_host* host) {
    Host* testhost = (Host*)host->host_data;
    testhost->clap_host_event_filter_changed();
  }

  // clap.fd-support

  static bool clap_host_fd_support_register_fd_callback(const clap_host* host, clap_fd fd, clap_fd_flags flags) {
    Host* testhost = (Host*)host->host_data;
    return testhost->clap_host_fd_support_register_fd(fd,flags);
  }

  static bool clap_host_fd_support_modify_fd_callback(const clap_host* host, clap_fd fd, clap_fd_flags flags) {
    Host* testhost = (Host*)host->host_data;
    return testhost->clap_host_fd_support_modify_fd(fd,flags);
  }

  static bool clap_host_fd_support_unregister_fd_callback(const clap_host* host, clap_fd fd) {
    Host* testhost = (Host*)host->host_data;
    return testhost->clap_host_fd_support_unregister_fd(fd);
  }

  // clap.file-reference.draft/0

  static void clap_host_file_reference_changed_callback(const clap_host* host) {
    Host* testhost = (Host*)host->host_data;
    testhost->clap_host_file_reference_changed();
  }

  static void clap_host_file_reference_set_dirty_callback(const clap_host* host, clap_id resource_id) {
    Host* testhost = (Host*)host->host_data;
    testhost->clap_host_file_reference_set_dirty(resource_id);
  }

  // clap.gui

  static bool clap_host_gui_resize_callback(const clap_host* host, uint32_t width, uint32_t height) {
    Host* testhost = (Host*)host->host_data;
    return testhost->clap_host_gui_resize(width,height);
  }

  // clap.latency

  static void clap_host_latency_changed_callback(const clap_host* host) {
    Host* testhost = (Host*)host->host_data;
    testhost->clap_host_latency_changed();
  }

  // clap.log

  static void clap_host_log_log_callback(const clap_host* host, clap_log_severity severity, const char *msg) {
    Host* testhost = (Host*)host->host_data;
    testhost->clap_host_log_log(severity,msg);
  }

  // clap.note-name

  static void clap_host_note_name_changed_callback(const clap_host* host) {
    Host* testhost = (Host*)host->host_data;
    testhost->clap_host_note_name_changed();
  }

  // clap.params

  static void clap_host_params_rescan_callback(const clap_host* host, clap_param_rescan_flags flags) {
    Host* testhost = (Host*)host->host_data;
    testhost->clap_host_params_rescan(flags);
  }

  static void clap_host_params_clear_callback(const clap_host* host, clap_id param_id, clap_param_clear_flags flags) {
    Host* testhost = (Host*)host->host_data;
    testhost->clap_host_params_clear(param_id,flags);
  }

  static void clap_host_params_request_flush_callback(const clap_host* host) {
    Host* testhost = (Host*)host->host_data;
    testhost->clap_host_params_request_flush();
  }

  // clap.quick-controls.draft/0

  static void clap_host_quick_controls_changed_callback(const clap_host* host, clap_quick_controls_changed_flags flags) {
    Host* testhost = (Host*)host->host_data;
    testhost->clap_host_quick_controls_changed(flags);
  }

  // clap.state

  static void clap_host_state_mark_dirty_callback(const clap_host* host) {
    Host* testhost = (Host*)host->host_data;
    testhost->clap_host_state_mark_dirty();
  }

  // clap.thread-check

  static bool clap_host_thread_check_is_main_thread_callback(const clap_host* host) {
    Host* testhost = (Host*)host->host_data;
    return testhost->clap_host_thread_check_is_main_thread();
  }

  static bool clap_host_thread_check_is_audio_thread_callback(const clap_host* host) {
    Host* testhost = (Host*)host->host_data;
    return testhost->clap_host_thread_check_is_audio_thread();
  }

  // clap.thread-pool.draft/0

  static bool clap_host_thread_pool_request_exec_callback(const clap_host* host, uint32_t num_tasks) {
    Host* testhost = (Host*)host->host_data;
    return testhost->clap_host_thread_pool_request_exec(num_tasks);
  }

  // clap.timer-support

  static bool clap_host_timer_support_register_timer_callback(const clap_host* host, uint32_t period_ms, clap_id* timer_id) {
    Host* testhost = (Host*)host->host_data;
    return testhost->clap_host_timer_support_register_timer(period_ms,timer_id);
  }

  static bool clap_host_timer_support_unregister_timer_callback(const clap_host* host, clap_id timer_id) {
    Host* testhost = (Host*)host->host_data;
    return testhost->clap_host_timer_support_unregister_timer(timer_id);
  }

  // clap.track-info.draft/0

  static bool clap_host_track_info_get_callback(const clap_host* host, clap_track_info* info) {
    Host* testhost = (Host*)host->host_data;
    return testhost->clap_host_track_info_get(info);
  }

//------------------------------
private:
//------------------------------

  // If the plugin does not implement this extension, it will have a stereo
  // input and output.

  struct clap_host_audio_ports MClapHostAudioPorts = {
    clap_host_audio_ports_get_preferred_sample_size_callback,
    clap_host_audio_ports_rescan_callback
  };

  struct clap_host_event_filter MClapHostEventFilter = {
    clap_host_event_filter_changed_callback
  };

  struct clap_host_fd_support MClapHostFdSupport = {
    clap_host_fd_support_register_fd_callback,
    clap_host_fd_support_modify_fd_callback,
    clap_host_fd_support_unregister_fd_callback
  };

  struct clap_host_file_reference MClapHostFileReference = {
    clap_host_file_reference_changed_callback,
    clap_host_file_reference_set_dirty_callback
  };

  struct clap_host_gui MClapHostGui = {
    clap_host_gui_resize_callback
  };

  struct clap_host_latency MClapHostLatency = {
    clap_host_latency_changed_callback
  };

  struct clap_host_log MClapHostLog = {
    clap_host_log_log_callback
  };

  struct clap_host_note_name MClapHostNoteName = {
    clap_host_note_name_changed_callback
  };

  struct clap_host_params MClapHostParams = {
    clap_host_params_rescan_callback,
    clap_host_params_clear_callback,
    clap_host_params_request_flush_callback
  };

  struct clap_host_quick_controls MClapHostQuickControls = {
    clap_host_quick_controls_changed_callback
  };

  struct clap_host_state MClapHostState = {
    clap_host_state_mark_dirty_callback
  };

  struct clap_host_thread_check MClapHostThreadCheck = {
    clap_host_thread_check_is_main_thread_callback,
    clap_host_thread_check_is_audio_thread_callback
  };

  struct clap_host_timer_support MClapHostTimerSupport = {
    clap_host_timer_support_register_timer_callback,
    clap_host_timer_support_unregister_timer_callback
  };

  struct clap_host_thread_pool MClapHostThreadPool = {
    clap_host_thread_pool_request_exec_callback
  };

  struct clap_host_track_info MClapHostTrackInfo = {
    clap_host_track_info_get_callback
  };

  //----------

};

//----------------------------------------------------------------------
#endif

#endif // 0
