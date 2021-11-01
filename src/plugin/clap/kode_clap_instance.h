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

  KODE_Instance*    MInstance = nullptr;
  const clap_host*  MClapHost = nullptr;

//------------------------------
public:
//------------------------------

  /*
    NOTE_CLAP:
      is host_data for host usage, or for plugin usage?
      should we stay away?
  */

  KODE_ClapInstance(const clap_host *host, KODE_Instance* AInstance) {
    KODE_PRINT;
    MClapHost = host;
    MInstance = AInstance;
  }

  //----------

  ~KODE_ClapInstance() {
    KODE_PRINT;
  }

//------------------------------
public: // instance
//------------------------------

  /*
    Must be called after creating the plugin.
    If init returns false, the host must destroy the plugin instance.
  */

  bool clap_instance_init() {
    KODE_PRINT;
    return false;
  }

  //----------

  /*
    Free the plugin and its resources.
    It is not required to deactivate the plugin prior to this call.
  */

  void clap_instance_destroy() {
    KODE_PRINT;
  }

  //----------

  /*
    activation
    [main-thread]
  */

  bool clap_instance_activate(double sample_rate) {
    KODE_PRINT;
    return false;
  }

  //----------

  /*
    deactivation
    [main-thread]
  */

  void clap_instance_deactivate() {
    KODE_PRINT;
  }

  //----------

  /*
    Set to true before processing
    (and to false before sending the plugin to sleep)
    [audio-thread]

    NOTE_CLAP: clarify documentation/comments
  */

  bool clap_instance_start_processing() {
    KODE_PRINT;
    return false;
  }

  //----------

  /*
    (Set to true before processing)
    and to false before sending the plugin to sleep.
    [audio-thread]
  */

  void clap_instance_stop_processing() {
    KODE_PRINT;
  }


  //----------

  /*
    process audio, events, ...
    [audio-thread]
  */

  clap_process_status clap_instance_process(const clap_process *process) {
    //KODE_PRINT;
    return CLAP_PROCESS_ERROR;
  }

  //----------

  /*
    Query an extension.
    The returned pointer is owned by the plugin.
    [thread-safe]
  */

  const void* clap_instance_get_extension(const char *id) {
    KODE_Print("id: %s\n",id);
    if (strcmp(id,CLAP_EXT_AUDIO_PORTS) == 0)     return &MClapPluginAudioPorts;
    if (strcmp(id,CLAP_EXT_EVENT_FILTER) == 0)    return &MClapPluginEventFilter;
    if (strcmp(id,CLAP_EXT_GUI) == 0)             return &MClapPluginGui;
    if (strcmp(id,CLAP_EXT_GUI_X11) == 0)         return &MClapPluginGuiX11;
    if (strcmp(id,CLAP_EXT_PARAMS) == 0)          return &MClapPluginParams;
    if (strcmp(id,CLAP_EXT_STATE) == 0)           return &MClapPluginState;
    if (strcmp(id,CLAP_EXT_TIMER_SUPPORT) == 0)   return &MClapPluginTimerSupport;
    return nullptr;
  }

  //----------

  /*
    Called by the host on the main thread in response to a previous call to:
    host->request_callback(host);
    [main-thread]
  */

  void clap_instance_on_main_thread() {
    KODE_PRINT;
  }

//------------------------------
public:
//------------------------------

  //clap_audio_ports_count
  //clap_audio_ports_get

  //clap_audio_ports_config_count
  //clap_audio_ports_config_get
  //clap_audio_ports_config_select

  //clap_event_filter accepts

  //clap_gui_create_callback,
  //clap_gui_destroy_callback,
  //clap_gui_set_scale_callback,
  //clap_gui_get_size_callback,
  //clap_gui_can_resize_callback,
  //clap_gui_round_size_callback,
  //clap_gui_set_size_callback,
  //clap_gui_show_callback,
  //clap_gui_hide_callback,

  //clap_gui_x11_attach_callback,

  //clap_params_count_callback,
  //clap_params_get_info_callback,
  //clap_params_get_value_callback,
  //clap_params_value_to_text_callback,
  //clap_params_text_to_value_callback,
  //clap_params_flush_callback

  //clap_render_set_callback

//------------------------------
public:
//------------------------------

//------------------------------
private:
//------------------------------

  const clap_plugin_audio_ports MClapPluginAudioPorts = {
    //clap_audio_ports_count
    //clap_audio_ports_get
  };

  const clap_plugin_audio_ports_config MClapPluginAudioPortsConfig = {
    //clap_audio_ports_config_count
    //clap_audio_ports_config_get
    //clap_audio_ports_config_select
  };

  const clap_plugin_event_filter MClapPluginEventFilter = {
    //clap_event_filter accepts
  };

  const clap_plugin_gui MClapPluginGui = {
    //clap_gui_create_callback,
    //clap_gui_destroy_callback,
    //clap_gui_set_scale_callback,
    //clap_gui_get_size_callback,
    //clap_gui_can_resize_callback,
    //clap_gui_round_size_callback,
    //clap_gui_set_size_callback,
    //clap_gui_show_callback,
    //clap_gui_hide_callback,
  };

  const clap_plugin_gui_x11 MClapPluginGuiX11 = {
    //clap_gui_x11_attach_callback,
  };

  const clap_plugin_params MClapPluginParams = {
    //clap_params_count_callback,
    //clap_params_get_info_callback,
    //clap_params_get_value_callback,
    //clap_params_value_to_text_callback,
    //clap_params_text_to_value_callback,
    //clap_params_flush_callback
  };

  const clap_plugin_render MClapPluginRender = {
    //clap_render_set_callback
  };

  const clap_plugin_state MClapPluginState = {
    clap_state_save_callback,
    clap_state_load_callback
  };

  const clap_plugin_timer_support MClapPluginTimerSupport = {
    clap_timer_callback,
  };

//------------------------------
private:
//------------------------------

  //clap_audio_ports_count
  //clap_audio_ports_get

  //clap_audio_ports_config_count
  //clap_audio_ports_config_get
  //clap_audio_ports_config_select

  //clap_event_filter accepts

  //clap_gui_create_callback,
  //clap_gui_destroy_callback,
  //clap_gui_set_scale_callback,
  //clap_gui_get_size_callback,
  //clap_gui_can_resize_callback,
  //clap_gui_round_size_callback,
  //clap_gui_set_size_callback,
  //clap_gui_show_callback,
  //clap_gui_hide_callback,

  //clap_gui_x11_attach_callback,

  //clap_params_count_callback,
  //clap_params_get_info_callback,
  //clap_params_get_value_callback,
  //clap_params_value_to_text_callback,
  //clap_params_text_to_value_callback,
  //clap_params_flush_callback

  //clap_render_set_callback

  //----------

  static
  bool clap_state_save_callback(const clap_plugin *plugin, clap_ostream *stream) {
    //KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    //if (instance) return instance->clap_instance_state_save(stream);
    return false;
  }

  //----------

  static
  bool clap_state_load_callback(const clap_plugin *plugin, clap_istream *stream) {
    //KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    //if (instance) return instance->clap_instance_state_load(stream);
    return false;
  }

  //----------

  static
  void clap_timer_callback(const clap_plugin *plugin, clap_id timer_id) {
    //KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    //if (instance) instance->clap_instance_timer(stream);
  }

};

//----------------------------------------------------------------------
#endif
