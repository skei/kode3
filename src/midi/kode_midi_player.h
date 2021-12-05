#if 0

#ifndef midi_player_included
#define midi_player_included
//----------------------------------------------------------------------

// "plays" a MidiSequence
// keeps track of 'blocksize' window into event stream

#include "midi_file.h"

//----------------------------------------------------------------------

class MidiPlayer {

  MidiFile*     MMidiFile       = nullptr;
  MidiSequence* MSequence       = nullptr;
  uint32_t      MSamplePos      = 0;

  float         MSampleRate     = 44100.0;
  float         MInvSampleRate  = (1.0 / MSampleRate);
  float         MCurrentTime    = 0.0;

//------------------------------
public:
//------------------------------

  MidiPlayer() {
  }

  //----------

  ~MidiPlayer() {
  }

//------------------------------
public:
//------------------------------

  void initialize(MidiFile* AMidiFile, float ASampleRate=44100.0, float AStartPos=0.0) {

    MMidiFile       = AMidiFile;
    MSequence       = AMidiFile->getMidiSequence();
    MSampleRate     = ASampleRate;
    MInvSampleRate  = 1.0 / MSampleRate;
    MCurrentTime    = AStartPos;

    for (uint32_t i=0; i<MSequence->num_tracks; i++) {
      MSequence->tracks[i]->active = true;
      MSequence->tracks[i]->next_event = 0;
    }

  }

  //----------

  // process 1 sample

  void process(uint32_t ASampleRate) {
    for (uint32_t t=0; t<MSequence->tracks.size(); t++) {
      if (MSequence) {
        MidiTrack* track = MSequence->tracks[t];
        if (track) {
          if (track->next_event < track->events.size()) {
            while (track->events[track->next_event]->time <= MCurrentTime) {
              MidiEvent* next_event = track->events[track->next_event];

              //handlee next_event
              printf("event.. track %i time %.2f : %02x %02x %02x\n",t,next_event->time,next_event->msg1,next_event->msg2,next_event->msg3);

              track->next_event += 1;
              if (track->next_event >= track->events.size()) {
                MSequence->tracks[t] = nullptr;
                break;
              }
            }
          }
        }
      }
    }
    MCurrentTime += MInvSampleRate;
  }

  //----------

};

//----------------------------------------------------------------------
#endif

#endif
