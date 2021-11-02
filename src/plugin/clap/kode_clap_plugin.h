#ifndef kode_clap_plugin_included
#define kode_clap_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/clap/kode_clap.h"
#include "plugin/clap/kode_clap_instance.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

template <class DESCRIPTOR, class INSTANCE, class EDITOR>
class KODE_ClapPluginEntry {

//------------------------------
private:
//------------------------------

  DESCRIPTOR*                     MDescriptor     = nullptr;
  struct clap_plugin_descriptor*  MClapDescriptor = nullptr;

//------------------------------
public:
//------------------------------

  KODE_ClapPluginEntry() {
  }

  //----------

  ~KODE_ClapPluginEntry() {
    cleanupDescriptor();
  }

//------------------------------
public:
//------------------------------


//------------------------------
public:
//------------------------------

  void initDescriptor() {
    MDescriptor = new DESCRIPTOR();                                                     // TODO: delete
    MClapDescriptor = (clap_plugin_descriptor*)malloc(sizeof(clap_plugin_descriptor));  // TODO: free
    MClapDescriptor->clap_version = CLAP_VERSION;
    MClapDescriptor->id           = "";
    MClapDescriptor->name         = MDescriptor->name;
    MClapDescriptor->vendor       = MDescriptor->author;
    MClapDescriptor->url          = "";
    MClapDescriptor->manual_url   = "";
    MClapDescriptor->support_url  = "";
    MClapDescriptor->version      = "";
    MClapDescriptor->description  = "";
    MClapDescriptor->keywords     = "";
    MClapDescriptor->plugin_type  = CLAP_PLUGIN_AUDIO_EFFECT;
  }

  //----------

  void cleanupDescriptor() {
    if (MClapDescriptor) free(MClapDescriptor);
    MClapDescriptor = nullptr;
    if (MDescriptor) delete MDescriptor;
    MDescriptor = nullptr;
  }

//------------------------------
public: // instance callbacks
//------------------------------

  /*
    Must be called after creating the plugin.
    If init returns false, the host must destroy the plugin instance
  */

  static bool clap_instance_init_callback(const struct clap_plugin* plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_instance_init();
  }

  /*
    Free the plugin and its resources.
    It is not required to deactivate the plugin prior to this call.
  */

  static void clap_instance_destroy_callback(const struct clap_plugin* plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_instance_destroy();
    // !!!
    delete instance;
    //free(plugin);
  }

  /*
    activation/deactivation
    [main-thread]
  */

  static bool clap_instance_activate_callback(const struct clap_plugin* plugin, double sample_rate) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_instance_activate(sample_rate);
  }

  static void clap_instance_deactivate_callback(const struct clap_plugin* plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_instance_deactivate();
  }

  /*
    Set to true before processing, and to false before sending the plugin to sleep.
    [audio-thread]
  */

  static bool clap_instance_start_processing_callback(const struct clap_plugin* plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_instance_start_processing();
  }

  static void clap_instance_stop_processing_callback(const struct clap_plugin* plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_instance_stop_processing();
  }

  /*
    process audio, events, ...
    [audio-thread]
  */

  static clap_process_status clap_instance_process_callback(const struct clap_plugin* plugin, const clap_process *process) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_instance_process(process);
  }

  /*
    Query an extension.
    The returned pointer is owned by the plugin.
    [thread-safe]
  */

  static const void* clap_instance_get_extension_callback(const struct clap_plugin* plugin, const char *id) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_instance_get_extension(id);
  }

  /*
    Called by the host on the main thread in response to a previous call to:
    host->request_callback(host);
    [main-thread]
  */

  static void clap_instance_on_main_thread_callback(const struct clap_plugin* plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_instance_on_main_thread();
  }

