#ifndef kode_dssi_plugin_included
#define kode_dssi_plugin_included
//----------------------------------------------------------------------

// todo: KODE_DssiInstance

#include "kode.h"
#include "plugin/dssi/kode_dssi.h"

//----------------------------------------------------------------------

//struct DSSI_Descriptor {
//};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

template <class DESCRIPTOR, class INSTANCE, class EDITOR>
class KODE_DssiPlugin {

//------------------------------
private:
//------------------------------

  DESCRIPTOR*       MDescriptor     = nullptr;

  const LADSPA_PortDescriptor*  MLadspaPortDescriptors  = nullptr;
  const char* const*            MLadspaPortNames        = nullptr;
  const LADSPA_PortRangeHint*   MLadspaPortRangeHints   = nullptr;

  LADSPA_Descriptor MLadspaDescriptor = {
    0,                              // UniqueID
    "",                             // Label
    0,                              // Properties
    "",                             // Name
    "",                             // Maker
    "",                             // Copyright
    0,                              // PortCount
    MLadspaPortDescriptors,
    MLadspaPortNames,
    MLadspaPortRangeHints,
    this,                           // ImplementationData
    ladspa_instantiate_callback,
    ladspa_connect_port_callback,
    ladspa_activate_callback,
    ladspa_run_callback,
    ladspa_run_adding_callback,
    ladspa_set_run_adding_gain_callback,
    ladspa_deactivate_callback,
    ladspa_cleanup_callback
  };

  DSSI_Descriptor MDssiDescriptor = {
    0,
    nullptr,
    dssi_configure_callback,
    dssi_get_program_callback,
    dssi_select_program_callback,
    dssi_get_midi_controller_for_port_callback,
    dssi_run_synth_callback,
    dssi_run_synth_adding_callback,
    dssi_run_multiple_synths_callback,
    dssi_run_multiple_synths_adding_callback
  };

//------------------------------
public:
//------------------------------

  KODE_DssiPlugin() {
    KODE_PRINT;
    MDescriptor = new DESCRIPTOR();
  }

  //----------

  ~KODE_DssiPlugin() {
    KODE_PRINT;
    delete MDescriptor;
  }

//------------------------------
public: // ladspa
//------------------------------

  /* This member is a function pointer that instantiates a plugin. A
     handle is returned indicating the new plugin instance. The
     instantiation function accepts a sample rate as a parameter. The
     plugin descriptor from which this instantiate function was found
     must also be passed. This function must return NULL if
     instantiation fails.

     Note that instance initialisation should generally occur in
     activate() rather than here. */

  LADSPA_Handle ladspa_instantiate(/*const struct _LADSPA_Descriptor* Descriptor,*/ unsigned long SampleRate) {
    return nullptr;
  }

  /* This member is a function pointer that connects a port on an
     instantiated plugin to a memory location at which a block of data
     for the port will be read/written. The data location is expected
     to be an array of LADSPA_Data for audio ports or a single
     LADSPA_Data value for control ports. Memory issues will be
     managed by the host. The plugin must read/write the data at these
     locations every time run() or run_adding() is called and the data
     present at the time of this connection call should not be
     considered meaningful.

     connect_port() may be called more than once for a plugin instance
     to allow the host to change the buffers that the plugin is
     reading or writing. These calls may be made before or after
     activate() or deactivate() calls.

     connect_port() must be called at least once for each port before
     run() or run_adding() is called. When working with blocks of
     LADSPA_Data the plugin should pay careful attention to the block
     size passed to the run function as the block allocated may only
     just be large enough to contain the block of samples.

     Plugin writers should be aware that the host may elect to use the
     same buffer for more than one port and even use the same buffer
     for both input and output (see LADSPA_PROPERTY_INPLACE_BROKEN).
     However, overlapped buffers or use of a single buffer for both
     audio and control data may result in unexpected behaviour. */

