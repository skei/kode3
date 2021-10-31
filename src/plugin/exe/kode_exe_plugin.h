#ifndef kode_exe_plugin_included
#define kode_exe_plugin_included
//----------------------------------------------------------------------

template <class DESCRIPTOR, class INSTANCE>
class KODE_ExePlugin
: public KODE_EditorListener {

private:

    DESCRIPTOR*   descriptor  = nullptr;
    INSTANCE*     instance    = nullptr;
    KODE_Editor*  editor      = nullptr;

public:

  // KODE_EditorListener
  void parameter_changed_from_editor(uint32_t index, float value) final {
  }

  //----------

  void editor_resized_from_editor(float delta_x, float delta_y) final {
  }

public:

  int main(int argc, char** argv) {
    descriptor = new DESCRIPTOR();
    if (descriptor) {
      descriptor->name = "myPlugin";
      instance = new INSTANCE();
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

#define KODE_EXE_PLUGIN_ENTRYPOINT(D,I) \
                                        \
  KODE_ExePlugin<D,I> EXE_PLUGIN;       \
                                        \
int main(int argc, char** argv) {       \
  return EXE_PLUGIN.main(argc,argv);    \
}                                       \


//----------------------------------------------------------------------
#endif

