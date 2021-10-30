#ifndef kode_widget_included
#define kode_widget_included
//----------------------------------------------------------------------

#include "kode.h"
#include "base/types/kode_array.h"

//class KODE_Window;

class KODE_Widget;
typedef KODE_Array<KODE_Widget*>  KODE_WidgetArray;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class KODE_Widget {

//------------------------------
private:
//------------------------------

  KODE_Widget*  MOwner  = nullptr;
  KODE_Widget*  MParent = nullptr;;
  int32_t       MIndex  = -1;

//------------------------------
public:
//------------------------------


};

//----------------------------------------------------------------------
#endif
