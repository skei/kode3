#ifndef kode_parameter_included
#define kode_parameter_included
//----------------------------------------------------------------------

#include <stdio.h> // sprintf

#include "base/kode_array.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

struct KODE_ParameterOptions {  bool can_automate = true;
};

//----------------------------------------------------------------------

class KODE_Parameter {

//------------------------------
private:
//------------------------------

  char MDisplayText[32] = {0};

//------------------------------
public:
//------------------------------

  const char*           name  = "";
  const char*           label = "";
  KODE_ParameterOptions options;

//------------------------------
public:
//------------------------------

  KODE_Parameter() {
  }

  virtual ~KODE_Parameter() {
  }

//------------------------------
public:
//------------------------------

  virtual float from_01(float value) {
    return value;
  }

  //----------

  virtual float to_01(float value) {
    return value;
  }

  //----------

//  virtual char* getDisplayText(float value) {
//    // TODO: KODE_FloatToString
//    sprintf(MDisplayText,"%.2f",value);
//    return MDisplayText;
//  }

  virtual char* getDisplayText(float value, char* buffer) {
    // TODO: KODE_FloatToString
    sprintf(buffer,"%.2f",value);
    return buffer;
  }

};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

typedef KODE_Array<KODE_Parameter*> KODE_ParameterArray;

//----------------------------------------------------------------------
#endif