   void ladspa_connect_port(unsigned long Port, LADSPA_Data * DataLocation) {
   }

  /* This member is a function pointer that initialises a plugin
     instance and activates it for use. This is separated from
     instantiate() to aid real-time support and so that hosts can
     reinitialise a plugin instance by calling deactivate() and then
     activate(). In this case the plugin instance must reset all state
     information dependent on the history of the plugin instance
     except for any data locations provided by connect_port() and any
     gain set by set_run_adding_gain(). If there is nothing for
     activate() to do then the plugin writer may provide a NULL rather
     than an empty function.

     When present, hosts must call this function once before run() (or
     run_adding()) is called for the first time. This call should be
     made as close to the run() call as possible and indicates to
     real-time plugins that they are now live. Plugins should not rely
     on a prompt call to run() after activate(). activate() may not be
     called again unless deactivate() is called first. Note that
     connect_port() may be called before or after a call to
     activate(). */

  void ladspa_activate() {
  }

  /* This method is a function pointer that runs an instance of a
     plugin for a block. Two parameters are required: the first is a
     handle to the particular instance to be run and the second
     indicates the block size (in samples) for which the plugin
     instance may run.

     Note that if an activate() function exists then it must be called
     before run() or run_adding(). If deactivate() is called for a
     plugin instance then the plugin instance may not be reused until
     activate() has been called again.

     If the plugin has the property LADSPA_PROPERTY_HARD_RT_CAPABLE
     then there are various things that the plugin should not do
     within the run() or run_adding() functions (see above). */

  void ladspa_run(unsigned long SampleCount) {
  }

  /* This method is a function pointer that runs an instance of a
     plugin for a block. This has identical behaviour to run() except
     in the way data is output from the plugin. When run() is used,
     values are written directly to the memory areas associated with
     the output ports. However when run_adding() is called, values
     must be added to the values already present in the memory
     areas. Furthermore, output values written must be scaled by the
     current gain set by set_run_adding_gain() (see below) before
     addition.

     run_adding() is optional. When it is not provided by a plugin,
     this function pointer must be set to NULL. When it is provided,
     the function set_run_adding_gain() must be provided also. */

  void ladspa_run_adding(unsigned long SampleCount) {
  }

  /* This method is a function pointer that sets the output gain for
     use when run_adding() is called (see above). If this function is
     never called the gain is assumed to default to 1. Gain
     information should be retained when activate() or deactivate()
     are called.

     This function should be provided by the plugin if and only if the
     run_adding() function is provided. When it is absent this
     function pointer must be set to NULL. */

  void ladspa_set_run_adding_gain(LADSPA_Data Gain) {
  }

  /* This is the counterpart to activate() (see above). If there is
     nothing for deactivate() to do then the plugin writer may provide
     a NULL rather than an empty function.

     Hosts must deactivate all activated units after they have been
     run() (or run_adding()) for the last time. This call should be
     made as close to the last run() call as possible and indicates to
     real-time plugins that they are no longer live. Plugins should
     not rely on prompt deactivation. Note that connect_port() may be
     called before or after a call to deactivate().

     Deactivation is not similar to pausing as the plugin instance
     will be reinitialised when activate() is called to reuse it. */

  void ladspa_deactivate() {
  }

  /* Once an instance of a plugin has been finished with it can be
     deleted using the following function. The instance handle passed
     ceases to be valid after this call.

     If activate() was called for a plugin instance then a
     corresponding call to deactivate() must be made before cleanup()
     is called. */

  void ladspa_cleanup() {
  }

//------------------------------
public: // dssi
//------------------------------

