#ifndef kode_rect_included
#define kode_rect_included
//----------------------------------------------------------------------

#include "kode.h"
#include "base/types/kode_point.h"

class KODE_Rect {

//------------------------------
public:
//------------------------------

  float x;
  float y;
  float w;
  float h;

//------------------------------
public:
//------------------------------

  KODE_Rect() {
    x = 0;
    y = 0;
    w = 0;
    h = 0;
  };

  KODE_Rect(float v) {
    x = 0;
    y = 0;
    w = v;
    h = v;
  };

  KODE_Rect(float aw, float ah) {
    x = 0;
    y = 0;
    w = aw;
    h = ah;
  };

  KODE_Rect(float ax, float ay, float aw, float ah) {
    x = ax;
    y = ay;
    w = aw;
    h = ah;
  };

//------------------------------
public:
//------------------------------

  bool  contains(KODE_Point p)        { return false; }
  bool  contains(float ax, float ay)  { return false; }
  bool  touches(KODE_Rect r)          { return false; }

  //void  intersect(KODE_Rect r) {}
  //void  include(KODE_Rect r) {}

};

//----------------------------------------------------------------------


//----------------------------------------------------------------------


//----------------------------------------------------------------------
#endif
