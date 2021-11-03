#ifndef kode_clap_plugin_included
#define kode_clap_plugin_included
//----------------------------------------------------------------------

#include "kode_clap.h"
#include "kode_descriptor.h"
#include "kode_instance.h"
#include "kode_editor.h"
#include "kode_clap_instance.h"

//----------------------------------------------------------------------

KODE_Descriptor*  _kode_clap_create_descriptor();
KODE_Instance*    _kode_clap_create_instance(KODE_Descriptor* ADescriptor);

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

  bool clap_init(const char *plugin_path) {
    MDescriptor = _kode_clap_create_descriptor();
    MClapDescriptor = (clap_plugin_descriptor*)malloc(sizeof(clap_plugin_descriptor));
    MClapDescriptor->clap_version = CLAP_VERSION;
    MClapDescriptor->id           = "";
    MClapDescriptor->name         = ""; // MDescriptor->name;
    MClapDescriptor->vendor       = ""; // MDescriptor->author;
    MClapDescriptor->url          = "";
    MClapDescriptor->manual_url   = "";
    MClapDescriptor->support_url  = "";
    MClapDescriptor->version      = "";
    MClapDescriptor->description  = "";
    MClapDescriptor->keywords     = "";
    MClapDescriptor->plugin_type  = CLAP_PLUGIN_AUDIO_EFFECT;
    return true;
  }

  void clap_deinit(void) {
    free(MClapDescriptor);
    delete MDescriptor;
  }

  uint32_t clap_get_plugin_count() {
    return 1;
  }

  const clap_plugin_descriptor* clap_get_plugin_descriptor(uint32_t index) {
    return MClapDescriptor;
  }

  const clap_plugin* clap_create_plugin(const clap_host* host, const char* plugin_id) {
    clap_plugin*        plugin        = (clap_plugin*)malloc(sizeof(clap_plugin));
    KODE_Instance*      instance      = _kode_clap_create_instance(MDescriptor);  // deleted by KODE_ClapInstance destructor
    KODE_ClapInstance*  clap_instance = new KODE_ClapInstance(instance);
    plugin->desc              = MClapDescriptor;
    plugin->plugin_data       = clap_instance;
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

  uint32_t clap_get_invalidation_sources_count(void) {
    return 0;
  }

  const clap_plugin_invalidation_source* clap_get_invalidation_sources(uint32_t index) {
    return nullptr;
  }

  void clap_refresh(void) {
  }

//------------------------------
public:
//------------------------------

  static bool clap_instance_init_callback(const struct clap_plugin *plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_instance_init();
  }

  static void clap_instance_destroy_callback(const struct clap_plugin *plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_instance_destroy();
    delete instance;
    //free(plugin);
  }

  static bool clap_instance_activate_callback(const struct clap_plugin *plugin, double sample_rate) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_instance_activate(sample_rate);
  }

  static void clap_instance_deactivate_callback(const struct clap_plugin *plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_instance_deactivate();
  }

  static bool clap_instance_start_processing_callback(const struct clap_plugin *plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_instance_start_processing();
  }

  static void clap_instance_stop_processing_callback(const struct clap_plugin *plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_instance_stop_processing();
  }

  static clap_process_status clap_instance_process_callback(const struct clap_plugin *plugin, const clap_process *process) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_instance_process(process);
  }

  static const void *clap_instance_get_extension_callback(const struct clap_plugin *plugin, const char *id) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    return instance->clap_instance_get_extension(id);
  }

  static void clap_instance_on_main_thread_callback(const struct clap_plugin *plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    instance->clap_instance_on_main_thread();
  }

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

KODE_ClapPlugin _GLOBAL_CLAP_PLUGIN;

//----------------------------------------------------------------------
//
// clap entry
//
//----------------------------------------------------------------------


static bool clap_init_callback(const char *plugin_path) {
  return _GLOBAL_CLAP_PLUGIN.clap_init(plugin_path);
}

static void clap_deinit_callback() {
  _GLOBAL_CLAP_PLUGIN.clap_deinit();
}

static uint32_t clap_get_plugin_count_callback() {
  return _GLOBAL_CLAP_PLUGIN.clap_get_plugin_count();
}

static const clap_plugin_descriptor* clap_get_plugin_descriptor_callback(uint32_t index) {
  return _GLOBAL_CLAP_PLUGIN.clap_get_plugin_descriptor(index);
}

static const clap_plugin* clap_create_plugin_callback(const clap_host* host, const char* plugin_id) {
  return _GLOBAL_CLAP_PLUGIN.clap_create_plugin(host,plugin_id);
}

static uint32_t clap_get_invalidation_sources_count_callback(void) {
  return _GLOBAL_CLAP_PLUGIN.clap_get_invalidation_sources_count();
}

static const clap_plugin_invalidation_source* clap_get_invalidation_sources_callback(uint32_t index) {
   return _GLOBAL_CLAP_PLUGIN.clap_get_invalidation_sources(index);
}

static void clap_refresh_callback(void) {
  _GLOBAL_CLAP_PLUGIN.clap_refresh();
}

//----------------------------------------------------------------------

//#ifdef __cplusplus
//extern "C" {
//#endif

//CLAP_EXPORT const struct clap_plugin_entry clap_plugin_entry  = {

//CLAP_EXPORT
__attribute__((visibility("default")))
//const
struct clap_plugin_entry CLAP_ENTRY_STRUCT asm("clap_plugin_entry") = {
   CLAP_VERSION,
   clap_init_callback,
   clap_deinit_callback,
   clap_get_plugin_count_callback,
   clap_get_plugin_descriptor_callback,
   clap_create_plugin_callback,
   clap_get_invalidation_sources_count_callback,
   clap_get_invalidation_sources_callback,
   clap_refresh_callback
};

//#ifdef __cplusplus
//}
//#endif

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#define KODE_CLAP_ENTRYPOINT(D,I,E)                                                               \
                                                                                                  \
  KODE_Descriptor*  _kode_clap_create_descriptor()                      { return new D(); }       \
  KODE_Instance*    _kode_clap_create_instance(KODE_Descriptor* ADesc)  { return new I(ADesc); }  \
  KODE_Editor*      _kode_clap_create_editor(KODE_Instance* AInst)      { return new E(AInst); }  \


//----------------------------------------------------------------------
#endif
