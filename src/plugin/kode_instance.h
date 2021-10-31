#ifndef kode_instance_included
#define kode_instance_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_editor.h"

class KODE_Instance {
public:
  KODE_Instance() {}
  virtual ~KODE_Instance() {}
public:
  virtual KODE_Editor*  createEditor(void* ptr)  { return nullptr; }
  virtual void          deleteEditor()           { }
  //virtual bool          openEditor()             { return false; }
  //virtual void          closeEditor()            { }
  //virtual void          updateEditor()           { }
};

//----------------------------------------------------------------------
#endif