    /**
     * configure()
     *
     * This member is a function pointer that sends a piece of
     * configuration data to the plugin.  The key argument specifies
     * some aspect of the synth's configuration that is to be changed,
     * and the value argument specifies a new value for it.  A plugin
     * that does not require this facility at all may set this member
     * to NULL.
     *
     * This call is intended to set some session-scoped aspect of a
     * plugin's behaviour, for example to tell the plugin to load
     * sample data from a particular file.  The plugin should act
     * immediately on the request.  The call should return NULL on
     * success, or an error string that may be shown to the user.  The
     * host will free the returned value after use if it is non-NULL.
     *
     * Calls to configure() are not automated as timed events.
     * Instead, a host should remember the last value associated with
     * each key passed to configure() during a given session for a
     * given plugin instance, and should call configure() with the
     * correct value for each key the next time it instantiates the
     * "same" plugin instance, for example on reloading a project in
     * which the plugin was used before.  Plugins should note that a
     * host may typically instantiate a plugin multiple times with the
     * same configuration values, and should share data between
     * instances where practical.
     *
     * Calling configure() completely invalidates the program and bank
     * information last obtained from the plugin.
     *
     * Reserved and special key prefixes
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     * The DSSI: prefix
     * ----------------
     * Configure keys starting with DSSI: are reserved for particular
     * purposes documented in the DSSI specification.  At the moment,
     * there is one such key: DSSI:PROJECT_DIRECTORY.  A host may call
     * configure() passing this key and a directory path value.  This
     * indicates to the plugin and its UI that a directory at that
     * path exists and may be used for project-local data.  Plugins
     * may wish to use the project directory as a fallback location
     * when looking for other file data, or as a base for relative
     * paths in other configuration values.
     *
     * The GLOBAL: prefix
     * ------------------
     * Configure keys starting with GLOBAL: may be used by the plugin
     * and its UI for any purpose, but are treated specially by the
     * host.  When one of these keys is used in a configure OSC call
     * from the plugin UI, the host makes the corresponding configure
     * call (preserving the GLOBAL: prefix) not only to the target
     * plugin but also to all other plugins in the same instance
     * group, as well as their UIs.  Note that if any instance
     * returns non-NULL from configure to indicate error, the host
     * may stop there (and the set of plugins on which configure has
     * been called will thus depend on the host implementation).
     * See also the configure OSC call documentation in RFC.txt.
     */

    char* dssi_configure(const char *Key, const char *Value) {
      return nullptr;
    }

    /**
     * get_program()
     *
     * This member is a function pointer that provides a description
     * of a program (named preset sound) available on this synth.  A
     * plugin that does not support programs at all should set this
     * member to NULL.
     *
     * The Index argument is an index into the plugin's list of
     * programs, not a program number as represented by the Program
     * field of the DSSI_Program_Descriptor.  (This distinction is
     * needed to support synths that use non-contiguous program or
     * bank numbers.)
     *
     * This function returns a DSSI_Program_Descriptor pointer that is
     * guaranteed to be valid only until the next call to get_program,
     * deactivate, or configure, on the same plugin instance.  This
     * function must return NULL if passed an Index argument out of
     * range, so that the host can use it to query the number of
     * programs as well as their properties.
     */

    const DSSI_Program_Descriptor* dssi_get_program(unsigned long Index) {
      return nullptr;
    }

    /**
     * select_program()
     *
     * This member is a function pointer that selects a new program
     * for this synth.  The program change should take effect
     * immediately at the start of the next run_synth() call.  (This
     * means that a host providing the capability of changing programs
     * between any two notes on a track must vary the block size so as
     * to place the program change at the right place.  A host that
     * wanted to avoid this would probably just instantiate a plugin
     * for each program.)
     *
     * A plugin that does not support programs at all should set this
     * member NULL.  Plugins should ignore a select_program() call
     * with an invalid bank or program.
     *
     * A plugin is not required to select any particular default
     * program on activate(): it's the host's duty to set a program
     * explicitly.  The current program is invalidated by any call to
     * configure().
     *
     * A plugin is permitted to re-write the values of its input
     * control ports when select_program is called.  The host should
     * re-read the input control port values and update its own
     * records appropriately.  (This is the only circumstance in
     * which a DSSI plugin is allowed to modify its own input ports.)
     */

