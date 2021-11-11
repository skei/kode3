
#define KODE_NO_PLUGIN
#define KODE_NO_GUI

//#define KODE_PLUGIN_NONE
//#define KODE_DEBUG_PRINT_SOCKET
// nc -U -l -k /tmp/kode.socket

#define FILENAME      "/DISKS/sda2/code/git/kode3/bin/kode_debug.so"
#define CLAP_FILENAME FILENAME
#define VST2_FILENAME FILENAME

//#define CLAP_FILENAME "/home/skei/.vst3/u-he/Hive.vst3/Contents/x86_64-linux/Hive.so"  // symloink
//#define CLAP_FILENAME "/DISKS/sda2/code/git/kode3/bin/kode_debug.so"
//#define VST2_FILENAME "/DISKS/sda2/audio/vst/linux/tal/libTAL-NoiseMaker.so"
//#define VST2_FILENAME "/DISKS/sda2/audio/vst/linux/gvst/GBand.so"

//----------

#include "kode.h"

//#define DR_WAV_IMPLEMENTATION
//#include "extern/dr_wav.h"

#include "plugin/clap/kode_hosted_clap_instance.h"
#include "plugin/clap/kode_hosted_clap_plugin.h"
#include "plugin/vst2/kode_hosted_vst2_instance.h"
#include "plugin/vst2/kode_hosted_vst2_plugin.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

int main() {

  KODE_HostedPlugin* plugin1 = new KODE_HostedVst2Plugin(CLAP_FILENAME);
  KODE_HostedInstance* instance1 = plugin1->createInstance();
  delete instance1;
  delete plugin1;

  KODE_HostedPlugin* plugin2 = new KODE_HostedClapPlugin(CLAP_FILENAME);
  KODE_HostedInstance* instance2 = plugin2->createInstance();
  delete instance2;
  delete plugin2;

  return 0;
}
