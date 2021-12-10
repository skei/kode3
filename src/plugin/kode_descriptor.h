#ifndef kode_descriptor_included
#define kode_descriptor_included
//----------------------------------------------------------------------

#include "kode.h"
#include "base/types/kode_array.h"
#include "base/utils/kode_utils.h"
#include "plugin/kode_parameter.h"
#include "plugin/kode_preset.h"

//----------------------------------------------------------------------

//enum KODE_EPortType {
//  KODE_PORT_AUDIO = 0,
//  KODE_PORT_MIDI  = 1,
//};
//
//enum KODE_EPortDirection {
//  KODE_PORT_INPUT   = 0,
//  KODE_PORT_OUTPUT  = 1,
//};

struct KODE_PluginPort {
  const char* name      = "";
  uint32_t    type      = KODE_PLUGIN_PORT_AUDIO;
  uint32_t    channels  = 2;
  uint32_t    direction = KODE_PLUGIN_PORT_OUTPUT;
  KODE_PluginPort(const char* AName="", uint32_t AType=KODE_PLUGIN_PORT_AUDIO, uint32_t AChannels=2, uint32_t ADirection=KODE_PLUGIN_PORT_OUTPUT) {
    name      = AName;
    type      = AType;
    channels  = AChannels;
    direction = ADirection;
  }
};

typedef KODE_Array<KODE_PluginPort*>  KODE_PluginPortArray;

//----------

struct KODE_PluginOptions {
  bool has_editor         = false;
  bool can_resize_editor  = false;
  bool is_synth           = false;
  bool can_send_midi      = false;
  bool can_receive_midi   = false;
};

//----------------------------------------------------------------------


//----------------------------------------------------------------------


class KODE_Descriptor {

//------------------------------
private:
//------------------------------

  uint8_t   MLongId[16]         = {0};
  uint8_t   MLongEditorId[16]   = {0};
  char      MVersionString[32]  = {0};
  char      MIdString[256]      = {0};


//------------------------------
//public:
protected:
//------------------------------

  const char*           MName          = "name";
  const char*           MAuthor        = "author";
  uint32_t              MVersion       = 0;
  uint32_t              MShortId      = 0;
  const char*           MEmail         = "email";
  const char*           MUrl           = "url";
  const char*           MDescription   = "description";
  const char*           MKeywords      = "keywords";
  const char*           MLicenseText  = "";

  uint32_t              MEditorWidth   = 640;  // default width
  uint32_t              MEditorHeight  = 480;  // default height

//int32_t             plugin_type = 0;
//const char*         id          = "skei.audio/kode_debug/0.0.0";
//const char*         version     = "0.0.0";

  KODE_PluginOptions    MOptions     = {};
  KODE_PluginPortArray  MInputs      = {};
  KODE_PluginPortArray  MOutputs     = {};
  KODE_ParameterArray   MParameters  = {};
  KODE_PresetArray      MPresets     = {};

//------------------------------
public:
//------------------------------

  const char*           getName()         { return MName; }
  const char*           getAuthor()       { return MAuthor; }
  uint32_t              getVersion()      { return MVersion; }
  uint32_t              getShortId()      { return MShortId; }
  const char*           getEmail()        { return MEmail; }
  const char*           getUrl()          { return MUrl; }
  const char*           getDescription()  { return MDescription; }
  const char*           getKeywords()     { return MKeywords; }
  const char*           getLicenseText()  { return MLicenseText; }
  uint32_t              getEditorWidth()  { return MEditorWidth; }
  uint32_t              getEditorHeight() { return MEditorHeight; }

  //KODE_PluginOptions    options     = {};
  //KODE_PluginPortArray  inputs      = {};
  //KODE_PluginPortArray  outputs     = {};
  //KODE_ParameterArray   parameters  = {};
  //KODE_PresetArray      presets     = {};

