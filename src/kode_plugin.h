#ifndef kode_plugin_included
#define kode_plugin_included
//----------------------------------------------------------------------

#include "kode.h"
#include "kode_descriptor.h"
#include "kode_instance.h"
#include "kode_editor.h"

KODE_Descriptor*  _kode_create_descriptor();
KODE_Instance*    _kode_create_instance(KODE_Descriptor* ADescriptor);
KODE_Editor*      _kode_create_editor(KODE_Instance* AInstance);

#include "kode_clap_plugin.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#define KODE_MAIN(D,I,E)                                                                    \
                                                                                            \
  KODE_Descriptor*  _kode_create_descriptor()                     { return new D();      }  \
  KODE_Instance*    _kode_create_instance(KODE_Descriptor* ADesc) { return new I(ADesc); }  \
  KODE_Editor*      _kode_create_editor(KODE_Instance* AInst)     { return new E(AInst); }  \
                                                                                            \
  KODE_CLAP_MAIN(D,I,E);                                                                    \




//----------------------------------------------------------------------
#endif
