#ifndef kode_clap_utils_included
#define kode_clap_utils_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/clap/kode_clap.h"

//----------------------------------------------------------------------

const char* KODE_ClapEventNames[] = {
  "CLAP_EVENT_NOTE_ON",
  "CLAP_EVENT_NOTE_OFF",
  "CLAP_EVENT_NOTE_END",
  "CLAP_EVENT_NOTE_CHOKE",
  "CLAP_EVENT_NOTE_EXPRESSION",
  "CLAP_EVENT_NOTE_MASK",
  "CLAP_EVENT_PARAM_VALUE",
  "CLAP_EVENT_PARAM_MOD",
  "CLAP_EVENT_TRANSPORT",
  "CLAP_EVENT_MIDI",
  "CLAP_EVENT_MIDI_SYSEX"
};

const char* KODE_ClapNoteExpressionNames[] = {
  "CLAP_NOTE_EXPRESSION_VOLUME",
  "CLAP_NOTE_EXPRESSION_PAN",
  "CLAP_NOTE_EXPRESSION_TUNING",
  "CLAP_NOTE_EXPRESSION_VIBRATO",
  "CLAP_NOTE_EXPRESSION_BRIGHTNESS",
  "CLAP_NOTE_EXPRESSION_BREATH",
  "CLAP_NOTE_EXPRESSION_PRESSURE",
  "CLAP_NOTE_EXPRESSION_TIMBRE"
};

const char* KODE_ClapParamValueFlagNames[] = {
  "CLAP_EVENT_PARAM_BEGIN_ADJUST",
  "CLAP_EVENT_PARAM_END_ADJUST",
  "CLAP_EVENT_PARAM_SHOULD_RECORD"
};

const char* KODE_ClapTransportFlagNames[] = {
  "CLAP_TRANSPORT_HAS_TEMPO",
  "CLAP_TRANSPORT_HAS_BEATS_TIMELINE",
  "CLAP_TRANSPORT_HAS_SECONDS_TIMELINE",
  "CLAP_TRANSPORT_HAS_TIME_SIGNATURE",
  "CLAP_TRANSPORT_IS_PLAYING",
  "CLAP_TRANSPORT_IS_RECORDING",
  "CLAP_TRANSPORT_IS_LOOP_ACTIVE",
  "CLAP_TRANSPORT_IS_WITHIN_PRE_ROLL"
};

//----------------------------------------------------------------------