    void dssi_select_program(unsigned long Bank, unsigned long Program) {
    }

    /**
     * get_midi_controller_for_port()
     *
     * This member is a function pointer that returns the MIDI
     * controller number or NRPN that should be mapped to the given
     * input control port.  If the given port should not have any MIDI
     * controller mapped to it, the function should return DSSI_NONE.
     * The behaviour of this function is undefined if the given port
     * number does not correspond to an input control port.  A plugin
     * that does not want MIDI controllers mapped to ports at all may
     * set this member NULL.
     *
     * Correct values can be got using the macros DSSI_CC(num) and
     * DSSI_NRPN(num) as appropriate, and values can be combined using
     * bitwise OR: e.g. DSSI_CC(23) | DSSI_NRPN(1069) means the port
     * should respond to CC #23 and NRPN #1069.
     *
     * The host is responsible for doing proper scaling from MIDI
     * controller and NRPN value ranges to port ranges according to
     * the plugin's LADSPA port hints.  Hosts should not deliver
     * through run_synth any MIDI controller events that have already
     * been mapped to control port values.
     *
     * A plugin should not attempt to request mappings from
     * controllers 0 or 32 (MIDI Bank Select MSB and LSB).
     */

    int dssi_get_midi_controller_for_port(unsigned long Port) {
      return 0;
    }

    /**
     * run_synth()
     *
     * This member is a function pointer that runs a synth for a
     * block.  This is identical in function to the LADSPA run()
     * function, except that it also supplies events to the synth.
     *
     * A plugin may provide this function, run_multiple_synths() (see
     * below), both, or neither (if it is not in fact a synth).  A
     * plugin that does not provide this function must set this member
     * to NULL.  Authors of synth plugins are encouraged to provide
     * this function if at all possible.
     *
     * The Events pointer points to a block of EventCount ALSA
     * sequencer events, which is used to communicate MIDI and related
     * events to the synth.  Each event is timestamped relative to the
     * start of the block, (mis)using the ALSA "tick time" field as a
     * frame count. The host is responsible for ensuring that events
     * with differing timestamps are already ordered by time.
     *
     * See also the notes on activation, port connection etc in
     * ladpsa.h, in the context of the LADSPA run() function.
     *
     * Note Events
     * ~~~~~~~~~~~
     * There are two minor requirements aimed at making the plugin
     * writer's life as simple as possible:
     *
     * 1. A host must never send events of type SND_SEQ_EVENT_NOTE.
     * Notes should always be sent as separate SND_SEQ_EVENT_NOTE_ON
     * and NOTE_OFF events.  A plugin should discard any one-point
     * NOTE events it sees.
     *
     * 2. A host must not attempt to switch notes off by sending
     * zero-velocity NOTE_ON events.  It should always send true
     * NOTE_OFFs.  It is the host's responsibility to remap events in
     * cases where an external MIDI source has sent it zero-velocity
     * NOTE_ONs.
     *
     * Bank and Program Events
     * ~~~~~~~~~~~~~~~~~~~~~~~
     * Hosts must map MIDI Bank Select MSB and LSB (0 and 32)
     * controllers and MIDI Program Change events onto the banks and
     * programs specified by the plugin, using the DSSI select_program
     * call.  No host should ever deliver a program change or bank
     * select controller to a plugin via run_synth.
     */

    void dssi_run_synth(unsigned long SampleCount, snd_seq_event_t *Events, unsigned long EventCount) {
    }

    /**
     * run_synth_adding()
     *
     * This member is a function pointer that runs an instance of a
     * synth for a block, adding its outputs to the values already
     * present at the output ports.  This is provided for symmetry
     * with LADSPA run_adding(), and is equally optional.  A plugin
     * that does not provide it must set this member to NULL.
     */

    void dssi_run_synth_adding(unsigned long SampleCount, snd_seq_event_t *Events, unsigned long EventCount) {
    }

