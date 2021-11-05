#ifndef kode_dssi_instance_included
#define kode_dssi_instance_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_instance.h"
#include "plugin/kode_process_context.h"
//#include "plugin/kode_instance_listener.h"

class KODE_DssiInstance
/*: public KODE_InstanceListener*/ {

//----------
//------------------------------
private:
//------------------------------

  KODE_Instance*          MInstance           = nullptr;
  KODE_Descriptor*        MDescriptor         = nullptr;
  float**                 MInputPtrs          = nullptr;
  float**                 MOutputPtrs         = nullptr;
  float**                 MParameterPtrs      = nullptr;
  DSSI_Program_Descriptor MProgramDescriptor  = {0};
  uint32_t                MCurrentBank        = 0;
  uint32_t                MCurrentProgram     = 0;
  uint32_t                MNumInputs          = 0;
  uint32_t                MNumOutputs         = 0;
  uint32_t                MNumParameters      = 0;
  float                   MSampleRate         = 0.0f;

  //KODE_Rect               MEditorRect         = KODE_Rect(0);
  //float*                  MHostValues     = nullptr;
  //float*                  MProcessValues  = nullptr;

//------------------------------
public:
//------------------------------

  KODE_DssiInstance(KODE_Instance* AInstance, uint32_t ASampleRate) {
    MInstance = AInstance;
    MDescriptor = AInstance->getDescriptor();
    MSampleRate = ASampleRate;
    MNumInputs      = MDescriptor->inputs.size();
    MNumOutputs     = MDescriptor->outputs.size();
    MNumParameters  = MDescriptor->parameters.size();
    MInputPtrs      = (float**)malloc(MNumInputs     * sizeof(float*));
    MOutputPtrs     = (float**)malloc(MNumOutputs    * sizeof(float*));
    MParameterPtrs  = (float**)malloc(MNumParameters * sizeof(float*));
    //MHostValues     = (float*) KODE_Malloc(MNumParameters * sizeof(float ));
    //MProcessValues  = (float*) KODE_Malloc(MNumParameters * sizeof(float ));
  }

  virtual ~KODE_DssiInstance() {
    if (MInstance)      delete MInstance;
    if (MInputPtrs)     free(MInputPtrs);
    if (MOutputPtrs)    free(MOutputPtrs);
    if (MParameterPtrs) free(MParameterPtrs);
    //if (MHostValues)    free(MHostValues);
    //if (MProcessValues) free(MProcessValues);
  }

//------------------------------
public:
//------------------------------

  //void setSampleRate(float ASampleRate) {
  //  MSampleRate = ASampleRate;
  //}

//------------------------------
private:
//------------------------------

  void updateParametersInProcess(void) {
    for (uint32_t i=0; i<MNumParameters; i++) {
     float v = *MParameterPtrs[i];
      if (v != MInstance->getParameterValue(i)) {
        MInstance->setParameterValue(i,v);
        KODE_Parameter* param = MDescriptor->parameters[i];
        v = param->from_01(v);
//        MInstance->on_parameterChange(i,v);
      }
    }
  }

  //----------

  void updateMidiInputInProcess(snd_seq_event_t* Events, unsigned long EventCount) {
    uint32_t event_index = 0;
    while ((event_index < EventCount)) {
      snd_seq_event_t* event = &Events[event_index];
      uint32_t ofs = event->time.tick;
      uint32_t chn = 0;
      uint32_t idx = 0;
      uint32_t val = 0;
      switch (event->type) {
        case SND_SEQ_EVENT_NOTEOFF:
          // note off
          chn = event->data.note.channel;
          idx = event->data.note.note;
          val = event->data.note.velocity;
//          MInstance->on_midiInput(ofs,0x80+chn,idx,val);
          break;
        case SND_SEQ_EVENT_NOTEON:
          // note on
          chn = event->data.note.channel;
          idx = event->data.note.note;
          val = event->data.note.velocity;
//          if (val > 0) MInstance->on_midiInput(ofs,0x90+chn,idx,val);
//          else MInstance->on_midiInput(ofs,0x80+chn,idx,val);
          break;
        case SND_SEQ_EVENT_KEYPRESS:
          // polyphonic key pressure (aftertouch)
          chn = event->data.note.channel;
          idx = event->data.note.note;
          val = event->data.note.velocity;
//          MInstance->on_midiInput(ofs,0xA0+chn,idx,val);
          break;
        case SND_SEQ_EVENT_CONTROLLER:
          //control_change
          chn = event->data.control.channel;
          idx = event->data.control.param;
          val = event->data.control.value;
//          MInstance->on_midiInput(ofs,0xB0+chn,idx,val);
          break;
        //case // 0xC0 = program change
        //  break;
        case SND_SEQ_EVENT_CHANPRESS:
          //channel_pressure;
          chn = event->data.control.channel;
          idx = 0;
          val = event->data.control.value;
//          MInstance->on_midiInput(ofs,0xD0+chn,0,val);
          break;
        case SND_SEQ_EVENT_PITCHBEND:
          //pitch_bend
          chn = event->data.control.channel;
          idx = 0;
          val = event->data.control.value;
//          MInstance->on_midiInput(ofs,0xE0+chn,0,val);
          break;
      }
      event_index++;
    }
  }

//------------------------------
public:
//------------------------------

  void dssi_connect_port(unsigned long Port, LADSPA_Data* DataLocation) {
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

  void dssi_activate() {
//    MInstance->on_activate();
  }

  //----------

  void dssi_run(unsigned long SampleCount) {
    updateParametersInProcess();
    KODE_ProcessContext context;
    //...
//    MInstance->on_process(&context);
    //on_processBlock(MInputPtrs,MOutputPtrs,SampleCount);
  }

  //----------

  //void dssi_run_adding(unsigned long SampleCount) {
  //  //DSSI_Trace("dssi: run_adding SampleCount:%i\n",SampleCount);
  //}

  //----------

  //void dssi_set_run_adding_gain(LADSPA_Data Gain) {
  //  //DSSI_Trace("dssi: set_run_adding_gain Gain:%.3f\n",Gain);
  //}

  //----------

  void dssi_deactivate() {
//    MInstance->on_deactivate();
  }

  //----------

  void dssi_cleanup() {
//    MInstance->on_terminate();
//    MInstance->on_close();
  }

//------------------------------
// dssi
//------------------------------

public:

  char* dssi_configure(const char* Key, const char* Value) {
    return nullptr;
  }

  /*
    This function returns a DSSI_Program_Descriptor pointer that is
    guaranteed to be valid only until the next call to get_program,
    deactivate, or configure, on the same plugin instance.  This
    function must return NULL if passed an Index argument out of
    range, so that the host can use it to query the number of
    programs as well as their properties.
  */

  const DSSI_Program_Descriptor* dssi_get_program(unsigned long Index) {
    MProgramDescriptor.Bank = 0;
    MProgramDescriptor.Program = 0;
    MProgramDescriptor.Name = "name";
    return nullptr;
  }

  void dssi_select_program(unsigned long Bank, unsigned long Program) {
    MCurrentBank = Bank;
    MCurrentProgram = Program;
  }

  int dssi_get_midi_controller_for_port(unsigned long Port) {
    return 0;
  }

  //----------

  void dssi_run_synth(unsigned long SampleCount, snd_seq_event_t* Events, unsigned long EventCount) {
    updateParametersInProcess();
    updateMidiInputInProcess(Events,EventCount);
    dssi_run(SampleCount);
  }

  //void dssi_run_synth_adding(unsigned long SampleCount, snd_seq_event_t *Events, unsigned long EventCount) {
  //  //DSSI_Trace("dssi: run_synth_adding SampleCount:%i EventCount:%i\n",SampleCount,EventCount);
  //}

  //void dssi_run_multiple_synths(unsigned long InstanceCount, LADSPA_Handle *Instances, unsigned long SampleCount, snd_seq_event_t **Events, unsigned long *EventCounts) {
  //}

  //void dssi_run_multiple_synths_adding(unsigned long InstanceCount, LADSPA_Handle *Instances, unsigned long SampleCount, snd_seq_event_t **Events, unsigned long *EventCounts) {
  //}

};

//----------------------------------------------------------------------
#endif
