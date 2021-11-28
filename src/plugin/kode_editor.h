#ifndef kode_editor_included
#define kode_editor_included
//----------------------------------------------------------------------

/*
  TODO: separate editor for each format?

  * note, editor shouldn't know about instance (cyclic)
    -> KODE_EditorListener
*/

//----------------------------------------------------------------------

#include "kode.h"
//#include "plugin/kode_instance.h"
#include "plugin/kode_parameter.h"
#include "gui/kode_widget.h"
#include "gui/kode_window.h"

//----------------------------------------------------------------------

//class KODE_Control {
//  KODE_ParameterArray   parameters;
//  KODE_WidgetArray      widgets;
//};
//
//typedef KODE_Array<KODE_Control*> KODE_ControlArray;

class KODE_EditorListener {
  virtual void on_editor_updateparameter(uint32_t AIndex, float AValue) {}
  virtual void on_editor_resize(uint32_t AWidth, uint32_t AHeight) {}
};

//----------------------------------------------------------------------

class KODE_Editor {

//------------------------------
private:
//------------------------------

  KODE_EditorListener*  MListener   = nullptr;

  KODE_Descriptor*  MDescriptor = nullptr;
  //KODE_Instance*    MInstance   = nullptr;
  KODE_Window*      MWindow     = nullptr;
  //KODE_ControlArray MControls   = {};
  //float             MScale      = 1.0;

//------------------------------
public:
//------------------------------

  KODE_Editor(KODE_EditorListener* AListener, KODE_Descriptor* ADescriptor) {
    KODE_PRINT;
    MListener = AListener;
    MDescriptor = ADescriptor;
    //MInstance = AInstance;
    //MDescriptor = AInstance->getDescriptor();
  }

  //----------

  virtual ~KODE_Editor() {
    if (MWindow) {
      MWindow->close();
      delete MWindow;
    }
    KODE_PRINT;
  }

//------------------------------
public:
//------------------------------

  void attach(const char* display_name, unsigned long window) {
    KODE_PRINT;
    MWindow = new KODE_Window(MDescriptor->editorWidth,MDescriptor->editorHeight,"test",(void*)window);
    MWindow->setFillBackground(true);
    MWindow->open();
  }

  void show() {
    KODE_PRINT;
  }

  void hide() {
    if (MWindow) {
      delete MWindow;
      MWindow = nullptr;
    }
    KODE_PRINT;
  }

//------------------------------
public:
//------------------------------

//  //KODE_Window* getWindow() {
//  //  return MWindow;
//  //}
//
//  //----------
//
//  //void connect(KODE_Control* AControl) {
//  //}
//
//  void connect(KODE_Widget* AWidget, KODE_Parameter* AParameter) {
//    KODE_PRINT;
//  }
//
//  void connect(KODE_Widget* AWidget, uint32_t AParameterIndex) {
//    KODE_PRINT;
//  }
//
//  //----------
//
//  void open(uint32_t AWidth, uint32_t AHeight, void* AParent=nullptr) {
//    KODE_PRINT;
//    if (MWindow) { close(); }
//    MWindow = new KODE_Window(AWidth,AHeight,"KODE_Editor",AParent);
//    MWindow->setFillBackground(true);
//    MWindow->setBackgroundColor(0.4);
//    MWindow->open();
//  }
//
//  //----------
//
//  void close() {
//    KODE_PRINT;
//    if (MWindow) {
//      MWindow->close();
//      delete MWindow;
//      MWindow = nullptr;
//    }
//  }
//
//  //----------
//
//  void eventLoop() {
//    if (MWindow) {
//      MWindow->eventLoop();
//    }
//  }
//
//  //----------
//
//
//  void update() {
//    //KODE_PRINT;
//  }
//
//  //----------
//
//  void updateParameter(uint32_t AIndex, float AValue) {
//    //KODE_Print("%i = %.3f\n",AIndex,AValue);
//  }

};

//----------------------------------------------------------------------
#endif
