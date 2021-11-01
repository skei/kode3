#ifndef kode_vst3_base_included
#define kode_vst3_base_included
//----------------------------------------------------------------------
//
// based on (extracted from) steinberg vst3 sdk (gpl3)
// so this file also needs to be gpl3
//
//----------------------------------------------------------------------

#ifdef __gnu_linux__
  #define VST3_COM_COMPATIBLE 0
  #define VST3_PLUGIN_API
#endif

#ifdef _WIN32
  #define VST3_COM_COMPATIBLE 1
  #define VST3_PLUGIN_API __stdcall
#endif

//----------

#if VST3_COM_COMPATIBLE
  #define VST3_INLINE_UID(l1,l2,l3,l4) {                             \
    (int8_t)((l1 & 0x000000FF)      ), (int8_t)((l1 & 0x0000FF00) >>  8), \
    (int8_t)((l1 & 0x00FF0000) >> 16), (int8_t)((l1 & 0xFF000000) >> 24), \
    (int8_t)((l2 & 0x00FF0000) >> 16), (int8_t)((l2 & 0xFF000000) >> 24), \
    (int8_t)((l2 & 0x000000FF)      ), (int8_t)((l2 & 0x0000FF00) >>  8), \
    (int8_t)((l3 & 0xFF000000) >> 24), (int8_t)((l3 & 0x00FF0000) >> 16), \
    (int8_t)((l3 & 0x0000FF00) >>  8), (int8_t)((l3 & 0x000000FF)      ), \
    (int8_t)((l4 & 0xFF000000) >> 24), (int8_t)((l4 & 0x00FF0000) >> 16), \
    (int8_t)((l4 & 0x0000FF00) >>  8), (int8_t)((l4 & 0x000000FF)      )  \
  }
#else
  #define VST3_INLINE_UID(l1,l2,l3,l4) {                             \
    (int8_t)((l1 & 0xFF000000) >> 24), (int8_t)((l1 & 0x00FF0000) >> 16), \
    (int8_t)((l1 & 0x0000FF00) >>  8), (int8_t)((l1 & 0x000000FF)      ), \
    (int8_t)((l2 & 0xFF000000) >> 24), (int8_t)((l2 & 0x00FF0000) >> 16), \
    (int8_t)((l2 & 0x0000FF00) >>  8), (int8_t)((l2 & 0x000000FF)      ), \
    (int8_t)((l3 & 0xFF000000) >> 24), (int8_t)((l3 & 0x00FF0000) >> 16), \
    (int8_t)((l3 & 0x0000FF00) >>  8), (int8_t)((l3 & 0x000000FF)      ), \
    (int8_t)((l4 & 0xFF000000) >> 24), (int8_t)((l4 & 0x00FF0000) >> 16), \
    (int8_t)((l4 & 0x0000FF00) >>  8), (int8_t)((l4 & 0x000000FF)      )  \
  }
#endif

//#ifdef VST3_INIT_CLASS_IID
//  #define VST3_DECLARE_CLASS_IID(classname,l1,l2,l3,l4)
//	static const vst3_uuid classname##_iid = VST3_INLINE_UID(l1,l2,l3,l4);
//  const vst3_uuid classname::iid(classname##_iid);
//#else

#define VST3_DECLARE_CLASS_IID(classname,l1,l2,l3,l4) \
  static const VST3_Id classname##_iid = VST3_INLINE_UID(l1,l2,l3,l4);

//----------

// todo: implement newer vst3 version..

#define vst3_VstVersionString     "VST 3.6.10"          // SDK version for PClassInfo2
#define vst3_VstAudioEffectClass  "Audio Module Class"

//----------------------------------------------------------------------
//
// typedefs
//
//----------------------------------------------------------------------

typedef char      VST3_Id[16];      // was TUID
typedef char16_t  VST3_String[128]; // was String128

//----------------------------------------------------------------------
//
// enums
//
//----------------------------------------------------------------------

#if VST3_COM_COMPATIBLE

  #ifdef _WIN32
  enum {
    vst3_NoInterface     = 0x80004002;         // static_cast<int32_t>(0x80004002L), // E_NOINTERFACE
    vst3_ResultOk        = 0x00000000;         // static_cast<int32_t>(0x00000000L), // S_OK
    vst3_ResultTrue      = vst3_ResultOk,
    vst3_ResultFalse     = 0x00000001;         // static_cast<int32_t>(0x00000001L), // S_FALSE
    vst3_InvalidArgument = 0x80070057;         // static_cast<int32_t>(0x80070057L), // E_INVALIDARG
    vst3_NotImplemented  = 0x80004001;         // static_cast<int32_t>(0x80004001L), // E_NOTIMPL
    vst3_InternalError   = 0x80004005;         // static_cast<int32_t>(0x80004005L), // E_FAIL
    vst3_NotInitialized  = 0x8000FFFF;         // static_cast<int32_t>(0x8000FFFFL), // E_UNEXPECTED
    vst3_OutOfMemory     = 0x8007000E;         // static_cast<int32_t>(0x8007000EL)  // E_OUTOFMEMORY
  };
  #else // __gnu_linux__
  enum {
    vst3_NoInterface     = 0x80000004;         // static_cast<int32_t>(0x80000004L), // E_NOINTERFACE
    vst3_ResultOk        = 0x00000000;         // static_cast<int32_t>(0x00000000L), // S_OK
    vst3_ResultTrue      = vst3_ResultOk,
    vst3_ResultFalse     = 0x00000001;         // static_cast<int32_t>(0x00000001L), // S_FALSE
    vst3_InvalidArgument = 0x80000003;         // static_cast<int32_t>(0x80000003L), // E_INVALIDARG
    vst3_NotImplemented  = 0x80000001;         // static_cast<int32_t>(0x80000001L), // E_NOTIMPL
    vst3_InternalError   = 0x80000008;         // static_cast<int32_t>(0x80000008L), // E_FAIL
    vst3_NotInitialized  = 0x8000FFFF;         // static_cast<int32_t>(0x8000FFFFL), // E_UNEXPECTED
    vst3_OutOfMemory     = 0x80000002;         // static_cast<int32_t>(0x80000002L)  // E_OUTOFMEMORY
  };
  #endif

