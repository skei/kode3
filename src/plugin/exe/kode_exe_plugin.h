#ifndef kode_exe_plugin_included
#define kode_exe_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_plugin.h"
#include "plugin/exe/kode_exe.h"
//#include "plugin/exe/kode_exe_instance.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

//template <class DESCRIPTOR, class INSTANCE, class EDITOR>
class KODE_ExePlugin {

//------------------------------
private:
//------------------------------

//------------------------------
public:
//------------------------------

  int main(int argc, char** argv) {
    KODE_Descriptor* descriptor = _kode_create_descriptor(); // new DESCRIPTOR();
    if (descriptor) {
      KODE_Instance* instance = _kode_create_instance(descriptor); // new INSTANCE(descriptor);
      if (instance) {
        //KODE_ExeInstance* exe_instance = new KODE_ExeInstance(instance);
        KODE_Editor* editor = _kode_create_editor(instance); // new EDITOR(instacne);
        if (editor) {
          //editor->create(parent);
          //editor->open(640,480);
          //editor->eventLoop();
          //editor->close();
          //editor->destroy();
          delete editor;
        }
        //delete exe_instance;
        delete instance;
      }
      //delete descriptor; // deleted by KODE_Instance
    }
    return 0;
  }

//------------------------------
public:
//------------------------------

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#define KODE_EXE_MAIN(D,I,E)            \
                                        \
  KODE_ExePlugin EXE_PLUGIN;            \
  /*KODE_ExePlugin<D,I,E> EXE_PLUGIN;*/ \
                                        \
  int main(int argc, char** argv) {     \
    return EXE_PLUGIN.main(argc,argv);  \
  }                                     \


//----------------------------------------------------------------------
#endif
