#ifndef kode_lv2_plugin_included
#define kode_lv2_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/lv2/kode_lv2.h"
#include "plugin/lv2/kode_lv2_instance.h"
#include "plugin/lv2/kode_lv2_editor.h"

//----------------------------------------------------------------------

template <class DESCRIPTOR, class INSTANCE>
class KODE_Lv2Plugin {

//------------------------------
private:
//------------------------------

  LV2_Descriptor    MLv2Descriptor            = {};
  LV2UI_Descriptor  MLv2UiDescriptor          = {};

  char              MManifestTtlBuffer[65536] = {0};
  char              MPluginTtlBuffer[65536]   = {0};

//------------------------------
public:
//------------------------------

  KODE_Lv2Plugin() {
    KODE_PRINT;
  }

  //----------

  ~KODE_Lv2Plugin() {
    KODE_PRINT;
  }

//------------------------------
public:
//------------------------------

  const LV2_Descriptor* get_lv2_descriptor(uint32_t index) {
    KODE_Print("index %i\n",index);
    MLv2Descriptor.URI               = "urn:skei.audio/plugin";
    MLv2Descriptor.instantiate       = lv2_instantiate_callback;
    MLv2Descriptor.connect_port      = lv2_connect_port_callback;
    MLv2Descriptor.activate          = lv2_activate_callback;
    MLv2Descriptor.run               = lv2_run_callback;
    MLv2Descriptor.deactivate        = lv2_deactivate_callback;
    MLv2Descriptor.cleanup           = lv2_cleanup_callback;
    MLv2Descriptor.extension_data    = lv2_extension_data_callback;
    return &MLv2Descriptor;
  }

  //----------

  const LV2UI_Descriptor* get_lv2ui_descriptor(uint32_t index) {
    KODE_Print("index %i\n",index);
    MLv2UiDescriptor.URI             = "urn:skei.audio/editor";
    MLv2UiDescriptor.instantiate     = lv2ui_instantiate_callback;
    MLv2UiDescriptor.cleanup         = lv2ui_cleanup_callback;
    MLv2UiDescriptor.port_event      = lv2ui_port_event_callback;
    MLv2UiDescriptor.extension_data  = lv2ui_extension_data_callback;
    return &MLv2UiDescriptor;
  }

  //----------

