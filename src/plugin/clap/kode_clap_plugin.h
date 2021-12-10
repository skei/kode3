#ifndef kode_clap_plugin_included
#define kode_clap_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_plugin.h"
#include "plugin/clap/kode_clap.h"
#include "plugin/clap/kode_clap_host.h"
#include "plugin/clap/kode_clap_instance.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class KODE_ClapPlugin {

//------------------------------
private:
//------------------------------

  KODE_Descriptor*        MDescriptor     = nullptr;
  clap_plugin_descriptor* MClapDescriptor = nullptr;

//------------------------------
public:
//------------------------------

  /*
    This interface is the entry point of the dynamic library.

    There is an invalidation mechanism for the set of plugins which is based on
    files. The host can watch the plugin DSO's mtime and a set of files's mtime
    provided by get_clap_invalidation_source().

    The set of plugins must not change, except during a call to refresh() by
    the host.

    Every methods must be thread-safe.
  */

  //----------

  bool clap_entry_init(const char *plugin_path) {
    //KODE_ClapPrint("-> true\n");
    MDescriptor     = _kode_create_descriptor();
    MClapDescriptor = (clap_plugin_descriptor*)malloc(sizeof(clap_plugin_descriptor));
    MClapDescriptor->clap_version = CLAP_VERSION;
    MClapDescriptor->id           = MDescriptor->getIdString();
    MClapDescriptor->name         = MDescriptor->getName();
    MClapDescriptor->vendor       = MDescriptor->getAuthor();
    MClapDescriptor->url          = MDescriptor->getUrl();
    MClapDescriptor->manual_url   = "";
    MClapDescriptor->support_url  = "";
    MClapDescriptor->version      = MDescriptor->getVersionString();
    MClapDescriptor->description  = "";
    MClapDescriptor->keywords     = ""; // Arbitrary list of keywords, separated by `;'

    if (MDescriptor->isSynth()) MClapDescriptor->plugin_type  = CLAP_PLUGIN_INSTRUMENT;
    else MClapDescriptor->plugin_type  = CLAP_PLUGIN_AUDIO_EFFECT; //CLAP_PLUGIN_EVENT_EFFECT, CLAP_PLUGIN_ANALYZER

    return true;
  }

  //----------


  /*
  */

  void clap_entry_deinit(void) {
    //KODE_ClapPrint("\n");
    if (MClapDescriptor) free(MClapDescriptor);
    MClapDescriptor = nullptr;
    // crash..
    //if (MDescriptor) delete MDescriptor; // deleted in  ~KODE_Instance()
    //MDescriptor = nullptr;
  }

  //----------

  /*
    Get the number of plugins available.
    [thread-safe]
  */

  uint32_t clap_entry_get_plugin_count() {
    //KODE_ClapPrint("-> 1\n");
    return 1;
  }

  //----------

  /*
    Retrieves a plugin descriptor by its index.
    Returns null in case of error.
    The descriptor does not need to be freed.
    [thread-safe]
  */

  const clap_plugin_descriptor* clap_entry_get_plugin_descriptor(uint32_t index) {
    //KODE_ClapPrint("index %i -> 0x%p\n",index,MClapDescriptor);
    return MClapDescriptor;
  }

  //----------

  /*
    Create a clap_plugin by its plugin_id.
    The returned pointer must be freed by calling plugin->destroy(plugin);
    The plugin is not allowed to use the host callbacks in the create method.
    Returns null in case of error.
    [thread-safe]
  */

  const clap_plugin* clap_entry_create_plugin(const clap_host* host, const char* plugin_id) {
    KODE_ClapHost*      claphost      = new KODE_ClapHost(host);
    clap_plugin*        plugin        = (clap_plugin*)malloc(sizeof(clap_plugin));
    KODE_Instance*      instance      = _kode_create_instance(MDescriptor);  // deleted by KODE_ClapInstance destructor
    instance->setPluginFormat(KODE_PLUGIN_FORMAT_CLAP);
    KODE_ClapInstance*  clapinstance = new KODE_ClapInstance(instance,claphost);
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
    //KODE_ClapPrint("plugin_id %s -> %p\n",plugin_id,plugin);
    return plugin;
  }

  //----------

  /*
    Get the number of invalidation source.
  */

  uint32_t clap_entry_get_invalidation_sources_count(void) {
    //KODE_ClapPrint("-> 0\n");
    return 0;
  }

  //----------

  /*
    Get the invalidation source by its index.
    [thread-safe]
  */

  const clap_plugin_invalidation_source* clap_entry_get_invalidation_sources(uint32_t index) {
    //KODE_ClapPrint("index %i -> NULL\n",index);
    return nullptr;
  }

  //----------

  /*
    In case the host detected a invalidation event, it can call refresh() to
    let the plugin_entry scan the set of plugins available.
  */

  void clap_entry_refresh(void) {
    //KODE_ClapPrint("\n");
  }

