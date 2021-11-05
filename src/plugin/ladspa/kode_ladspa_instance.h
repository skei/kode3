#ifndef kode_ladspa_instance_included
#define kode_ladspa_instance_included
//----------------------------------------------------------------------

// in progress

#include "kode.h"
//#include "base/kode_queue.h"
#include "plugin/kode_descriptor.h"
#include "plugin/kode_instance.h"
//#include "plugin/kode_instance_listener.h"
#include "plugin/kode_process_context.h"
#include "plugin/ladspa/kode_ladspa.h"

//typedef KODE_Queue<uint32_t,KODE_MAX_PROCESS_EVENTS>  KODE_ParameterQueue;

//----------------------------------------------------------------------

class KODE_LadspaInstance
/*: public KODE_InstanceListener*/ {

  //friend class KODE_LadspaPlugin;

//------------------------------
private:
//------------------------------

  KODE_Descriptor*  MDescriptor     = nullptr;
  KODE_Instance*    MInstance       = nullptr;
  //KODE_Editor*      MEditor         = nullptr;
  float**           MInputPtrs      = nullptr;
  float**           MOutputPtrs     = nullptr;
  float**           MParameterPtrs  = nullptr;
  uint32_t          MNumInputs      = 0;
  uint32_t          MNumOutputs     = 0;
  uint32_t          MNumParameters  = 0;
  //float*            MHostValues     = nullptr;
  //float*            MProcessValues  = nullptr;
  float             MSampleRate     = 0.0f;


//------------------------------
public:
//------------------------------

  KODE_LadspaInstance(KODE_Instance* AInstance, uint32_t ASampleRate) {
    MDescriptor     = AInstance->getDescriptor();
    MInstance       = AInstance;
    MSampleRate     = ASampleRate;
    MNumInputs      = MDescriptor->inputs.size();
    MNumOutputs     = MDescriptor->outputs.size();
    MNumParameters  = MDescriptor->parameters.size();
    MInputPtrs      = (float**)malloc(MNumInputs     * sizeof(float*));
    MOutputPtrs     = (float**)malloc(MNumOutputs    * sizeof(float*));
    MParameterPtrs  = (float**)malloc(MNumParameters * sizeof(float*));
    //MHostValues     = (float*)malloc(MNumParameters * sizeof(float ));
    //MProcessValues  = (float*)malloc(MNumParameters * sizeof(float ));

    //instance->on_open();
    //MInstance->on_initialize(); // open?

  }

  //----------

  virtual ~KODE_LadspaInstance() {
    if (MInstance) delete MInstance;
    if (MInputPtrs)     free(MInputPtrs);
    if (MOutputPtrs)    free(MOutputPtrs);
    if (MParameterPtrs) free(MParameterPtrs);
    //if (MHostValues)    free(MHostValues);
    //if (MProcessValues) free(MProcessValues);
  }

  //----------

  //KODE_Instance* getInstance() {
  //  return MInstance;
  //}
//------------------------------
public:
//------------------------------

  void ladspa_connect_port(unsigned long Port, LADSPA_Data * DataLocation) {
    //LADSPA_Trace("ladspa: connect_port Port:%i DataLocation:%p\n",Port,DataLocation);
    //if (Port < 0) return;

    if (Port < MNumInputs) {
      MInputPtrs[Port] = (float*)DataLocation;
      return;
    }
    Port -= MNumInputs;
    if (Port < MNumOutputs) {
      MOutputPtrs[Port] = (float*)DataLocation;
      return;
    }
    Port -= MNumOutputs;
    if (Port < MNumParameters) {
      MParameterPtrs[Port] = (float*)DataLocation;
      return;
    }
    Port -= MNumParameters;
  }

  //----------

  void ladspa_activate() {
    //LADSPA_Trace("ladspa: activate\n");
    if (MInstance) {
      //MSampleRate = MPlugin->getSampleRate();
      //MInstance->on_stateChange(kps_initialize);
      //MInstance->on_initialize();
//      MInstance->on_activate();
    }
  }

  //----------

  void ladspa_run(unsigned long SampleCount) {
    //LADSPA_Trace("ladspa: run SampleCount:%i\n",SampleCount);

    if (MInstance) {
      for (uint32_t i=0; i<MNumParameters; i++) {
        float v = *MParameterPtrs[i];
        //MHostValues[i] = v;
        if (v != MInstance->getParameterValue(i)) {
          MInstance->setParameterValue(i,v); // almoste3qual

          KODE_Parameter* param = MDescriptor->parameters[i];
          /*if (param)*/ v = param->from_01(v);

//          MInstance->on_parameterChange(i,v);
        }
      }

      KODE_ProcessContext context;
      uint32_t num_in  = MDescriptor->inputs.size();
      uint32_t num_out = MDescriptor->outputs.size();
//      for (uint32_t i=0; i<num_in; i++)  { context.inputs[i]  = MInputPtrs[i]; }
//      for (uint32_t i=0; i<num_out; i++) { context.outputs[i] = MOutputPtrs[i]; }
//      context.playstate     = KODE_PLUGIN_PLAYSTATE_NONE;
//      context.samplepos     = 0;
//      context.beatpos       = 0.0f;
//      context.tempo         = 0.0f;
//      context.timesig_num   = 0;
//      context.timesig_denom = 0;
//      context.numInputs     = num_in;
//      context.numOutputs    = num_out;
//      context.numSamples    = SampleCount;
//      context.samplerate    = MSampleRate;

//      MInstance->on_process(&context);

    }
  }

  //----------

  void ladspa_run_adding(unsigned long SampleCount) {
    //LADSPA_Trace("ladspa: run_adding SampleCount:%i\n",SampleCount);
  }

  //----------

  void ladspa_set_run_adding_gain(LADSPA_Data Gain) {
    //LADSPA_Trace("ladspa: set_run_adding_gain Gain:%.3f\n",Gain);
  }

  //----------

  void ladspa_deactivate() {
    //LADSPA_Trace("ladspa: deactivate\n");
    if (MInstance) {
//      MInstance->on_deactivate();
      //MInstance->on_stop();
    }
  }

  //----------

  void ladspa_cleanup() {
    //LADSPA_Trace("ladspa: cleanup\n");
    if (MInstance) {
//      MInstance->on_terminate();
      //MInstance->on_close();
    }
  }

  //----------


};

//----------------------------------------------------------------------
#endif