  bool hasEditor()        { return MOptions.has_editor; }
  bool canResizeEditor()  { return MOptions.can_resize_editor; }
  bool isSynth()          { return MOptions.is_synth; }
  bool canSendMidi()      { return MOptions.can_send_midi; }
  bool canReceiveMidi()   { return MOptions.can_receive_midi; }

  KODE_PluginPortArray*  getInputs()     { return &MInputs; }
  KODE_PluginPortArray*  getOutputs()    { return &MOutputs; }
  KODE_ParameterArray*   getParameters() { return &MParameters; }
  KODE_PresetArray*      getPresets()    { return &MPresets; }

  uint32_t          getNumInputs()                { return MInputs.size(); }
  uint32_t          getNumOutputs()               { return MOutputs.size(); }
  uint32_t          getNumParameters()            { return MParameters.size(); }
  uint32_t          getNumPresets()               { return MPresets.size(); }

  KODE_PluginPort*  getInput(uint32_t AIndex)     { return MInputs[AIndex]; }
  KODE_PluginPort*  getOutput(uint32_t AIndex)    { return MOutputs[AIndex]; }
  KODE_Parameter*   getParameter(uint32_t AIndex) { return MParameters[AIndex]; }
  KODE_Preset*      getPreset(uint32_t AIndex)    { return MPresets[AIndex]; }

  void setName(const char* txt)               { MName = txt; }
  void setAuthor(const char* txt)             { MAuthor = txt; }
  void setVersion(uint32_t value)             { MVersion = value; }
  void setShortId(uint32_t value)             { MShortId = value; }
  void setEmail(const char* txt)              { MEmail = txt; }
  void setUrl(const char* txt)                { MUrl = txt; }
  void setDescription(const char* txt)        { MDescription = txt; }
  void setKeywords(const char* txt)           { MKeywords = txt; }
  void setLicenseText(const char* txt)        { MLicenseText = txt; }
  void setEditorWidth(uint32_t value)         { MEditorWidth = value; }
  void setEditorHeight(uint32_t value)        { MEditorHeight = value; }
  void setEditorSize(uint32_t w, uint32_t h)  { MEditorWidth = w; MEditorHeight = h; }

  //KODE_PluginOptions    options     = {};
  //KODE_PluginPortArray  inputs      = {};
  //KODE_PluginPortArray  outputs     = {};
  //KODE_ParameterArray   parameters  = {};
  //KODE_PresetArray      presets     = {};

  void setHasEditor(bool AState=true)        { MOptions.has_editor = AState; }
  void setCanResizeEditor(bool AState=true)  { MOptions.can_resize_editor = AState; }
  void setIsSynth(bool AState=true)          { MOptions.is_synth = AState; }
  void setCanSendMidi(bool AState=true)      { MOptions.can_send_midi = AState; }
  void setCanReceiveMidi(bool AState=true)   { MOptions.can_receive_midi = AState; }


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
    KODE_DPrint("name          = %s\n",MName);
    KODE_DPrint("author        = %s\n",MAuthor);
    KODE_DPrint("version       = 0x%08x\n",MVersion);
    KODE_DPrint("short_id      = 0x%08x (%c%c%c%c)\n",MShortId,((MShortId & 0xff000000) >> 24),((MShortId & 0x00ff0000) >> 16),((MShortId & 0x0000ff00) >> 8),(MShortId & 0x000000ff));
    KODE_DPrint("email         = %s\n",MEmail);
    KODE_DPrint("url           = %s\n",MUrl);
    KODE_DPrint("description   = %s\n",MDescription);
    KODE_DPrint("keywords      = %s\n",MKeywords);
    KODE_DPrint("license_text  = %s\n",MLicenseText);

    KODE_DPrint("editorWidth   = %i\n",MEditorWidth);  // default width
    KODE_DPrint("editorHeight  = %i\n",MEditorHeight);  // default height