#else // VST3_COM_COMPATIBLE

  enum {
    vst3_NoInterface = -1,
    vst3_ResultOk,
    vst3_ResultTrue = vst3_ResultOk,
    vst3_ResultFalse,
    vst3_InvalidArgument,
    vst3_NotImplemented,
    vst3_InternalError,
    vst3_NotInitialized,
    vst3_OutOfMemory
  };

#endif // VST3_COM_COMPATIBLE

//----------

/*
enum NoteExpressionTypeIDs {
  vst3_VolumeTypeID = 0,
  vst3_PanTypeID,
  vst3_TuningTypeID,
  vst3_VibratoTypeID,
  vst3_ExpressionTypeID,
  vst3_BrightnessTypeID,
  vst3_TextTypeID,
  vst3_PhonemeTypeID,
  vst3_CustomStart = 100000
};
*/

enum VST3_BusDirections {
  vst3_Input = 0,
  vst3_Output
};

enum VST3_BusTypes {
  vst3_Main = 0,
  vst3_Aux
};

enum VST3_ControllerNumbers {
  vst3_CtrlBankSelectMSB      = 0,
  vst3_CtrlModWheel           = 1,
  vst3_CtrlBreath             = 2,
  vst3_CtrlFoot               = 4,
  vst3_CtrlPortaTime          = 5,
  vst3_CtrlDataEntryMSB       = 6,
  vst3_CtrlVolume             = 7,
  vst3_CtrlBalance            = 8,
  vst3_CtrlPan                = 10,
  vst3_CtrlExpression         = 11,
  vst3_CtrlEffect1            = 12,
  vst3_CtrlEffect2            = 13,
  vst3_CtrlGPC1               = 16,
  vst3_CtrlGPC2               = 17,
  vst3_CtrlGPC3               = 18,
  vst3_CtrlGPC4               = 19,
  vst3_CtrlBankSelectLSB      = 32,
  vst3_CtrlDataEntryLSB       = 38,
  vst3_CtrlSustainOnOff       = 64,
  vst3_CtrlPortaOnOff         = 65,
  vst3_CtrlSustenutoOnOff     = 66,
  vst3_CtrlSoftPedalOnOff     = 67,
  vst3_CtrlLegatoFootSwOnOff  = 68,
  vst3_CtrlHold2OnOff         = 69,
  vst3_CtrlSoundVariation     = 70,
  vst3_CtrlFilterCutoff       = 71,
  vst3_CtrlReleaseTime        = 72,
  vst3_CtrlAttackTime         = 73,
  vst3_CtrlFilterResonance    = 74,
  vst3_CtrlDecayTime          = 75,
  vst3_CtrlVibratoRate        = 76,
  vst3_CtrlVibratoDepth       = 77,
  vst3_CtrlVibratoDelay       = 78,
  vst3_CtrlSoundCtrler10      = 79,
  vst3_CtrlGPC5               = 80,
  vst3_CtrlGPC6               = 81,
  vst3_CtrlGPC7               = 82,
  vst3_CtrlGPC8               = 83,
  vst3_CtrlPortaControl       = 84,
  vst3_CtrlEff1Depth          = 91,
  vst3_CtrlEff2Depth          = 92,
  vst3_CtrlEff3Depth          = 93,
  vst3_CtrlEff4Depth          = 94,
  vst3_CtrlEff5Depth          = 95,
  vst3_CtrlDataIncrement      = 96,
  vst3_CtrlDataDecrement      = 97,
  vst3_CtrlNRPNSelectLSB      = 98,
  vst3_CtrlNRPNSelectMSB      = 99,
  vst3_CtrlRPNSelectLSB       = 100,
  vst3_CtrlRPNSelectMSB       = 101,
  vst3_CtrlAllSoundsOff       = 120,
  vst3_CtrlResetAllCtrlers    = 121,
  vst3_CtrlLocalCtrlOnOff     = 122,
  vst3_CtrlAllNotesOff        = 123,
  vst3_CtrlOmniModeOff        = 124,
  vst3_CtrlOmniModeOn         = 125,
  vst3_CtrlPolyModeOnOff      = 126,
  vst3_CtrlPolyModeOn         = 127,
  vst3_AfterTouch             = 128,
  vst3_PitchBend,           //= 129,
  vst3_CountCtrlNumber
};

enum VST3_MediaTypes {
  vst3_Audio = 0,
  vst3_Event,
  vst3_NumMediaTypes
};

enum VST3_SymbolicSampleSizes {
  vst3_Sample32,
  vst3_Sample64
};

enum VST3_IoModes {
  vst3_Simple = 0,
  vst3_Advanced,
  vst3_OfflineProcessing
};

//----------------------------------------------------------------------
//
// const
//
//----------------------------------------------------------------------

const char*     vst3_Editor                        = "editor"; // not capitalized?
const char*     vst3_Fx                            = "Fx";
const char*     vst3_Instrument                    = "Instrument";

const char*     vst3_PlatformTypeHWND              = "HWND";
const char*     vst3_PlatformTypeHIView            = "HIView";
const char*     vst3_PlatformTypeNSView            = "NSView";
const char*     vst3_PlatformTypeUIView            = "UIView";
const char*     vst3_PlatformTypeX11EmbedWindowID  = "X11EmbedWindowID";

const uint64_t  vst3_Empty                         = 0;
const uint64_t  vst3_SpeakerL                      = 1 << 0;
const uint64_t  vst3_SpeakerR                      = 1 << 1;
const uint64_t  vst3_SpeakerM                      = 1 << 19;


const uint64_t  vst3_Mono                          = vst3_SpeakerM;
const uint64_t  vst3_Stereo                        = (vst3_SpeakerL | vst3_SpeakerR);


/*static*/
const int32_t   vst3_NoParentUnitId                = -1;
const int32_t   vst3_NoProgramListId               = -1;
const uint32_t  vst3_NoTail                        = 0;
const int32_t   vst3_RootUnitId                    = 0;

