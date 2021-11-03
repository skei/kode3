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
    we must delete AInstance
  */

  KODE_ClapInstance(const clap_host *host, KODE_Instance* AInstance) {
    MClapHost = host;
    MInstance = AInstance;
  }

  //----------

  ~KODE_ClapInstance() {
    //if (MInstance) delete MInstance; // ?????
  }

//------------------------------
public: // instance
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

    NOTE_CLAP: clarify documentation/comments
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
    if (strcmp(id,CLAP_EXT_AUDIO_PORTS        ) == 0) return &MClapPluginAudioPorts;
    if (strcmp(id,CLAP_EXT_AUDIO_PORTS_CONFIG ) == 0) return &MClapPluginAudioPortsConfig;
    if (strcmp(id,CLAP_EXT_EVENT_FILTER       ) == 0) return &MClapPluginEventFilter;
    if (strcmp(id,CLAP_EXT_GUI                ) == 0) return &MClapPluginGui;
    if (strcmp(id,CLAP_EXT_GUI_X11            ) == 0) return &MClapPluginGuiX11;
    if (strcmp(id,CLAP_EXT_PARAMS             ) == 0) return &MClapPluginParams;
    if (strcmp(id,CLAP_EXT_STATE              ) == 0) return &MClapPluginState;
    if (strcmp(id,CLAP_EXT_TIMER_SUPPORT      ) == 0) return &MClapPluginTimerSupport;
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
private: // audio-ports
//------------------------------

  /*
    number of ports, for either input or output
    [main-thread]
  */

  uint32_t clap_audio_ports_count(bool is_input) {
    return 0;
  }

  /*
    get info about about an audio port.
    [main-thread]
  */

  bool clap_audio_ports_get(uint32_t index, bool is_input, clap_audio_port_info* info) {
    return false;
  }

//------------------------------
private: // audio-ports-config
//------------------------------

  /*
    gets the number of available configurations
    [main-thread]
  */

  uint32_t clap_audio_ports_config_count() {
    return 0;
  }

  /*
    gets information about a configuration
    [main-thread]
  */

  bool clap_audio_ports_config_get(uint32_t index, clap_audio_ports_config *config) {
    return false;
  }

  /*
    selects the configuration designated by id
    returns true if the configuration could be applied
    [main-thread,plugin-deactivated]
  */

  bool clap_audio_ports_config_select(clap_id config_id) {
    return false;
  }

//------------------------------
private: // event-filter
//------------------------------

  /*
    Returns true if the plugin is interested in the given event type.
    [main-thread]
  */

  bool clap_event_filter(clap_event_type event_type) {
    return false;
  }

//------------------------------
private: // gui
//------------------------------

  /*
    Create and allocate all resources necessary for the gui.
    After this call, the GUI is ready to be shown but it is not yet visible.
    [main-thread]
  */

  bool clap_gui_create() {
    return false;
  }

  /*
    Free all resources associated with the gui.
    [main-thread]
  */

  void clap_gui_destroy() {
  }

  /*
    Set the absolute GUI scaling factor.
    [main-thread]
  */

  void clap_gui_set_scale(double scale) {
  }

  /*
    Get the current size of the plugin UI, with the scaling applied.
    clap_plugin_gui->create() must have been called prior to asking the size.
    [main-thread]
  */

  bool clap_gui_get_size(uint32_t *width, uint32_t *height) {
    return false;
  }

  /*
    [main-thread]
  */

  bool clap_gui_can_resize() {
    return false;
  }

  /*
    If the plugin gui is resizable, then the plugin will calculate the closest
    usable size to the given arguments.
    The scaling is applied.
    This method does not change the size.

    [main-thread]
  */

  void clap_gui_round_size(uint32_t *width, uint32_t *height) {
  }

  /*
    Sets the window size
    Returns true if the size is supported.
    [main-thread]
  */

  bool clap_gui_set_size(uint32_t width, uint32_t height) {
    return false;
  }

  /*
    Show the window.
    [main-thread]
  */

  void clap_gui_show() {
  }

  /*
    Hide the window, this method do not free the resources, it just hides
    the window content. Yet it maybe a good idea to stop painting timers.
    [main-thread]
  */

  void clap_gui_hide() {
  }

