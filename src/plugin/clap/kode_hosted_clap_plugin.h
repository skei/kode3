#ifndef kode_hosted_clap_plugin_included
#define kode_hosted_clap_plugin_included
//----------------------------------------------------------------------

#include <dlfcn.h>

#include "kode.h"
#include "plugin/clap/kode_clap.h"

//----------------------------------------------------------------------

class KODE_HostedClapPlugin {

//------------------------------
private:
//------------------------------

  void* MLibHandle  = nullptr;

//------------------------------
public:
//------------------------------

  KODE_HostedClapPlugin() {
  }

  KODE_HostedClapPlugin(const char* APath) {
    load(APath);
  }

  virtual ~KODE_HostedClapPlugin() {
  }

//------------------------------
public:
//------------------------------

  bool load(const char* AFilePath) {
    MLibHandle = dlopen(AFilePath,RTLD_LAZY | RTLD_LOCAL ); // RTLD_NOW, RTLD_LAZY
    return (MLibHandle != nullptr);
  }

  //----------

  void unload() {
    dlclose(MLibHandle);
    MLibHandle = nullptr;
  }

  //----------

  void* getSymbol(const char* ASymbol) {
    void* result = dlsym(MLibHandle,ASymbol);
    return result;
  }

  //----------

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

  void test() {
    const char*     PATH = "/home/skei/.vst3/u-he/ZebraCM.vst3/Contents/x86_64-linux/";
    const char* FILENAME = "/home/skei/.vst3/u-he/ZebraCM.vst3/Contents/x86_64-linux/ZebraCM.so";
    printf("KODE_HostedClapPlugin.test()\n");
    printf("* loading '%s'\n",FILENAME);
    KODE_HostedClapPlugin* plugin = new KODE_HostedClapPlugin();
    bool loaded = plugin->load(FILENAME);
    printf("* load: %s\n",(loaded) ? "true" : "false");
    struct clap_plugin_entry* plugin_entry = (struct clap_plugin_entry*)plugin->getSymbol("clap_plugin_entry");
    printf("* getSymbol 'clap_plugin_entry': %p\n",plugin_entry);
    uint32_t major = plugin_entry->clap_version.major;
    uint32_t minor = plugin_entry->clap_version.minor;
    uint32_t revision = plugin_entry->clap_version.revision;
    printf("* clap_version(%i,%i,%i)\n",major,minor,revision);
    bool initialized = plugin_entry->init(PATH);
    printf("* initialized: %s\n",(initialized) ? "true" : "false");
    uint32_t count = plugin_entry->get_plugin_count();                    // crash !!!
    printf("* get_plugin_count %i\n",count);
    plugin_entry->deinit();
    delete plugin;
  }

};

//----------------------------------------------------------------------
#endif