  void export_ttl(KODE_Descriptor* ADescriptor) {
    KODE_PRINT;
    char TXT[512];
    char plugin_uri[256];
    MManifestTtlBuffer[0] = 0;
    MPluginTtlBuffer[0]   = 0;
    const char* plugin_name   = ADescriptor->name;                // "plugin";
    const char* plugin_author = ADescriptor->author;              // "author";
    sprintf(plugin_uri,"<urn:%s/%s>",plugin_author,plugin_name);  // "<urn:author/plugin>"
    // manifest.ttl
    sprintf( TXT, "@prefix lv2:      %s          . \n",  "<http://lv2plug.in/ns/lv2core#>"           );   strcat( MManifestTtlBuffer, TXT );
    sprintf( TXT, "@prefix rdfs:     %s          . \n",  "<http://www.w3.org/2000/01/rdf-schema#>"   );   strcat( MManifestTtlBuffer, TXT );
    sprintf( TXT, "                                \n"                                               );   strcat( MManifestTtlBuffer, TXT );
    sprintf( TXT, "%s                              \n",  plugin_uri                                  );   strcat( MManifestTtlBuffer, TXT );
    sprintf( TXT, "  a               lv2:Plugin  ; \n"                                               );   strcat( MManifestTtlBuffer, TXT );
    sprintf( TXT, "  rdfs:seeAlso    <%s.ttl>    . \n",  plugin_name                                 );   strcat( MManifestTtlBuffer, TXT );
    // plugin.ttl
    sprintf( TXT, "@prefix lv2:      %s          . \n",  "<http://lv2plug.in/ns/lv2core#>"           );   strcat( MPluginTtlBuffer, TXT );
    sprintf( TXT, "@prefix doap:     %s          . \n",  "<http://usefulinc.com/ns/doap#>"           );   strcat( MPluginTtlBuffer, TXT );
    sprintf( TXT, "                                \n"                                               );   strcat( MPluginTtlBuffer, TXT );
    sprintf( TXT, "%s                              \n",  plugin_uri                                  );   strcat( MPluginTtlBuffer, TXT );
    sprintf( TXT, "  a lv2:Plugin                ; \n"                                               );   strcat( MPluginTtlBuffer, TXT );
    sprintf( TXT, "  lv2:binary      %s.so       ; \n",  plugin_name                                 );   strcat( MPluginTtlBuffer, TXT );
    sprintf( TXT, "  doap:name       %s          ; \n",  plugin_name                                 );   strcat( MPluginTtlBuffer, TXT );
    sprintf( TXT, "  doap:license    %s          ; \n",  "<http://usefulinc.com/doap/licenses/gpl>"  );   strcat( MPluginTtlBuffer, TXT );
    sprintf( TXT, "                                \n"                                               );   strcat( MPluginTtlBuffer, TXT );
    sprintf( TXT, "  lv2:port [                    \n"                                               );   strcat( MPluginTtlBuffer, TXT );
    sprintf( TXT, "    a             %s          ; \n",  "lv2:ControlPort, lv2:InputPort"            );   strcat( MPluginTtlBuffer, TXT );
    sprintf( TXT, "    lv2:index     %i          ; \n",  0                                           );   strcat( MPluginTtlBuffer, TXT );
    sprintf( TXT, "    lv2:symbol    \"%s\"      ; \n",  "width"                                     );   strcat( MPluginTtlBuffer, TXT );
    sprintf( TXT, "    lv2:name      \"%s\"      ; \n",  "Width parameter"                           );   strcat( MPluginTtlBuffer, TXT );
    sprintf( TXT, "  ]                           , \n"                                               );   strcat( MPluginTtlBuffer, TXT );
    sprintf( TXT, "  [                             \n"                                               );   strcat( MPluginTtlBuffer, TXT );
    sprintf( TXT, "    a             %s          ; \n",  "lv2:AudioPort, lv2:OutputPort"             );   strcat( MPluginTtlBuffer, TXT );
    sprintf( TXT, "    lv2:index     %i          ; \n",  1                                           );   strcat( MPluginTtlBuffer, TXT );
    sprintf( TXT, "    lv2:symbol    \"%s\"      ; \n",  "right_output"                              );   strcat( MPluginTtlBuffer, TXT );
    sprintf( TXT, "    lv2:name      \"%s\"      ; \n",  "Right output"                              );   strcat( MPluginTtlBuffer, TXT );
    sprintf( TXT, "  ]                           . \n"                                               );   strcat( MPluginTtlBuffer, TXT );
    //FILE* fp = fopen("manifest.ttl","wt");
    //fwrite(MManifestTtlBuffer,strlen(MManifestTtlBuffer),fp);
    //fclose(fp);
    //FILE* fp = fopen("plugin.ttl","wt");
    //fwrite(MPluginTtlBuffer,strlen(MPluginTtlBuffer),fp);
    //fclose(fp);
  }

//------------------------------
public: // lv2 callbacks
//------------------------------

  static
  LV2_Handle lv2_instantiate_callback(const struct LV2_Descriptor* descriptor, double sample_rate, const char* bundle_path, const LV2_Feature* const* features) {
    DESCRIPTOR* desc = new DESCRIPTOR(); // TODO: who deletes this? and where?
    INSTANCE* inst = new INSTANCE(desc); // TODO: who deletes this? and where?
    KODE_Lv2Instance* lv2_instance = new KODE_Lv2Instance(desc,inst);
    lv2_instance->lv2_instantiate(descriptor,sample_rate,bundle_path,features);
    return lv2_instance;
  }

  //----------

  static
  void lv2_connect_port_callback(LV2_Handle handle, uint32_t port, void* data_location) {
    KODE_Lv2Instance* lv2_instance = (KODE_Lv2Instance*)handle;
    if (lv2_instance) lv2_instance->lv2_connect_port(port,data_location);
  }

  //----------

  static
  void lv2_activate_callback(LV2_Handle handle) {
    KODE_Lv2Instance* inst = (KODE_Lv2Instance*)handle;
    if (inst) inst->lv2_activate();
  }

  //----------

  static
  void lv2_run_callback(LV2_Handle handle, uint32_t sample_count) {
    KODE_Lv2Instance* inst = (KODE_Lv2Instance*)handle;
    if (inst) inst->lv2_run(sample_count);
  }

  //----------

  static
  void lv2_deactivate_callback(LV2_Handle handle) {
    KODE_Lv2Instance* inst = (KODE_Lv2Instance*)handle;
    if (inst) inst->lv2_deactivate();
  }

  //----------

  static
  void lv2_cleanup_callback(LV2_Handle handle) {
    KODE_Lv2Instance* inst = (KODE_Lv2Instance*)handle;
    if (inst) inst->lv2_cleanup();
  }

  //----------

  /*
    Return additional plugin data defined by some extension.
    A typical use of this facility is to return a struct containing function
    pointers to extend the LV2_Descriptor API.
    The actual type and meaning of the returned object MUST be specified
    precisely by the extension. This function MUST return NULL for any
    unsupported URI. If a plugin does not support any extension data, this
    field may be NULL.
    The host is never responsible for freeing the returned value.
  */

