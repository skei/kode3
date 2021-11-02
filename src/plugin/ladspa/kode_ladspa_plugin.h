#ifndef kode_ladspa_plugin_included
#define kode_ladspa_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/ladspa/kode_ladspa.h"
#include "plugin/ladspa/kode_ladspa_instance.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

template <class DESCRIPTOR, class INSTANCE, class EDITOR>
class KODE_LadspaPlugin {

//------------------------------
private:
//------------------------------

  DESCRIPTOR*             MDescriptor             = nullptr;
  LADSPA_Descriptor*      MLadspaDescriptor       = nullptr;
  LADSPA_PortDescriptor*  MLadspaPortDescriptors  = nullptr;
  char**                  MLadspaPortNames        = nullptr;
  LADSPA_PortRangeHint*   MLadspaPortRangeHints   = nullptr;

//------------------------------
public:
//------------------------------

  KODE_LadspaPlugin() {
    KODE_PRINT;
  }

  //----------

  ~KODE_LadspaPlugin() {
    KODE_PRINT;
    if (MLadspaPortDescriptors) free(MLadspaPortDescriptors);
    if (MLadspaPortNames)       free(MLadspaPortNames);
    if (MLadspaPortRangeHints)  free(MLadspaPortRangeHints);
    if (MLadspaDescriptor)      free(MLadspaDescriptor);
    if (MDescriptor)            delete MDescriptor;
  }

//------------------------------
public:
//------------------------------

  uint32_t init_ports() {
    uint32_t num_ports = 0;
    MLadspaPortDescriptors  = (LADSPA_PortDescriptor*)malloc(num_ports * sizeof(LADSPA_PortDescriptor));
    MLadspaPortNames        = (char**)malloc(num_ports * sizeof(char*));
    MLadspaPortRangeHints   = (LADSPA_PortRangeHint*)malloc(num_ports * sizeof(LADSPA_PortRangeHint));
    return num_ports;
  }

  //----------

  /*
    LADSPA_PROPERTY_REALTIME indicates that the plugin has a real-time
    dependency (e.g. listens to a MIDI device) and so its output must not be
    cached or subject to significant latency.
    LADSPA_PROPERTY_INPLACE_BROKEN indicates that the plugin may cease to work
    correctly if the host elects to use the same data location for both input
    and output (see connect_port()). This should be avoided as enabling this
    flag makes it impossible for hosts to use the plugin to process audio
    `in-place.'
    LADSPA_PROPERTY_HARD_RT_CAPABLE indicates that the plugin is capable of
    running not only in a conventional host but also in a `hard real-time'
    environment. To qualify for this the plugin must satisfy all of the
    following:
    (1) The plugin must not use malloc(), free() or other heap memory
        management within its run() or run_adding() functions. All new memory
        used in run() must be managed via the stack. These restrictions only
        apply to the run() function.
    (2) The plugin will not attempt to make use of any library functions with
        the exceptions of functions in the ANSI standard C and C maths
        libraries, which the host is expected to provide.
    (3) The plugin will not access files, devices, pipes, sockets, IPC or any
        other mechanism that might result in process or thread blocking.
    (4) The plugin will take an amount of time to execute a run() or run
        adding() call approximately of form (A+B*SampleCount) where A and B
        depend on the machine and host in use. This amount of time may not
        depend on input signals or plugin state. The host is left the
        responsibility to perform timings to estimate upper bounds for A and B.
  */

  void init_descriptor() {
    MDescriptor = new DESCRIPTOR();
    uint32_t num_ports = init_ports();
    MLadspaDescriptor = (LADSPA_Descriptor*)malloc(sizeof(LADSPA_Descriptor));
    MLadspaDescriptor->UniqueID           = MDescriptor->short_id;
    MLadspaDescriptor->Label              = MDescriptor->name; // safe_name ??
    MLadspaDescriptor->Properties         = LADSPA_PROPERTY_REALTIME /*| LADSPA_PROPERTY_INPLACE_BROKEN*/ | LADSPA_PROPERTY_HARD_RT_CAPABLE;
    MLadspaDescriptor->Name               = MDescriptor->name;
    MLadspaDescriptor->Maker              = MDescriptor->author;
    MLadspaDescriptor->Copyright          = "";
    MLadspaDescriptor->PortCount          = num_ports;
    MLadspaDescriptor->PortDescriptors    = MLadspaPortDescriptors;
    MLadspaDescriptor->PortNames          = MLadspaPortNames;
    MLadspaDescriptor->PortRangeHints     = MLadspaPortRangeHints;
    MLadspaDescriptor->ImplementationData = MDescriptor;
  }

//------------------------------
public: // ladspa callbacks
//------------------------------

