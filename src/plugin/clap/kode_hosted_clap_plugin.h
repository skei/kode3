#ifndef kode_hosted_clap_plugin_included
#define kode_hosted_clap_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_hosted_plugin.h"
#include "plugin/clap/kode_clap.h"
#include "plugin/clap/kode_hosted_clap_instance.h"

//----------------------------------------------------------------------

class KODE_HostedClapPlugin
: public KODE_HostedPlugin {

//------------------------------
private:
//------------------------------

  KODE_Descriptor*  MDescriptor = nullptr;

//  void*                     MLibHandle        = nullptr;
//  clap_plugin*              MClapPlugin       = nullptr;
//  clap_plugin_descriptor*   MClapDescriptor   = nullptr;
//  struct clap_plugin_entry* MClapPluginEntry  = nullptr;

//------------------------------
public:
//------------------------------

  KODE_HostedClapPlugin()
  : KODE_HostedPlugin() {
    //KODE_PRINT;
  }

  //----------

  virtual ~KODE_HostedClapPlugin() {
    //KODE_PRINT;
  }

//------------------------------
public:
//------------------------------

  KODE_HostedInstance* createInstance() final {
    KODE_HostedClapInstance* instance = new KODE_HostedClapInstance(MDescriptor);
    return instance;
  }



//------------------------------
public:
//------------------------------

//------------------------------
public:
//------------------------------

    /*
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
    */

  bool clap_init(const char *plugin_path) { return false; }
  void clap_deinit() {}
  uint32_t clap_get_plugin_count() { return 0; }
  const clap_plugin_descriptor* clap_get_plugin_descriptor(uint32_t index) { return nullptr; }
  const clap_plugin* clap_create_plugin(const clap_host* host, const char* plugin_id) { return nullptr; }
  uint32_t clap_get_invalidation_sources_count() { return 0; }
  const clap_plugin_invalidation_source* clap_get_invalidation_sources(uint32_t index) { return nullptr; }
  void clap_refresh() {}

};

//----------------------------------------------------------------------
#endif