/*
namespace VST3_PlugType {
  const CString vst3_FxAnalyzer              = "Fx|Analyzer";
  const CString vst3_FxDelay                 = "Fx|Delay";
  const CString vst3_FxDistortion            = "Fx|Distortion";
  const CString vst3_FxDynamics              = "Fx|Dynamics";
  const CString vst3_FxEQ                    = "Fx|EQ";
  const CString vst3_FxFilter                = "Fx|Filter";
  const CString vst3_Fx                      = "Fx";
  const CString vst3_FxInstrument            = "Fx|Instrument";
  const CString vst3_FxInstrumentExternal    = "Fx|Instrument|External";
  const CString vst3_FxSpatial               = "Fx|Spatial";
  const CString vst3_FxGenerator             = "Fx|Generator";
  const CString vst3_FxMastering             = "Fx|Mastering";
  const CString vst3_FxModulation            = "Fx|Modulation";
  const CString vst3_FxPitchShift            = "Fx|Pitch Shift";
  const CString vst3_FxRestoration           = "Fx|Restoration";
  const CString vst3_FxReverb                = "Fx|Reverb";
  const CString vst3_FxSurround              = "Fx|Surround";
  const CString vst3_FxTools                 = "Fx|Tools";
  const CString vst3_FxNetwork               = "Fx|Network";
  const CString vst3_Instrument              = "Instrument";
  const CString vst3_InstrumentDrum          = "Instrument|Drum";
  const CString vst3_InstrumentSampler       = "Instrument|Sampler";
  const CString vst3_InstrumentSynth         = "Instrument|Synth";
  const CString vst3_InstrumentSynthSampler  = "Instrument|Synth|Sampler";
  const CString vst3_InstrumentExternal      = "Instrument|External";
  const CString vst3_Spatial                 = "Spatial";
  const CString vst3_SpatialFx               = "Spatial|Fx";
  const CString vst3_OnlyRealTime            = "OnlyRT";
  const CString vst3_OnlyOfflineProcess      = "OnlyOfflineProcess";
  const CString vst3_NoOfflineProcess        = "NoOfflineProcess";
  const CString vst3_UpDownMix               = "Up-Downmix";
  const CString vst3_Analyzer                = "Analyzer";
  const CString vst3_Ambisonic               = "Ambisonic";
  const CString vst3_Mono                    = "Mono";
  const CString vst3_Stereo                  = "Stereo";
  const CString vst3_Surround                = "Surround";
};
*/

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

//#define strncpy8 strncpy

char* kode_strncpy8(char* destination, const char* source, size_t maxnum) {
  //memset(destination,0,maxnum);
  destination[maxnum-1] = 0;
  strncpy(destination,source,maxnum-1);
  return destination;
}


//----------------------------------------------------------------------
//
// structs
//
//----------------------------------------------------------------------

struct VST3_AudioBusBuffers {
  //VST3_AudioBusBuffers ()
  //  : numChannels(0)
  //  , silenceFlags(0)
  //  , channelBuffers64(0) {}
  int32_t   numChannels;
  uint64_t  silenceFlags;
  union {
    float**   channelBuffers32;
    double**  channelBuffers64;
  };
};

struct VST3_BusInfo {
  enum BusFlags {
    vst3_DefaultActive = 1 << 0
  };
  //
  int32_t         mediaType;
  int32_t         direction;
  int32_t         channelCount;
  VST3_String     name;
  int32_t         busType;
  uint32_t        flags;
};

struct VST3_Chord {
  enum Masks {
    vst3_ChordMask    = 0x0FFF,
    vst3_ReservedMask = 0xF000
  };
  //
  uint8_t keyNote;
  uint8_t rootNote;
  int16_t chordMask;
};

struct VST3_FrameRate {
  enum FrameRateFlags {
    vst3_PullDownRate = 1 << 0,
    vst3_DropRate     = 1 << 1
  };
  //
  uint32_t  framesPerSecond;
  uint32_t  flags;
};

struct VST3_KeyswitchInfo {
  uint32_t        typeId;
  VST3_String title;
  VST3_String shortTitle;
  int32_t         keyswitchMin;
  int32_t         keyswitchMax;
  int32_t         keyRemapped;
  int32_t         unitId;
  int32_t         flags;
};

struct VST3_ParameterInfo {
  enum ParameterFlags {
    vst3_CanAutomate      = 1 << 0,
    vst3_IsReadOnly       = 1 << 1,
    vst3_IsWrapAround     = 1 << 2,
    vst3_IsList           = 1 << 3,
    vst3_IsProgramChange  = 1 << 15,
    vst3_IsBypass         = 1 << 16
  };
  //
  uint32_t        id;
  VST3_String title;
  VST3_String shortTitle;
  VST3_String units;
  int32_t         stepCount;
  double          defaultNormalizedValue;
  int32_t         unitId;
  int32_t         flags;
};

struct VST3_PClassInfo {
  enum ClassCardinality {
    vst3_ManyInstances = 0x7FFFFFFF
  };
  enum {
    vst3_CategorySize  = 32,
    vst3_NameSize      = 64
  };
  //
  VST3_Id cid;
  int32_t     cardinality;
  char        category[vst3_CategorySize];
  char        name[vst3_NameSize];
//  VST3_PClassInfo(const VST3_Id _cid, int32_t _cardinality, const char* _category, const char* _name) {
//    memset(this,0,sizeof(VST3_PClassInfo));
//    memcpy(cid,_cid,sizeof(VST3_Id));
//    if (_category) kode_strncpy8(category,_category,vst3_CategorySize);
//    if (_name) kode_strncpy8(name,_name,vst3_NameSize);
//    cardinality = _cardinality;
//  }
//  //#if SMTG_CPP11
//  constexpr VST3_PClassInfo() : cid(), cardinality(), category(), name() {}
//  //#else
//  //PClassInfo () { memset (this, 0, sizeof (PClassInfo)); }
//  //#endif
};

