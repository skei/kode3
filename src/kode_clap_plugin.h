#ifndef kode_clap_plugin_included
#define kode_clap_plugin_included
//----------------------------------------------------------------------

#include "kode_clap.h"
#include "kode_descriptor.h"
#include "kode_instance.h"
#include "kode_clap_instance.h"

// (see kode_clap.h)
KODE_Descriptor*  _kode_clap_create_descriptor();
KODE_Instance*    _kode_clap_create_instance(KODE_Descriptor* ADescriptor);

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
    KODE_Instance*      instance      = _kode_clap_create_instance(MDescriptor);  // deleted bu KODE_ClapInstance destructor
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
#endif
