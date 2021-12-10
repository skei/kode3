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
class KODE_ExePlugin
: public KODE_EditorListener {

//------------------------------
private:
//------------------------------

//------------------------------
public:
//------------------------------

  /*
    descriptor = _kode_create_descriptor
    instance   = _kode_create_instance
    editor     = _kode_create_editor

    instance->on_plugin_createEditor        // on_plugin_initEditor
    editor->attach
    editor->show
    instance->on_plugin_openEditor          // on_plugin_showEditor
    instance->on_plugin_updateEditor
    editor->getWindow->eventLoop
    instance->on_plugin_closeEditor         // on_plugin_hideEditor
    editor->hide
    editor->detach
    instance->on_plugin_destroyEditor       (( op_plugion_exitEditor
    delete editor

    delete instance
    //delete descriptor
  */

  int main(int argc, char** argv) {

    // descriptor

    KODE_Descriptor* descriptor = _kode_create_descriptor(); // new DESCRIPTOR();
    if (descriptor) {

      // instance

      KODE_Instance* instance = _kode_create_instance(descriptor); // new INSTANCE(descriptor);
      if (instance) {

        // editor

        if (descriptor->hasEditor()) {
          KODE_Editor* editor = _kode_create_editor(this,descriptor);
          if (editor) {
            KODE_Print("editor %p\n",editor);
            if (instance->on_plugin_createEditor(editor)) {
              editor->attach("",nullptr);
              editor->show();
              if (instance->on_plugin_openEditor(editor)) {
                instance->on_plugin_updateEditor(editor);
                KODE_Window* window = editor->getWindow();
                if (window) {
                  window->eventLoop();
                }
                instance->on_plugin_closeEditor(editor);
              }
              editor->hide();
              editor->detach();
              instance->on_plugin_destroyEditor(editor);
            }
            delete editor;
          }
        }

        // editor

        delete instance;
      }

      // instance

      //delete descriptor; // deleted by KODE_Instance
    }

    // descriptor

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
