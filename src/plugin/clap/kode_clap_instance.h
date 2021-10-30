#ifndef kode_clap_instance_included
#define kode_clap_instance_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/clap/kode_clap.h"

//----------------------------------------------------------------------

class KODE_ClapInstance {

private:

  clap_plugin MClapPlugin;

public:

  const clap_plugin* getClapPlugin() { return &MClapPlugin; }


public:

  bool clap_instance_init() {
    return false;
  }

  //----------

  void clap_instance_destroy() {
  }

  //----------

  bool clap_instance_activate(double sample_rate) {
    return false;
  }

  //----------

  void clap_instance_deactivate() {
  }

  //----------

  bool clap_instance_start_processing() {
    return false;
  }

  //----------

  void clap_instance_stop_processing() {
  }


  //----------

  clap_process_status clap_instance_process(const clap_process *process) {
    return CLAP_PROCESS_ERROR;
  }

  //----------

  const void* clap_instance_get_extension(const char *id) {
    return nullptr;
  }

  //----------

  void clap_instance_on_main_thread() {
  }


};

//----------------------------------------------------------------------
#endif
