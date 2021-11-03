#ifndef kode_clap_included
#define kode_clap_included
//----------------------------------------------------------------------

#include "../../clap/include/clap/all.h"

#include "kode.h"
#include "kode_descriptor.h"
#include "kode_instance.h"
#include "kode_editor.h"

#include "kode_clap_plugin.h"
//#include "kode_clap_instance.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

KODE_ClapPlugin CLAP_PLUGIN;

//----------------------------------------------------------------------
//
// clap entry
//
//----------------------------------------------------------------------

static bool clap_init_callback(const char *plugin_path) {
  return CLAP_PLUGIN.clap_init(plugin_path);
}

static void clap_deinit_callback() {
  CLAP_PLUGIN.clap_deinit();
}

static uint32_t clap_get_plugin_count_callback() {
  return CLAP_PLUGIN.clap_get_plugin_count();
}

static const clap_plugin_descriptor* clap_get_plugin_descriptor_callback(uint32_t index) {
  return CLAP_PLUGIN.clap_get_plugin_descriptor(index);
}

static const clap_plugin* clap_create_plugin_callback(const clap_host* host, const char* plugin_id) {
  return CLAP_PLUGIN.clap_create_plugin(host,plugin_id);
}

static uint32_t clap_get_invalidation_sources_count_callback(void) {
  return CLAP_PLUGIN.clap_get_invalidation_sources_count();
}

static const clap_plugin_invalidation_source* clap_get_invalidation_sources_callback(uint32_t index) {
   return CLAP_PLUGIN.clap_get_invalidation_sources(index);
}

static void clap_refresh_callback(void) {
  CLAP_PLUGIN.clap_refresh();
}

//----------------------------------------------------------------------
//
// clap entry struct
//
//----------------------------------------------------------------------

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

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#define KODE_CLAP_ENTRYPOINT(D,I,E)                                                               \
                                                                                                  \
  KODE_Descriptor*  _kode_clap_create_descriptor()                      { return new D(); }       \
  KODE_Instance*    _kode_clap_create_instance(KODE_Descriptor* ADesc)  { return new I(ADesc); }  \


//----------------------------------------------------------------------
#endif