struct VST3_PClassInfo2 {
	enum {
		vst3_VendorSize = 64,
		vst3_VersionSize = 64,
		vst3_SubCategoriesSize = 128
	};
	//
	VST3_Id cid;
	int32_t     cardinality;
	char        category[VST3_PClassInfo::vst3_CategorySize];
	char        name[VST3_PClassInfo::vst3_NameSize];
	uint32_t    classFlags;
	char        subCategories[vst3_SubCategoriesSize];
	char        vendor[vst3_VendorSize];
	char        version[vst3_VersionSize];
	char        sdkVersion[vst3_VersionSize];
//	VST3_PClassInfo2 (const VST3_Id _cid, int32_t _cardinality, const char* _category, const char* _name,
//		int32_t _classFlags, const char* _subCategories, const char* _vendor, const char* _version, const char* _sdkVersion) {
//      memset (this, 0, sizeof (VST3_PClassInfo2));
//      memcpy (cid, _cid, sizeof (VST3_Id));
//      cardinality = _cardinality;
//      if (_category) kode_strncpy8 (category, _category, VST3_PClassInfo::vst3_CategorySize);
//      if (_name) kode_strncpy8 (name, _name, VST3_PClassInfo::vst3_NameSize);
//      classFlags = static_cast<uint32_t> (_classFlags);
//      if (_subCategories) kode_strncpy8 (subCategories, _subCategories, vst3_SubCategoriesSize);
//      if (_vendor) kode_strncpy8 (vendor, _vendor, vst3_VendorSize);
//      if (_version) kode_strncpy8 (version, _version, vst3_VersionSize);
//      if (_sdkVersion) kode_strncpy8 (sdkVersion, _sdkVersion, vst3_VersionSize);
//    }
//  //#if SMTG_CPP11
//	constexpr VST3_PClassInfo2()
//    : cid(), cardinality(), category(), name(), classFlags(), subCategories(), vendor(), version(), sdkVersion() {}
//  //#else
//  //	VST3_PClassInfo2() { memset(this,0,sizeof(VST3_PClassInfo2)); }
//  //#endif
};

/*
struct VST3_PClassInfoW {
	VST3_Id cid;
	int32 cardinality;
	char8 category[PClassInfo::vst3_CategorySize];
	char16 name[PClassInfo::vst3_NameSize];
	enum { vst3_VendorSize = 64,
		vst3_VersionSize = 64,
		vst3_SubCategoriesSize = 128
	};
	uint32  classFlags;
	char8   subCategories[vst3_SubCategoriesSize];
	char16  vendor[vst3_VendorSize];
	char16  version[vst3_VersionSize];
	char16  sdkVersion[vst3_VersionSize];
	VST3_PClassInfoW(const VST3_Id _cid, int32 _cardinality, const char8* _category, const char16* _name, int32 _classFlags, const char8* _subCategories, const char16* _vendor, const char16* _version, const char16* _sdkVersion) {
    memset (this, 0, sizeof (PClassInfoW));
    memcpy (cid, _cid, sizeof (VST3_Id));
    cardinality = _cardinality;
    if (_category) kode_strncpy8 (category, _category, PClassInfo::vst3_CategorySize);
    if (_name) strncpy16 (name, _name, PClassInfo::vst3_NameSize);
    classFlags = static_cast<uint32> (_classFlags);
    if (_subCategories) kode_strncpy8 (subCategories, _subCategories, vst3_SubCategoriesSize);
    if (_vendor) strncpy16 (vendor, _vendor, vst3_VendorSize);
    if (_version) strncpy16 (version, _version, vst3_VersionSize);
    if (_sdkVersion) strncpy16 (sdkVersion, _sdkVersion, vst3_VersionSize);
	}
  //#if SMTG_CPP11
  constexpr VST3_PClassInfoW ()
    : cid ()
    , cardinality ()
    , category ()
    , name ()
    , classFlags ()
    , subCategories ()
    , vendor ()
    , version ()
    , sdkVersion ()
  {
  }
  //#else
  //	VST3_PClassInfoW () { memset (this, 0, sizeof (PClassInfoW)); }
  //#endif
  void fromAscii (const PClassInfo2& ci2) {
    //memcpy (cid, ci2.cid, sizeof (VST3_Id));
    //cardinality = ci2.cardinality;
    //kode_strncpy8 (category, ci2.category, PClassInfo::vst3_CategorySize);
    //str8ToStr16 (name, ci2.name, PClassInfo::vst3_NameSize);
    //classFlags = ci2.classFlags;
    //kode_strncpy8 (subCategories, ci2.subCategories, vst3_SubCategoriesSize);
    //str8ToStr16(vendor, ci2.vendor, vst3_VendorSize);
    //str8ToStr16(version, ci2.version, vst3_VersionSize);
    //str8ToStr16(sdkVersion, ci2.sdkVersion, vst3_VersionSize);
  }
};
*/

struct VST3_PClassInfoW {
};

struct VST3_PFactoryInfo {
  enum FactoryFlags {
    vst3_NoFlags					        = 0,
    vst3_ClassesDiscardable			= 1 << 0,
    vst3_LicenseCheck				    = 1 << 1,
    vst3_ComponentNonDiscardable = 1 << 3,
    vst3_Unicode                 = 1 << 4
  };
  enum {
    vst3_URLSize    = 256,
    vst3_EmailSize  = 128,
    vst3_NameSize   = 64
  };
  //
  char    vendor[vst3_NameSize];
  char    url[vst3_URLSize];
  char    email[vst3_EmailSize];
  int32_t flags;
//  VST3_PFactoryInfo(const char* _vendor, const char* _url, const char* _email, int32_t _flags) {
//    kode_strncpy8(vendor,_vendor,vst3_NameSize);
//    kode_strncpy8(url,_url,vst3_URLSize);
//    kode_strncpy8(email,_email,vst3_EmailSize);
//    flags = _flags;
//    //#ifdef UNICODE
//    //  flags |= vst3_Unicode;
//    //#endif
//  }
//  //#if SMTG_CPP11
//  constexpr VST3_PFactoryInfo() : vendor(), url(), email(), flags() {}
//  //#else
//  //  VST3_PFactoryInfo() { memset(this,0,sizeof(PFactoryInfo)); }
//  //#endif
};

struct VST3_ProgramListInfo {
  int32_t         id;
  VST3_String name;
  int32_t         programCount;
};

class VST3_IParameterChanges;
class VST3_IEventList;

