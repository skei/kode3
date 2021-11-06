#ifndef kode_editor_included
#define kode_editor_included
//----------------------------------------------------------------------

/*
  TODO: separate editor for each format?
*/

//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_instance.h"
#include "plugin/kode_parameter.h"
#include "gui/kode_widget.h"
#include "gui/kode_window.h"

//----------------------------------------------------------------------

class KODE_Control {
  KODE_ParameterArray   parameters;
  KODE_WidgetArray      widgets;
};

typedef KODE_Array<KODE_Control*> KODE_ControlArray;

//----------------------------------------------------------------------

class KODE_Editor {

//------------------------------
private:
//------------------------------

  KODE_Instance*    MInstance   = nullptr;
  KODE_Descriptor*  MDescriptor = nullptr;
  KODE_Window*      MWindow     = nullptr;
  KODE_ControlArray MControls   = {};

//float             MScale    = 1.0;

//------------------------------
public:
//------------------------------

  KODE_Editor(KODE_Instance* AInstance) {
    MInstance = AInstance;
    MDescriptor = AInstance->getDescriptor();
  }

  //----------

  virtual ~KODE_Editor() {
  }

//------------------------------
public:
//------------------------------

  void connect(KODE_Control* AControl) {};
  void connect(KODE_Widget* AWidget, KODE_Parameter* AParameter) {};
  void connect(KODE_Widget* AWidget, uint32_t AParameterIndex) {};

  void open_editor() {}
  void close_editor() {}
  void update() {}
  void updateParameter(uint32_t AIndex, float AValue) {}

};

//----------------------------------------------------------------------
#endif