//------------------------------
public: // entry callbacks
//------------------------------

  /*
  */

  bool clap_entry_init(const char *plugin_path) {
    initDescriptor();
    return true;
  }

  /*
  */

  void clap_entry_deinit(void) {
    cleanupDescriptor();
  }

  /*
    Get the number of plugins available.
    [thread-safe]
  */

  uint32_t clap_entry_get_plugin_count(void) {
    return 1;
  }

  /*
    Retrieves a plugin descriptor by its index.
    Returns null in case of error.
    The descriptor does not need to be freed.
    [thread-safe]
  */

  const clap_plugin_descriptor* clap_entry_get_plugin_descriptor(uint32_t index) {
    return MClapDescriptor;
    //return nullptr;
  }

  /*
    Create a clap_plugin by its plugin_id.
    The returned pointer must be freed by calling plugin->destroy(plugin);
    The plugin is not allowed to use the host callbacks in the create method.
    Returns null in case of error.
    [thread-safe]
  */

  const clap_plugin* clap_entry_create_plugin(const clap_host *host, const char *plugin_id) {
    KODE_Instance* instance = new INSTANCE(MDescriptor);                      // TODO: delete
    KODE_ClapInstance* clapinstance = new KODE_ClapInstance(host,instance);   // TODO: delete
    clap_plugin* plugin = (clap_plugin*)malloc(sizeof(clap_plugin));          // TODO: free
    plugin->desc              = MClapDescriptor;
    plugin->plugin_data       = clapinstance;
    plugin->init              = clap_instance_init_callback;
    plugin->destroy           = clap_instance_destroy_callback;
    plugin->activate          = clap_instance_activate_callback;
    plugin->deactivate        = clap_instance_deactivate_callback;
    plugin->start_processing  = clap_instance_start_processing_callback;
    plugin->stop_processing   = clap_instance_stop_processing_callback;
    plugin->process           = clap_instance_process_callback;
    plugin->get_extension     = clap_instance_get_extension_callback;
    plugin->on_main_thread    = clap_instance_on_main_thread_callback;
    return plugin;
 }

  /*
    Get the number of invalidation source.
  */

  uint32_t clap_entry_get_invalidation_sources_count(void) {
    return 0;
  }

  /*
    Get the invalidation source by its index.
    [thread-safe]
  */

  const clap_plugin_invalidation_source* clap_entry_get_invalidation_sources(uint32_t index) {
    return nullptr;
  }

  /*
    In case the host detected a invalidation event, it can call refresh() to let
    the plugin_entry scan the set of plugins available.
  */

  void clap_entry_refresh(void) {
  }

};

//----------------------------------------------------------------------
//
// entrypoint
//
//----------------------------------------------------------------------

/*
  This interface is the entry point of the dynamic library.
  There is an invalidation mechanism for the set of plugins which is based on
  files. The host can watch the plugin DSO's mtime and a set of files's mtime
  provided by get_clap_invalidation_source().
  The set of plugins must not change, except during a call to refresh() by the
  host.
  Every methods must be thread-safe.
*/

//----------------------------------------------------------------------

//#define CLAP_ENTRYPOINT_SYMBOL asm ("clap_plugin_entry")
//struct clap_plugin_entry CLAP_PLUGIN_ENTRY CLAP_ENTRYPOINT_SYMBOL

//----------

#define KODE_CLAP_PLUGIN_ENTRYPOINT(D,I,E)                              \
                                                                        \
  KODE_ClapPluginEntry<D,I,E> CLAP_PLUGIN;                              \
                                                                        \
  /* ----- */                                                           \
                                                                        \
  bool clap_entry_init_callback(const char *plugin_path)                                              { return  CLAP_PLUGIN.clap_entry_init(plugin_path); }                 \
  void clap_entry_deinit_callback()                                                                   {         CLAP_PLUGIN.clap_entry_deinit(); }                          \
  uint32_t clap_entry_get_plugin_count_callback()                                                     { return  CLAP_PLUGIN.clap_entry_get_plugin_count(); }                \
  const clap_plugin_descriptor* clap_entry_get_plugin_descriptor_callback(uint32_t index)             { return  CLAP_PLUGIN.clap_entry_get_plugin_descriptor(index); }      \
  const clap_plugin* clap_entry_create_plugin_callback(const clap_host *host, const char *plugin_id)  { return  CLAP_PLUGIN.clap_entry_create_plugin(host,plugin_id); }     \
  uint32_t clap_entry_get_invalidation_sources_count_callback()                                       { return  CLAP_PLUGIN.clap_entry_get_invalidation_sources_count(); }  \
  const clap_plugin_invalidation_source* clap_entry_get_invalidation_sources_callback(uint32_t index) { return  CLAP_PLUGIN.clap_entry_get_invalidation_sources(index); }   \
  void clap_entry_refresh_callback()                                                                  {         CLAP_PLUGIN.clap_entry_refresh(); }                         \
                                                                                  \
  /* ----- */                                                                     \
                                                                                  \
  /*CLAP_EXPORT*/                                                                 \
  __attribute__ ((visibility ("default")))                                        \
  struct clap_plugin_entry CLAP_PLUGIN_ENTRY_STRUCT asm ("clap_plugin_entry") = { \
    CLAP_VERSION,                                                                 \
    clap_entry_init_callback,                                                     \
    clap_entry_deinit_callback,                                                   \
    clap_entry_get_plugin_count_callback,                                         \
    clap_entry_get_plugin_descriptor_callback,                                    \
    clap_entry_create_plugin_callback,                                            \
    clap_entry_get_invalidation_sources_count_callback,                           \
    clap_entry_get_invalidation_sources_callback,                                 \
    clap_entry_refresh_callback,                                                  \
  };                                                                              \


//----------------------------------------------------------------------
#endif

//----------------------------------------------------------------------

/*
  (simplified)
  > g++ --version
  g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
  > g++ -Wall -g -I../src -c build.cpp -o build.o
  > g++  -o kode3_debug build.o
  warning: ‘visibility’ attribute ignored [-Wattributes]|
*/
