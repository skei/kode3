#ifndef kode_parameter_included
#define kode_parameter_included
//----------------------------------------------------------------------

#include "kode.h"
#include "base/kode_array.h"

class KODE_Parameter {
public:
  const char* name;
  const char* label;
public:

};

typedef KODE_Array<KODE_Parameter*>  KODE_ParameterArray;


//----------------------------------------------------------------------
#endif
