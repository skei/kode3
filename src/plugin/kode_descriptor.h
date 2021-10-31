#ifndef kode_descriptor_included
#define kode_descriptor_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/kode_parameter.h"
#include "plugin/kode_preset.h"

//----------------------------------------------------------------------

#define KODE_MAGIC 0xffff0000

//----------

enum KODE_PluginFlags {
  NONE              = 0,
  CAN_RECEIVE_MIDI  = 1,
  CAN_SEND_MIDI     = 2,
  IS_SYNTH          = 4,// + CAN_RECEIVE_MIDI,
  HAS_EDITOR        = 8
};

//----------

struct KODE_PluginPort {
  const char* name      = "port";
  uint32_t    type      = 0; // audio, midi, ..
  uint32_t    channels  = 2;  // mono, stereo, (num midi channels?)
  uint32_t    direction = 0; // 0=input, 1=output
};

//----------

typedef KODE_Array<KODE_PluginPort*> KODE_PluginPortArray;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class KODE_Descriptor {
public:
  KODE_Descriptor()           { KODE_PRINT; }
  virtual ~KODE_Descriptor()  { KODE_PRINT; }
public:
  const char*           name            = "plugin";
  const char*           author          = "author";
  const char*           description     = "my plugin..";
  const char*           url             = "http://website.com";
  const char*           email           = "support@mail.com";
  uint32_t              version         = 0;
  KODE_PluginFlags      flags           = KODE_PluginFlags::NONE;
  uint32_t              short_id        = KODE_MAGIC;
  uint32_t              editor_width    = 640;
  uint32_t              editor_height   = 480;
  KODE_PluginPortArray  input_ports     = {};
  KODE_PluginPortArray  output_ports    = {};
  KODE_ParameterArray   parameters      = {};
  KODE_PresetArray      presets         = {};
};

//----------------------------------------------------------------------
#endif
