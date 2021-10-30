#ifndef kode_parameter_included
#define kode_parameter_included
//----------------------------------------------------------------------

#include <stdio.h> // sprintf

#include "base/types/kode_array.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class KODE_Parameter {

//------------------------------
private:
//------------------------------

  char MDisplayText[32] = {0};

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

  virtual char* getDisplayText(float value) {
    // TODO: KODE_FloatToString
    sprintf(MDisplayText,"%.2f",value);
    return MDisplayText;
  }

};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

typedef KODE_Array<KODE_Parameter*> KODE_ParameterArray;

//----------------------------------------------------------------------
#endif
