#ifndef kode_color_included
#define kode_color_included
//----------------------------------------------------------------------

class KODE_Color {

public:

  float r,g,b,a;

public:

  KODE_Color() {
    r = 0.0;
    g = 0.0;
    b = 0.0;
    a = 1.0;
  }

  KODE_Color(float v) {
    r = v;
    g = v;
    b = v;
    a = 1.0;
  }


  KODE_Color(float ar, float ag, float ab, float aa=1.0) {
    r = v;
    g = v;
    b = v;
    a = aa;
  }

}

//----------------------------------------------------------------------
#endif
