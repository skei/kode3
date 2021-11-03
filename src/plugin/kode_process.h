#ifndef kode_process_included
#define kode_process_included
//----------------------------------------------------------------------

#include "kode.h"

#define KODE_MAX_AUDIO_INPUTS   8
#define KODE_MAX_AUDIO_OUTPUTS  8

//----------

struct KODE_ProcessContext {

  uint32_t  mode;
  uint32_t  playstate;
  float     samplerate;
  uint32_t  samplepos;
  float     tempo;
  uint32_t  timesig_num;
  uint32_t  timesig_denom;
  float     beatpos;
  uint32_t  numsamples;
  float*    inputs[KODE_MAX_AUDIO_INPUTS];
  float*    outputs[KODE_MAX_AUDIO_OUTPUTS];

};

//----------------------------------------------------------------------
#endif
