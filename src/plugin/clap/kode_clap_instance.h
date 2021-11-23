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

  KODE_Instance*        MInstance       = nullptr;
  KODE_ProcessContext   MProcessContext = {};


//------------------------------
public:
//------------------------------

  KODE_ClapInstance(KODE_Instance* AInstance) {
    KODE_CLAPPRINT;
    MInstance = AInstance;
  }

  //----------

  ~KODE_ClapInstance() {
    KODE_CLAPPRINT;
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
    KODE_CLAPPRINT;
    MInstance->on_plugin_init();
    return true;
  }

  /*
    Free the plugin and its resources.
    It is not required to deactivate the plugin prior to this call.
  */

  void clap_instance_destroy() {
    KODE_CLAPPRINT;
    MInstance->on_plugin_destroy();
  }

  /*
    activation/deactivation
    [main-thread]
  */

  bool clap_instance_activate(double sample_rate) {
    KODE_CLAPPRINT;
    MInstance->on_plugin_activate();
    return true;
  }

  void clap_instance_deactivate() {
    KODE_CLAPPRINT;
    MInstance->on_plugin_deactivate();
  }

  /*
    Set to true before processing,
    and to false before sending the plugin to sleep.
    [audio-thread]
  */

  bool clap_instance_start_processing() {
    KODE_CLAPPRINT;
    MInstance->on_plugin_startProcessing();
    return true;
  }

  void clap_instance_stop_processing() {
    KODE_CLAPPRINT;
    MInstance->on_plugin_stopProcessing();
  }

  /*
    process audio, events, ...
    [audio-thread]
  */

  clap_process_status clap_instance_process(const clap_process *process) {
    //KODE_CLAPPRINT;
    MInstance->on_plugin_process(&MProcessContext);
    return CLAP_PROCESS_CONTINUE;
  }

  /*
    Query an extension.
    The returned pointer is owned by the plugin.
    [thread-safe]
  */


  const void *clap_instance_get_extension(const char *id) {
    KODE_ClapPrint("%s\n",id);
    if (strcmp(id,CLAP_EXT_AUDIO_PORTS_CONFIG) == 0)  { return &MClapAudioPortsConfig; }
    if (strcmp(id,CLAP_EXT_AUDIO_PORTS) == 0)         { return &MClapAudioPorts; }
    if (strcmp(id,CLAP_EXT_EVENT_FILTER) == 0)        { return &MClapEventFilter; }
    if (strcmp(id,CLAP_EXT_FD_SUPPORT) == 0)          { return &MClapFdSupport; }
    if (strcmp(id,CLAP_EXT_GUI) == 0)                 { return &MClapGui; }
    if (strcmp(id,CLAP_EXT_GUI_X11) == 0)             { return &MClapGuiX11; }
    if (strcmp(id,CLAP_EXT_LATENCY) == 0)             { return &MClapLatency; }
    if (strcmp(id,CLAP_EXT_NOTE_NAME) == 0)           { return &MClapNoteName; }
    if (strcmp(id,CLAP_EXT_PARAMS) == 0)              { return &MClapParams; }
    if (strcmp(id,CLAP_EXT_RENDER) == 0)              { return &MClapRender; }
    if (strcmp(id,CLAP_EXT_STATE) == 0)               { return &MClapState; }
    if (strcmp(id,CLAP_EXT_TIMER_SUPPORT) == 0)       { return &MClapTimerSupport; }
    return nullptr;
  }

  /*
    Called by the host on the main thread in response to a previous call to:
      host->request_callback(host);
    [main-thread]
  */

  void clap_instance_on_main_thread() {
    KODE_CLAPPRINT;
  }

