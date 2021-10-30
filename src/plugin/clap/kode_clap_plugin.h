#ifndef kode_clap_plugin_included
#define kode_clap_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/clap/kode_clap.h"
#include "plugin/clap/kode_clap_instance.h"

//#include "plugs/dc-offset/dc-offset.hh"
//#include "plugs/gain/gain.hh"
//#include "plugs/transport/transport-info.hh"
//#include "path-provider.hh"

//----------------------------------------------------------------------

bool                clap_init_callback(const char *plugin_path);
void                clap_deinit_callback(void);
uint32_t            clap_get_plugin_count_callback(void);
const               clap_plugin_descriptor* clap_get_plugin_descriptor_callback(uint32_t index);
const               clap_plugin* clap_create_plugin_callback(const clap_host *host, const char *plugin_id);
uint32_t            clap_get_invalidation_sources_count_callback(void);
const               clap_plugin_invalidation_source* clap_get_invalidation_sources_callback(uint32_t index);
void                clap_refresh_callback(void);

bool                clap_instance_init_callback(const struct clap_plugin* plugin);
void                clap_instance_destroy_callback(const struct clap_plugin* plugin);
bool                clap_instance_activate_callback(const struct clap_plugin* plugin, double sample_rate);
void                clap_instance_deactivate_callback(const struct clap_plugin* plugin);
bool                clap_instance_start_processing_callback(const struct clap_plugin* plugin);
void                clap_instance_stop_processing_callback(const struct clap_plugin* plugin);
clap_process_status clap_instance_process_callback(const struct clap_plugin* plugin, const clap_process *process);
const void*         clap_instance_get_extension_callback(const struct clap_plugin* plugin, const char *id);
void                clap_instance_on_main_thread_callback(const struct clap_plugin* plugin);

// TODO: fill out with info from KODE_Descriptort

const struct clap_plugin_descriptor kode_clap_descriptor = {
  CLAP_VERSION,
  "plugin_id",
  "plugin",
  "skei.audio",
  "url",
  "manual_url",
  "support_url",
  "version - '0.0.0'",
  "description",
  "keyword1;jeyword2",
  CLAP_PLUGIN_AUDIO_EFFECT,
};

//----------------------------------------------------------------------
//
// clap instance callbacks
//
//----------------------------------------------------------------------

bool clap_instance_init_callback(const struct clap_plugin* plugin) {
  if (plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    if (instance) {
      return instance->clap_instance_init();
    }
  }
  return false;
}

//----------

void clap_instance_destroy_callback(const struct clap_plugin* plugin) {
  if (plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    if (instance) {
      instance->clap_instance_destroy();
    }
  }
}

//----------

bool clap_instance_activate_callback(const struct clap_plugin* plugin, double sample_rate) {
  if (plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    if (instance) {
      return instance->clap_instance_activate(sample_rate);
    }
  }
  return false;
}

//----------

void clap_instance_deactivate_callback(const struct clap_plugin* plugin) {
  if (plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    if (instance) {
      instance->clap_instance_deactivate();
    }
  }
}

//----------

bool clap_instance_start_processing_callback(const struct clap_plugin* plugin) {
  if (plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    if (instance) {
      return instance->clap_instance_start_processing();
    }
  }
  return false;
}

//----------

void clap_instance_stop_processing_callback(const struct clap_plugin* plugin) {
  if (plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    if (instance) {
      instance->clap_instance_stop_processing();
    }
  }
}


//----------

clap_process_status clap_instance_process_callback(const struct clap_plugin* plugin, const clap_process *process) {
  if (plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    if (instance) {
      return instance->clap_instance_process(process);
    }
  }
  return CLAP_PROCESS_ERROR;
}

//----------

const void* clap_instance_get_extension_callback(const struct clap_plugin* plugin, const char *id) {
  if (plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    if (instance) {
      return instance->clap_instance_get_extension(id);
    }
  }
  return nullptr;
}

//----------

void clap_instance_on_main_thread_callback(const struct clap_plugin* plugin) {
  if (plugin) {
    KODE_ClapInstance* instance = (KODE_ClapInstance*)plugin->plugin_data;
    if (instance) {
      instance->clap_instance_on_main_thread();
    }
  }
}

//----------------------------------------------------------------------
//
// clap callbacks
//
//----------------------------------------------------------------------

bool clap_init_callback(const char *plugin_path) {
  return true;
}

//----------

void clap_deinit_callback(void) {
}

//----------

uint32_t clap_get_plugin_count_callback(void) {
  return 1;
}

//----------

const clap_plugin_descriptor* clap_get_plugin_descriptor_callback(uint32_t index) {
  switch(index) {
    case 0:
      return &kode_clap_descriptor;
      break;
  }
  return nullptr;
}

//----------

const clap_plugin* clap_create_plugin_callback(const clap_host *host, const char *plugin_id) {
  clap_plugin*        plugin = (clap_plugin*)malloc(sizeof(clap_plugin));
  KODE_ClapInstance*  instance = new KODE_ClapInstance();
  plugin->desc              = &kode_clap_descriptor;
  plugin->plugin_data       = instance;
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

uint32_t clap_get_invalidation_sources_count_callback(void) {
  return 0;
}

//----------

/*
  typedef struct clap_plugin_invalidation_source {
    const char *directory;      // Directory containing the file(s) to scan
    const char *filename_glob;  // globing pattern, in the form *.dll
    bool recursive_scan;        // should the directory be scanned recursively?
  };
*/

const clap_plugin_invalidation_source* clap_get_invalidation_sources_callback(uint32_t index) {
  return nullptr;
}

//----------

void clap_refresh_callback(void) {
}

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

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

//----------

#define KODE_CLAP_PLUGIN_ENTRYPOINT(D,I)      \
                                              \

//----------------------------------------------------------------------
#endif
