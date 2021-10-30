#ifndef kode_lv2_editor_included
#define kode_lv2_editor_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/lv2/kode_lv2.h"

class KODE_Lv2Editor {

//------------------------------
private:
//------------------------------


//------------------------------
public:
//------------------------------

  KODE_Lv2Editor() {
  }

  //----------

  virtual ~KODE_Lv2Editor() {
  }

//------------------------------
public: // lv2
//------------------------------

  /*
    Create a new UI and return a handle to it.  This function works
    similarly to LV2_Descriptor::instantiate().

    descriptor
      The descriptor for the UI to instantiate.
    plugin_uri
      The URI of the plugin that this UI will control.
    bundle_path
      The path to the bundle containing this UI, including the trailing
      directory separator.
    write_function
      A function that the UI can use to send data to the plugin's input ports.
    controller
      A handle for the UI instance to be passed as the first parameter of UI
      methods.
    widget (output)
      widget pointer. The UI points this at its main widget, which has the type
      defined by the UI type in the data file.
    features
      An array of LV2_Feature pointers. The host must pass all feature URIs
      that it and the UI supports and any additional data, as in
      LV2_Descriptor::instantiate(). Note that UI features and plugin features
      are not necessarily the same.
  */

  void lv2ui_instantiate(const struct LV2UI_Descriptor* descriptor, const char* plugin_uri, const char* bundle_path, LV2UI_Write_Function write_function, LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features) {
  }

  //----------

  /*
    Destroy the UI.
    The host must not try to access the widget after calling this function.
  */

  void lv2ui_cleanup() {
  }

  //----------

  /*
    Tell the UI that something interesting has happened at a plugin port.
    What is "interesting" and how it is written to `buffer` is defined by
    `format`, which has the same meaning as in LV2UI_Write_Function().
    Format 0 is a special case for lv2:ControlPort, where this function
    should be called when the port value changes (but not necessarily for
    every change), `buffer_size` must be sizeof(float), and `buffer`
    points to a single IEEE-754 float.
    By default, the host should only call this function for lv2:ControlPort
    inputs.  However, the UI can request updates for other ports statically
    with ui:portNotification or dynamically with ui:portSubscribe.
    The UI MUST NOT retain any reference to `buffer` after this function
    returns, it is only valid for the duration of the call.
    This member may be NULL if the UI is not interested in any port events.
  */

  void lv2ui_port_event(uint32_t port_index, uint32_t buffer_size, uint32_t format, const void* buffer) {
  }

//------------------------------
public:
//------------------------------

};

//----------------------------------------------------------------------
#endif


/*
  LV2UI_Write_Function
  A host-provided function that sends data to a plugin's input ports.

  controller
    The opaque controller pointer passed to LV2UI_Descriptor::instantiate().
  port_index
    Index of the port to update.
  buffer
    Buffer containing `buffer_size` bytes of data.
  buffer_size
    Size of `buffer` in bytes.
  port_protocol
    Either 0 or the URID for a ui:PortProtocol.  If 0, the protocol is
    implicitly ui:floatProtocol, the port MUST be an lv2:ControlPort input,
    `buffer` MUST point to a single float value, and `buffer_size` MUST be
    sizeof(float).  The UI SHOULD NOT use a protocol not supported by the
    host, but the host MUST gracefully ignore any protocol it does not
    understand.
*/