    /**
     * run_multiple_synths()
     *
     * This member is a function pointer that runs multiple synth
     * instances for a block.  This is very similar to run_synth(),
     * except that Instances, Events, and EventCounts each point to
     * arrays that hold the LADSPA handles, event buffers, and
     * event counts for each of InstanceCount instances.  That is,
     * Instances points to an array of InstanceCount pointers to
     * DSSI plugin instantiations, Events points to an array of
     * pointers to each instantiation's respective event list, and
     * EventCounts points to an array containing each instantiation's
     * respective event count.
     *
     * A host using this function must guarantee that ALL active
     * instances of the plugin are represented in each call to the
     * function -- that is, a host may not call run_multiple_synths()
     * for some instances of a given plugin and then call run_synth()
     * as well for others.  'All .. instances of the plugin' means
     * every instance sharing the same LADSPA label and shared object
     * (*.so) file (rather than every instance sharing the same *.so).
     * 'Active' means any instance for which activate() has been called
     * but deactivate() has not.
     *
     * A plugin may provide this function, run_synths() (see above),
     * both, or neither (if it not in fact a synth).  A plugin that
     * does not provide this function must set this member to NULL.
     * Plugin authors implementing run_multiple_synths are strongly
     * encouraged to implement run_synth as well if at all possible,
     * to aid simplistic hosts, even where it would be less efficient
     * to use it.
     */

    void dssi_run_multiple_synths(/*unsigned long InstanceCount, LADSPA_Handle* Instances,*/ unsigned long SampleCount, snd_seq_event_t **Events, unsigned long* EventCounts) {
    }

    /**
     * run_multiple_synths_adding()
     *
     * This member is a function pointer that runs multiple synth
     * instances for a block, adding each synth's outputs to the
     * values already present at the output ports.  This is provided
     * for symmetry with both the DSSI run_multiple_synths() and LADSPA
     * run_adding() functions, and is equally optional.  A plugin
     * that does not provide it must set this member to NULL.
     */

    void dssi_run_multiple_synths_adding(/*unsigned long InstanceCount, LADSPA_Handle *Instances,*/ unsigned long SampleCount, snd_seq_event_t** Events, unsigned long *EventCounts) {
    }

//------------------------------
public: // ladspa callbacks
//------------------------------

  static
  LADSPA_Handle ladspa_instantiate_callback(const struct _LADSPA_Descriptor* Descriptor, unsigned long SampleRate) {
    return nullptr;
  }

  static
   void ladspa_connect_port_callback(LADSPA_Handle Instance, unsigned long Port, LADSPA_Data * DataLocation) {
    KODE_DssiPlugin* plugin = (KODE_DssiPlugin*)Instance;
    plugin->ladspa_connect_port(Port,DataLocation);
   }

  static
  void ladspa_activate_callback(LADSPA_Handle Instance) {
    KODE_DssiPlugin* plugin = (KODE_DssiPlugin*)Instance;
    plugin->ladspa_activate();
  }

  static
  void ladspa_run_callback(LADSPA_Handle Instance, unsigned long SampleCount) {
    KODE_DssiPlugin* plugin = (KODE_DssiPlugin*)Instance;
    plugin->ladspa_run(SampleCount);
  }

  static
  void ladspa_run_adding_callback(LADSPA_Handle Instance, unsigned long SampleCount) {
    KODE_DssiPlugin* plugin = (KODE_DssiPlugin*)Instance;
    plugin->ladspa_run_adding(SampleCount);
  }

  static
  void ladspa_set_run_adding_gain_callback(LADSPA_Handle Instance, LADSPA_Data Gain) {
    KODE_DssiPlugin* plugin = (KODE_DssiPlugin*)Instance;
    plugin->ladspa_set_run_adding_gain(Gain);
  }

