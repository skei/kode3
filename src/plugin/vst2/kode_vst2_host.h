#ifndef kode_vst2_host_included
#define kode_vst2_host_included
//----------------------------------------------------------------------

#include "kode.h"
#include "plugin/vst2/kode_vst2.h"

class KODE_Vst2Host {

//------------------------------
private:
//------------------------------

  audioMasterCallback   MAudioMaster  = nullptr;
  //AEffect*              MAEffect      = nullptr;

//------------------------------
public:
//------------------------------

  KODE_Vst2Host(audioMasterCallback AAudioMaster/*, AEffect* AAEffect*/) {
    MAudioMaster = AAudioMaster;
  }

//------------------------------
private:
//------------------------------

  //bool processEvents(VstEvents* events) {
  //  if (MVstMaster) {
  //    if ((VstInt32)MVstMaster(&MVstEffect,audioMasterProcessEvents,0,0,events,0) == 1) return true;
  //  }
  //  return false;
  //}

  void flushMidi(AEffect* AAEffect, VstEvents* AVstEvents) {
    if (MAudioMaster) {
      //MAudioMaster(MAEffect,audioMasterProcessEvents,0,0,(VstEvents*)&MVstEvents,0);
      MAudioMaster(AAEffect,audioMasterProcessEvents,0,0,AVstEvents,0);
      AVstEvents->numEvents = 0;
    }
  }

  //----------

  //bool sizeWindow(KODE_int32 AWidth, KODE_int32 AHeight) {
  //  if (MVstMaster) {
  //    if ((VstInt32)MVstMaster(&MVstEffect,audioMasterSizeWindow,AWidth,AHeight,KODE_NULL,0) == 1) return true;
  //  }
  //  return false;
  //}

  void resizeEditor(AEffect* AAEffect, uint32_t AWidth, uint32_t AHeight) {
    if (MAudioMaster) {
      MAudioMaster(AAEffect,audioMasterSizeWindow,AWidth,AHeight,0,0);
    }
  }

  //----------

  //bool canDo(const char* AText) {
  //  if (MVstMaster) {
  //    if ( (VstInt32)MVstMaster(&MVstEffect,audioMasterCanDo,0,0,(void*)AText,0) == 1) return true;
  //  }
  //  return false;
  //}

  //VstInt32 currentId(void) {
  //  if (MVstMaster) {
  //    return (VstInt32)MVstMaster(&MVstEffect,audioMasterCurrentId,0,0,KODE_NULL,0);
  //  }
  //  return 0;
  //}

