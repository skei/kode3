#ifndef kode_utils_included
#define kode_utils_included
//----------------------------------------------------------------------

#include "kode.h"

//----------------------------------------------------------------------

const char  KODE_HEX_TABLE[]  = "0123456789ABCDEF";

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

//----------

void KODE_MakeValidSymbol(char* buffer) {

  const char CSYMBOLS[]   = "________________________________________________0123456789_______ABCDEFGHIJKLMNOPQRSTUVWXYZ______abcdefghijklmnopqrstuvwxyz_____";

  for (uint32_t i=0; i<strlen(buffer); i++) {
    unsigned char c = buffer[i];
    if ((c<32) || (c>127)) buffer[i] = '_';
    else buffer[i] = CSYMBOLS[c];
  }
}

//----------------------------------------------------------------------
#endif
