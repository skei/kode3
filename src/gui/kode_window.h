#ifndef kode_window_included
#define kode_window_included
//----------------------------------------------------------------------

#include "kode.h"
//#include "gui/kode_widget.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class KODE_Window
/*: public KODE_Widget*/ {

//------------------------------
private:
//------------------------------

  uint32_t    MWindowWidth  = 0;
  uint32_t    MWindowHeight = 0;
  const char* MWindowTitle  = "";

//------------------------------
public:
//------------------------------

  KODE_Window(uint32_t AWidth, uint32_t AHeight, void* AParent=nullptr)
  /*: KODE_Widget()*/ {
  }

  virtual ~KODE_Window() {
  }

//------------------------------
public: // window
//------------------------------

  virtual void on_window_move() {}
  virtual void on_window_resize() {}

  virtual void on_window_open() {}
  virtual void on_window_close() {}
  virtual void on_window_mouse_click() {}
  virtual void on_window_mouse_release() {}
  virtual void on_window_mouse_move() {}
  virtual void on_window_key_press() {}
  virtual void on_window_key_release() {}
  virtual void on_window_paint() {}

//------------------------------
public: // widget
//------------------------------


};

//----------------------------------------------------------------------
#endif

