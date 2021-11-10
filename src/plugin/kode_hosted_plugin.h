#ifndef kode_hosted_plugin_included
#define kode_hosted_plugin_included
//----------------------------------------------------------------------

#include <dlfcn.h>

#include "kode.h"
#include "plugin/kode_instance.h"

//----------------------------------------------------------------------

class KODE_HostedPlugin {

//------------------------------
private:
//------------------------------

  void* MLibHandle = nullptr;

//------------------------------
protected:
//------------------------------

  void* loadLib(const char* AFilename) {
    MLibHandle = dlopen(AFilename,RTLD_LAZY | RTLD_LOCAL ); // RTLD_NOW, RTLD_LAZY
    return MLibHandle;
  }

  void* getSymbol(const char* ASymbol) {
    if (MLibHandle) {
      return dlsym(MLibHandle,ASymbol);
    }
    return nullptr;
  }

  void unloadLib() {
    if (MLibHandle) {
      dlclose(MLibHandle);
      MLibHandle = nullptr;
    }
  }

  virtual KODE_HostedInstance* createInstance() {
    return nullptr;
  }

//------------------------------
public:
//------------------------------

  virtual bool      on_plugin_init() { return false; }
  virtual void      on_plugin_destroy() {}
  virtual bool      on_plugin_activate() { return false; }
  virtual void      on_plugin_deactivate() {}
  virtual bool      on_plugin_start_processing() { return false; }
  virtual void      on_plugin_stop_processing() {}
  virtual uint32_t  on_plugin_process(KODE_ProcessContext* AContext) { return 0; }
  virtual void      on_plugin_parameter(uint32_t AIndex, float AValue) {}
  virtual void      on_plugin_midi(uint32_t AOffset, uint8_t AMsg1, uint8_t AMsg2, uint8_t AMsg3) {}
  virtual uint32_t  on_plugin_save_state(void** ABuffer, uint32_t AMode) { *ABuffer = nullptr; return 0; }
  virtual uint32_t  on_plugin_load_state(uint32_t ASize, void* ABuffer, uint32_t AMode) { return 0; }
  virtual void*     on_plugin_create_editor(void* AParent) { return nullptr; }
  virtual bool      on_plugin_open_editor() { return false; }
  virtual void      on_plugin_close_editor() {}
  virtual uint32_t  on_plugin_update_editor() { return 0; }

};

//----------------------------------------------------------------------
#endif