  /*
    Instantiates a plugin.
    A handle is returned indicating the new plugin instance. The instantiation
    function accepts a sample rate as a parameter. The plugin descriptor from
    which this instantiate function was found must also be passed.
    This function must return NULL if instantiation fails.
    Note that instance initialisation should generally occur in activate()
    rather than here.
  */

  static
  LADSPA_Handle ladspa_instantiate_callback(const struct _LADSPA_Descriptor* Descriptor, unsigned long SampleRate) {
    KODE_Descriptor*      descriptor  = (KODE_Descriptor*)Descriptor->ImplementationData;
    KODE_LadspaInstance*  instance    = new KODE_LadspaInstance(descriptor,SampleRate);
    return instance;
  }

  /*
    connects a port on an instantiated plugin to a memory location at which a
    block of data for the port will be read/written. The data location is
    expected to be an array of LADSPA_Data for audio ports or a single
    LADSPA_Data value for control ports. Memory issues will be managed by the
    host. The plugin must read/write the data at these locations every time
    run() or run_adding() is called and the data present at the time of this
    connection call should not be considered meaningful.

    connect_port() may be called more than once for a plugin instance to allow
    the host to change the buffers that the plugin is reading or writing. These
    calls may be made before or after activate() or deactivate() calls.

    connect_port() must be called at least once for each port before run() or
    run_adding() is called. When working with blocks of LADSPA_Data the plugin
    should pay careful attention to the block size passed to the run function
    as the block allocated may only just be large enough to contain the block
    of samples.

    Plugin writers should be aware that the host may elect to use the same
    buffer for more than one port and even use the same buffer for both input
    and output (see LADSPA_PROPERTY_INPLACE_BROKEN). However, overlapped
    buffers or use of a single buffer for both audio and control data may
    result in unexpected behaviour.
  */

  static
   void ladspa_connect_port_callback(LADSPA_Handle Instance, unsigned long Port, LADSPA_Data* DataLocation) {
    KODE_LadspaInstance* instance = (KODE_LadspaInstance*)Instance;
    instance->ladspa_connect_port(Port,DataLocation);
   }

  /*
    This member is a function pointer that initialises a plugin instance and
    activates it for use. This is separated from instantiate() to aid real-time
    support and so that hosts can reinitialise a plugin instance by calling
    deactivate() and then activate(). In this case the plugin instance must
    reset all state information dependent on the history of the plugin instance
    except for any data locations provided by connect_port() and any gain set
    by set_run_adding_gain(). If there is nothing for activate() to do then the
    plugin writer may provide a NULL rather than an empty function.

    When present, hosts must call this function once before run() (or
    run_adding()) is called for the first time. This call should be made as
    close to the run() call as possible and indicates to real-time plugins that
    they are now live. Plugins should not rely on a prompt call to run() after
    activate(). activate() may not be called again unless deactivate() is
    called first. Note that connect_port() may be called before or after a call
    to activate().
  */

  static
  void ladspa_activate_callback(LADSPA_Handle Instance) {
    KODE_LadspaInstance* instance = (KODE_LadspaInstance*)Instance;
    instance->ladspa_activate();
  }

  /*
    runs an instance of a plugin for a block. Two parameters are required:
    the first is a handle to the particular instance to be run and the second
    indicates the block size (in samples) for which the plugin instance may
    run.

    Note that if an activate() function exists then it must be called before
    run() or run_adding(). If deactivate() is called for a plugin instance then
    the plugin instance may not be reused until activate() has been called
    again.

    If the plugin has the property LADSPA_PROPERTY_HARD_RT_CAPABLE then there
    are various things that the plugin should not do within the run() or
    run_adding() functions (see above).
  */

  static
  void ladspa_run_callback(LADSPA_Handle Instance, unsigned long SampleCount) {
    KODE_LadspaInstance* instance = (KODE_LadspaInstance*)Instance;
    instance->ladspa_run(SampleCount);
  }

