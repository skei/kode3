#ifndef kode_ladspa_instance_incuded
#define kode_ladspa_instance_incuded
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/ladspa/kode_ladspa.h"

//----------------------------------------------------------------------

class KODE_LadspaInstance {

//------------------------------
private:
//------------------------------

  KODE_Descriptor*  MDescriptor = nullptr;
  uint32_t          MSampleRate = 0;

//------------------------------
public:
//------------------------------

  KODE_LadspaInstance(KODE_Descriptor* ADescriptor, unsigned long ASampleRate) {
    MSampleRate = ASampleRate;
  }

//------------------------------
public:
//------------------------------

  void ladspa_connect_port(unsigned long Port, LADSPA_Data * DataLocation) {
  }

  void ladspa_activate() {
  }

  void ladspa_run(unsigned long SampleCount) {
  }

  void ladspa_run_adding(unsigned long SampleCount) {
  }

  void ladspa_set_run_adding_gain(LADSPA_Data Gain) {
  }

  void ladspa_deactivate() {
  }

  void ladspa_cleanup() {
  }

};

//----------------------------------------------------------------------
#endif
