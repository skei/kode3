
#define KODE_PLUGIN_NONE
//#define KODE_DEBUG_PRINT_SOCKET
// nc -U -l -k /tmp/kode.socket

//----------

#include "kode.h"

//----- clap -----

#include "plugin/clap/kode_hosted_clap_instance.h"
#include "plugin/clap/kode_hosted_clap_plugin.h"

//#define FILENAME "/home/skei/.u-he/Hive/Hive.64.so"
//#define FILENAME "/home/skei/.vst3/u-he/Hive.vst3/Contents/x86_64-linux/Hive.so"  // symloink
//#define FILENAME "/home/skei/.vst3/Instinct.vst3/Contents/x86_64-linux/Instinct.so" // vst3
#define CLAP_FILENAME "/DISKS/sda2/code/git/kode3/bin/kode_debug.so"

//----- vst2 -----

#include "plugin/vst2/kode_hosted_vst2_instance.h"
#include "plugin/vst2/kode_hosted_vst2_plugin.h"
#define VST2_FILENAME "/DISKS/sda2/audio/vst/linux/tal/libTAL-NoiseMaker.so"

//----------------------------------------------------------------------
// clap
//----------------------------------------------------------------------

/*
  https://github.com/free-audio/clap-host/blob/master/host/plugin-host.cc
  line 86
*/

void test_clap() {
  KODE_HostedClapPlugin* plugin = new KODE_HostedClapPlugin();
  if (plugin) {
    KODE_DPrint("plugin created\n");
    KODE_DPrint("loading %s\n",CLAP_FILENAME);
    plugin->loadLib(CLAP_FILENAME);
    if (plugin) {
      KODE_DPrint("plugin loaded\n");

      const struct clap_plugin_entry* plugin_entry =
        (const struct clap_plugin_entry*)plugin->getSymbol("clap_plugin_entry");

      //void* plugin_entry_ptr = plugin->getSymbol("clap_plugin_entry");
      //const struct clap_plugin_entry* plugin_entry =
      //  reinterpret_cast<const struct clap_plugin_entry *>(plugin_entry_ptr);

      if (plugin_entry) {

        KODE_DPrint("\n");
        KODE_DPrint("clap_plugin_entry:               %p\n",plugin_entry);
        KODE_DPrint("  clap_version.major             %i\n",plugin_entry->clap_version.major);
        KODE_DPrint("  clap_version.minor             %i\n",plugin_entry->clap_version.minor);
        KODE_DPrint("  clap_version.revision          %i\n",plugin_entry->clap_version.revision);
        KODE_DPrint("  init                           %p\n",plugin_entry->init);
        KODE_DPrint("  deinit                         %p\n",plugin_entry->deinit);
        KODE_DPrint("  get_plugin_count               %p\n",plugin_entry->get_plugin_count);
        KODE_DPrint("  get_plugin_descriptor          %p\n",plugin_entry->get_plugin_descriptor);
        KODE_DPrint("  create_plugin                  %p\n",plugin_entry->create_plugin);
        KODE_DPrint("  get_invalidation_source_count  %p\n",plugin_entry->get_invalidation_source_count);
        KODE_DPrint("  get_invalidation_source        %p\n",plugin_entry->get_invalidation_source);
        KODE_DPrint("  refresh                        %p\n",plugin_entry->refresh);
        KODE_DPrint("\n");

        bool result = plugin_entry->init("./");
        KODE_DPrint("clap_plugin_entry->init() returned: %s\n", result?"true":"false");

        // crashes:

        uint32_t num = plugin_entry->get_plugin_count();
        KODE_DPrint("clap_plugin_entry->get_plugin_count() returned: %i\n", num);

      }
      else {
        KODE_DPrint("'clap_plugin_entry' symbol not found\n");
      }

      plugin->unloadLib();
      KODE_DPrint("plugin unloaded\n");

      delete plugin;
      KODE_DPrint("plugin deleted\n");

    }
    else {
      KODE_DPrint("error loading plugin\n");
    }
  }
}

//----------------------------------------------------------------------
// vst2
//----------------------------------------------------------------------

void test_vst2() {
  KODE_HostedVst2Plugin* plugin = new KODE_HostedVst2Plugin();
  if (plugin) {
    KODE_DPrint("plugin created\n");
    KODE_DPrint("loading %s\n",VST2_FILENAME);
    plugin->loadLib(VST2_FILENAME);
    if (plugin) {
      KODE_DPrint("plugin loaded\n");
      AEffect* aeffect = (AEffect*)plugin->getSymbol("VSTPluginMain");
      if (aeffect) {

        KODE_DPrint("\n");
        KODE_DPrint("AEffect:                 %p\n",  aeffect);
        KODE_DPrint("  magic                  %08x\n",aeffect->magic);
        KODE_DPrint("  uniqueID               %08x\n",aeffect->uniqueID);
        KODE_DPrint("  numInputs              %i\n",  aeffect->numInputs);
        KODE_DPrint("  numOutputs             %i\n",  aeffect->numOutputs);
        KODE_DPrint("  numParams              %i\n",  aeffect->numParams);
        KODE_DPrint("  numPrograms            %i\n",  aeffect->numPrograms);
        KODE_DPrint("  version                %i\n",  aeffect->version);
        KODE_DPrint("  initialDelay           %i\n",  aeffect->initialDelay);
        KODE_DPrint("  object                 %p\n",  aeffect->object);
        KODE_DPrint("  user                   %p\n",  aeffect->user);
        KODE_DPrint("  dispatcher             %p\n",  aeffect->dispatcher);
        KODE_DPrint("  setParameter           %p\n",  aeffect->setParameter);
        KODE_DPrint("  getParameter           %p\n",  aeffect->getParameter);
        KODE_DPrint("  processReplacing       %p\n",  aeffect->processReplacing);
        KODE_DPrint("  processDoubleReplacing %p\n",  aeffect->processDoubleReplacing);
        KODE_DPrint("\n");

      }
      else {
        KODE_DPrint("'VSTPluginMain' symbol not found\n");
      }

      plugin->unloadLib();
      KODE_DPrint("plugin unloaded\n");

      delete plugin;
      KODE_DPrint("plugin deleted\n");

    }
    else {
      KODE_DPrint("error loading plugin\n");
    }
  }
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

int main() {
  //test_clap();
  test_vst2();
  return 0;
}