    KODE_DPrint("num inputs    = %i\n",MInputs.size());
    KODE_DPrint("num outputs   = %i\n",MOutputs.size());
    KODE_DPrint("num params    = %i\n",MParameters.size());

  }

//------------------------------
public:
//------------------------------

  uint8_t* getLongId() {
    uint32_t* ptr = (uint32_t*)MLongId;
    ptr[0] = KODE_MAGIC_K_PL;
    ptr[1] = KODE_HashString(MName);
    ptr[2] = KODE_HashString(MAuthor);
    ptr[3] = MVersion;
    return MLongId;
  }

  //----------

  uint8_t* getLongEditorId() {
    uint32_t* ptr = (uint32_t*)MLongEditorId;
    ptr[0] = KODE_MAGIC_K_ED;
    ptr[1] = KODE_HashString(MName);
    ptr[2] = KODE_HashString(MAuthor);
    ptr[3] = MVersion;
    return MLongEditorId;
  }

  //----------

  // 0x03030001 -> "3.3.1"
  // buffer = 32 bytes, maxlen = 31
  // '255.255.65535' + 0 = 14 chars..

  //char* getVersionString(char* buffer) {
  char* getVersionString() {
    char* buffer = MVersionString;
    snprintf( buffer,
              31, // safety...
              "%i.%i.%i",
              ((MVersion & 0xff000000) >> 24),
              ((MVersion & 0x00ff0000) >> 16),
               (MVersion & 0x0000ffff)
    );
    return buffer;
  }

  //----------

  /*
    warning: ‘char* __builtin___strcat_chk(char*, const char*, long unsigned int)’
    accessing 33 or more bytes at offsets 72 and 40 may overlap 1 byte at offset 72
    [-Wrestrict]|
  */

  //char* getIdString(char* buffer) {
  char* getIdString() {
    char* buffer = MIdString;
    char* ver    = getVersionString();
    //strcpy(buffer,name);
    //strcat(buffer,"/");
    //strcat(buffer,author);
    //strcat(buffer,"/");
    //strcat(buffer,ver);
    snprintf( buffer,
              255, // safety...
              "%s/%s/%s",MName,MAuthor,ver
    );
    return buffer;
  }

//------------------------------
public:
//------------------------------

  void appendInput(KODE_PluginPort* APort) {
    MInputs.append(APort);
  }

  void appendInput(const char* AName) {
    KODE_PluginPort* port = new KODE_PluginPort(AName,KODE_PLUGIN_PORT_AUDIO,1,KODE_PLUGIN_PORT_INPUT);
    MInputs.append(port);
  }

  void deleteInputs() {
    for (uint32_t i=0; i<MInputs.size(); i++) {
      delete MInputs[i];
      MInputs[i] = nullptr;
    }
  }

  void appendOutput(KODE_PluginPort* APort) {
    MOutputs.append(APort);
  }

  void appendOutput(const char* AName) {
    KODE_PluginPort* port = new KODE_PluginPort(AName,KODE_PLUGIN_PORT_AUDIO,1,KODE_PLUGIN_PORT_OUTPUT);
    MOutputs.append(port);
  }

  void deleteOutputs() {
    for (uint32_t i=0; i<MOutputs.size(); i++) {
      delete MOutputs[i];
      MOutputs[i] = nullptr;
    }
  }

  void appendParameter(KODE_Parameter* AParameter) {
    int32_t index = MParameters.size();
    AParameter->MIndex = index;
    MParameters.append(AParameter);
  }

  void deleteParameters() {
    for (uint32_t i=0; i<MParameters.size(); i++) {
      delete MParameters[i];
      MParameters[i] = nullptr;
    }
  }

  void appendPreset(KODE_Preset* APreset) {
    MPresets.append(APreset);
  }

  void deletePresets() {
    for (uint32_t i=0; i<MPresets.size(); i++) {
      delete MPresets[i];
      MPresets[i] = nullptr;
    }
  }

};

//----------------------------------------------------------------------
#endif
