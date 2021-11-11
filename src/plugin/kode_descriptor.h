#ifndef kode_descriptor_included
#define kode_descriptor_included
//----------------------------------------------------------------------

#include "kode.h"
#include "base/types/kode_array.h"
#include "base/utils/kode_utils.h"
#include "plugin/kode_parameter.h"
#include "plugin/kode_preset.h"

//----------------------------------------------------------------------

enum KODE_EPortType {
  KODE_PORT_AUDIO = 0,
  KODE_PORT_MIDI  = 1,
};

enum KODE_EPortDirection {
  KODE_PORT_INPUT   = 0,
  KODE_PORT_OUTPUT  = 1,
};

struct KODE_PluginPort {
  const char* name;
  uint32_t    type;
  uint32_t    channels;
  uint32_t    direction;
  KODE_PluginPort(const char* AName, uint32_t AType, uint32_t AChannels, uint32_t ADirection) {
    name      = AName;
    type      = AType;
    channels  = AChannels;
    direction = ADirection;
  }
};

typedef KODE_Array<KODE_PluginPort*>  KODE_PluginPortArray;

//----------

struct KODE_PluginOptions {
  bool has_editor       = false;
  bool can_send_midi    = false;
  bool can_receive_midi = false;
  bool is_synth         = false;
};

//----------------------------------------------------------------------


//----------------------------------------------------------------------


class KODE_Descriptor {

//------------------------------
private:
//------------------------------

  uint8_t   MLongId[16] = {0};
  uint8_t   MLongEditorId[16] = {0};
  char      MVersionString[32] = {0};
  char      MIdString[256] = {0};


//------------------------------
public:
//------------------------------

  const char*           name          = "name";
  const char*           author        = "author";
  uint32_t              version       = 0;
  uint32_t              short_id      = 0;
  const char*           email         = "email";
  const char*           url           = "url";
  const char*           description   = "description";
  const char*           keywords      = "keywords";
  const char*           license_text  = "";

  uint32_t              editorWidth   = 640;  // default width
  uint32_t              editorHeight  = 480;  // default height

//int32_t             plugin_type = 0;
//const char*         id          = "skei.audio/kode_debug/0.0.0";
//const char*         version     = "0.0.0";

  KODE_PluginOptions    options     = {};
  KODE_PluginPortArray  inputs      = {};
  KODE_PluginPortArray  outputs     = {};
  KODE_ParameterArray   parameters  = {};
  KODE_PresetArray      presets     = {};

//------------------------------
public:
//------------------------------

  KODE_Descriptor() {
  }

  virtual ~KODE_Descriptor() {
    #ifndef KODE_NO_AUTODELETE
      deleteInputs();
      deleteOutputs();
      deleteParameters();
      deletePresets();
    #endif
  }

//------------------------------
public:
//------------------------------

//  void setName(const char* AName)               { name = AName; }
//  void setAuthor(const char* AAuthor)           { author = AAuthor; }
//  void setVersion(uint32_t AVersion)            { version = AVersion; }
//  void setUrl(const char* AUrl)                 { url = AUrl; }
//  void setEmail(const char* AEmail)             { email = AEmail; }
//  void setShortId(uint32_t AShortId)            { short_id = AShortId; }
//  void setDescription(const char* ADescription) { description = ADescription; }
//  void setKeyWords(const char* AKeyWords)       { keywords = AKeyWords; }

//------------------------------
public:
//------------------------------

  void print() {
    KODE_DPrint("name          = %s\n",name);
    KODE_DPrint("author        = %s\n",author);
    KODE_DPrint("version       = 0x%08x\n",version);
    KODE_DPrint("short_id      = 0x%08x (%c%c%c%c)\n",short_id,((short_id & 0xff000000) >> 24),((short_id & 0x00ff0000) >> 16),((short_id & 0x0000ff00) >> 8),(short_id & 0x000000ff));
    KODE_DPrint("email         = %s\n",email);
    KODE_DPrint("url           = %s\n",url);
    KODE_DPrint("description   = %s\n",description);
    KODE_DPrint("keywords      = %s\n",keywords);
    KODE_DPrint("license_text  = %s\n",license_text);

    KODE_DPrint("editorWidth   = %i\n",editorWidth);  // default width
    KODE_DPrint("editorHeight  = %i\n",editorHeight);  // default height

    KODE_DPrint("num inputs    = %i\n",inputs.size());
    KODE_DPrint("num outputs   = %i\n",outputs.size());
    KODE_DPrint("num params    = %i\n",parameters.size());

  }

//------------------------------
public:
//------------------------------

  uint8_t* getLongId() {
    uint32_t* ptr = (uint32_t*)MLongId;
    ptr[0] = KODE_MAGIC_K_PL;
    ptr[1] = KODE_HashString(name);
    ptr[2] = KODE_HashString(author);
    ptr[3] = version;
    return MLongId;
  }

  //----------

  uint8_t* getLongEditorId() {
    uint32_t* ptr = (uint32_t*)MLongEditorId;
    ptr[0] = KODE_MAGIC_K_ED;
    ptr[1] = KODE_HashString(name);
    ptr[2] = KODE_HashString(author);
    ptr[3] = version;
    return MLongEditorId;
  }

  //----------

    // 0x03030001 -> "3.3.1"

  //char* getVersionString(char* buffer) {
  char* getVersionString() {
    char* buffer = MVersionString;
    sprintf(buffer,"%i.%i.%i",((version & 0xff000000) >> 24),((version & 0x00ff0000) >> 16),(version & 0x0000ffff));
    return buffer;
  }

  //----------

  //char* getIdString(char* buffer) {
  char* getIdString() {
    char* buffer = MIdString;
    char * ver = getVersionString();
    buffer[0] = 0;
    strcat(buffer,name);
    strcat(buffer,"/");
    strcat(buffer,author);
    strcat(buffer,"/");
    strcat(buffer,ver);
    return buffer;
  }

//------------------------------
public:
//------------------------------

  void appendInput(KODE_PluginPort* APort) {
    inputs.append(APort);
  }

  void appendInput(const char* AName) {
    KODE_PluginPort* port = new KODE_PluginPort(AName,KODE_PORT_AUDIO,1,KODE_PORT_INPUT);
    inputs.append(port);
  }

  void deleteInputs() {
    for (uint32_t i=0; i<inputs.size(); i++) {
      delete inputs[i];
      inputs[i] = nullptr;
    }
  }

  void appendOutput(KODE_PluginPort* APort) {
    outputs.append(APort);
  }

  void appendOutput(const char* AName) {
    KODE_PluginPort* port = new KODE_PluginPort(AName,KODE_PORT_AUDIO,1,KODE_PORT_OUTPUT);
    outputs.append(port);
  }

  void deleteOutputs() {
    for (uint32_t i=0; i<outputs.size(); i++) {
      delete outputs[i];
      outputs[i] = nullptr;
    }
  }

  void appendParameter(KODE_Parameter* AParameter) {
    parameters.append(AParameter);
  }

  void deleteParameters() {
    for (uint32_t i=0; i<parameters.size(); i++) {
      delete parameters[i];
      parameters[i] = nullptr;
    }
  }

  void appendPreset(KODE_Preset* APreset) {
    presets.append(APreset);
  }

  void deletePresets() {
    for (uint32_t i=0; i<presets.size(); i++) {
      delete presets[i];
      presets[i] = nullptr;
    }
  }

};

//----------------------------------------------------------------------
#endif