//------------------------------
public:
//------------------------------

  // trampolines to KODE_ClapInstance

  //----------

  static
  bool clap_instance_init_callback(const struct clap_plugin *plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_instance_init();
  }

  static
  void clap_instance_destroy_callback(const struct clap_plugin *plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_instance_destroy();
    delete instance;
    //free(plugin);
  }

  static
  bool clap_instance_activate_callback(const struct clap_plugin *plugin, double sample_rate, uint32_t minframes, uint32_t maxframes) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_instance_activate(sample_rate,minframes,maxframes);
  }

  static
  void clap_instance_deactivate_callback(const struct clap_plugin *plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_instance_deactivate();
  }

  static
  bool clap_instance_start_processing_callback(const struct clap_plugin *plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_instance_start_processing();
  }

  static
  void clap_instance_stop_processing_callback(const struct clap_plugin *plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_instance_stop_processing();
  }

  static
  clap_process_status clap_instance_process_callback(const struct clap_plugin *plugin, const clap_process *process) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_instance_process(process);
  }

  static
  const void *clap_instance_get_extension_callback(const struct clap_plugin *plugin, const char *id) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_instance_get_extension(id);
  }

  static
  void clap_instance_on_main_thread_callback(const struct clap_plugin *plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_instance_on_main_thread();
  }

//------------------------------

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

KODE_ClapPlugin KODE_GLOBAL_CLAP_PLUGIN;

//----------------------------------------------------------------------
//
// clap entry
//
//----------------------------------------------------------------------

// trampolines to KODE_GLOBAL_CLAP_PLUGIN

//----------

static bool clap_entry_init_callback(const char *plugin_path) {
  return KODE_GLOBAL_CLAP_PLUGIN.clap_entry_init(plugin_path);
}

static void clap_entry_deinit_callback() {
  KODE_GLOBAL_CLAP_PLUGIN.clap_entry_deinit();
}

static uint32_t clap_entry_get_plugin_count_callback() {
  return KODE_GLOBAL_CLAP_PLUGIN.clap_entry_get_plugin_count();
}

static const clap_plugin_descriptor* clap_entry_get_plugin_descriptor_callback(uint32_t index) {
  return KODE_GLOBAL_CLAP_PLUGIN.clap_entry_get_plugin_descriptor(index);
}

static const clap_plugin* clap_entry_create_plugin_callback(const clap_host* host, const char* plugin_id) {
  return KODE_GLOBAL_CLAP_PLUGIN.clap_entry_create_plugin(host,plugin_id);
}

static uint32_t clap_entry_get_invalidation_sources_count_callback(void) {
  return KODE_GLOBAL_CLAP_PLUGIN.clap_entry_get_invalidation_sources_count();
}

static const clap_plugin_invalidation_source* clap_entry_get_invalidation_sources_callback(uint32_t index) {
  return KODE_GLOBAL_CLAP_PLUGIN.clap_entry_get_invalidation_sources(index);
}

static void clap_entry_refresh_callback(void) {
  KODE_GLOBAL_CLAP_PLUGIN.clap_entry_refresh();
}

//----------------------------------------------------------------------

/*
  This interface is the entry point of the dynamic library.
  There is an invalidation mechanism for the set of plugins which is based on
  files.
  The host can watch the plugin DSO's mtime and a set of files's mtime provided
  by get_clap_invalidation_source().
  The set of plugins must not change, except during a call to refresh() by the
  host.
  Every methods must be thread-safe.
*/

//----------------------------------------------------------------------

//#ifdef __cplusplus
//extern "C" {
//#endif

//CLAP_EXPORT const struct clap_plugin_entry clap_plugin_entry  = {
//warning: ‘visibility’ attribute ignored [-Wattributes]|

//__attribute__((visibility("default")))
__KODE_DLLEXPORT
struct clap_plugin_entry CLAP_ENTRY_STRUCT asm("clap_plugin_entry") = {
  CLAP_VERSION,
  clap_entry_init_callback,
  clap_entry_deinit_callback,
  clap_entry_get_plugin_count_callback,
  clap_entry_get_plugin_descriptor_callback,
  clap_entry_create_plugin_callback,
  clap_entry_get_invalidation_sources_count_callback,
  clap_entry_get_invalidation_sources_callback,
  clap_entry_refresh_callback
};

//#ifdef __cplusplus
//}
//#endif

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#define KODE_CLAP_MAIN(D,I,E)             \
                                          \
  /*bool print_CLAP() {              */   \
  /*  KODE_ClapPrint("CLAP\n");      */   \
  /*  return true;                   */   \
  /*}                                */   \
  /*                                 */   \
  /*bool printed_CLAP = print_CLAP();*/   \


//----------------------------------------------------------------------
#endif