void KODE_PrintClapEvent(const clap_event* event) {

  //#ifdef KODE_DEBUG_CLAP

  switch (event->type) {
    case CLAP_EVENT_NOTE_ON:
      KODE_Print("CLAP_EVENT_NOTE_ON\n");
      KODE_Print("- time %i\n",event->time);
      KODE_Print("- port_index %i\n",event->note.port_index);
      KODE_Print("- key %i\n",event->note.key);
      KODE_Print("- channel %i\n",event->note.channel);
      KODE_Print("- velocity %.3f\n",event->note.velocity);
      break;
    case CLAP_EVENT_NOTE_OFF:
      KODE_Print("CLAP_EVENT_NOTE_OFF\n");
      KODE_Print("- time %i\n",event->time);
      KODE_Print("- port_index %i\n",event->note.port_index);
      KODE_Print("- key %i\n",event->note.key);
      KODE_Print("- channel %i\n",event->note.channel);
      KODE_Print("- velocity %.3f\n",event->note.velocity);
      break;
    case CLAP_EVENT_NOTE_END:
      KODE_Print("CLAP_EVENT_NOTE_END\n");
      KODE_Print("- time %i\n",event->time);
      KODE_Print("- port_index %i\n",event->note.port_index);
      KODE_Print("- key %i\n",event->note.key);
      KODE_Print("- channel %i\n",event->note.channel);
      KODE_Print("- velocity %.3f\n",event->note.velocity);
      break;
    case CLAP_EVENT_NOTE_CHOKE:
      KODE_Print("CLAP_EVENT_NOTE_CHOKE\n");
      KODE_Print("- time %i\n",event->time);
      KODE_Print("- port_index %i\n",event->note.port_index);
      KODE_Print("- key %i\n",event->note.key);
      KODE_Print("- channel %i\n",event->note.channel);
      KODE_Print("- velocity %.3f\n",event->note.velocity);
      break;
    case CLAP_EVENT_NOTE_EXPRESSION:
      KODE_Print("CLAP_EVENT_NOTE_EXPRESSION\n");
      KODE_Print("- time %i\n",event->time);
      KODE_Print("- expression_id %i (%s)\n",event->note_expression.expression_id,KODE_ClapNoteExpressionNames[event->note_expression.expression_id]);
      KODE_Print("- port_index %i\n",event->note_expression.port_index);
      KODE_Print("- key %i\n",event->note_expression.key);
      KODE_Print("- channel %i\n",event->note_expression.channel);
      KODE_Print("- value %.3f\n",event->note_expression.value);
      break;

    case CLAP_EVENT_NOTE_MASK:
      KODE_Print("CLAP_EVENT_NOTE_MASK\n");
      KODE_Print("- time %i\n",event->time);
      KODE_Print("- port_index %i\n",event->note_mask.port_index);
      KODE_Print("- note_mask %i (%11b)\n",event->note_mask.note_mask,event->note_mask.note_mask);
      KODE_Print("- root_note %i\n",event->note_mask.root_note);
      break;
    case CLAP_EVENT_PARAM_VALUE:
      KODE_Print("CLAP_EVENT_PARAM_VALUE\n");
      KODE_Print("- time %i\n",event->time);
      KODE_Print("- cookie %p\n",event->param_value.cookie);
      KODE_Print("- param_id %i\n",event->param_value.param_id);
      KODE_Print("- port_index %i\n",event->param_value.port_index);
      KODE_Print("- key %i\n",event->param_value.key);
      KODE_Print("- channel %i\n",event->param_value.channel);
      KODE_Print("- flags %i (%08b)\n",event->param_value.flags,event->param_value.flags);
      KODE_Print("- value %.3f\n",event->param_value.value);
      break;
    case CLAP_EVENT_PARAM_MOD:
      KODE_Print("CLAP_EVENT_PARAM_MOD\n");
      KODE_Print("- time %i\n",event->time);
      KODE_Print("- cookie %p\n",event->param_mod.cookie);
      KODE_Print("- param_id %i\n",event->param_mod.param_id);
      KODE_Print("- port_index %i\n",event->param_mod.port_index);
      KODE_Print("- key %i\n",event->param_mod.key);
      KODE_Print("- channel %i\n",event->param_mod.channel);
      KODE_Print("- amount %.3f\n",event->param_mod.amount);
      break;
    case CLAP_EVENT_TRANSPORT:
      KODE_Print("CLAP_EVENT_TRANSPORT\n");
      KODE_Print("- time %i\n",event->time);
      KODE_Print("- flags %i (%08b)\n",event->time_info.flags,event->time_info.flags,event->time_info.flags);
      KODE_Print("- song_pos_beats %i\n",event->time_info.song_pos_beats);
      KODE_Print("- song_pos_seconds %f\n",event->time_info.song_pos_seconds);
      KODE_Print("- tempo %.2f\n",event->time_info.tempo);
      KODE_Print("- tempo_inc %.2f\n",event->time_info.tempo_inc);
      KODE_Print("- bar_start %i\n",event->time_info.bar_start);
      KODE_Print("- bar_number %i\n",event->time_info.bar_number);
      KODE_Print("- loop_start_beats %i\n",event->time_info.loop_start_beats);
      KODE_Print("- loop_end_beats %i\n",event->time_info.loop_end_beats);
      KODE_Print("- loop_start_seconds %f\n",event->time_info.loop_start_seconds);
      KODE_Print("- loop_end_seconds %f\n",event->time_info.loop_end_seconds);
      KODE_Print("- tsig_num %i\n",event->time_info.tsig_num);
      KODE_Print("- tsig_denom %i\n",event->time_info.tsig_denom);
      break;
    case CLAP_EVENT_MIDI:
      KODE_Print("CLAP_EVENT_MIDI\n");
      KODE_Print("- time %i\n",event->time);
      KODE_Print("- port_index %i\n",event->midi.port_index);
      KODE_Print("- port_index %i\n",event->midi.port_index);
      KODE_Print("- data %02x 02x 02x\n",event->midi.data[0],event->midi.data[1],event->midi.data[2]);
      break;
    case CLAP_EVENT_MIDI_SYSEX:
      KODE_Print("CLAP_EVENT_MIDI_SYSEX\n");
      KODE_Print("- time %i\n",event->time);
      KODE_Print("- port_index %i\n",event->midi_sysex.port_index);
      KODE_Print("- size %i\n",event->midi_sysex.size);
      KODE_Print("- buffer %p\n",event->midi_sysex.buffer);
      break;
    default:
      KODE_Print("unknown clap_event.type: %i\n",event->type);
      break;

  } // switch event type

  //#endif // KODE_DEBUG_CLAP

}

//----------------------------------------------------------------------
#endif
