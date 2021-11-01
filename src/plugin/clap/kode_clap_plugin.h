#ifndef kode_clap_plugin_included
#define kode_clap_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/clap/kode_clap.h"
#include "plugin/clap/kode_clap_instance.h"

KODE_Descriptor*        kode_clap_get_descriptor();
KODE_Instance*          kode_clap_create_instance(KODE_Descriptor* ADescriptor);
clap_plugin_descriptor* kode_clap_get_clap_descriptor(uint32_t AIndex);

//----------------------------------------------------------------------

template <class DESCRIPTOR, class INSTANCE, class EDITOR>
class KODE_ClapPluginEntry {

//------------------------------
private:
//------------------------------

  DESCRIPTOR*                     MDescriptor       = nullptr;
  struct clap_plugin_descriptor*  MClapDescriptor   = {0};

//------------------------------
public:
//------------------------------

  KODE_ClapPluginEntry() {
    MDescriptor = new DESCRIPTOR();
    MClapDescriptor = (clap_plugin_descriptor*)malloc(sizeof(clap_plugin_descriptor));
    MClapDescriptor->clap_version = CLAP_VERSION;
    MClapDescriptor->id          = "id";
    MClapDescriptor->name        = MDescriptor->name;
    MClapDescriptor->vendor      = MDescriptor->author;
    MClapDescriptor->url         = MDescriptor->url;
    MClapDescriptor->manual_url  = "manual_url";
    MClapDescriptor->support_url = "support_url";
    MClapDescriptor->version     = "version";
    MClapDescriptor->description = MDescriptor->description;
    MClapDescriptor->keywords    = "keywords";
    MClapDescriptor->plugin_type = CLAP_PLUGIN_AUDIO_EFFECT;
  }

  //----------

  ~KODE_ClapPluginEntry() {
    free(MClapDescriptor);
    delete MDescriptor;
  }

//------------------------------
public:
//------------------------------

  KODE_Descriptor* getDescriptor() {
    return new DESCRIPTOR();
  }

  //----------

  KODE_Instance* createInstance(KODE_Descriptor* ADescriptor) {
    // TODO: switch (AIndex)
    return new INSTANCE(ADescriptor);
  }

  //----------

  struct clap_plugin_descriptor* getClapDescriptor(uint32_t AIndex) {
    switch (AIndex) {
      case 0: return MClapDescriptor; break;
    }
    return nullptr;
  }

  //----------

};

// TODO:


//----------------------------------------------------------------------
//
// clap instance callbacks
//
//----------------------------------------------------------------------

// (these could be moved to KODE_ClapInstance, but i keep them here,
// so that we have all callbacks in one place)

/*
  Must be called after creating the plugin.
  If init returns false, the host must destroy the plugin instance.
*/

bool clap_instance_init_callback(const struct clap_plugin* plugin) {
  KODE_PRINT;
  KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
  if (instance) return instance->clap_instance_init();
  return false;
}

//----------

/*
  Free the plugin and its resources.
  It is not required to deactivate the plugin prior to this call.
*/

void clap_instance_destroy_callback(const struct clap_plugin* plugin) {
  KODE_PRINT;
  KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
  if (instance) instance->clap_instance_destroy();
}

//----------

/*
  activation
  [main-thread]
*/

bool clap_instance_activate_callback(const struct clap_plugin* plugin, double sample_rate) {
  KODE_PRINT;
  KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
  if (instance) return instance->clap_instance_activate(sample_rate);
  return false;
}

//----------

/*
  deactivation
  [main-thread]
*/

void clap_instance_deactivate_callback(const struct clap_plugin* plugin) {
  KODE_PRINT;
  KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
  if (instance) instance->clap_instance_deactivate();
}

//----------

/*
  Set to true before processing
  (and to false before sending the plugin to sleep)
  [audio-thread]
*/

bool clap_instance_start_processing_callback(const struct clap_plugin* plugin) {
  KODE_PRINT;
  KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
  if (instance) return instance->clap_instance_start_processing();
  return false;
}

//----------

/*
  (Set to true before processing)
  and to false before sending the plugin to sleep.
  [audio-thread]
*/

void clap_instance_stop_processing_callback(const struct clap_plugin* plugin) {
  KODE_PRINT;
  KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
  if (instance) instance->clap_instance_stop_processing();
}


//----------

/*
  process audio, events, ...
  [audio-thread]
*/

clap_process_status clap_instance_process_callback(const struct clap_plugin* plugin, const clap_process *process) {
  //KODE_PRINT;
  KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
  if (instance) return instance->clap_instance_process(process);
  return CLAP_PROCESS_ERROR;
}

//----------

/*
  Query an extension.
  The returned pointer is owned by the plugin.
  [thread-safe]
*/

const void* clap_instance_get_extension_callback(const struct clap_plugin* plugin, const char *id) {
  KODE_Print("id: %s\n",id);
  KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
  if (instance) return instance->clap_instance_get_extension(id);
  //if (strcmp(id,CLAP_EXT_GUI_X11) == 0) return &MClapPluginParams;
  //if (strcmp(id,CLAP_EXT_PARAMS) == 0)  return &MClapPluginParams;
  return nullptr;
}