//------------------------------
private: // gui-x11
//------------------------------

  /*
    Use the protocol XEmbed
    [main-thread]
  */

  bool clap_gui_x11_attach(const char* display_name, unsigned long window) {
    return false;
  }

//------------------------------
private: // params
//------------------------------

  /*
    Returns the number of parameters.
    [main-thread]
  */

  uint32_t clap_params_count() {
    return 0;
  }

  /*
    Copies the parameter's info to param_info and returns true on success.
    [main-thread]
  */

  bool clap_params_get_info(int32_t param_index, clap_param_info *param_info) {
    return false;
  }

  /*
    Gets the parameter plain value.
    [main-thread]
  */

  bool clap_params_get_value(clap_id param_id, double *value) {
    return false;
  }

  /*
    Formats the display text for the given parameter value.
    [main-thread]
  */

  bool clap_params_value_to_text(clap_id param_id, double value, char *display, uint32_t size) {
    return false;
  }

  /*
    Converts the display text to a parameter value.
    [main-thread]
  */

  bool clap_params_text_to_value(clap_id param_id, const char* display, double* value) {
    return false;
  }

  /*
    Flushes a set of parameter changes.
    This method must not be called concurrently to clap_plugin->process().
    This method must not be used if the plugin is processing.

    [active && !processing : audio-thread]
    [!active : main-thread]
  */

  void clap_params_flush(const clap_event_list *input_parameter_changes, const clap_event_list *output_parameter_changes) {
  }

//------------------------------
private: // render
//------------------------------

  /*
    The render extension is used to let the plugin know if it has "realtime"
    pressure to process.
    If this information does not influence your rendering code, then don't
    implement this extension.
  */

  /*
    [main-thread]
  */

  void clap_render_set(clap_plugin_render_mode mode) {
  }

//------------------------------
private: // state
//------------------------------

  /*
    Saves the plugin state into stream.
    Returns true if the state was correctly saved.
    [main-thread]
  */

  bool clap_state_save(clap_ostream *stream) {
    return false;
  }

  /*
    Loads the plugin state from stream.
    Returns true if the state was correctly restored.
    [main-thread]
  */

  bool clap_state_load(clap_istream *stream) {
    return false;
  }

//------------------------------
private: // timer-support
//------------------------------

  /*
    [main-thread]
  */

  void clap_timer_on_timer(clap_id timer_id) {
  }

//------------------------------
private:
//------------------------------

  const clap_plugin_audio_ports MClapPluginAudioPorts = {
    clap_audio_ports_count_callback,
    clap_audio_ports_get_callback
  };

  const clap_plugin_audio_ports_config MClapPluginAudioPortsConfig = {
    clap_audio_ports_config_count_callback,
    clap_audio_ports_config_get_callback,
    clap_audio_ports_config_select_callback
  };

  const clap_plugin_event_filter MClapPluginEventFilter = {
    clap_event_filter_callback
  };

  const clap_plugin_gui MClapPluginGui = {
    clap_gui_create_callback,
    clap_gui_destroy_callback,
    clap_gui_set_scale_callback,
    clap_gui_get_size_callback,
    clap_gui_can_resize_callback,
    clap_gui_round_size_callback,
    clap_gui_set_size_callback,
    clap_gui_show_callback,
    clap_gui_hide_callback
  };

  const clap_plugin_gui_x11 MClapPluginGuiX11 = {
    clap_gui_x11_attach_callback
  };

  const clap_plugin_params MClapPluginParams = {
    clap_params_count_callback,
    clap_params_get_info_callback,
    clap_params_get_value_callback,
    clap_params_value_to_text_callback,
    clap_params_text_to_value_callback,
    clap_params_flush_callback
  };

  const clap_plugin_render MClapPluginRender = {
    clap_render_set_callback
  };

  const clap_plugin_state MClapPluginState = {
    clap_state_save_callback,
    clap_state_load_callback
  };

  const clap_plugin_timer_support MClapPluginTimerSupport = {
    clap_timer_on_timer_callback,
  };