struct VST3_ProcessContext {
	enum StatesAndFlags {
		vst3_Playing                = 1 << 1,
		vst3_CycleActive            = 1 << 2,
		vst3_Recording              = 1 << 3,
		vst3_SystemTimeValid        = 1 << 8,
		vst3_ContTimeValid          = 1 << 17,
		vst3_ProjectTimeMusicValid  = 1 << 9,
		vst3_BarPositionValid       = 1 << 11,
		vst3_CycleValid             = 1 << 12,
		vst3_TempoValid             = 1 << 10,
		vst3_TimeSigValid           = 1 << 13,
		vst3_ChordValid             = 1 << 18,
		vst3_SmpteValid             = 1 << 14,
		vst3_ClockValid             = 1 << 15
	};
	//
	uint32_t            state;
	double              sampleRate;
	int64_t             projectTimeSamples;
	int64_t             systemTime;
	int64_t             continousTimeSamples;
	double              projectTimeMusic;
	double              barPositionMusic;
	double              cycleStartMusic;
	double              cycleEndMusic;
	double              tempo;
	int32_t             timeSigNumerator;
	int32_t             timeSigDenominator;
	VST3_Chord      chord;
	int32_t             smpteOffsetSubframes;
	VST3_FrameRate  frameRate;
	int32_t             samplesToNextClock;
};

struct VST3_ProcessData {
//  VST3_ProcessData()
//    : processMode(0),symbolicSampleSize(vst3_Sample32),numSamples(0),numInputs(0)
//    , numOutputs(0),inputs (0),outputs(0),inputParameterChanges(0),outputParameterChanges(0)
//    , inputEvents(0),outputEvents(0),processContext(0) {}
  int32_t                     processMode;
  int32_t                     symbolicSampleSize;
  int32_t                     numSamples;
  int32_t                     numInputs;
  int32_t                     numOutputs;
  VST3_AudioBusBuffers*   inputs;
  VST3_AudioBusBuffers*   outputs;
  VST3_IParameterChanges* inputParameterChanges;
  VST3_IParameterChanges* outputParameterChanges;
  VST3_IEventList*        inputEvents;
  VST3_IEventList*        outputEvents;
  VST3_ProcessContext*    processContext;
};

struct VST3_ProcessSetup {
  int32_t processMode;
  int32_t symbolicSampleSize;
  int32_t maxSamplesPerBlock;
  double  sampleRate;
};

struct VST3_RoutingInfo {
	int32_t mediaType;
	int32_t busIndex;
	int32_t channel;
};

struct VST3_UnitInfo {
	int32_t         id;
	int32_t         parentUnitId;
	VST3_String name;
	int32_t         programListId;
};

struct VST3_ViewRect {
  //ViewRect(int32 l=0, int32 t=0, int32 r=0, int32 b=0)
  //: left(l), top(t), right(r), bottom(b) {}
  int32_t left;
  int32_t top;
  int32_t right;
  int32_t bottom;
  //int32 getWidth() const { return right - left; }
  //int32 getHeight() const { return bottom - top; }
};

//----------------------------------------------------------------------

struct VST3_NoteOnEvent {
  int16_t channel;
  int16_t pitch;
  float   tuning;
  float   velocity;
  int32_t length;
  int32_t noteId;
};

struct VST3_NoteOffEvent {
  int16_t channel;
  int16_t pitch;
  float   velocity;
  int32_t noteId;
  float   tuning;
};

struct VST3_DataEvent {
  enum DataTypes {
    vst3_MidiSysEx = 0
  };
  //
  uint32_t        size;
  uint32_t        type;
  const uint8_t*  bytes;
};

struct VST3_PolyPressureEvent {
  int16_t channel;
  int16_t pitch;
  float   pressure;
  int32_t noteId;
};

struct VST3_ChordEvent {
  int16_t         root;
  int16_t         bassNote;
  int16_t         mask;
  uint16_t        textLen;
  const char16_t* text;
};

struct VST3_ScaleEvent {
  int16_t         root;
  int16_t         mask;
  uint16_t        textLen;
  const char16_t* text;
};

struct VST3_NoteExpressionValueEvent {
  uint32_t  typeId;
  int32_t   noteId;
  double    value;
};

struct VST3_NoteExpressionTextEvent {
  uint32_t        typeId;
  int32_t         noteId;
  uint32_t        textLen;
  const char16_t* text;
};

