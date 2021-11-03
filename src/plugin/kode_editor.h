#ifndef kode_editor_included
#define kode_editor_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_instance.h"

//----------------------------------------------------------------------

class KODE_Editor {

private:

  KODE_Instance*  MInstance = nullptr;

public:

  KODE_Editor(KODE_Instance* AInstance) {
  }

  virtual ~KODE_Editor() {
  }

};

//----------------------------------------------------------------------
#endif
