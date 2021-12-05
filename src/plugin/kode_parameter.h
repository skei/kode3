#ifndef kode_parameter_included
#define kode_parameter_included
//----------------------------------------------------------------------

#include <stdio.h> // sprintf

#include "base/types/kode_array.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

struct KODE_ParameterOptions {
  bool is_hidden    = false;
  bool is_readonly  = false;
  bool can_automate = true;
  bool can_modulate = false;
};

//----------------------------------------------------------------------

class KODE_Parameter {

//------------------------------
private:
//------------------------------

  char  MDisplayText[32]    = {0};

  // vst3: give these to host (when it asks for param info
  float internal_def_value  = 0.0;
  float internal_min_value  = 0.0;
  float internal_max_value  = 0.0;

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
  int32_t               index       = -1;

//------------------------------
public:
//------------------------------

  KODE_Parameter(const char* AName, float ADefValue=0.0f, float AMinValue=0.0f, float AMaxValue=1.0f ) {
    name = AName;
    def_value = ADefValue;
    min_value = AMinValue;
    max_value = AMaxValue;
    internal_def_value = ADefValue;
    internal_min_value = AMinValue;
    internal_max_value = AMaxValue;
  }

  virtual ~KODE_Parameter() {
  }

//------------------------------
public:
//------------------------------

  // the values the parameter were created with
  // def/min/max might change depending on plugin format
  // (converted to 0..1)

  float getInternalDefValue() { return internal_def_value; }
  float getInternalMinValue() { return internal_min_value; }
  float getInternalMaxValue() { return internal_max_value; }

  //----------

  virtual float from01(float value) {
    float range = internal_max_value - internal_min_value;
    return internal_min_value + (value * range);
  }

  //----------

  virtual float to01(float value) {
    float range = internal_max_value - internal_min_value;
    return ((value - internal_min_value) / range);
  }

  //----------

  virtual char* getDisplayText(float value, char* buffer, uint32_t num_digits=2) {
    char format[16] = {0};
    //sprintf(buffer,"%.2f",value);
    format[0] = '%';
    format[1] = '.';
    format[2] = 48 + num_digits;
    format[3] = 'f';
    format[4] = 0;
    sprintf(buffer,format,value);
    return buffer;
  }

};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

typedef KODE_Array<KODE_Parameter*> KODE_ParameterArray;

//----------------------------------------------------------------------
#endif