struct VST3_Event {
  enum EventFlags {
    vst3_IsLive        = 1 << 0,
    vst3_UserReserved1 = 1 << 14,
    vst3_UserReserved2 = 1 << 15
  };
  enum EventTypes
  {
    vst3_NoteOnEvent = 0,
    vst3_NoteOffEvent,
    vst3_DataEvent,
    vst3_PolyPressureEvent,
    vst3_NoteExpressionValueEvent,
    vst3_NoteExpressionTextEvent,
    vst3_ChordEvent,
    vst3_ScaleEvent
  };
  //
  int32_t   busIndex;
  int32_t   sampleOffset;
  double    ppqPosition;
  uint16_t  flags;
  uint16_t  type;
  union {
    VST3_NoteOnEvent noteOn;
    VST3_NoteOffEvent noteOff;
    VST3_DataEvent data;
    VST3_PolyPressureEvent polyPressure;
    VST3_NoteExpressionValueEvent noteExpressionValue;
    VST3_NoteExpressionTextEvent noteExpressionText;
    VST3_ChordEvent chord;
    VST3_ScaleEvent scale;
  };
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class VST3_FUnknown {
public:
	virtual int32_t   VST3_PLUGIN_API queryInterface (const VST3_Id _iid, void** obj) = 0;
	virtual uint32_t  VST3_PLUGIN_API addRef () = 0;
	virtual uint32_t  VST3_PLUGIN_API release () = 0;
	//
	static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID(VST3_FUnknown, 0x00000000, 0x00000000, 0xC0000000, 0x00000046)

//----------

class VST3_IBStream
: public VST3_FUnknown {
public:
  enum IStreamSeekMode {
    vst3_IBSeekSet = 0,
    vst3_IBSeekCur,
    vst3_IBSeekEnd
  };
  //
  virtual int32_t VST3_PLUGIN_API read(void* buffer, int32_t numBytes, int32_t* numBytesRead = 0) = 0;
  virtual int32_t VST3_PLUGIN_API write(void* buffer, int32_t numBytes, int32_t* numBytesWritten = 0) = 0;
  virtual int32_t VST3_PLUGIN_API seek(int64_t pos, int32_t mode, int64_t* result = 0) = 0;
  virtual int32_t VST3_PLUGIN_API tell(int64_t* pos) = 0;
	//
  static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID(VST3_IBStream,0xC3BF6EA2,0x30994752,0x9B6BF990,0x1EE33E9B)

//----------

class VST3_IPluginFactory
: public VST3_FUnknown {
public:
  virtual int32_t  VST3_PLUGIN_API getFactoryInfo(VST3_PFactoryInfo* info) = 0;
  virtual int32_t  VST3_PLUGIN_API countClasses() = 0;
  virtual int32_t  VST3_PLUGIN_API getClassInfo (int32_t index, VST3_PClassInfo* info) = 0;
  virtual int32_t  VST3_PLUGIN_API createInstance(const char* cid, const char* _iid, void** obj) = 0;
	//
  static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID(VST3_IPluginFactory, 0x7A4D811C, 0x52114A1F, 0xAED9D2EE, 0x0B43BF9F)

//----------

class VST3_IPluginFactory2
: public VST3_IPluginFactory {
public:
	virtual int32_t VST3_PLUGIN_API getClassInfo2 (int32_t index, VST3_PClassInfo2* info) = 0;
	//
	static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID (VST3_IPluginFactory2, 0x0007B650, 0xF24B4C0B, 0xA464EDB9, 0xF00B2ABB)

//----------

class VST3_IPluginFactory3
: public VST3_IPluginFactory2 {
public:
	virtual int32_t VST3_PLUGIN_API getClassInfoUnicode(int32_t index, VST3_PClassInfoW* info) = 0;
	virtual int32_t VST3_PLUGIN_API setHostContext(VST3_FUnknown* context) = 0;
	//
	static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID (VST3_IPluginFactory3, 0x4555A2AB, 0xC1234E57, 0x9B122910, 0x36878931)

//----------

class VST3_IPluginBase
: public VST3_FUnknown {
public:
  virtual int32_t  VST3_PLUGIN_API initialize(VST3_FUnknown* context) = 0;
  virtual int32_t  VST3_PLUGIN_API terminate() = 0;
	//
  static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID(VST3_IPluginBase,0x22888DDB,0x156E45AE,0x8358B348,0x08190625)

//----------

class VST3_IComponent
: public VST3_IPluginBase {
public:
  virtual int32_t  VST3_PLUGIN_API getControllerClassId(VST3_Id classId) = 0;
  virtual int32_t  VST3_PLUGIN_API setIoMode(int32_t mode) = 0;
  virtual int32_t  VST3_PLUGIN_API getBusCount(int32_t type, int32_t dir) = 0;
  virtual int32_t  VST3_PLUGIN_API getBusInfo(int32_t type, int32_t dir, int32_t index, VST3_BusInfo& bus) = 0;
  virtual int32_t  VST3_PLUGIN_API getRoutingInfo(VST3_RoutingInfo& inInfo, VST3_RoutingInfo& outInfo) = 0;
  virtual int32_t  VST3_PLUGIN_API activateBus(int32_t type, int32_t dir, int32_t index, uint8_t state) = 0;
  virtual int32_t  VST3_PLUGIN_API setActive(uint8_t state) = 0;
  virtual int32_t  VST3_PLUGIN_API setState(VST3_IBStream* state) = 0;
  virtual int32_t  VST3_PLUGIN_API getState(VST3_IBStream* state) = 0;
	//
  static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID(VST3_IComponent,0xE831FF31,0xF2D54301,0x928EBBEE,0x25697802)

//----------

class VST3_IAudioProcessor
: public VST3_FUnknown {
public:
  virtual int32_t  VST3_PLUGIN_API setBusArrangements(uint64_t* inputs, int32_t numIns, uint64_t* outputs, int32_t numOuts) = 0;
  virtual int32_t  VST3_PLUGIN_API getBusArrangement(int32_t dir, int32_t index, uint64_t& arr) = 0;
  virtual int32_t  VST3_PLUGIN_API canProcessSampleSize(int32_t symbolicSampleSize) = 0;
  virtual uint32_t VST3_PLUGIN_API getLatencySamples() = 0;
  virtual int32_t  VST3_PLUGIN_API setupProcessing(VST3_ProcessSetup& setup) = 0;
  virtual int32_t  VST3_PLUGIN_API setProcessing(uint8_t state) = 0;
  virtual int32_t  VST3_PLUGIN_API process(VST3_ProcessData& data) = 0;
  virtual uint32_t VST3_PLUGIN_API getTailSamples() = 0;
	//
  static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID(VST3_IAudioProcessor,0x42043F99,0xB7DA453C,0xA569E79D,0x9AAEC33D)

//----------

class VST3_IUnitInfo
: public VST3_FUnknown {
public:
	virtual int32_t VST3_PLUGIN_API getUnitCount() = 0;
	virtual int32_t VST3_PLUGIN_API getUnitInfo(int32_t unitIndex, VST3_UnitInfo& info /*out*/) = 0;
	virtual int32_t VST3_PLUGIN_API getProgramListCount() = 0;
	virtual int32_t VST3_PLUGIN_API getProgramListInfo(int32_t listIndex, VST3_ProgramListInfo& info /*out*/) = 0;
	virtual int32_t VST3_PLUGIN_API getProgramName(int32_t listId, int32_t programIndex, VST3_String name /*out*/) = 0;
	virtual int32_t VST3_PLUGIN_API getProgramInfo(int32_t listId, int32_t programIndex, const char* attributeId /*in*/, VST3_String attributeValue /*out*/) = 0;
	virtual int32_t VST3_PLUGIN_API hasProgramPitchNames(int32_t listId, int32_t programIndex) = 0;
	virtual int32_t VST3_PLUGIN_API getProgramPitchName(int32_t listId, int32_t programIndex, int16_t midiPitch, VST3_String name /*out*/) = 0;
	virtual int32_t VST3_PLUGIN_API getSelectedUnit() = 0;
	virtual int32_t VST3_PLUGIN_API selectUnit(int32_t unitId) = 0;
	virtual int32_t VST3_PLUGIN_API getUnitByBus(int32_t type, int32_t dir, int32_t busIndex, int32_t channel, int32_t& unitId /*out*/) = 0;
	virtual int32_t VST3_PLUGIN_API setUnitProgramData(int32_t listOrUnitId, int32_t programIndex, VST3_IBStream* data) = 0;
	//
	static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID (VST3_IUnitInfo, 0x3D4BD6B5, 0x913A4FD2, 0xA886E768, 0xA5EB92C1)

//----------

class VST3_IAttributeList
: public VST3_FUnknown {
public:
	virtual int32_t VST3_PLUGIN_API setInt(const char* id, int64_t value) = 0;
	virtual int32_t VST3_PLUGIN_API getInt(const char* id, int64_t& value) = 0;
	virtual int32_t VST3_PLUGIN_API setFloat(const char* id, double value) = 0;
	virtual int32_t VST3_PLUGIN_API getFloat(const char* id, double& value) = 0;
	virtual int32_t VST3_PLUGIN_API setString(const char* id, const char16_t* string) = 0;
	virtual int32_t VST3_PLUGIN_API getString(const char* id, char16_t* string, uint32_t size) = 0;
	virtual int32_t VST3_PLUGIN_API setBinary(const char* id, const void* data, uint32_t size) = 0;
	virtual int32_t VST3_PLUGIN_API getBinary(const char* id, const void*& data, uint32_t& size) = 0;
	//
	static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID (VST3_IAttributeList, 0x1E5F0AEB, 0xCC7F4533, 0xA2544011, 0x38AD5EE4)

//----------

class VST3_IMessage
: public VST3_FUnknown {
public:
	virtual const char*               VST3_PLUGIN_API getMessageID () = 0;
	virtual void                      VST3_PLUGIN_API setMessageID (const char* id /*in*/) = 0;
	virtual VST3_IAttributeList*  VST3_PLUGIN_API getAttributes () = 0;
	//
	static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID (VST3_IMessage, 0x936F033B, 0xC6C047DB, 0xBB0882F8, 0x13C1E613)

//----------

class VST3_IConnectionPoint
: public VST3_FUnknown {
public:
	virtual int32_t VST3_PLUGIN_API connect(VST3_IConnectionPoint* other) = 0;
	virtual int32_t VST3_PLUGIN_API disconnect(VST3_IConnectionPoint* other) = 0;
	virtual int32_t VST3_PLUGIN_API notify(VST3_IMessage* message) = 0;
	//
	static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID (VST3_IConnectionPoint, 0x70A4156F, 0x6E6E4026, 0x989148BF, 0xAA60D8D1)

//----------

class VST3_IMidiMapping
: public VST3_FUnknown {
public:
	virtual int32_t VST3_PLUGIN_API getMidiControllerAssignment (int32_t busIndex, int16_t channel, int16_t midiControllerNumber, uint32_t& id/*out*/) = 0;
	//
	static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID (VST3_IMidiMapping, 0xDF0FF9F7, 0x49B74669, 0xB63AB732, 0x7ADBF5E5)

//----------

class VST3_IKeyswitchController
: public VST3_FUnknown {
public:
	virtual int32_t VST3_PLUGIN_API getKeyswitchCount (int32_t busIndex, int16_t channel) = 0;
	virtual int32_t VST3_PLUGIN_API getKeyswitchInfo (int32_t busIndex, int16_t channel, int32_t keySwitchIndex, VST3_KeyswitchInfo& info /*out*/) = 0;
	//
	static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID (VST3_IKeyswitchController, 0x1F2F76D3, 0xBFFB4B96, 0xB99527A5, 0x5EBCCEF4)

//----------

//INoteExpressionController

//----------

class VST3_IComponentHandler
: public VST3_FUnknown {
public:
	virtual int32_t VST3_PLUGIN_API beginEdit (uint32_t id) = 0;
	virtual int32_t VST3_PLUGIN_API performEdit (uint32_t id, double valueNormalized) = 0;
	virtual int32_t VST3_PLUGIN_API endEdit (uint32_t id) = 0;
	virtual int32_t VST3_PLUGIN_API restartComponent (int32_t flags) = 0;
	//
	static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID (VST3_IComponentHandler, 0x93A0BEA3, 0x0BD045DB, 0x8E890B0C, 0xC1E46AC6)

//----------

class VST3_IComponentHandler2
: public VST3_FUnknown {
public:
	virtual int32_t VST3_PLUGIN_API setDirty (uint8_t state) = 0;
	virtual int32_t VST3_PLUGIN_API requestOpenEditor (const char* name = /*ViewType::*/vst3_Editor) = 0;
	virtual int32_t VST3_PLUGIN_API startGroupEdit () = 0;
	virtual int32_t VST3_PLUGIN_API finishGroupEdit () = 0;
	//
	static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID (VST3_IComponentHandler2, 0xF040B4B3, 0xA36045EC, 0xABCDC045, 0xB4D5A2CC)

//----------

class VST3_IPlugFrame;

class VST3_IPlugView
: public VST3_FUnknown {
public:
	virtual int32_t VST3_PLUGIN_API isPlatformTypeSupported (const char* type) = 0;
	virtual int32_t VST3_PLUGIN_API attached (void* parent, const char* type) = 0;
	virtual int32_t VST3_PLUGIN_API removed () = 0;
	virtual int32_t VST3_PLUGIN_API onWheel (float distance) = 0;
	virtual int32_t VST3_PLUGIN_API onKeyDown (char16_t key, int16_t keyCode, int16_t modifiers) = 0;
	virtual int32_t VST3_PLUGIN_API onKeyUp (char16_t key, int16_t keyCode, int16_t modifiers) = 0;
	virtual int32_t VST3_PLUGIN_API getSize (VST3_ViewRect* size) = 0;
	virtual int32_t VST3_PLUGIN_API onSize (VST3_ViewRect* newSize) = 0;
	virtual int32_t VST3_PLUGIN_API onFocus (uint8_t state) = 0;
	virtual int32_t VST3_PLUGIN_API setFrame (VST3_IPlugFrame* frame) = 0;
	virtual int32_t VST3_PLUGIN_API canResize () = 0;
	virtual int32_t VST3_PLUGIN_API checkSizeConstraint (VST3_ViewRect* rect) = 0;
	//
	static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID (VST3_IPlugView, 0x5BC32507, 0xD06049EA, 0xA6151B52, 0x2B755B29)

//----------

class VST3_IPlugFrame
: public VST3_FUnknown {
public:
	virtual int32_t VST3_PLUGIN_API resizeView(VST3_IPlugView* view, VST3_ViewRect* newSize) = 0;
	//
	static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID (VST3_IPlugFrame, 0x367FAF01, 0xAFA94693, 0x8D4DA2A0, 0xED0882A3)

//----------

#define setState setEditorState
#define getState getEditorState

class VST3_IEditController
: public VST3_IPluginBase {
public:
	virtual int32_t             VST3_PLUGIN_API setComponentState (VST3_IBStream* state) = 0;
	virtual int32_t             VST3_PLUGIN_API setState (VST3_IBStream* state) = 0;
	virtual int32_t             VST3_PLUGIN_API getState (VST3_IBStream* state) = 0;
	virtual int32_t             VST3_PLUGIN_API getParameterCount () = 0;
	virtual int32_t             VST3_PLUGIN_API getParameterInfo (int32_t paramIndex, VST3_ParameterInfo& info /*out*/) = 0;
	virtual int32_t             VST3_PLUGIN_API getParamStringByValue (uint32_t id, double valueNormalized /*in*/, VST3_String string /*out*/) = 0;
	virtual int32_t             VST3_PLUGIN_API getParamValueByString (uint32_t id, char16_t* string /*in*/, double& valueNormalized /*out*/) = 0;
	virtual double              VST3_PLUGIN_API normalizedParamToPlain (uint32_t id, double valueNormalized) = 0;
	virtual double              VST3_PLUGIN_API plainParamToNormalized (uint32_t id, double plainValue) = 0;
	virtual double              VST3_PLUGIN_API getParamNormalized (uint32_t id) = 0;
	virtual int32_t             VST3_PLUGIN_API setParamNormalized (uint32_t id, double value) = 0;
	virtual int32_t             VST3_PLUGIN_API setComponentHandler (VST3_IComponentHandler* handler) = 0;
	virtual VST3_IPlugView* VST3_PLUGIN_API createView (const char* name) = 0;
	//
	static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID (VST3_IEditController, 0xDCD7BBE3, 0x7742448D, 0xA874AACC, 0x979C759E)

#undef setState
#undef getState

//----------

class VST3_IEditController2
: public VST3_FUnknown {
public:
	virtual int32_t VST3_PLUGIN_API setKnobMode (int32_t mode) = 0;
	virtual int32_t VST3_PLUGIN_API openHelp (uint8_t onlyCheck) = 0;
	virtual int32_t VST3_PLUGIN_API openAboutBox (uint8_t onlyCheck) = 0;
	//
	static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID (VST3_IEditController2, 0x7F4EFE59, 0xF3204967, 0xAC27A3AE, 0xAFB63038)

//----------

class VST3_ITimerHandler
: public VST3_FUnknown {
public:
	virtual void VST3_PLUGIN_API onTimer () = 0;
	//
	static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID (VST3_ITimerHandler, 0x10BDD94F, 0x41424774, 0x821FAD8F, 0xECA72CA9)

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class VST3_IHostApplication
: public VST3_FUnknown {
public:
	virtual int32_t VST3_PLUGIN_API getName (VST3_String name) = 0;
	virtual int32_t VST3_PLUGIN_API createInstance (VST3_Id cid, VST3_Id _iid, void** obj) = 0;
	//
	static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID (VST3_IHostApplication, 0x58E595CC, 0xDB2D4969, 0x8B6AAF8C, 0x36A664E5)

//----------

class VST3_IEventHandler
: public VST3_FUnknown {
public:
	virtual void VST3_PLUGIN_API onFDIsSet (int fd) = 0;
	//
	static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID (VST3_IEventHandler, 0x561E65C9, 0x13A0496F, 0x813A2C35, 0x654D7983)

//----------

class VST3_IRunLoop
: public VST3_FUnknown {
public:
	virtual int32_t VST3_PLUGIN_API registerEventHandler (VST3_IEventHandler* handler, int fd) = 0;
	virtual int32_t VST3_PLUGIN_API unregisterEventHandler (VST3_IEventHandler* handler) = 0;
	virtual int32_t VST3_PLUGIN_API registerTimer (VST3_ITimerHandler* handler, uint64_t milliseconds) = 0;
	virtual int32_t VST3_PLUGIN_API unregisterTimer (VST3_ITimerHandler* handler) = 0;
	//
	static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID (VST3_IRunLoop, 0x18C35366, 0x97764F1A, 0x9C5B8385, 0x7A871389)

//----------

class VST3_IParamValueQueue
: public VST3_FUnknown {
public:
	virtual uint32_t  VST3_PLUGIN_API getParameterId () = 0;
	virtual int32_t   VST3_PLUGIN_API getPointCount () = 0;
	virtual int32_t   VST3_PLUGIN_API getPoint (int32_t index, int32_t& sampleOffset /*out*/, double& value /*out*/) = 0;
	virtual int32_t   VST3_PLUGIN_API addPoint (int32_t sampleOffset, double value, int32_t& index /*out*/) = 0;
	//
	static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID (VST3_IParamValueQueue, 0x01263A18, 0xED074F6F, 0x98C9D356, 0x4686F9BA)

//----------

class VST3_IParameterChanges
: public VST3_FUnknown {
public:
	virtual int32_t                     VST3_PLUGIN_API getParameterCount () = 0;
	virtual VST3_IParamValueQueue*  VST3_PLUGIN_API getParameterData (int32_t index) = 0;
	virtual VST3_IParamValueQueue*  VST3_PLUGIN_API addParameterData (const uint32_t& id, int32_t& index /*out*/) = 0;
	//
	static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID (VST3_IParameterChanges, 0xA4779663, 0x0BB64A56, 0xB44384A8, 0x466FEB9D)

//----------

class VST3_IEventList
: public VST3_FUnknown {
public:
	virtual int32_t VST3_PLUGIN_API getEventCount () = 0;
	virtual int32_t VST3_PLUGIN_API getEvent (int32_t index, VST3_Event& e /*out*/) = 0;
	virtual int32_t VST3_PLUGIN_API addEvent (VST3_Event& e /*in*/) = 0;
	//
	static const VST3_Id iid;
};

VST3_DECLARE_CLASS_IID (VST3_IEventList, 0x3A2C4214, 0x346349FE, 0xB2C4F397, 0xB9695A44)

//----------------------------------------------------------------------
#endif
