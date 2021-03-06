#ifndef kode_editor_included
#define kode_editor_included
//----------------------------------------------------------------------

/*
  TODO: separate editor for each format?
*/

//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_parameter.h"
#include "gui/kode_widget.h"
#include "gui/kode_window.h"

//----------------------------------------------------------------------
//
// editor listener
//
//----------------------------------------------------------------------

class KODE_EditorListener {
public:
  virtual void on_editor_updateParameter(uint32_t AIndex, float AValue) {}
  virtual void on_editor_resize(uint32_t AWidth, uint32_t AHeight) {}
};

//----------------------------------------------------------------------
//
// editor window
//
//----------------------------------------------------------------------

class KODE_EditorWindow
: public KODE_Window {

//------------------------------
private:
//------------------------------

  KODE_EditorListener*  MListener   = nullptr;
  KODE_Descriptor*      MDescriptor = nullptr;

//------------------------------
public:
//------------------------------

  KODE_EditorWindow(KODE_EditorListener* AListener, KODE_Descriptor* ADescriptor, uint32_t AWidth, uint32_t AHeight, const char* ATitle="", void* AParent=KODE_NULL)
  : KODE_Window(AWidth,AHeight,ATitle,AParent) {
    MListener = AListener;
    MDescriptor = ADescriptor;
  }

  virtual ~KODE_EditorWindow() {
  }

//------------------------------
public:
//------------------------------

  //void on_window_move(uint32_t AXpos, uint32_t AYpos) override {}
  //void on_window_resize(uint32_t AWidth, uint32_t AHeight) override {}
  //void on_window_paint(uint32_t AXpos, uint32_t AYpos, uint32_t AWidth, uint32_t AHeight) override {}
  //void on_window_keyPress(uint32_t AKey, uint32_t AState, uint32_t ATimeStamp) override {}
  //void on_window_keyRelease(uint32_t AKey, uint32_t AState, uint32_t ATimeStamp) override {}
  //void on_window_mouseClick(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATimeStamp) override {}
  //void on_window_mouseRelease(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATimeStamp) override {}
  //void on_window_mouseMove(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATimeStamp) override {}
  //void on_window_enter(int32_t AXpos, int32_t AYpos, uint32_t ATimeStamp) override {}
  //void on_window_leave(int32_t AXpos, int32_t AYpos, uint32_t ATimeStamp) override {}
  //void on_window_timer() override {}
  //void on_window_idle() override {}
  //void on_window_clientMessage(uint32_t AMsg, void* AData) override {}

//------------------------------
public:
//------------------------------


//------------------------------
public: // widget
//------------------------------

  void do_widget_update(KODE_Widget* AWidget) override {
    KODE_Window::do_widget_update(AWidget);
    KODE_Parameter* parameter = AWidget->getParameter();
    if (parameter) {
      int32_t index = parameter->MIndex;
      float   value = AWidget->getValue();
      // convert to/from 01 in do_editor_updateparameter instead..
      // KODE_Vst3Instance, KODE_ClapInstance, ..
      //KODE_Print("%i = %.3f\n",index,value);
      //value = parameter->from01(value);
      MListener->on_editor_updateParameter(index,value);
    }
  }

  //void do_widget_redraw(KODE_Widget* AWidget, KODE_FRect ARect, uint32_t AMode=0) override {
  //  KODE_Window::do_widget_redraw(AWidget,ARect,AMode);
  //}

  //void do_widget_realign(KODE_Widget* ASender, bool ARecursive=true) override {
  //  KODE_Window::do_widget_realign(ASender,ARecursive);
  //}

  //void do_widget_resized(KODE_Widget* ASender, float ADeltaX=0.0f, float ADeltaY=0.0f) override {
  //  KODE_Window::do_widget_resized(ASender,ADeltaX,ADeltaY);
  //}

  //void do_widget_grabMouseCursor(KODE_Widget* ASender) override {
  //  KODE_Window::do_widget_grabMouseCursor(ASender);
  //}

  //void do_widget_grabKeyboard(KODE_Widget* AWidget) override {
  //  KODE_Window::do_widget_grabKeyboard(AWidget);
  //}

  //void do_widget_grabModal(KODE_Widget* AWidget) override {
  //  KODE_Window::do_widget_grabModal(AWidget);
  //}

  //void do_widget_setMouseCursor(KODE_Widget* AWidget, int32_t ACursor) override {
  //  KODE_Window::do_widget_setMouseCursor(AWidget,ACursor);
  //}

  //void do_widget_setMouseCursorPos(KODE_Widget* ASender, float AXpos, float AYpos) override {
  //  KODE_Window::do_widget_setMouseCursorPos(ASender,AXpos,AYpos);
  //}

  //void do_widget_setHint(KODE_Widget* AWidget, const char* AHint) override {
  //  KODE_Window::do_widget_setHint(AWidget,AHint);
  //}

  //void do_widget_notify(KODE_Widget* AWidget, uint32_t AValue=0) override {
  //  KODE_Window::do_widget_notify(AWidget,AValue);
  //}

};

