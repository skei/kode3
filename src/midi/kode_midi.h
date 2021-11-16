#ifndef kode_midi_included
#define kode_midi_included
//----------------------------------------------------------------------

#include "kode.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------


//----------------------------------------------------------------------
#endif













//#define KODE_MIDI_SET_TEMPO  0x51

//enum KODE_MidiSystemType {
//	KODE_MIDI_SYS_TEXT            = 0x01,
//	KODE_MIDI_SYS_COPYRIGHT       = 0x02,
//	KODE_MIDI_SYS_TRACK_NAME      = 0x03,
//	KODE_MIDI_SYS_INST_NAME       = 0x04,
//	KODE_MIDI_SYS_LYRIC           = 0x05,
//	KODE_MIDI_SYS_MARKER          = 0x06,
//	KODE_MIDI_SYS_CUE_POINT       = 0x07,
//	KODE_MIDI_SYS_EOT             = 0x2f,
//	KODE_MIDI_SYS_SMPTE_OFFSET    = 0x54,
//	KODE_MIDI_SYS_TIME_SIGNATURE  = 0x58,
//	KODE_MIDI_SYS_KEY_SIGNATURE   = 0x59,
//	KODE_MIDI_SYS_SEQUENCER_EVENT = 0x7f,
//	KODE_MIDI_SYS_SYSEX           = 0xf0,
//	KODE_MIDI_SYS_TIME_CODE       = 0xf1,
//	KODE_MIDI_SYS_SONG_POSITION   = 0xf2,
//	KODE_MIDI_SYS_SONG_SELECT     = 0xf3,
//	KODE_MIDI_SYS_TUNE_REQUEST    = 0xf6,
//	KODE_MIDI_SYS_EOX             = 0xf7,
//	KODE_MIDI_SYS_SYNC            = 0xf8,
//	KODE_MIDI_SYS_TICK            = 0xf9,
//	KODE_MIDI_SYS_START           = 0xfa,
//	KODE_MIDI_SYS_CONTINUE        = 0xfb,
//	KODE_MIDI_SYS_STOP            = 0xfc,
//	KODE_MIDI_SYS_ACTIVE_SENSING  = 0xfe,
//	KODE_MIDI_SYS_SYSTEM_RESET    = 0xff
//};


//----------

//struct KODE_MidiEvent {
//  uint32_t  delay_us;
//  uint8_t   channel;
//  uint8_t   type;
//  union {
//    struct { uint8_t  program;                    } program_change;
//    struct { uint8_t  note; uint8_t velocity;     } note_on;
//    struct { uint8_t  note;                       } note_off;
//    struct { uint8_t  key; uint8_t key_pressure;  } key_pressure;
//    struct { uint16_t value;                      } pitch_bend;
//    struct { uint8_t  control, control_value;     } control_change;
//    struct { uint8_t  channel_pressure;           } channel_pressure;
//  } data;
//};

//----------

//struct KODE_MidiSong {
//  int event_count;
//  KODE_MidiEvent* events;
//};

//----------

//struct KODE_MidiMessage {
//  unsigned int time;
//  unsigned char type, channel;
//  union {
//    struct {
//      union { char key, control, program, channel_pressure; };
//      union { char velocity, key_pressure, control_value;   };
//    };
//    struct { unsigned short pitch_bend; };
//  };
//  KODE_MidiMessage* next;
//};

//----------

//struct KODE_MidiStream {
//  void* data;
//  int (*read)(void* data, void* ptr, unsigned int size);
//};

//----------

//struct KODE_MidiStreamMemory {
//  const char* buffer;
//  unsigned int total;
//  unsigned int pos;
//};

//----------

//struct KODE_MidiTrack {
//	unsigned int Idx;
//	unsigned int End;
//	unsigned int Ticks;
//};

//----------

//struct KODE_MidiTempoMessage {
//	unsigned int time;
//	unsigned char type, Tempo[3];
//	KODE_MidiMessage* next;
//};