  static
  void ladspa_deactivate_callback(LADSPA_Handle Instance) {
    KODE_DssiPlugin* plugin = (KODE_DssiPlugin*)Instance;
    plugin->ladspa_deactivate();
  }

 static
  void ladspa_cleanup_callback(LADSPA_Handle Instance) {
    KODE_DssiPlugin* plugin = (KODE_DssiPlugin*)Instance;
    plugin->ladspa_cleanup();
  }

//------------------------------
private: // dssi callbacks
//------------------------------

  static
  char* dssi_configure_callback(LADSPA_Handle Instance, const char *Key, const char *Value) {
    KODE_DssiPlugin* plugin = (KODE_DssiPlugin*)Instance;
    return plugin->dssi_configure(Key,Value);
  }

  static
  const DSSI_Program_Descriptor* dssi_get_program_callback(LADSPA_Handle Instance, unsigned long Index) {
    KODE_DssiPlugin* plugin = (KODE_DssiPlugin*)Instance;
    return plugin->dssi_get_program(Index);
  }

  static
  void dssi_select_program_callback(LADSPA_Handle Instance, unsigned long Bank, unsigned long Program) {
    KODE_DssiPlugin* plugin = (KODE_DssiPlugin*)Instance;
    return plugin->dssi_select_program(Bank,Program);
  }

  static
  int dssi_get_midi_controller_for_port_callback(LADSPA_Handle Instance, unsigned long Port) {
    KODE_DssiPlugin* plugin = (KODE_DssiPlugin*)Instance;
    return plugin->dssi_get_midi_controller_for_port(Port);
  }

  static
  void dssi_run_synth_callback(LADSPA_Handle Instance, unsigned long SampleCount, snd_seq_event_t* Events, unsigned long EventCount) {
    KODE_DssiPlugin* plugin = (KODE_DssiPlugin*)Instance;
    plugin->dssi_run_synth(SampleCount,Events,EventCount);
  }

  static
  void dssi_run_synth_adding_callback(LADSPA_Handle Instance, unsigned long SampleCount, snd_seq_event_t* Events, unsigned long EventCount) {
    KODE_DssiPlugin* plugin = (KODE_DssiPlugin*)Instance;
    plugin->dssi_run_synth_adding(SampleCount,Events,EventCount);
  }

  static
  void dssi_run_multiple_synths_callback(unsigned long InstanceCount, LADSPA_Handle* Instances, unsigned long SampleCount, snd_seq_event_t** Events, unsigned long* EventCounts) {
    //KODE_DssiPlugin* plugin = (KODE_DssiPlugin*)Instance;
    //return plugin->dssi_configure(Key,Value);
  }

  static
  void dssi_run_multiple_synths_adding_callback(unsigned long InstanceCount, LADSPA_Handle* Instances, unsigned long SampleCount, snd_seq_event_t** Events, unsigned long*EventCounts) {
    //KODE_DssiPlugin* plugin = (KODE_DssiPlugin*)Instance;
    //plugin->dssi_configure(Key,Value);
  }

//------------------------------
public:
//------------------------------

  const DSSI_Descriptor* entrypoint(int32_t AIndex) {
    return nullptr;
  }

};



//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#define DSSI_ENTRYPOINT_SYMBOL asm ("dssi_descriptor");
const DSSI_Descriptor* dssi_entrypoint(uint32_t index) DSSI_ENTRYPOINT_SYMBOL;

//----------

#define KODE_DSSI_PLUGIN_ENTRYPOINT(D,I,E)                  \
                                                            \
  KODE_DssiPlugin<D,I,E> DSSI_PLUGIN;                       \
                                                            \
  /* ----- */                                               \
                                                            \
  __attribute__ ((visibility ("default")))                  \
  const DSSI_Descriptor* dssi_entrypoint(uint32_t index) {  \
    KODE_Print("index %i\n",index);                         \
    return DSSI_PLUGIN.entrypoint(index);                   \
  }                                                         \


//----------------------------------------------------------------------
#endif
