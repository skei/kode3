#ifndef kode_parameter_included
#define kode_parameter_included
//----------------------------------------------------------------------

#include <stdio.h> // sprintf

#include "base/types/kode_array.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

struct KODE_ParameterOptions {
  bool can_automate = true;
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

  const char*           name        = "";
  const char*           short_name  = "";
  const char*           label       = "";
  KODE_ParameterOptions options     = {};

  float                 def_value   = 0.0;
  float                 min_value   = 0.0;
  float                 max_value   = 1.0;

  uint32_t              num_steps   = 0;

  int32_t               index = -1;

//------------------------------
public:
//------------------------------

  KODE_Parameter(const char* AName, float ADefValue=0.0f, float AMinValue=0.0f, float AMaxValue=1.0f ) {
    name = AName;
    def_value = ADefValue;
    min_value = AMinValue;
    max_value = AMaxValue;
  }

  virtual ~KODE_Parameter() {
  }

//------------------------------
public:
//------------------------------

  virtual float from01(float value) {
    float range = max_value - min_value;
    return min_value + (value * range);
  }

  //----------

  virtual float to01(float value) {
    float range = max_value - min_value;
    return ((value - min_value) / range);
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
