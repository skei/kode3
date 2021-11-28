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

  KODE_Descriptor*              MDescriptor           = nullptr;
  KODE_Instance*                MInstance             = nullptr;
  KODE_ProcessContext           MProcessContext       = {};
  KODE_ClapHost*                MHost                 = nullptr;
  KODE_Editor*                  MEditor               = nullptr;
  bool                          MEditorIsOpen         = false;
  // activate
  float                         MSampleRate           = 0.0;
  uint32_t                      MMinFrames            = 0;
  uint32_t                      MMaxFrames            = INT_MAX;
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

  KODE_ClapInstance(KODE_Instance* AInstance, KODE_ClapHost* AHost) {
    KODE_CLAPPRINT;
    MInstance = AInstance;
    MDescriptor = MInstance->getDescriptor();
    MHost = AHost;
    //init_extensions();
  }

  //----------

  ~KODE_ClapInstance() {
    KODE_CLAPPRINT;
    if (MInstance) delete MInstance;
  }

//------------------------------
private:
//------------------------------

  void init_extensions() {
    MHostAudioPortsConfig = (clap_host_audio_ports_config*)MHost->get_extension(CLAP_EXT_AUDIO_PORTS_CONFIG);
    MHostAudioPorts       = (clap_host_audio_ports*)MHost->get_extension(CLAP_EXT_AUDIO_PORTS);
    MHostEventFilter      = (clap_host_event_filter*)MHost->get_extension(CLAP_EXT_EVENT_FILTER);
    MHostFdSupport        = (clap_host_fd_support*)MHost->get_extension(CLAP_EXT_FD_SUPPORT);
    MHostGui              = (clap_host_gui*)MHost->get_extension(CLAP_EXT_GUI);
    MHostLatency          = (clap_host_latency*)MHost->get_extension(CLAP_EXT_LATENCY);
    MHostLog              = (clap_host_log*)MHost->get_extension(CLAP_EXT_LOG);
    MHostNoteName         = (clap_host_note_name*)MHost->get_extension(CLAP_EXT_NOTE_NAME);
    MHostParams           = (clap_host_params*)MHost->get_extension(CLAP_EXT_PARAMS);
    MHostState            = (clap_host_state*)MHost->get_extension(CLAP_EXT_STATE);
    MHostThreadCheck      = (clap_host_thread_check*)MHost->get_extension(CLAP_EXT_THREAD_CHECK);
    MHostTimerSupport     = (clap_host_timer_support*)MHost->get_extension(CLAP_EXT_TIMER_SUPPORT);
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
    init_extensions();
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
    Activate and deactivate the plugin.
    In this call the plugin may allocate memory and prepare everything needed
    for the process call. The process's sample rate will be constant and
    process's frame count will included in the [min, max] range, which is
    bounded by [1, INT32_MAX]. Once activated the latency and port
    configuration must remain constant, until deactivation.
    [main-thread
  */

  bool clap_instance_activate(double sample_rate, uint32_t minframes, uint32_t maxframes) {
    KODE_ClapPrint("sample_rate %.2f minframes %i maxframes %i\n",sample_rate,minframes,maxframes);
    MSampleRate = sample_rate;
    MMinFrames  = minframes;
    MMaxFrames  = maxframes;
    MInstance->on_plugin_activate();
    return true;
  }

  /* */

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

  /* */

  void clap_instance_stop_processing() {
    KODE_CLAPPRINT;
    MInstance->on_plugin_stopProcessing();
  }

  /*
    process audio, events, ...
    [audio-thread]
  */

  //TODO

  clap_process_status clap_instance_process(const clap_process *process) {
    //KODE_Assert(process);
    //KODE_Assert(process->audio_inputs);
    //KODE_Assert(process->audio_outputs);
    //KODE_Assert(process->transport);
    MProcessContext.mode          = 0;
    MProcessContext.offset        = 0;
    MProcessContext.numsamples    = process->frames_count;
    MProcessContext.numinputs     = process->audio_inputs_count;
    MProcessContext.numoutputs    = process->audio_outputs_count;
    MProcessContext.inputs[0]     = process->audio_inputs[0].data32[0];
    MProcessContext.inputs[1]     = process->audio_inputs[0].data32[1];
    MProcessContext.outputs[0]    = process->audio_outputs[0].data32[0];
    MProcessContext.outputs[1]    = process->audio_outputs[0].data32[1];
    MProcessContext.samplerate    = MSampleRate;//48000;
    MProcessContext.tempo         = process->transport->tempo;
    MProcessContext.timesignum    = process->transport->tsig_num;
    MProcessContext.timesigdenom  = process->transport->tsig_denom;
    MProcessContext.samplepos     = process->steady_time;
    MProcessContext.beatpos       = process->transport->song_pos_beats;
    MProcessContext.playstate     = KODE_PLUGIN_PLAYSTATE_NONE;
    if (process->transport->flags & CLAP_TRANSPORT_IS_PLAYING) MProcessContext.playstate |= KODE_PLUGIN_PLAYSTATE_PLAYING;
    if (process->transport->flags & CLAP_TRANSPORT_IS_RECORDING) MProcessContext.playstate |= KODE_PLUGIN_PLAYSTATE_RECORDING;
    if (process->transport->flags & CLAP_TRANSPORT_IS_LOOP_ACTIVE) MProcessContext.playstate |= KODE_PLUGIN_PLAYSTATE_LOOPING;
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

  //--------------------
  // clap.audio-ports-config
  //--------------------

  /*
    This extension provides a way for the plugin to describe possible ports
    configurations, for example mono, stereo, surround, ... and a way for the
    host to select a configuration.

    After the plugin initialization, the host may scan the list of
    configurations and eventually select one that fits the plugin context.
    The host can only select a configuration if the plugin is deactivated.

    A configuration is a very simple description of the audio ports:
    - it describes the main input and output ports
    - it has a name that can be displayed to the user

    The idea behind the configurations, is to let the user choose one via a
    menu.

    Plugin with very complex configuration possibilities should let the user
    configure the ports from the plugin GUI, and call
    clap_host_audio_ports.rescan(CLAP_AUDIO_PORTS_RESCAN_ALL).
  */

  //----------

  /*
    gets the number of available configurations
    [main-thread]
  */

  uint32_t clap_audio_ports_config_count() {
    KODE_CLAPPRINT;
    return 1;
  }

  /*
    gets information about a configuration
    [main-thread]
  */

  bool clap_audio_ports_config_get(uint32_t index, clap_audio_ports_config *config) {
    KODE_ClapPrint("%i\n",index);
    switch(index) {
      case 0:
        config->id                    = 0;
        strcpy(config->name,"ports");
        config->input_channel_count   = 2;
        config->input_channel_map     = CLAP_CHMAP_STEREO;
        config->output_channel_count  = 2;
        config->output_channel_map    = CLAP_CHMAP_STEREO;
        return true;
    }
    return false;
  }

  /*
   selects the configuration designated by id
   returns true if the configuration could be applied
   [main-thread,plugin-deactivated]
  */

  bool clap_audio_ports_config_select(clap_id config_id) {
    KODE_ClapPrint("%i\n",config_id);
    return true;
  }

  //--------------------
  // clap.audio-ports
  //--------------------

  /*
    This extension provides a way for the plugin to describe its current audio
    ports.
    If the plugin does not implement this extension, it will have a default
    stereo input and output.
    The plugin is only allowed to change its ports configuration while it is
    deactivated.
  */

  //----------

  /*
    number of ports, for either input or output
    [main-thread]
  */

  uint32_t clap_audio_ports_count(bool is_input) {
    KODE_CLAPPRINT;
    return 1;
  }

  /*
    get info about about an audio port.
    [main-thread]
  */

  bool clap_audio_ports_get(uint32_t index, bool is_input, clap_audio_port_info *info) {
    KODE_ClapPrint("%i\n",index);
    switch(index) {
      case 0:
        info->id = 0;
        strcpy(info->name,"ports");
        info->channel_count = 2;
        info->channel_map = CLAP_CHMAP_STEREO;
        info->sample_size = 32;
        info->is_main = true;
        info->is_cv = false;
        info->in_place = true;
        return true;
    };
    return false;
  }

  //--------------------
  // clap.event-filter
  //--------------------

  /*
    This extension lets the host know which event types the plugin is
    interested in.
  */

  //----------

  /*
    Returns true if the plugin is interested in the given event type.
    [main-thread]
  */

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

  /*
  */

  //----------

  /*
    This callback is "level-triggered".
    It means that a writable fd will continuously produce "on_fd()" events;
    don't forget using modify_fd() to remove the write notification once you're
    done writting.
    [main-thread]
  */

  void clap_fd_support_on_fd(clap_fd fd, clap_fd_flags flags) {
    KODE_CLAPPRINT;
  }

  //--------------------
  // clap.gui
  //--------------------

  /*
    This extension is split in two interfaces:
    - `gui` which is the generic part
    - `gui_XXX` which is the platform specific interfaces; @see clap_gui_win32.

    Showing the GUI works as follow:
    1. clap_plugin_gui->create(), allocates gui resources
    2. clap_plugin_gui->set_scale()
    3. clap_plugin_gui->get_size(), gets initial size
    4. clap_plugin_gui_win32->embed(), or any other platform specific interface
    5. clap_plugin_gui->show()
    6. clap_plugin_gui->hide()/show() ...
    7. clap_plugin_gui->close() when done with the gui

    Resizing the window:
    1. Only possible if clap_plugin_gui->can_resize() returns true
    2. Mouse drag -> new_size
    3. clap_plugin_gui->round_size(new_size) -> working_size
    4. clap_plugin_gui->set_size(working_
  */

  //----------

  /*
    Create and allocate all resources necessary for the gui.
    After this call, the GUI is ready to be shown but it is not yet visible.
    [main-thread]
  */

  // note: the editor doesn't have a window yet!

  bool clap_gui_create() {
    KODE_CLAPPRINT;
    MEditorIsOpen = false;
    MEditor = _kode_create_editor(MInstance,MDescriptor);
    return MInstance->on_plugin_createEditor(MEditor);
  }

  /*
    Free all resources associated with the gui.
    [main-thread]
  */

  void clap_gui_destroy() {
    KODE_CLAPPRINT;
    MEditorIsOpen = false;
    if (MEditor) {
      MInstance->on_plugin_destroyEditor(MEditor);
      delete MEditor;
      MEditor = nullptr;
    }
  }

  /*
    Set the absolute GUI scaling factor.
    [main-thread]
  */

  void clap_gui_set_scale(double scale) {
    KODE_ClapPrint("%f\n",scale);
    if (MEditor) {
      MEditor->setScale(scale);
    }
  }

  /*
    Get the current size of the plugin UI, with the scaling applied.
    clap_plugin_gui->create() must have been called prior to asking the size.
    [main-thread]
  */

  bool clap_gui_get_size(uint32_t *width, uint32_t *height) {
    KODE_CLAPPRINT;
    *width  = MDescriptor->editorWidth;
    *height = MDescriptor->editorHeight;
    return true;
  }

  /*
    [main-thread]
  */

  bool clap_gui_can_resize() {
    KODE_CLAPPRINT;
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
    KODE_CLAPPRINT;
    //*width  = MDescriptor->editorWidth;
    //*height = MDescriptor->editorHeight;
  }

  /*
    Sets the window size
    Returns true if the size is supported.
    [main-thread]
  */

  bool clap_gui_set_size(uint32_t width, uint32_t height) {
    KODE_ClapPrint("%i,%i\n",width,height);
    if (MEditor) {
      MEditor->resize(width,height);
    }
    return true;
  }

  /*
    Show the window.
    [main-thread]
  */

  void clap_gui_show() {
    KODE_CLAPPRINT;
    if (MEditor && !MEditorIsOpen) {
      //MEditor->open(MDescriptor->editorWidth,MDescriptor->editorHeight,nullptr);
      MEditorIsOpen = MInstance->on_plugin_openEditor(MEditor);
      MEditor->show();

    }
  }

  /*
    Hide the window, this method do not free the resources, it just hides
    the window content. Yet it maybe a good idea to stop painting timers.
    [main-thread]
  */

  void clap_gui_hide() {
    KODE_CLAPPRINT;
    if (MEditor && MEditorIsOpen) {
      //MEditor->close();
      MEditor->hide();
      MEditorIsOpen = false;
    }
  }

  //--------------------
  // clap.gui-x11
  //--------------------

  /*
  */

  //----------

  /*
    Use the protocol XEmbed
    [main-thread]
  */

  bool clap_gui_x11_attach(const char* display_name, unsigned long window) {
    KODE_ClapPrint("display:name: %s, window: %i\n",display_name,window);
    MEditor->attach(display_name,window);
    MEditorIsOpen = MInstance->on_plugin_openEditor(MEditor);
    return true;
  }

  //--------------------
  // clap.latency
  //--------------------

  /*
    The audio ports scan has to be done while the plugin is deactivated.
  */

  //----------

  /*
    Returns the plugin latency.
    [main-thread]
  */

  uint32_t clap_latency_get() {
    KODE_CLAPPRINT;
    return 0;
  }

  //--------------------
  // clap.note-name
  //--------------------

  /*
  */

  //----------

  /*
    Return the number of note names
    [main-thread]
  */

  uint32_t clap_note_name_count() {
    KODE_CLAPPRINT;
    return 0;
  }

  /*
    Returns true on success and stores the result into note_name
    [main-thread]
  */

  bool clap_note_name_get(uint32_t index, clap_note_name *note_name) {
    KODE_CLAPPRINT;
    return false;
  }

  //--------------------
  // clap.params
  //--------------------

  /*
    Main idea:

    The host sees the plugin as an atomic entity; and acts as a controler on top of its parameters.
    The plugin is responsible to keep in sync its audio processor and its GUI.

    The host can read at any time parameters value on the [main-thread] using
    @ref clap_plugin_params.value().

    There is two options to communicate parameter value change, and they are not concurrent.
    - send automation points during clap_plugin.process()
    - send automation points during clap_plugin_params.flush(), this one is used when the plugin is
      not processing

    When the plugin changes a parameter value, it must inform the host.
    It will send @ref CLAP_EVENT_PARAM_VALUE event during process() or flush().
    - set the flag CLAP_EVENT_PARAM_BEGIN_ADJUST to mark the begining of automation recording
    - set the flag CLAP_EVENT_PARAM_END_ADJUST to mark the end of automation recording
    - set the flag CLAP_EVENT_PARAM_SHOULD_RECORD if the event should be recorded

    @note MIDI CCs are a tricky because you may not know when the parameter adjustment ends.
    Also if the hosts records incoming MIDI CC and parameter change automation at the same time,
    there will be a conflict at playback: MIDI CC vs Automation.
    The parameter automation will always target the same parameter because the param_id is stable.
    The MIDI CC may have a different mapping in the future and may result in a different playback.

    When a MIDI CC changes a parameter's value, set @ref clap_event_param.should_record to false.
    That way the host may record the MIDI CC automation, but not the parameter change and there
    won't be conflict at playback.

    Scenarios:

    I. Loading a preset
    - load the preset in a temporary state
    - call @ref clap_host_params.changed() if anything changed
    - call @ref clap_host_latency.changed() if latency changed
    - invalidate any other info that may be cached by the host
    - if the plugin is activated and the preset will introduce breaking change
      (latency, audio ports, new parameters, ...) be sure to wait for the host
      to deactivate the plugin to apply those changes.
      If there are no breaking changes, the plugin can apply them them right away.
      The plugin is resonsible to update both its audio processor and its gui.

    II. Turning a knob on the DAW interface
    - the host will send an automation event to the plugin via a process() or flush()

    III. Turning a knob on the Plugin interface
    - if the plugin is not processing, call clap_host_params->request_flush() or
      clap_host->request_process().
    - send an automation event and don't forget to set begin_adjust, end_adjust and should_record
      attributes
    - the plugin is responsible to send the parameter value to its audio processor

    IV. Turning a knob via automation
    - host sends an automation point during clap_plugin->process() or clap_plugin_params->flush().
    - the plugin is responsible to update its GUI

    V. Turning a knob via plugin's internal MIDI mapping
    - the plugin sends a CLAP_EVENT_PARAM_SET output event, set should_record to false
    - the plugin is responsible to update its GUI

    VI. Adding or removing parameters
    - if the plugin is activated call clap_host->restart()
    - once the plugin isn't active:
      - apply the new state
      - call clap_host_params->rescan(CLAP_PARAM_RESCAN_ALL)
      - if a parameter is created with an id that may have been used before,
        call clap_host_params.clear(host, param_id, CLAP_PARAM_CLEAR_ALL)
  */

  //----------

  /*
    Returns the number of parameters.
    [main-thread]
  */

  uint32_t clap_params_count() {
    KODE_CLAPPRINT;
    return MDescriptor->parameters.size();
  }

  /*
    Copies the parameter's info to param_info and returns true on success.
    [main-thread]
  */

  bool clap_params_get_info(int32_t param_index, clap_param_info *param_info) {
    KODE_CLAPPRINT;
    KODE_Parameter* param     = MDescriptor->parameters[param_index];
    param_info->id            = param_index;
    param_info->flags         = 0;
    param_info->cookie        = nullptr;
    strcpy(param_info->name,param->name); // todo: strncpy
    strcpy(param_info->module,""); // todo: strncpy
    param_info->min_value     = 0.0;
    param_info->max_value     = 1.0;
    param_info->default_value = 0.5;
    return true;
  }

  /*
    Gets the parameter plain value.
    [main-thread]
  */

  bool clap_params_get_value(clap_id param_id, double *value) {
    KODE_CLAPPRINT;
    MInstance->getParameterValue(param_id); // !!!
    return true;
  }

  /*
    Formats the display text for the given parameter value.
    [main-thread]
  */

  bool clap_params_value_to_text(clap_id param_id, double value, char *display, uint32_t size) {
    char buffer[256];
    KODE_CLAPPRINT;
    KODE_Parameter* param = MDescriptor->parameters[param_id];
    param->getDisplayText(value,buffer);
    strcpy(display,buffer);
    return true;
  }

  /*
    Converts the display text to a parameter value.
    [main-thread]
  */

  bool clap_params_text_to_value(clap_id param_id, const char* display, double* value) {
    KODE_CLAPPRINT;
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
    KODE_CLAPPRINT;
  }

  //--------------------
  // clap.render
  //--------------------

  /*
    The render extension is used to let the plugin know if it has "realtime"
    pressure to process.
    If this information does not influence your rendering code, then don't
    implement this extension
  */

  //----------

  /*
    [main-thread]
  */

  void clap_render_set(clap_plugin_render_mode mode) {
    KODE_CLAPPRINT;
  }

  //--------------------
  // clap.state
  //--------------------

  /*
  */

  //----------

  /*
    Saves the plugin state into stream.
    Returns true if the state was correctly saved.
    [main-thread]
  */

  bool clap_state_save(clap_ostream *stream) {
    KODE_CLAPPRINT;
    return false;
  }

  /*
    Tell the host that the plugin state has changed and should be saved again.
    If a parameter value changes, then it is implicit that the state is dirty.
    [main-thread]
  */

  bool clap_state_load(clap_istream *stream) {
    KODE_CLAPPRINT;
    return false;
  }

  //--------------------
  // clap.timer-support
  //--------------------

  /*
  */

  //----------

  /*
    [main-thread]
  */

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