  /*
    runs an instance of a plugin for a block. This has identical behaviour to
    run() except in the way data is output from the plugin. When run() is used,
    values are written directly to the memory areas associated with the output
    ports. However when run_adding() is called, values must be added to the
    values already present in the memory areas. Furthermore, output values
    written must be scaled by the current gain set by set_run_adding_gain()
    (see below) before addition.

    run_adding() is optional. When it is not provided by a plugin, this
    function pointer must be set to NULL. When it is provided, the function
    set_run_adding_gain() must be provided also.
  */

  static
  void ladspa_run_adding_callback(LADSPA_Handle Instance, unsigned long SampleCount) {
    KODE_LadspaInstance* instance = (KODE_LadspaInstance*)Instance;
    instance->ladspa_run_adding(SampleCount);
  }

  /*
    sets the output gain for use when run_adding() is called (see above).
    If this function is never called the gain is assumed to default to 1.
    Gain information should be retained when activate() or deactivate() are
    called.

    This function should be provided by the plugin if and only if the
    run_adding() function is provided. When it is absent this function pointer
    must be set to NULL.
  */

  static
  void ladspa_set_run_adding_gain_callback(LADSPA_Handle Instance, LADSPA_Data Gain) {
    KODE_LadspaInstance* instance = (KODE_LadspaInstance*)Instance;
    instance->ladspa_set_run_adding_gain(Gain);
  }

  /*
    This is the counterpart to activate() (see above). If there is nothing for
    deactivate() to do then the plugin writer may provide a NULL rather than
    an empty function.

    Hosts must deactivate all activated units after they have been run() (or
    run_adding()) for the last time. This call should be made as close to the
    last run() call as possible and indicates to real-time plugins that they
    are no longer live. Plugins should not rely on prompt deactivation. Note
    that connect_port() may be called before or after a call to deactivate().

    Deactivation is not similar to pausing as the plugin instance will be
    reinitialised when activate() is called to reuse it.
  */

  static
  void ladspa_deactivate_callback(LADSPA_Handle Instance) {
    KODE_LadspaInstance* instance = (KODE_LadspaInstance*)Instance;
    instance->ladspa_deactivate();
  }

  /*
    Once an instance of a plugin has been finished with it can be deleted
    using the following function. The instance handle passed ceases to be
    valid after this call.
    If activate() was called for a plugin instance then a corresponding call to
    deactivate() must be made before cleanup() is called.
  */

  static
  void ladspa_cleanup_callback(LADSPA_Handle Instance) {
    KODE_LadspaInstance* instance = (KODE_LadspaInstance*)Instance;
    instance->ladspa_cleanup();
    delete instance;
  }

//------------------------------
public:
//------------------------------

  LADSPA_Descriptor* entrypoint(uint32_t AIndex) {
    init_descriptor();
    return MLadspaDescriptor;
  }

};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

/*
  The exact mechanism by which plugins are loaded is host-dependent, however
  all most hosts will need to know is the name of shared object file containing
  the plugin types. To allow multiple hosts to share plugin types, hosts may
  wish to check for environment variable LADSPA_PATH. If present, this should
  contain a colon-separated path indicating directories that should be searched
  (in order) when loading plugin types.

  A plugin programmer must include a function called "ladspa_descriptor" with
  the following function prototype within the shared object file. This function
  will have C-style linkage (if you are using C++ this is taken care of by the
  'extern "C"' clause at the top of the file).

  A host will find the plugin shared object file by one means or another, find
  the ladspa_descriptor() function, call it, and proceed from there.

  Plugin types are accessed by index (not ID) using values from 0 upwards.
  Out of range indexes must result in this function returning NULL, so the
  plugin count can be determined by checking for the least index that results
  in NULL being returned.
*/

//----------------------------------------------------------------------

#define LADSPA_ENTRYPOINT_SYMBOL asm ("ladspa_descriptor");
const LADSPA_Descriptor* ladspa_entrypoint() LADSPA_ENTRYPOINT_SYMBOL;

//----------

#define KODE_LADSPA_PLUGIN_ENTRYPOINT(D,I,E)                    \
                                                                \
  KODE_LadspaPlugin<D,I,E> LADSPA_PLUGIN;                       \
                                                                \
  /* ----- */                                                   \
                                                                \
  __attribute__ ((visibility ("default")))                      \
  const LADSPA_Descriptor* ladspa_entrypoint(uint32_t index) {  \
    return LADSPA_PLUGIN.entrypoint(index);                     \
  }                                                             \


//----------------------------------------------------------------------
#endif
