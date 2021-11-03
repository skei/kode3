
#include "kode.h"
#include "kode_clap.h"
#include "kode_clap_plugin.h"

#include "kode_descriptor.h"
#include "kode_instance.h"
#include "kode_editor.h"

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
public:
  myEditor(KODE_Instance* AInstance) : KODE_Editor(AInstance) {}
};

//----------------------------------------------------------------------

KODE_CLAP_ENTRYPOINT(myDescriptor,myInstance,myEditor);
