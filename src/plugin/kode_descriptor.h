#ifndef kode_descriptor_included
#define kode_descriptor_included
//----------------------------------------------------------------------

#include "kode.h"
//#include "plugin/kode_parameter.h"

//----------------------------------------------------------------------

class KODE_Descriptor {

//------------------------------
public:
//------------------------------

  const char* name        = "kode_debug";
  const char* author      = "skei.audio";
  const char* url         = "https://torhelgeskei.com";
  uint32_t    short_id    = 0xdead0000;
  uint32_t    version     = 0x00000000;
  //const char* description = "";
  //const char* keywords    = "";
  //int32_t     plugin_type = 0;

  //const char* id          = "skei.audio/kode_debug/0.0.0";
  //const char* version     = "0.0.0";

//------------------------------
public:
//------------------------------

  char* getVersion(char* buffer) {
    sprintf(buffer,"%i.%i.%i",((version & 0xff000000) >> 24),((version & 0x00ff0000) >> 16),((version & 0x0000ffff)));
    return buffer;
  }

  //----------

  char* getId(char* buffer) {
    char ver[32];
    getVersion(ver);
    buffer[0] = 0;
    strcat(buffer,name);
    strcat(buffer,"/");
    strcat(buffer,author);
    strcat(buffer,"/");
    strcat(buffer,ver);
    return buffer;
  }

};

//----------------------------------------------------------------------
#endif
