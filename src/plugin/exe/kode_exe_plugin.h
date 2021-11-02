#ifndef kode_exe_plugin_included
#define kode_exe_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/exe/kode_exe.h"
//#include "plugin/exe/kode_exe_instance.h"

//----------------------------------------------------------------------

template <class DESCRIPTOR, class INSTANCE, class EDITOR>
class KODE_ExePlugin
: public KODE_EditorListener {

//------------------------------
private:
//------------------------------

  DESCRIPTOR*   descriptor  = nullptr;
  INSTANCE*     instance    = nullptr;
  KODE_Editor*  editor      = nullptr;

//------------------------------
public: // KODE_EditorListener
//------------------------------

  void parameter_changed_from_editor(uint32_t index, float value) final {
    KODE_PRINT;
  }

  //----------

  void editor_resized_from_editor(float delta_x, float delta_y) final {
    KODE_PRINT;
  }

//------------------------------
public:
//------------------------------

  int main(int argc, char** argv) {
    KODE_PRINT;
    descriptor = new DESCRIPTOR();
    if (descriptor) {
      descriptor->name = "myPlugin";
      instance = new INSTANCE(descriptor);
      if (instance) {
        editor = instance->createEditor(nullptr);
        if (editor) {
          editor->setListener(this);
          //instance->openEditor();
          //editor->eventLoop();
          //instance->closeEditor();
          instance->deleteEditor();
        } // editor
        delete instance;
      } // instamce
      delete descriptor;
    } // descriptor
    return 0;
  }

};

//----------------------------------------------------------------------
//
// entrypoint
//
//----------------------------------------------------------------------

#define KODE_EXE_PLUGIN_ENTRYPOINT(D,I,E)   \
                                            \
  KODE_ExePlugin<D,I,E> EXE_PLUGIN;         \
                                            \
  /* ----- */                               \
                                            \
  int main(int argc, char** argv) {         \
    KODE_PRINT;                             \
    return EXE_PLUGIN.main(argc,argv);      \
  }                                         \


//----------------------------------------------------------------------
#endif
