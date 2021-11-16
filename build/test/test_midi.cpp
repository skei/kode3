
#define KODE_NO_PLUGIN
#define KODE_NO_GUI

#include "kode.h"
#include "midi/kode_midi_file.h"

//----------------------------------------------------------------------

KODE_MidiFile*  midifile = nullptr;

//#define MIDIFILE "/DISKS/sda2/code/git/kode3/bin/data/Jambala8.mid"
#define MIDIFILE "/DISKS/sda2/code/git/kode3/bin/data/larry.mid"
//#define MIDIFILE "/DISKS/sda2/code/git/kode3/bin/data/stranded.mid"

//----------------------------------------------------------------------

int main(void) {

  //KODE_DPrint("Loading: '%s'\n",MIDIFILE);

  midifile = new KODE_MidiFile();
  midifile->load(MIDIFILE);
  midifile->print();

  //KODE_MidiSequence* sequence = midifile->getMidiSequence();

  //KODE_DPrint("name '%s'\n",sequence->name);
  //KODE_DPrint("num_tracks: %i\n",sequence->tracks.size());
  //for (uint32_t i=0; i<sequence->tracks.size(); i++) {
  //  KODE_DPrint("%i. '%s' num_events %i\n",i,sequence->tracks[i]->name,sequence->tracks[i]->events.size());
  //}

  midifile->unload();
  delete midifile;

  return 0;
}