//------------------------------
public: // extensions
//------------------------------

  uint32_t clap_audio_ports_config_count() {
    KODE_CLAPPRINT;
    return 0;
  }

  bool clap_audio_ports_config_get(uint32_t index, clap_audio_ports_config *config) {
    KODE_CLAPPRINT;
    //config->id                    = 0;
    //strcpy(config->name,"name");
    //config->input_channel_count   = 2;
    //config->input_channel_map     = CLAP_CHMAP_STEREO;
    //config->output_channel_count  = 2;
    //config->output_channel_map    = CLAP_CHMAP_STEREO;
    return false;
  }

  bool clap_audio_ports_config_select(clap_id config_id) {
    KODE_CLAPPRINT;
    return false;
  }

  //--------------------
  // clap.audio-ports
  //--------------------

  uint32_t clap_audio_ports_count(bool is_input) {
    return 0;
  }

  bool clap_audio_ports_get(uint32_t index, bool is_input, clap_audio_port_info *info) {
    //info->id
    //info->name
    //channel_count;
    //channel_map;
    //sample_size
    //is_main
    //is_cv
    //in_place
    return false;
  };

  //--------------------
  // clap.event-filter
  //--------------------

  bool clap_event_filter_accepts(clap_event_type event_type) {
    KODE_CLAPPRINT;
    //switch (event_type) {
    //  case CLAP_EVENT_NOTE_ON:          return true; break;
    //  case CLAP_EVENT_NOTE_OFF:         return true; break;
    //  case CLAP_EVENT_NOTE_END:         return true; break;
    //  case CLAP_EVENT_NOTE_CHOKE:       return true; break;
    //  case CLAP_EVENT_NOTE_EXPRESSION:  return true; break;
    //  case CLAP_EVENT_NOTE_MASK:        return true; break;
    //  case CLAP_EVENT_PARAM_VALUE:      return true; break;
    //  case CLAP_EVENT_PARAM_MOD:        return true; break;
    //  case CLAP_EVENT_TRANSPORT:        return true; break;
    //  case CLAP_EVENT_MIDI:             return true; break;
    //  case CLAP_EVENT_MIDI_SYSEX:       return true; break;
    //}
    return false;
  }

  //--------------------
  // clap.fd-support
  //--------------------

  void clap_fd_support_on_fd(clap_fd fd, clap_fd_flags flags) {
    KODE_CLAPPRINT;
  }

  //--------------------
  // clap.gui
  //--------------------

  bool clap_gui_create() {
    //KODE_Editor* MEditor = _kode_create_editor(MInstance);
    KODE_CLAPPRINT;
    return false;
  }

  void clap_gui_destroy() {
    //delete MEditor;
    KODE_CLAPPRINT;
  }

  void clap_gui_set_scale(double scale) {
    KODE_CLAPPRINT;
  }

  bool clap_gui_get_size(uint32_t *width, uint32_t *height) {
    KODE_CLAPPRINT;
    //*width  = MInstance->getDescriptor()->editorWidth;
    //*height = MInstance->getDescriptor()->editorHeight;
    return false;
  }

  bool clap_gui_can_resize() {
    KODE_CLAPPRINT;
    return false;
  }

  void clap_gui_round_size(uint32_t *width, uint32_t *height) {
    KODE_CLAPPRINT;
  }

  bool clap_gui_set_size(uint32_t width, uint32_t height) {
    KODE_CLAPPRINT;
    //MEditor->resize(width,height);
    return false;
  }

  void clap_gui_show() {
    KODE_CLAPPRINT;
    //MEditor->open();
  }

  void clap_gui_hide() {
    KODE_CLAPPRINT;
    //MEditor->close();
  }

  //--------------------
  // clap.gui-x11
  //--------------------

  bool clap_gui_x11_attach(const char* display_name, unsigned long window) {
    KODE_ClapPrint("display:name: %s, window: %i\n",display_name,window);
    // create window
    return false;
  }

  //--------------------
  // clap.latency
  //--------------------

  uint32_t clap_latency_get() {
    KODE_CLAPPRINT;
    return 0;
  }

  //--------------------
  // clap.note-name
  //--------------------

  uint32_t clap_note_name_count() {
    KODE_CLAPPRINT;
    return 0;
  }

  bool clap_note_name_get(uint32_t index, clap_note_name *note_name) {
    KODE_CLAPPRINT;
    return false;
  }

  //--------------------
  // clap.params
  //--------------------

  uint32_t clap_params_count() {
    KODE_CLAPPRINT;
    return 0;
  }

  bool clap_params_get_info(int32_t param_index, clap_param_info *param_info) {
    KODE_CLAPPRINT;
    //param_info->id = 0;
    //param_info->flags
    //param_info->cookie
    //param_info->name
    //param_info->module
    //param_info->min_value
    //param_info->max_value
    //param_info->default_value
    return false;
  }

  bool clap_params_get_value(clap_id param_id, double *value) {
    KODE_CLAPPRINT;
    //MInstance->getParameterValue(index);
    return false;
  }

  bool clap_params_value_to_text(clap_id param_id, double value, char *display, uint32_t size) {
    KODE_CLAPPRINT;
    //KODE_Parameter* param;
    //param->getDisplayText(value,buffer);)
    return false;
  }

  bool clap_params_text_to_value(clap_id param_id, const char* display, double* value) {
    KODE_CLAPPRINT;
    return false;
  }

  void clap_params_flush(const clap_event_list *input_parameter_changes, const clap_event_list *output_parameter_changes) {
    KODE_CLAPPRINT;
  }

  //--------------------
  // clap.render
  //--------------------

  void clap_render_set(clap_plugin_render_mode mode) {
    KODE_CLAPPRINT;
  }

  //--------------------
  // clap.state
  //--------------------

  bool clap_state_save(clap_ostream *stream) {
    KODE_CLAPPRINT;
    return false;
  }

  bool clap_state_load(clap_istream *stream) {
    KODE_CLAPPRINT;
    return false;
  }

  //--------------------
  // clap.timer-support
  //--------------------

  void clap_timer_support_on_timer(clap_id timer_id) {
    KODE_CLAPPRINT;
  }
