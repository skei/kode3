#ifndef kode_clap_instance_included
#define kode_clap_instance_included
//----------------------------------------------------------------------

#include "kode_clap.h"
#include "kode_instance.h"

//----------------------------------------------------------------------

class KODE_ClapInstance {

//------------------------------
private:
//------------------------------

  KODE_Instance* MInstance = nullptr;

//------------------------------
public:
//------------------------------

  KODE_ClapInstance(KODE_Instance* AInstance) {
    MInstance = AInstance;
  }

  ~KODE_ClapInstance() {
    if (MInstance) delete MInstance;
  }

//------------------------------
public:
//------------------------------

  bool clap_instance_init() {
    MInstance->on_plugin_init();
    return false;
  }

  void clap_instance_destroy() {
    MInstance->on_plugin_destroy();
  }

  bool clap_instance_activate(double sample_rate) {
    MInstance->on_plugin_activate();
    //return MInstance->on_plugin_activate(sample_rate);
    return true;
  }

  void clap_instance_deactivate() {
    MInstance->on_plugin_deactivate();
  }

  bool clap_instance_start_processing() {
    MInstance->on_plugin_start_processing();
    return true;
  }

  void clap_instance_stop_processing() {
    MInstance->on_plugin_stop_processing();
  }

  clap_process_status clap_instance_process(const clap_process *process) {
    MInstance->on_plugin_process();
    return 0;//CLAP_PROCESS_CONTINUE;
  }

  const void *clap_instance_get_extension(const char *id) {
    return nullptr;
  }

  void clap_instance_on_main_thread() {
  }

};

//----------------------------------------------------------------------
#endif