//----------

/*
  Called by the host on the main thread in response to a previous call to:
  host->request_callback(host);
  [main-thread]
*/

void clap_instance_on_main_thread_callback(const struct clap_plugin* plugin) {
  KODE_PRINT;
  KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
  if (instance) instance->clap_instance_on_main_thread();
}

//----------------------------------------------------------------------
//
// clap callbacks
//
//----------------------------------------------------------------------

/*
  NOTE_CLAP: missing comments/documentation
*/

bool clap_init_callback(const char *plugin_path) {
  KODE_PRINT;
  return true;
}

//----------

/*
  NOTE: missing comments/documentation
*/

void clap_deinit_callback(void) {
  KODE_PRINT;
}

//----------

/*
  Get the number of plugins available.
  [thread-safe]
*/

uint32_t clap_get_plugin_count_callback(void) {
  KODE_PRINT;
  return 1;
}

//----------

/*
  Retrieves a plugin descriptor by its index.
  Returns null in case of error.
  The descriptor does not need to be freed.
  [thread-safe]
*/

/*
  NOTE_CLAP:
  what does 'The descriptor does not need to be freed' mean?
*/

const clap_plugin_descriptor* clap_get_plugin_descriptor_callback(uint32_t index) {
  KODE_PRINT;
  return kode_clap_get_clap_descriptor(index); //&kode_clap_descriptor;
}

//----------

/*
  Create a clap_plugin by its plugin_id.
  The returned pointer must be freed by calling plugin->destroy(plugin);
  The plugin is not allowed to use the host callbacks in the create method.
  Returns null in case of error.
  [thread-safe]
*/

// assumes 1 plugin, index #0

const clap_plugin* clap_create_plugin_callback(const clap_host *host, const char *plugin_id) {
  KODE_PRINT;
  KODE_Descriptor*    descriptor    = kode_clap_get_descriptor();
  KODE_Instance*      instance      = kode_clap_create_instance(descriptor);
  KODE_ClapInstance*  clapinstance  = new KODE_ClapInstance(host,instance);       // TODO: who deletes this? and where?
  clap_plugin*        plugin        = (clap_plugin*)malloc(sizeof(clap_plugin));  // TODO: who frees this? and where?
  plugin->desc              = kode_clap_get_clap_descriptor(0);
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

//----------

/*
  Get the number of invalidation source.
*/

uint32_t clap_get_invalidation_sources_count_callback(void) {
  KODE_PRINT;
  return 0;
}

//----------

/*
  Get the invalidation source by its index.
  [thread-safe]
*/

/*
  typedef struct clap_plugin_invalidation_source {
    const char *directory;      // Directory containing the file(s) to scan
    const char *filename_glob;  // globing pattern, in the form *.dll
    bool recursive_scan;        // should the directory be scanned recursively?
  };
*/

const clap_plugin_invalidation_source* clap_get_invalidation_sources_callback(uint32_t index) {
  KODE_PRINT;
  return nullptr;
}

//----------

/*
  In case the host detected a invalidation event, it can call refresh() to let
  the plugin_entry scan the set of plugins available.
*/

void clap_refresh_callback(void) {
  KODE_PRINT;
}

//----------------------------------------------------------------------
//
//
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

/*
  NOTE_CLAP:
    (simplified)
    > g++ --version
    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
    > g++ -Wall -g -I../src -c build.cpp -o build.o
    > g++  -o kode3_debug build.o
    warning: ‘visibility’ attribute ignored [-Wattributes]|
*/

//CLAP_EXPORT
//__attribute__ ((visibility ("default")))
const struct clap_plugin_entry clap_plugin_entry = {
  CLAP_VERSION,
  clap_init_callback,
  clap_deinit_callback,
  clap_get_plugin_count_callback,
  clap_get_plugin_descriptor_callback,
  clap_create_plugin_callback,
  clap_get_invalidation_sources_count_callback,
  clap_get_invalidation_sources_callback,
  clap_refresh_callback,
};

//----------------------------------------------------------------------

#define KODE_CLAP_PLUGIN_ENTRYPOINT(D,I,E)                                  \
                                                                            \
  /*static*/                                                                \
  KODE_ClapPluginEntry<D,I,E> CLAP_PLUGIN;                                  \
                                                                            \
  KODE_Descriptor* kode_clap_get_descriptor() {                             \
    return CLAP_PLUGIN.getDescriptor();                                     \
  }                                                                         \
                                                                            \
  KODE_Instance* kode_clap_create_instance(KODE_Descriptor* ADescriptor) {  \
    return CLAP_PLUGIN.createInstance(ADescriptor);                         \
  }                                                                         \
                                                                            \
  clap_plugin_descriptor* kode_clap_get_clap_descriptor(uint32_t AIndex) {  \
    return CLAP_PLUGIN.getClapDescriptor(AIndex);                           \
  }                                                                         \



//----------------------------------------------------------------------
#endif