  void updateInfo(AEffect* AAEffect) {

    /*

    MHostCanDo = khc_none;
    if (canDo("acceptIOChanges"))                MHostCanDo += khc_acceptIOChanges;
  //if (canDo("asyncProcessing"))                MHostCanDo += khc_asyncProcessing;
    if (canDo("closeFileSelector"))              MHostCanDo += khc_closeFileSelector;
  //if (canDo("editFile"))                       MHostCanDo += khc_editFile;
  //if (canDo("getChunkFile"))                   MHostCanDo += khc_getChunkFile;
  //if (canDo("midiProgramNames"))               MHostCanDo += khc_midiProgramNames;
  //if (canDo("NIMKPIVendorSpecificCallbacks"))  MHostCanDo += khc_nimkpi;
    if (canDo("offline"))                        MHostCanDo += khc_offline;
    if (canDo("openFileSelector"))               MHostCanDo += khc_openFileSelector;
    if (canDo("receiveVstEvents"))               MHostCanDo += khc_receiveVstEvents;
    if (canDo("receiveVstMidiEvent"))            MHostCanDo += khc_receiveVstMidiEvent;
  //if (canDo("receiveVstTimeInfo"))             MHostCanDo += khc_receiveVstTimeInfo;
    if (canDo("reportConnectionChanges"))        MHostCanDo += khc_reportConnectionChanges;
    if (canDo("sendVstEvents"))                  MHostCanDo += khc_sendVstEvents;
    if (canDo("sendVstMidiEvent"))               MHostCanDo += khc_sendVstMidiEvent;
    if (canDo("sendVstMidiEventFlagIsRealtime")) MHostCanDo += khc_sendVstMidiEventFlagIsRealtime;
    if (canDo("sendVstTimeInfo"))                MHostCanDo += khc_sendVstTimeInfo;
    if (canDo("shellCategory"))                  MHostCanDo += khc_shellCategory;
  //if (canDo("shellCategorycurID"))             MHostCanDo += khc_shellCategoryCurId;
    if (canDo("sizeWindow"))                     MHostCanDo += khc_sizeWindow;
    if (canDo("startStopProcess"))               MHostCanDo += khc_startStopProcess;
  //if (canDo("supplyIdle"))                     MHostCanDo += khc_supplyIdle;
  //if (canDo("supportShell"))                   MHostCanDo += khc_supportShell;

    MHostId = khi_unknown;
    char buffer[256];
    buffer[0] = 0;
    getProductString(buffer);
  //if (KStrcmp("AudioMulch",buffer) == 0)              MHostId = khi_audiomulch;       // http://www.audiomulch.com/mulchnotes/mulchnote_2.htm
    if (KODE_Strcmp("Bitwig Studio",buffer) == 0)       MHostId = khi_bitwig;
    if (KODE_Strcmp("Carla",buffer) == 0)               MHostId = khi_carla;
    if (KODE_Strcmp("Carla_Discovery",buffer) == 0)     MHostId = khi_carla_discovery;  // 'Carla_Discovery' during scanning..
  //if (KStrcmp("DSSI-VST Plugin",buffer) == 0)         MHostId = khi_dssi_plugin;      // https://github.com/falkTX/dssi-vst/blob/master/dssi-vst-server.cpp
  //if (KStrcmp("DSSI-VST Scanner",buffer) == 0)        MHostId = khi_dssi_scanner;     // https://github.com/falkTX/dssi-vst/blob/master/dssi-vst-scanner.cpp
  //if (KStrcmp("DSSI VST Wrapper Plugin",buffer) == 0) MHostId = khi_linvst;           // https://github.com/osxmidi/LinVst/blob/master/lin-vst-server.cpp
    if (KODE_Strcmp("energyXT",buffer) == 0)            MHostId = khi_energyxt;
    if (KODE_Strcmp("Fruity Wrapper",buffer) == 0)      MHostId = khi_fruity;
    if (KODE_Strcmp("Live",buffer) == 0)                MHostId = khi_live;
    if (KODE_Strcmp("Multi Host 4 Linux",buffer) == 0)  MHostId = khi_jost;
    if (KODE_Strcmp("Qtractor",buffer) == 0)            MHostId = khi_qtractor;
    if (KODE_Strcmp("REAPER",buffer) == 0)              MHostId = khi_reaper;
  //if (KStrcmp("Tracktion",buffer) == 0)               MHostId = khi_tracktion;        // https://github.com/osxmidi/LinVst/blob/master/linvst.cpp
  //if (KStrcmp("Waveform",buffer) == 0)                MHostId = khi_waveform;

    MHostVersion = getVendorVersion();
    MHostVstVer = version();

    //KODE_HostInfo* info;
    MAudioMaster(AAEffect,audioMasterGetVendorString,0,0,MHostInfo.vendor,0);
    MAudioMaster(AAEffect,audioMasterGetProductString,0,0,MHostInfo.product,0);
    MHostInfo.version   = MAudioMaster(AAEffect,audioMasterGetVendorVersion,0,0,0,0);
    MHostInfo.language  = MAudioMaster(AAEffect,audioMasterGetLanguage,0,0,0,0);
    char* path = (char*)MAudioMaster(AAEffect,audioMasterGetDirectory,0,0,0,0);
    strcpy(MHostInfo.directory,path);
    //if (MAudioMaster(AAEffect,audioMasterCanDo,0,0,(char*)"acceptIOChanges",0) == 1) MHostInfo.canDo += khc_acceptIoChange;

    */

  }

  //----------

  //void automate(VstInt32 AIndex, float AValue) {
  //  if (MVstMaster) {
  //    //KODE_VST2TRACE;
  //    MVstMaster(&MVstEffect,audioMasterAutomate,AIndex,0,KODE_NULL,AValue);
  //  }
  //}

  //bool beginEdit(VstInt32 AIndex) {
  //  if (MVstMaster) {
  //    if ( (VstInt32)MVstMaster(&MVstEffect,audioMasterBeginEdit,AIndex,0,KODE_NULL,0) == 1) return true;
  //  }
  //  return false;
  //}

  //bool endEdit(VstInt32 AIndex) {
  //  if (MVstMaster) {
  //    if ((VstInt32)MVstMaster(&MVstEffect,audioMasterEndEdit,AIndex,0,KODE_NULL,0) == 1) return true;
  //  }
  //  return false;
  //}


  void updateParameter(AEffect* AAEffect, uint32_t AIndex, float AValue) {
    if (MAudioMaster) {
      MAudioMaster(AAEffect,audioMasterBeginEdit,AIndex,0,0,0);
      MAudioMaster(AAEffect,audioMasterAutomate,AIndex,0,0,AValue);
      MAudioMaster(AAEffect,audioMasterEndEdit,AIndex,0,0,0);
    }
  }

