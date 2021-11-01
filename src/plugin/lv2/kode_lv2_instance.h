#ifndef kode_lv2_instance_included
#define kode_lv2_instance_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_instance.h"
#include "plugin/lv2/kode_lv2.h"

//----------------------------------------------------------------------

class KODE_Lv2Instance {

//------------------------------
private:
//------------------------------

  KODE_Instance*            MInstance       = nullptr;

  const LV2_Descriptor*     MLv2Descriptor  = nullptr;
  double                    MLv2SampleRate  = 0.0;
  const char*               MLv2BundlePath  = nullptr;
  const LV2_Feature* const* MLv2Features    = nullptr;

  uint32_t                  MNumPorts       = 0;
  void**                    MPortPointers   = nullptr;

//------------------------------
public:
//------------------------------

  // we must delete ADescriptor & AInstance

  KODE_Lv2Instance(KODE_Descriptor* ADescriptor, KODE_Instance* AInstance) {
    KODE_PRINT;
    MInstance = AInstance;
  }

  //----------

  virtual ~KODE_Lv2Instance() {
    KODE_PRINT;
  }

//------------------------------
public: // lv2
//------------------------------

  /*
    Instantiate the plugin.
    Note that instance initialisation should generally occur in activate()
    rather than here. If a host calls instantiate(), it MUST call cleanup()
    at some point in the future.

    descriptor
      Descriptor of the plugin to instantiate.
    sample_rate
      Sample rate, in Hz, for the new plugin instance.
    bundle_path
      Path to the LV2 bundle which contains this plugin binary.
      It MUST include the trailing directory separator so that simply
      appending a filename will yield the path to that file in the bundle.
    features
      A NULL terminated array of LV2_Feature structs which represent the
      features the host supports. Plugins may refuse to instantiate if required
      features are not found here. However, hosts MUST NOT use this as a
      discovery mechanism: instead, use the RDF data to determine which
      features are required and do not attempt to instantiate unsupported
      plugins at all. This parameter MUST NOT be NULL, i.e. a host that
      supports no features MUST pass a single element array containing NULL.

    return
      A handle for the new plugin instance,
      or NULL if instantiation has failed.
  */

  void lv2_instantiate(const struct LV2_Descriptor* descriptor, double sample_rate, const char* bundle_path, const LV2_Feature* const* features) {
    KODE_PRINT;
    MLv2Descriptor  = descriptor;
    MLv2SampleRate  = sample_rate;
    MLv2BundlePath  = bundle_path;
    MLv2Features    = features;
  }

  //----------

  /*
    Connect a port on a plugin instance to a memory location.
    Plugin writers should be aware that the host may elect to use the same
    buffer for more than one port and even use the same buffer for both
    input and output (see lv2:inPlaceBroken in lv2.ttl).
    If the plugin has the feature lv2:hardRTCapable then there are various
    things that the plugin MUST NOT do within the connect_port() function;
    see lv2core.ttl for details.
    connect_port() MUST be called at least once for each port before run()
    is called, unless that port is lv2:connectionOptional. The plugin must
    pay careful attention to the block size passed to run() since the block
    allocated may only just be large enough to contain the data, and is not
    guaranteed to remain constant between run() calls.
    connect_port() may be called more than once for a plugin instance to
    allow the host to change the buffers that the plugin is reading or
    writing. These calls may be made before or after activate() or
    deactivate() calls.

    instance
      Plugin instance containing the port.
    port
      Index of the port to connect. The host MUST NOT try to connect a port
      index that is not defined in the plugin's RDF data. If it does, the
      plugin's behaviour is undefined (a crash is likely).
    data_location
      Pointer to data of the type defined by the port type in the plugin's RDF
      data (for example, an array of float for an lv2:AudioPort). This pointer
      must be stored by the plugin instance and used to read/write data when
      run() is called. Data present at the time of the connect_port() call
      MUST NOT be considered meaningful.
  */

  void lv2_connect_port(uint32_t port, void* data_location) {
    KODE_PRINT;
    MPortPointers[port] = data_location;
  }

  //----------

  /*
    Initialise a plugin instance and activate it for use.
    This is separated from instantiate() to aid real-time support and so
    that hosts can reinitialise a plugin instance by calling deactivate()
    and then activate(). In this case the plugin instance MUST reset all
    state information dependent on the history of the plugin instance except
    for any data locations provided by connect_port(). If there is nothing
    for activate() to do then this field may be NULL.
    When present, hosts MUST call this function once before run() is called
    for the first time. This call SHOULD be made as close to the run() call
    as possible and indicates to real-time plugins that they are now live,
    however plugins MUST NOT rely on a prompt call to run() after
    activate().
    The host MUST NOT call activate() again until deactivate() has been
    called first. If a host calls activate(), it MUST call deactivate() at
    some point in the future. Note that connect_port() may be called before
    or after activate().
  */

  void lv2_activate() {
    KODE_PRINT;
  }

  //----------

  /*
    Run a plugin instance for a block.
    Note that if an activate() function exists then it must be called before
    run(). If deactivate() is called for a plugin instance then run() may
    not be called until activate() has been called again.
    If the plugin has the feature lv2:hardRTCapable then there are various
    things that the plugin MUST NOT do within the run() function (see
    lv2core.ttl for details).
    As a special case, when `sample_count` is 0, the plugin should update
    any output ports that represent a single instant in time (for example,
    control ports, but not audio ports). This is particularly useful for
    latent plugins, which should update their latency output port so hosts
    can pre-roll plugins to compute latency. Plugins MUST NOT crash when
    `sample_count` is 0.

    instance
      Instance to be run.
    sample_count
      The block size (in samples) for which the plugin instance must run.
  */

  void lv2_run(uint32_t sample_count) {
    //KODE_PRINT;
  }

  //----------

  /*
    Deactivate a plugin instance (counterpart to activate()).
    Hosts MUST deactivate all activated instances after they have been run()
    for the last time. This call SHOULD be made as close to the last run()
    call as possible and indicates to real-time plugins that they are no
    longer live, however plugins MUST NOT rely on prompt deactivation. If
    there is nothing for deactivate() to do then this field may be NULL
    Deactivation is not similar to pausing since the plugin instance will be
    reinitialised by activate(). However, deactivate() itself MUST NOT fully
    reset plugin state. For example, the host may deactivate a plugin, then
    store its state (using some extension to do so).
    Hosts MUST NOT call deactivate() unless activate() was previously
    called. Note that connect_port() may be called before or after
    deactivate().
  */

  void lv2_deactivate() {
    KODE_PRINT;
  }

  //----------

  /*
    Clean up a plugin instance (counterpart to instantiate()).
    Once an instance of a plugin has been finished with it must be deleted
    using this function. The instance handle passed ceases to be valid after
    this call.
    If activate() was called for a plugin instance then a corresponding call
    to deactivate() MUST be made before cleanup() is called. Hosts MUST NOT
    call cleanup() unless instantiate() was previously called.
  */

  void lv2_cleanup() {
    KODE_PRINT;
  }

//------------------------------
public:
//------------------------------

};

//----------------------------------------------------------------------
#endif