//----------------------------------------------------------------------
//
// editor
//
//----------------------------------------------------------------------

class KODE_Editor {

//------------------------------
private:
//------------------------------


//------------------------------
protected:
//------------------------------

  KODE_EditorListener*  MListener           = nullptr;
  KODE_Descriptor*      MDescriptor         = nullptr;
  bool                  MIsOpen             = false;
  KODE_EditorWindow*    MWindow             = nullptr;
  float                 MScale              = 1.0;
  KODE_Widget**         MParameterToWidget  = nullptr;

//------------------------------


//------------------------------
public:
//------------------------------

  KODE_Editor(KODE_EditorListener* AListener, KODE_Descriptor* ADescriptor) {
    MListener = AListener;
    MDescriptor = ADescriptor;
    uint32_t num = ADescriptor->getNumParameters();
    MParameterToWidget = (KODE_Widget**)malloc( num * sizeof(KODE_Widget*) );
  }

  //----------

  virtual ~KODE_Editor() {
    if (MWindow) {
      MWindow->close();
      delete MWindow;
    }
    if (MParameterToWidget) free(MParameterToWidget);
  }

//------------------------------
//
//------------------------------

  KODE_Window* getWindow() {
    return MWindow;
  }

//------------------------------
public:
//------------------------------

  //virtual void on_editor_create() {}
  //virtual void on_editor_destroy() {}
  //virtual void on_editor_open() {}
  //virtual void on_editor_close() {}

//------------------------------
public:
//------------------------------

  //void attach(const char* display_name="", unsigned long window=0) {
  virtual void attach(const char* display_name="", void* window=nullptr) {
    //TODO: save arguments, use in open();
    MWindow = new KODE_EditorWindow(MListener,MDescriptor,MDescriptor->getEditorWidth(),MDescriptor->getEditorHeight(),"test",(void*)window);
    MWindow->setFillBackground(true);
    //MWindow->open();
    //MIsOpen = true;
  }

  //----------

  virtual void detach() {
    if (MWindow) {
      delete MWindow;
      MWindow = nullptr;
      //MIsOpen = false;
    }

  }

  //----------

  //void open(uint32_t AWidth, uint32_t AHeight, void* AParent=nullptr) {
  //  if (MWindow) { close(); }
  //  MWindow = new KODE_Window(AWidth,AHeight,"KODE_Editor",AParent);
  //  MWindow->setFillBackground(true);
  //  MWindow->setBackgroundColor(0.4);
  //  MWindow->open();
  //}

  //----------

  //void close() {
  //  if (MWindow) {
  //    MWindow->close();
  //    delete MWindow;
  //    MWindow = nullptr;
  //  }
  //}

  //----------

  virtual void show() {
    //if (MIsOpen) return;
    if (MWindow) MWindow->open();
    MIsOpen = true;
  }

  //----------

  virtual void hide() {
    if (MWindow) MWindow->close();
    MIsOpen = false;

//    detach(); // nope!

    //if (MIsOpen && MWindow) {
    //  delete MWindow;
    //  MWindow = nullptr;
    //  MIsOpen = false;
    //}
  }

  //----------

  //void update() {
  //}

  //----------

  virtual void setScale(float AScale) {
    MScale = AScale;
  }

  //----------

  virtual bool resize(uint32_t width, uint32_t height) {
    KODE_PRINT;
    //if (MWindow) MWindow->resizeWindow(width,height);
    return false;
  }

  //----------

  //void connect(KODE_Widget* AWidget, KODE_Parameter* AParameter) {
  //  AWidget->setParameter(AParameter);
  //  MParameterToWidget[AParameter->index] = AWidget;
  //  AWidget->on_widget_connect(AParameter);
  //}

  //----------

  virtual void connect(KODE_Widget* AWidget, uint32_t AParameterIndex) {
    KODE_Parameter* parameter = MDescriptor->getParameter(AParameterIndex);
    AWidget->setParameter(parameter);
    MParameterToWidget[AParameterIndex] = AWidget;
    AWidget->on_widget_connect(parameter);
  }

  //----------

  // todo: queue parameter changes, update in refresh/timer/idle

  // expects 0..1

  virtual void updateParameter(uint32_t AIndex, float AValue, bool ARedraw=true) {
    //KODE_Print("%i %f\n",AIndex,AValue);
    //KODE_Parameter* parameter = MDescriptor->parameters[AIndex];
    KODE_Widget* widget = MParameterToWidget[AIndex];
    if (widget) {
      //float value = parameter->to01(AValue);
      widget->setValue(AValue);
      if (ARedraw) widget->redraw();
    }
  }

  //----------

  virtual void eventLoop() {
    if (MWindow) {
      MWindow->eventLoop();
    }
  }

//------------------------------
public:
//------------------------------

  //void updateParameterFromGui(uint32_t AIndex, float AValue) {
  //}

  //void on_editor_resize(uint32_t AWidth, uint32_t AHeight) override {
  //}

};

//----------------------------------------------------------------------
#endif