  //----------

  /*
    samplePos:          Current Position. It must always be valid, and should
                        not cost a lot to ask for. The sample position is ahead
                        of the time displayed to the user. In sequencer stop
                        mode, its value does not change. A 32 bit integer is
                        too small for sample positions, and it's a double to
                        make it easier to convert between ppq and samples.
    ppqPos:             At tempo 120, 1 quarter makes 1/2 second, so 2.0 ppq
                        translates to 48000 samples at 48kHz sample rate.
                        .25 ppq is one sixteenth note then. if you need
                        something like 480ppq, you simply multiply ppq by that
                        scaler.
    barStartPos:        Say we're at bars/beats readout 3.3.3. That's 2 bars +
                        2 q + 2 sixteenth, makes 2 * 4 + 2 + .25 = 10.25 ppq.
                        at tempo 120, that's 10.25 * .5 = 5.125 seconds, times
                        48000 = 246000 samples.
    samplesToNextClock: MIDI Clock Resolution (24 per Quarter Note), can be
                        negative the distance to the next midi clock (24 ppq,
                        pulses per quarter) in samples. unless samplePos falls
                        precicely on a midi clock, this will either be negative
                        such that the previous MIDI clock is addressed, or
                        positive when referencing the following (future) MIDI
                        clock.
  */

  /*
    struct VstTimeInfo {
      double samplePos;             // current Position in audio samples (always valid)
      double sampleRate;            // current Sample Rate in Herz (always valid)
      double nanoSeconds;           // System Time in nanoseconds (10^-9 second)
      double ppqPos;                // Musical Position, in Quarter Note (1.0 equals 1 Quarter Note)
      double tempo;                 // current Tempo in BPM (Beats Per Minute)
      double barStartPos;           // last Bar Start Position, in Quarter Note
      double cycleStartPos;         // Cycle Start (left locator), in Quarter Note
      double cycleEndPos;           // Cycle End (right locator), in Quarter Note
      VstInt32 timeSigNumerator;    // Time Signature Numerator (e.g. 3 for 3/4)
      VstInt32 timeSigDenominator;  // Time Signature Denominator (e.g. 4 for 3/4)
      VstInt32 smpteOffset;         // SMPTE offset (in SMPTE subframes (bits; 1/80 of a frame)). The current SMPTE position can be calculated using #samplePos, #sampleRate, and #smpteFrameRate.
      VstInt32 smpteFrameRate;      // @see VstSmpteFrameRate
      VstInt32 samplesToNextClock;  // MIDI Clock Resolution (24 Per Quarter Note), can be negative (nearest clock)
      VstInt32 flags;               // @see VstTimeInfoFlags
    };

    enum VstTimeInfoFlags {

      kVstTransportChanged      = 1,        // indicates that play, cycle or record state has changed
      kVstTransportPlaying      = 1 << 1,   // set if Host sequencer is currently playing
      kVstTransportCycleActive  = 1 << 2,   // set if Host sequencer is in cycle mode
      kVstTransportRecording    = 1 << 3,   // set if Host sequencer is in record mode
      kVstAutomationWriting     = 1 << 6,   // set if automation write mode active (record parameter changes)
      kVstAutomationReading     = 1 << 7,   // set if automation read mode active (play parameter changes)

      kVstNanosValid            = 1 << 8,   // VstTimeInfo::nanoSeconds valid
      kVstPpqPosValid           = 1 << 9,   // VstTimeInfo::ppqPos valid
      kVstTempoValid            = 1 << 10,  // VstTimeInfo::tempo valid
      kVstBarsValid             = 1 << 11,  // VstTimeInfo::barStartPos valid
      kVstCyclePosValid         = 1 << 12,  // VstTimeInfo::cycleStartPos and VstTimeInfo::cycleEndPos valid
      kVstTimeSigValid          = 1 << 13,  // VstTimeInfo::timeSigNumerator and VstTimeInfo::timeSigDenominator valid
      kVstSmpteValid            = 1 << 14,  // VstTimeInfo::smpteOffset and VstTimeInfo::smpteFrameRate valid
      kVstClockValid            = 1 << 15   // VstTimeInfo::samplesToNextClock valid
    };
  */

