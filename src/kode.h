#ifndef kode_included
#define kode_included
//----------------------------------------------------------------------

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

//#include <string.h>
//#include <math.h>
//#include <array>
//#include <queue>
//#include <vector>
//using namespace std;

//----------------------------------------------------------------------

#include "base/kode_debug.h"

//----------------------------------------------------------------------

// 4         4    5         5
// 123456789abcdef0123456789a
// abcdefghijklmnopqrstuvwxyz
// 5f = _

#define KODE_MAGIC        0x4b5f0000    // 'K_'   // + 0x0000
#define KODE_MAGIC_USER   0x6b5f0000    // 'k_'   // + 0x0000
#define KODE_MAGIC_K_PL   0x4b5f504c    // K_PL   // plugin
#define KODE_MAGIC_K_ED   0x4b5f4544    // K_ED   // editor

#define KODE_MIDI_NOTE_OFF            0x80
#define KODE_MIDI_NOTE_ON             0x90
#define KODE_MIDI_POLY_AFTERTOUCH     0xA0
#define KODE_MIDI_CONTROL_CHANGE      0xB0
#define KODE_MIDI_PROGRAM_CHANGE      0xC0
#define KODE_MIDI_CHANNEL_AFTERTOUCH  0xD0
#define KODE_MIDI_PITCHBEND           0xE0
#define KODE_MIDI_SYS                 0xF0

#define KODE_MAX_STRING_LENGTH        512
#define KODE_MAX_PATH_LENGTH          512

//#define __KODE_DLLEXPORT              __attribute__((visibility("default")))

const char  KODE_HEX_TABLE[]  = "0123456789ABCDEF";
const char  KODE_CSYMBOLS[]   = "________________________________________________0123456789_______ABCDEFGHIJKLMNOPQRSTUVWXYZ______abcdefghijklmnopqrstuvwxyz_____";

//----------------------------------------------------------------------

uint32_t KODE_HashString(const char* buffer) {
  char* ptr = (char*)buffer;
  unsigned long h = 5381;
  int c;
  while ((c = *ptr++)) {
    h = ((h << 5) + h) + c; // h * 33 + c
  }
  return h;
}

//

void KODE_MakeValidSymbol(char* buffer) {
  for (uint32_t i=0; i<strlen(buffer); i++) {
    unsigned char c = buffer[i];
    if ((c<32) || (c>127)) buffer[i] = '_';
    else buffer[i] = KODE_CSYMBOLS[c];
  }
}

//----------------------------------------------------------------------
#endif
