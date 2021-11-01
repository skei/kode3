#ifndef kode_clap_hosted_plugin_included
#define kode_clap_hosted_plugin_included
//----------------------------------------------------------------------

#include <dlfcn.h>

#include "kode.h"
#include "plugin/clap/kode_clap.h"

class KODE_ClapHostedPlugin {

//------------------------------
private:
//------------------------------

  void*                     MLibHandle        = nullptr;
  struct clap_plugin_entry* MClapPluginEntry  = nullptr;

//------------------------------
private:
//------------------------------

  void* getSymbol(const char* ASymbol) {
    void* result = dlsym(MLibHandle,ASymbol);
    return result;
  }

//------------------------------
public:
//------------------------------

  int32_t load(const char* AFilename) {
    KODE_Print("loading: '%s'\n",AFilename);
    MLibHandle = dlopen(AFilename, RTLD_LAZY | RTLD_LOCAL ); // RTLD_NOW, RTLD_LAZY
    if (!MLibHandle) {
      return -1;
    }
    KODE_Print("  handle: %p\n",MLibHandle);

    KODE_Print("finding clap_plugin_entry symbol\n");
    MClapPluginEntry = (struct clap_plugin_entry*)getSymbol("clap_plugin_entry");
    if (!MClapPluginEntry) {
      dlclose(MLibHandle);
      return -2;
    }
    KODE_Print("  ptr: %p\n",MClapPluginEntry);

    KODE_Print("reading clap_version\n");
    uint32_t version_major    = MClapPluginEntry->clap_version.major;
    uint32_t version_minor    = MClapPluginEntry->clap_version.minor;
    uint32_t version_revision = MClapPluginEntry->clap_version.revision;
    KODE_Print("  version: %i %i %i\n",version_major,version_minor,version_revision);

    KODE_Print("calling get_plugin_count()\n");
    uint32_t num = MClapPluginEntry->get_plugin_count();
    KODE_Print("  count: %i\n",num);

    return 0;
  }

  //----------

  void unload() {
    if (MLibHandle) {
      dlclose(MLibHandle);
      MLibHandle = nullptr;
    }
  }



};

//----------------------------------------------------------------------
#endif
