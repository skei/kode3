#ifndef kode_widget_included
#define kode_widget_included
//----------------------------------------------------------------------

#include "kode.h"
#include "base/types/kode_array.h"
#include "base/types/kode_rect.h"

//class KODE_Window;

class KODE_Widget;
typedef KODE_Array<KODE_Widget*>  KODE_WidgetArray;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

enum KODE_EWidgetAlignment {
  KODE_WIGET_ALIGNMENT_NONE   = 0,
  KODE_WIGET_ALIGNMENT_PARENT = 1,
};

//----------

struct KODE_WidgetState {
  bool visible      = true;
  bool active       = true;
  bool interactive  = true;
};

//----------

struct KODE_WidgetLayout {
  uint32_t    alignment = KODE_WIGET_ALIGNMENT_NONE;
  KODE_Rect  border;
  KODE_Rect  spacing;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class KODE_Widget {

//------------------------------
protected:
//------------------------------

  KODE_Widget*      MWidgetParent   = nullptr;
  KODE_WidgetArray  MWidgetChildren = {};
  KODE_Widget*      MWidgetOwner    = nullptr;
  int32_t           MWidgetIndex    = -1;

  KODE_Rect         MWidgetRect     = {};
  float             MWidgetValue    = 0.0;
  KODE_WidgetState  MWidgetState    = {};
  KODE_WidgetLayout MWidgetLayout   = {};

//------------------------------
public:
//------------------------------

  virtual KODE_Widget*      getParent()     { return MWidgetParent; }
  virtual KODE_WidgetArray* getChildren()   { return &MWidgetChildren; }
  virtual KODE_Widget*      getOwner()      { return MWidgetOwner; }
  virtual int32_t           getIndex()      { return MWidgetIndex; }

  virtual KODE_Rect         getRect()       { return MWidgetRect; }
  virtual float             getValue()      { return MWidgetValue; }
//virtual KODE_WidgetState  getState()      { return MWidgetState; }
  virtual bool              isVisible()     { return MWidgetState.visible; }
  virtual bool              isActive()      { return MWidgetState.active; }
  virtual bool              isInteractive() { return MWidgetState.interactive; }
//virtual KODE_WidgetLayout getLayout()     { return MWidgetLayout; }
  virtual uint32_t          getAlignment()  { return MWidgetLayout.alignment; }
  virtual KODE_Rect         getBorder()     { return MWidgetLayout.border; }
  virtual KODE_Rect         getSpacing()    { return MWidgetLayout.spacing; }

  //----------

  virtual void setParent(KODE_Widget* AParent)          { MWidgetParent             = AParent; }
//virtual void setChildren(KODE_WidgetArray* AChildren) { MWidgetChildren           = AChildren; }
  virtual void setOwner(KODE_Widget* AOwner)            { MWidgetOwner              = AOwner; }
  virtual void setIndex(int32_t AIndex)                 { MWidgetIndex              = AIndex; }

  virtual void setRect(KODE_Rect ARect)                 { MWidgetRect               = ARect; }
  virtual void setValue(float AValue)                   { MWidgetValue              = AValue; }
//virtual void setState(KODE_WidgetState AFlags)        { MWidgetState              = AFlags; }
  virtual void setVisible(bool AState=true)             { MWidgetState.visible      = AState; }
  virtual void setActive(bool AState=true)              { MWidgetState.active       = AState; }
  virtual void setInteractive(bool AState=true)         { MWidgetState.interactive  = AState; }
//virtual void setLayout(KODE_WidgetLayout ALayout)     { MWidgetLayout = ALayout; }
  virtual void setAlignment(uint32_t AAlignment)        { MWidgetLayout.alignment   = AAlignment; }
  virtual void setBorder(KODE_Rect ABorder)             { MWidgetLayout.border      = ABorder; }
  virtual void setSpacing(KODE_Rect ASpacing)           { MWidgetLayout.spacing     = ASpacing; }

//------------------------------
public:
//------------------------------

  virtual void appendChild(KODE_Widget* AWidget) {
  }

  virtual void deleteChildren() {
  }

  virtual KODE_Widget* findChild(float AXpos, float AYpos) {
    return nullptr;
  }

//------------------------------
public:
//------------------------------

  virtual void redraw() {}
  virtual void rearrange() {}

//------------------------------
public:
//------------------------------

  virtual void on_widget_setpos() {}
  virtual void on_widget_setsize() {}
  virtual void on_widget_realign() {}
  virtual void on_widget_paint() {}
  virtual void on_widget_mouse_click() {}
  virtual void on_widget_mouse_move() {}
  virtual void on_widget_mouse_release() {}
  virtual void on_widget_key_press() {}
  virtual void on_widget_key_release() {}

//------------------------------
public:
//------------------------------

  virtual void do_widget_moved(KODE_Widget* ASender) {
    if (MWidgetParent) MWidgetParent->do_widget_moved(ASender);
  }

  virtual void do_widget_resized(KODE_Widget* ASender) {
    if (MWidgetParent) MWidgetParent->do_widget_resized(ASender);
  }

  virtual void do_widget_updated(KODE_Widget* ASender) {
    if (MWidgetParent) MWidgetParent->do_widget_updated(ASender);
  }

  virtual void do_widget_redraw(KODE_Widget* ASender) {
    if (MWidgetParent) MWidgetParent->do_widget_redraw(ASender);
  }

  virtual void do_widget_capture_mouse(KODE_Widget* ASender) {
    if (MWidgetParent) MWidgetParent->do_widget_capture_mouse(ASender);
  }

  virtual void do_widget_capture_keys(KODE_Widget* ASender) {
    if (MWidgetParent) MWidgetParent->do_widget_capture_keys(ASender);
  }

};

//----------------------------------------------------------------------
#endif