  void updateTime(AEffect* AAEffect) {
//    VstIntPtr mask = 0xffff;
//    VstIntPtr result = MAudioMaster(AAEffect,audioMasterGetTime,0,mask,0,0);
//    VstTimeInfo* timeinfo = (VstTimeInfo*)result;
//    if (timeinfo) {
//      MTempo          = timeinfo->tempo;
//      MTimeSigNum     = timeinfo->timeSigNumerator;
//      MTimeSigDenom   = timeinfo->timeSigDenominator;
//      MSamplePos      = timeinfo->samplePos;
//      MBeatPos        = timeinfo->ppqPos;
//      //MNanoSeconds    = timeinfo->nanoSeconds;
//      //MSampleRate     = timeinfo->sampleRate;
//      //MPPQBarStart    = timeinfo->barStartPos;
//      //MPPOCycleStart  = timeinfo->cycleStartPos;
//      //MPPQCycleEnd    = timeinfo->cycleEndPos;
//      //MPlayState      = timeinfo->flags & 127;
//      //if (timeinfo->flags & kVstTransportChanged) {
//        MPlayState = KODE_PLUGIN_PLAYSTATE_NONE;
//        if (timeinfo->flags & kVstTransportPlaying)     MPlayState |= KODE_PLUGIN_PLAYSTATE_PLAYING;
//        if (timeinfo->flags & kVstTransportRecording)   MPlayState |= KODE_PLUGIN_PLAYSTATE_RECORDING;
//        if (timeinfo->flags & kVstTransportCycleActive) MPlayState |= KODE_PLUGIN_PLAYSTATE_LOOPING;
//        MPrevPlayState = MPlayState;
//      //}
//    }
  }

  //----------
  //----------
  //----------

  uint32_t getAutomationState(AEffect* AAEffect) {
    return MAudioMaster(AAEffect,audioMasterGetAutomationState,0,0,0,0);
  }

  //----------

  uint32_t getBlockSize(AEffect* AAEffect) {
    return MAudioMaster(AAEffect,audioMasterGetBlockSize,0,0,0,0);
  }

  //----------

  uint32_t getInputLatency(AEffect* AAEffect) {
    return MAudioMaster(AAEffect,audioMasterGetInputLatency,0,0,0,0);
  }

  //----------

  uint32_t getOutputLatency(AEffect* AAEffect) {
    return MAudioMaster(AAEffect,audioMasterGetOutputLatency,0,0,0,0);
  }

  //----------

  uint32_t getProcessLevel(AEffect* AAEffect) {
    return MAudioMaster(AAEffect,audioMasterGetCurrentProcessLevel,0,0,0,0);
  }

  //----------

  uint32_t getSampleRate(AEffect* AAEffect) {
    return MAudioMaster(AAEffect,audioMasterGetSampleRate,0,0,0,0);
  }

  //----------

  void idle(AEffect* AAEffect) {
    if (MAudioMaster) MAudioMaster(AAEffect,audioMasterIdle,0,0,nullptr,0);
  }

  //----------

  bool ioChanged(AEffect* AAEffect) {
    if (MAudioMaster(AAEffect,audioMasterIOChanged,0,0,0,0) == 1) return true;
    return false;
  }

  //----------

  void updateDisplay(AEffect* AAEffect) {
    MAudioMaster(AAEffect,audioMasterUpdateDisplay,0,0,0,0);
  }

  //----------

  VstInt32 version(AEffect* AAEffect) {
    VstInt32 result = 1;
    if (MAudioMaster) result = (VstInt32)MAudioMaster(AAEffect,audioMasterVersion,0,0,nullptr,0);
    if (result==0) result = 1; // old (!version)
    return result;
  }

  //----------

  //audioMasterOfflineStart,              // [index]: numNewAudioFiles [value]: numAudioFiles [ptr]: #VstAudioFile*  @see AudioEffectX::offlineStart
  //audioMasterOfflineRead,               // [index]: bool readSource [value]: #VstOfflineOption* @see VstOfflineOption [ptr]: #VstOfflineTask*  @see VstOfflineTask @see AudioEffectX::offlineRead
  //audioMasterOfflineWrite,              // @see audioMasterOfflineRead @see AudioEffectX::offlineRead
  //audioMasterOfflineGetCurrentPass,     // @see AudioEffectX::offlineGetCurrentPass
  //audioMasterOfflineGetCurrentMetaPass, // @see AudioEffectX::offlineGetCurrentMetaPass
  //audioMasterOpenFileSelector,          // [ptr]: VstFileSelect* [return value]: 1 if supported  @see AudioEffectX::openFileSelector
  //audioMasterCloseFileSelector,         // [ptr]: VstFileSelect*  @see AudioEffectX::closeFileSelector
  //audioMasterVendorSpecific,            // no definition, vendor specific handling  @see AudioEffectX::hostVendorSpecific

};

//----------------------------------------------------------------------
#endif
