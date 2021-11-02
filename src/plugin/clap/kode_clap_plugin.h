#ifndef kode_clap_plugin_included
#define kode_clap_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/clap/kode_clap.h"
#include "plugin/clap/kode_clap_instance.h"

//----------------------------------------------------------------------

KODE_Descriptor*  _kode_clap_createDescriptor();
KODE_Instance*    _kode_clap_createInstance(KODE_Descriptor* ADescriptor);


//clap_plugin_descriptor  CLAP_GLOBAL_DESCRIPTOR = {};

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
    //if (MClapDescriptor) free(MClapDescriptor);
    //if (MDescriptor) delete MDescriptor;
  }


//------------------------------
public:
//------------------------------

};

//----------------------------------------------------------------------
//
// instance callbacks
//
//----------------------------------------------------------------------

/*
  Must be called after creating the plugin.
  If init returns false, the host must destroy the plugin instance
*/

bool clap_instance_init_callback(const struct clap_plugin* plugin) {
  KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
  return instance->clap_instance_init();
}

/*
  Free the plugin and its resources.
  It is not required to deactivate the plugin prior to this call.
*/

void clap_instance_destroy_callback(const struct clap_plugin* plugin) {
  KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
  instance->clap_instance_destroy();
  delete instance; // !!!
  //free(plugin);
}

/*
  activation/deactivation
  [main-thread]
*/

bool clap_instance_activate_callback(const struct clap_plugin* plugin, double sample_rate) {
  KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
  return instance->clap_instance_activate(sample_rate);
}

void clap_instance_deactivate_callback(const struct clap_plugin* plugin) {
  KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
  instance->clap_instance_deactivate();
}

/*
  Set to true before processing, and to false before sending the plugin to sleep.
  [audio-thread]
*/

bool clap_instance_start_processing_callback(const struct clap_plugin* plugin) {
  KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
  return instance->clap_instance_start_processing();
}

void clap_instance_stop_processing_callback(const struct clap_plugin* plugin) {
  KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
  instance->clap_instance_stop_processing();
}

/*
  process audio, events, ...
  [audio-thread]
*/

clap_process_status clap_instance_process_callback(const struct clap_plugin* plugin, const clap_process *process) {
  KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
  return instance->clap_instance_process(process);
}

/*
  Query an extension.
  The returned pointer is owned by the plugin.
  [thread-safe]
*/

const void* clap_instance_get_extension_callback(const struct clap_plugin* plugin, const char *id) {
  KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
  return instance->clap_instance_get_extension(id);
}

/*
  Called by the host on the main thread in response to a previous call to:
  host->request_callback(host);
  [main-thread]
*/

void clap_instance_on_main_thread_callback(const struct clap_plugin* plugin) {
  KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
  instance->clap_instance_on_main_thread();
}

//----------------------------------------------------------------------
//
// entry callbacks
//
//----------------------------------------------------------------------

/*
*/

bool clap_entry_init_callback(const char *plugin_path) {
  return true;
}

/*
*/

void clap_entry_deinit_callback(void) {
}

/*
  Get the number of plugins available.
  [thread-safe]
*/

uint32_t clap_entry_get_plugin_count_callback(void) {
  return 1;
}

/*
  Retrieves a plugin descriptor by its index.
  Returns null in case of error.
  The descriptor does not need to be freed.
  [thread-safe]
*/

const clap_plugin_descriptor* clap_entry_get_plugin_descriptor_callback(uint32_t index) {
  //KODE_Descriptor* descriptor = _createDescriptor();
  clap_plugin_descriptor* clap_descriptor = (clap_plugin_descriptor*)malloc(sizeof(clap_plugin_descriptor));
  clap_descriptor->clap_version = CLAP_VERSION;
  clap_descriptor->id           = "";
  clap_descriptor->name         = ""; // descriptor->name;
  clap_descriptor->vendor       = ""; // descriptor->author;
  clap_descriptor->url          = "";
  clap_descriptor->manual_url   = "";
  clap_descriptor->support_url  = "";
  clap_descriptor->version      = "";
  clap_descriptor->description  = "";
  clap_descriptor->keywords     = "";
  clap_descriptor->plugin_type  = CLAP_PLUGIN_AUDIO_EFFECT;
  return clap_descriptor;
  //delete descriptor;
  //return nullptr;
}

/*
  Create a clap_plugin by its plugin_id.
  The returned pointer must be freed by calling plugin->destroy(plugin);
  The plugin is not allowed to use the host callbacks in the create method.
  Returns null in case of error.
  [thread-safe]
*/

const clap_plugin* clap_entry_create_plugin_callback(const clap_host *host, const char *plugin_id) {

//  KODE_Descriptor*        descriptor      = _createDescriptor();
//  KODE_Instance*          instance        = _createInstance(descriptor);
//  clap_plugin_descriptor* clapdescriptor  = nullptr;

  KODE_ClapInstance*  clapinstance  = new KODE_ClapInstance(host/*,instance*/);
  clap_plugin*        plugin        = (clap_plugin*)malloc(sizeof(clap_plugin));

  plugin->desc              = nullptr;//clapdescriptor;
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
  //return nullptr;
}

/*
  Get the number of invalidation source.
*/

uint32_t clap_entry_get_invalidation_sources_count_callback(void) {
  return 0;
}

/*
  Get the invalidation source by its index.
  [thread-safe]
*/

const clap_plugin_invalidation_source* clap_entry_get_invalidation_sources_callback(uint32_t index) {
  return nullptr;
}

/*
  In case the host detected a invalidation event, it can call refresh() to let
  the plugin_entry scan the set of plugins available.
*/

void clap_entry_refresh_callback(void) {
}

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

#define CLAP_ENTRYPOINT_SYMBOL asm ("clap_plugin_entry")
//struct clap_plugin_entry CLAP_PLUGIN_ENTRY CLAP_ENTRYPOINT_SYMBOL

//

#define KODE_CLAP_PLUGIN_ENTRYPOINT(D,I,E)                              \
                                                                        \
  KODE_ClapPluginEntry<D,I,E> CLAP_PLUGIN;                              \
                                                                        \
  /* ----- */                                                           \
                                                                        \
  /*CLAP_EXPORT*/                                                       \
  __attribute__ ((visibility ("default")))                              \
  struct clap_plugin_entry CLAP_PLUGIN_ENTRY CLAP_ENTRYPOINT_SYMBOL = { \
    CLAP_VERSION,                                                       \
    clap_entry_init_callback,                                           \
    clap_entry_deinit_callback,                                         \
    clap_entry_get_plugin_count_callback,                               \
    clap_entry_get_plugin_descriptor_callback,                          \
    clap_entry_create_plugin_callback,                                  \
    clap_entry_get_invalidation_sources_count_callback,                 \
    clap_entry_get_invalidation_sources_callback,                       \
    clap_entry_refresh_callback,                                        \
  };                                                                    \
                                                                        \
  /* ----- */                                                           \
                                                                        \
  KODE_Descriptor* _kode_clap_createDescriptor() {                      \
    return new D();                                                     \
  }                                                                     \
                                                                        \
  KODE_Instance* _kode_clap_createInstance(KODE_Descriptor* desc) {     \
    return new I(desc);                                                 \
  }                                                                     \

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