//------------------------------
private:
//------------------------------

  static uint32_t clap_audio_ports_count_callback(const clap_plugin* plugin, bool is_input) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_audio_ports_count(is_input);
  }

  static bool clap_audio_ports_get_callback(const clap_plugin* plugin, uint32_t index, bool is_input, clap_audio_port_info* info) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_audio_ports_get(index,is_input,info);
  }

  //----------

  static uint32_t clap_audio_ports_config_count_callback(const clap_plugin *plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_audio_ports_config_count();
  }

  static bool clap_audio_ports_config_get_callback(const clap_plugin *plugin, uint32_t index, clap_audio_ports_config *config) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_audio_ports_config_get(index,config);
  }

  static bool clap_audio_ports_config_select_callback(const clap_plugin *plugin, clap_id config_id) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_audio_ports_config_select(config_id);
  }

  //----------

  static bool clap_event_filter_callback(const clap_plugin *plugin, clap_event_type event_type) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_event_filter(event_type);
  }

  //----------

  static bool clap_gui_create_callback(const clap_plugin *plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_gui_create();
  }

  static void clap_gui_destroy_callback(const clap_plugin *plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_gui_destroy();
  }

  static void clap_gui_set_scale_callback(const clap_plugin *plugin, double scale) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_gui_set_scale(scale);
  }

  static bool clap_gui_get_size_callback(const clap_plugin *plugin, uint32_t *width, uint32_t *height) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_gui_get_size(width,height);
  }

  static bool clap_gui_can_resize_callback(const clap_plugin *plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_gui_can_resize();
  }

  static void clap_gui_round_size_callback(const clap_plugin *plugin, uint32_t *width, uint32_t *height) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_gui_round_size(width,height);
  }

  static bool clap_gui_set_size_callback(const clap_plugin *plugin, uint32_t width, uint32_t height) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_gui_set_size(width,height);
  }

  static void clap_gui_show_callback(const clap_plugin *plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_gui_show();
  }

  static void clap_gui_hide_callback(const clap_plugin *plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_gui_hide();
  }

  //----------

  static bool clap_gui_x11_attach_callback(const clap_plugin* plugin, const char* display_name, unsigned long window) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_gui_x11_attach(display_name,window);
  }

  //----------

  static uint32_t clap_params_count_callback(const clap_plugin *plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_params_count();
  }

  static bool clap_params_get_info_callback(const clap_plugin *plugin, int32_t param_index, clap_param_info *param_info) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_params_get_info(param_index,param_info);
  }

  static bool clap_params_get_value_callback(const clap_plugin *plugin, clap_id param_id, double *value) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_params_get_value(param_id,value);
  }

  static bool clap_params_value_to_text_callback(const clap_plugin *plugin, clap_id param_id, double value, char *display, uint32_t size) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_params_value_to_text(param_id,value,display,size);
  }

  static bool clap_params_text_to_value_callback(const clap_plugin *plugin, clap_id param_id, const char* display, double* value) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_params_text_to_value(param_id,display,value);
  }

  static void clap_params_flush_callback(const clap_plugin* plugin, const clap_event_list *input_parameter_changes, const clap_event_list *output_parameter_changes) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_params_flush(input_parameter_changes,output_parameter_changes);
  }

  //----------

  static void clap_render_set_callback(const clap_plugin *plugin, clap_plugin_render_mode mode) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_render_set(mode);
  }

  //----------

  static bool clap_state_save_callback(const clap_plugin *plugin, clap_ostream *stream) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_state_save(stream);
  }

  static bool clap_state_load_callback(const clap_plugin *plugin, clap_istream *stream) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_state_load(stream);
  }

  //----------

  static void clap_timer_on_timer_callback(const clap_plugin *plugin, clap_id timer_id) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_timer_on_timer(timer_id);
  }

};

//----------------------------------------------------------------------
#endif
