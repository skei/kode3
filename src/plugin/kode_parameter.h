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
  void setHidden(bool state=true) { is_hidden = state; }
  void setReadOnly(bool state=true) { is_readonly = state; }
  void canAutomate(bool state=true) { can_automate = state; }
  void canModulate(bool state=true) { can_modulate = state; }
};

//----------------------------------------------------------------------

class KODE_Parameter {

  friend class KODE_Descriptor;
  friend class KODE_Instance;
  //friend class KODE_Editor;
  friend class KODE_EditorWindow;

//------------------------------
private:
//------------------------------

  char  MDisplayText[32]    = {0};

  // vst3: give these to host (when it asks for param info
  float MInternalDefValue  = 0.0;
  float MInternalMinValue  = 0.0;
  float MInternalMaxValue  = 0.0;

//------------------------------
//public:
protected:
//------------------------------

  const char*           MName       = "";
  const char*           MShortName  = "";
  const char*           MLabel      = "";
  KODE_ParameterOptions MOptions    = {};
  float                 MDefValue   = 0.0;
  float                 MMinValue   = 0.0;
  float                 MMaxValue   = 1.0;
  uint32_t              MNumSteps   = 0;
  int32_t               MIndex      = -1;

//------------------------------
public:
//------------------------------

  KODE_Parameter(const char* AName, float ADefValue=0.0f, float AMinValue=0.0f, float AMaxValue=1.0f, uint32_t ANumSteps=0) {
    MName = AName;
    MDefValue = ADefValue;
    MMinValue = AMinValue;
    MMaxValue = AMaxValue;
    MNumSteps = ANumSteps;
    MInternalDefValue = ADefValue;
    MInternalMinValue = AMinValue;
    MInternalMaxValue = AMaxValue;
  }

  virtual ~KODE_Parameter() {
  }

//------------------------------
public:
//------------------------------

  // the values the parameter were created with
  // def/min/max might change depending on plugin format
  // (converted to 0..1)

  float                   getInternalDefValue() { return MInternalDefValue; }
  float                   getInternalMinValue() { return MInternalMinValue; }
  float                   getInternalMaxValue() { return MInternalMaxValue; }

  const char*             getName()         { return MName; }
  const char*             getShortName()    { return MShortName; }
  const char*             getLabel()        { return MLabel; }
  KODE_ParameterOptions*  getOptions()      { return &MOptions; }
  float                   getDefValue()     { return MDefValue; }
  float                   getMinValue()     { return MMinValue; }
  float                   getMaxValue()     { return MMaxValue; }
  uint32_t                getNumSteps()     { return MNumSteps; }
  int32_t                 getIndex()        { return MIndex; }

  bool                    isHidden()     { return MOptions.is_hidden; }
  bool                    isReadOnly()   { return MOptions.is_readonly; }
  bool                    canAutomate()  { return MOptions.can_automate; }
  bool                    canModulate()  { return MOptions.can_modulate; }

  void setName(const char* AName)           { MName = AName; }
  void setShortName(const char* AShortName) { MShortName = AShortName; }
  void setLabel(const char* ALabel)         { MLabel = ALabel; }
  void setDefValue(float AValue)            { MDefValue = AValue; }
  void setMinValue(float AValue)            { MMinValue = AValue; }
  void setMaxValue(float AValue)            { MMaxValue = AValue; }
  void setNumSteps(uint32_t ANum)           { MNumSteps = ANum; }
  void setIndex(int32_t AIndex)             { MIndex = AIndex; }

  void setIsHidden(bool AState=true)        { MOptions.is_hidden = AState; }
  void setIsReadOnly(bool AState=true)      { MOptions.is_readonly = AState; }
  void setCanAutomate(bool AState=true)     { MOptions.can_automate = AState; }
  void setCanModulate(bool AState=true)     { MOptions.can_modulate = AState; }

//------------------------------
public:
//------------------------------

  virtual float to01(float value) {
    float range = MInternalMaxValue - MInternalMinValue;
    return ((value - MInternalMinValue) / range);
  }

  //----------

  virtual float from01(float AValue) {
    float range = MInternalMaxValue - MInternalMinValue;
    return MInternalMinValue + (AValue * range);
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
