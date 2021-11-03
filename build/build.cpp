
#include "kode.h"
#include "kode_clap.h"

//----------------------------------------------------------------------

int main() {
  return 0;
}

//----------------------------------------------------------------------

class myDescriptor : public KODE_Descriptor {
};

//----------

class myInstance : public KODE_Instance {

public:
  myInstance(KODE_Descriptor* ADescriptor) : KODE_Instance(ADescriptor) {}

};

//----------

class myEditor : public KODE_Editor {
};

//----------------------------------------------------------------------

KODE_CLAP_ENTRYPOINT(myDescriptor,myInstance,myEditor);
