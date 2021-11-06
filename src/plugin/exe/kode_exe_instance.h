#ifndef kode_exe_instance_included
#define kode_exe_instance_included
//----------------------------------------------------------------------

class KODE_ExeInstance {

//------------------------------
private:
//------------------------------

  KODE_Instance*    MInstance       = nullptr;
  KODE_Descriptor*  MDescriptor     = nullptr;

//------------------------------
public:
//------------------------------

  KODE_ExeInstance(KODE_Instance* AInstance) {
    MInstance       = AInstance;
    MDescriptor     = AInstance->getDescriptor();
  }

  virtual ~KODE_ExeInstance() {
  }

};

//----------------------------------------------------------------------
#endif
