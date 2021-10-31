#ifndef kode_instance_included
#define kode_instance_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_editor.h"

class KODE_Instance {

private:

  KODE_Descriptor*  MDescriptor = nullptr;

public:

  KODE_Instance(KODE_Descriptor* ADescriptor) {
    KODE_PRINT;
    MDescriptor = ADescriptor;
  }

  virtual ~KODE_Instance() {
    KODE_PRINT;
  }

public:

  virtual KODE_Editor* createEditor(void* ptr) {
    KODE_PRINT;
    return nullptr;
  }

  virtual void deleteEditor() {
    KODE_PRINT;
  }

  //void setDescriptor(KODE_Descriptor* ADescriptor) {
  //  MDescriptor = ADescriptor;
  //}

  //KODE_Descriptor* getDescriptor() {
  //  return MDescriptor;
  //}

  //virtual bool openEditor() { return false; }
  //virtual void closeEditor() { }
  //virtual void updateEditor() { }

};

//----------------------------------------------------------------------
#endif