//------------------------------
public: // extension callbacks
//------------------------------

  // clap.audio-ports-config

  static uint32_t clap_audio_ports_config_count_callback(const clap_plugin *plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_audio_ports_config_count();
    return 0;
  }

  static bool clap_audio_ports_config_get_callback(const clap_plugin *plugin, uint32_t index, clap_audio_ports_config *config) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_audio_ports_config_get(index,config);

  }

  static bool clap_audio_ports_config_select_callback(const clap_plugin *plugin, clap_id config_id) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_audio_ports_config_select(config_id);
  }

  // clap.audio-ports

  static uint32_t clap_audio_ports_count_callback(const clap_plugin *plugin, bool is_input) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_audio_ports_count(is_input);

  }

  static bool clap_audio_ports_get_callback(const clap_plugin* plugin, uint32_t index, bool is_input, clap_audio_port_info *info) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_audio_ports_get(index,is_input,info);
  };

  // clap.event-filter

  static bool clap_event_filter_accepts_callback(const clap_plugin *plugin, clap_event_type event_type) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_event_filter_accepts(event_type);
  }

  // clap.fd-support

  static void clap_fd_support_on_fd_callback(const clap_plugin *plugin, clap_fd fd, clap_fd_flags flags) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_fd_support_on_fd(fd,flags);
  }

  // clap.gui

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

  // clap.gui-x11

  static bool clap_gui_x11_attach_callback(const clap_plugin * plugin, const char* display_name, unsigned long window) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_gui_x11_attach(display_name,window);
  }

  // clap.latency

  static uint32_t clap_latency_get_callback(const clap_plugin *plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_latency_get();
  }

  // clap.note-name

  static uint32_t clap_note_name_count_callback(const clap_plugin *plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_note_name_count();
  }

  static bool clap_note_name_get_callback(const clap_plugin *plugin, uint32_t index, clap_note_name *note_name) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_note_name_get(index,note_name);
  }

  // clap.params

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

  // clap.render

  static void clap_render_set_callback(const clap_plugin *plugin, clap_plugin_render_mode mode) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_render_set(mode);
  }

  // clap.state

  static bool clap_state_save_callback(const clap_plugin *plugin, clap_ostream *stream) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_state_save(stream);
  }

  static bool clap_state_load_callback(const clap_plugin *plugin, clap_istream *stream) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_state_load(stream);
  }

  // clap.timer-support

  static void clap_timer_support_on_timer_callback(const clap_plugin *plugin, clap_id timer_id) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_timer_support_on_timer(timer_id);
  }

//------------------------------
private: // extension structs
//------------------------------

  struct clap_plugin_audio_ports_config MClapAudioPortsConfig = {
    clap_audio_ports_config_count_callback,
    clap_audio_ports_config_get_callback,
    clap_audio_ports_config_select_callback
  };

  struct clap_plugin_audio_ports MClapAudioPorts =  {
    clap_audio_ports_count_callback,
    clap_audio_ports_get_callback
  };

  struct clap_plugin_event_filter MClapEventFilter = {
    clap_event_filter_accepts_callback
  };

  struct clap_plugin_fd_support MClapFdSupport = {
    clap_fd_support_on_fd_callback
  };

  struct clap_plugin_gui MClapGui = {
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

  struct clap_plugin_gui_x11 MClapGuiX11 = {
    clap_gui_x11_attach_callback
  };

  struct clap_plugin_latency MClapLatency = {
    clap_latency_get_callback
  };

  struct clap_plugin_note_name MClapNoteName = {
    clap_note_name_count_callback,
    clap_note_name_get_callback
  };

  struct clap_plugin_params MClapParams = {
    clap_params_count_callback,
    clap_params_get_info_callback,
    clap_params_get_value_callback,
    clap_params_value_to_text_callback,
    clap_params_text_to_value_callback,
    clap_params_flush_callback
  };

  struct clap_plugin_render MClapRender = {
    clap_render_set_callback
  };

  struct clap_plugin_state MClapState = {
    clap_state_save_callback,
    clap_state_load_callback
  };

  struct clap_plugin_timer_support MClapTimerSupport = {
    clap_timer_support_on_timer_callback
  };

};

//----------------------------------------------------------------------
#endif
