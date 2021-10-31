#ifndef kode_editor_included
#define kode_editor_included
//----------------------------------------------------------------------

#include "kode.h"
#include "base/types/kode_array.h"
#include "plugin/kode_parameter.h"
#include "gui/kode_widget.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class KODE_Control {
public:
  KODE_Widget*    widget    = nullptr;
  KODE_Parameter* parameter = nullptr;
};

typedef KODE_Array<KODE_Control*> KODE_ControlArray;

//----------

class KODE_EditorListener {
  virtual void parameter_changed_from_editor(uint32_t index, float value) = 0;  //{}
  virtual void editor_resized_from_editor(float delta_x, float delta_y)   = 0;  //{}
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class KODE_Editor {

//------------------------------
private:
//------------------------------

  KODE_EditorListener*  MListener = nullptr;
  KODE_ControlArray     MControls = {};

//------------------------------
public:
//------------------------------

  KODE_Editor() { KODE_PRINT; };
  virtual ~KODE_Editor() { KODE_PRINT; };

//------------------------------
public:
//------------------------------

  void setListener(KODE_EditorListener* AListener) {
    KODE_PRINT;
    MListener = AListener;
  }

//------------------------------
public:
//------------------------------

//  virtual void open() {}
//  virtual void close() {}
//  virtual void eventLoop() {} // -> KODE_Window

  //virtual void set_parameter_value(uint32_t index, float value) {}
  //virtual void redraw_parameter(uint32_t index) {}

};

//----------------------------------------------------------------------
#endif