  static
  const void* lv2_extension_data_callback(const char* uri) {
    return nullptr;
  }

//------------------------------
public: // lv2ui callbacks
//------------------------------

  static
  LV2UI_Handle lv2ui_instantiate_callback(const struct LV2UI_Descriptor* descriptor, const char* plugin_uri, const char* bundle_path, LV2UI_Write_Function write_function, LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features) {
    KODE_Lv2Editor* lv2_editor = new KODE_Lv2Editor();
    lv2_editor->lv2ui_instantiate(descriptor,plugin_uri,bundle_path,write_function,controller,widget,features);
    return lv2_editor;
  }

  //----------

  static
  void lv2ui_cleanup_callback(LV2UI_Handle handle) {
    KODE_Lv2Editor* lv2_editor = (KODE_Lv2Editor*)handle;
    if (lv2_editor) lv2_editor->lv2ui_cleanup();
  }

  //----------

  static
  void lv2ui_port_event_callback(LV2UI_Handle handle, uint32_t port_index, uint32_t buffer_size, uint32_t format, const void* buffer) {
    KODE_Lv2Editor* lv2_editor = (KODE_Lv2Editor*)handle;
    if (lv2_editor) lv2_editor->lv2ui_port_event(port_index,buffer_size,format,buffer);
  }

  //----------

  /*
    Return a data structure associated with an extension URI, typically an
    interface struct with additional function pointers.
    This member may be set to NULL if the UI is not interested in supporting
    any extensions. This is similar to LV2_Descriptor::extension_data().
  */

  static
  const void* lv2ui_extension_data_callback(const char* uri) {
    return nullptr;
  }

};

//----------------------------------------------------------------------
//
// entrypoint
//
//----------------------------------------------------------------------

/*
  Prototype for plugin accessor function.
  Plugins are discovered by hosts using RDF data (not by loading libraries).
  See http://lv2plug.in for details on the discovery process, though most
  hosts should use an existing library to implement this functionality.
  This is the simple plugin discovery API, suitable for most statically
  defined plugins.  Advanced plugins that need access to their bundle during
  discovery can use lv2_lib_descriptor() instead.  Plugin libraries MUST
  include a function called "lv2_descriptor" or "lv2_lib_descriptor" with
  C-style linkage, but SHOULD provide "lv2_descriptor" wherever possible.
  When it is time to load a plugin (designated by its URI), the host loads the
  plugin's library, gets the lv2_descriptor() function from it, and uses this
  function to find the LV2_Descriptor for the desired plugin.  Plugins are
  accessed by index using values from 0 upwards.  This function MUST return
  NULL for out of range indices, so the host can enumerate plugins by
  increasing `index` until NULL is returned.
  Note that `index` has no meaning, hosts MUST NOT depend on it remaining
  consistent between loads of the plugin library.
*/

//----------

//#ifdef __cplusplus
//extern "C" {
//#endif

//----------

const LV2_Descriptor*   kode_lv2_descriptor(uint32_t index)   asm("lv2_descriptor");
const LV2UI_Descriptor* kode_lv2ui_descriptor(uint32_t index) asm("lv2ui_descriptor");
void                    kode_export_ttl(void)                 asm("export_ttl");

//----------

#define KODE_LV2_PLUGIN_ENTRYPOINT(DESCRIPTOR,INSTANCE)           \
                                                                  \
  /*static*/                                                      \
  KODE_Lv2Plugin<DESCRIPTOR,INSTANCE> LV2_PLUGIN;                 \
                                                                  \
  __attribute__ ((visibility ("default")))                        \
  const LV2_Descriptor* kode_lv2_descriptor(uint32_t index) {     \
    KODE_Print("index %i\n",index);                               \
    return LV2_PLUGIN.get_lv2_descriptor(index);                  \
  }                                                               \
                                                                  \
  __attribute__ ((visibility ("default")))                        \
  const LV2UI_Descriptor* kode_lv2ui_descriptor(uint32_t index) { \
    KODE_Print("index %i\n",index);                               \
    return LV2_PLUGIN.get_lv2ui_descriptor(index);                \
  }                                                               \
                                                                  \
  __attribute__ ((visibility ("default")))                        \
  void kode_export_ttl(void) {                                    \
    KODE_PRINT;                                                   \
    KODE_Descriptor* descriptor = new DESCRIPTOR();               \
    LV2_PLUGIN.export_ttl(descriptor);                            \
    delete descriptor;                                            \
  }                                                               \

//----------

//#ifdef __cplusplus
//} // extern "C"
//#endif

//----------------------------------------------------------------------
#endif

