/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: EL_Scale
 *** Description: The logic of an equipment block: one holder at a time, outputs switched off before new ones go on, all off on release or abort, inputs reported when they change. Technical: Scale: output values from its holder -> outputs (break before make); one holder at a time; all off on release or when the module aborts; inputs -> state channel when they change
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/filling/EL_Scale_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"
#include "forte/iec61131_functions/func_ADD.h"
#include "forte/iec61131_functions/func_AND.h"
#include "forte/iec61131_functions/func_CONCAT.h"
#include "forte/iec61131_functions/func_EQ.h"
#include "forte/iec61131_functions/func_GE.h"
#include "forte/iec61131_functions/func_NE.h"
#include "forte/iec61131_functions/func_OR.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::filling {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:evyZb8Tqz4_ms69Xl_PeXi_rgQmI0Zf0yelHLfoBitmZMNzZMNeXAc2mWs6h7bKTQa1X44XPIdtWX2shUs0KZQ=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "CMD"_STRID, "RELEASE"_STRID, "SAMPLE"_STRID, "REFRESH"_STRID, "DRIVEN"_STRID, "MOD_CHG"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "DRIVE"_STRID, "STATE"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"Module"_STRID, "Name"_STRID, "UaRoot"_STRID, "C_Holder"_STRID, "C_Release"_STRID, "R_Holder"_STRID, "I_Weight"_STRID, "ModuleState"_STRID};
    const auto cDataOutputNames = std::array{"IdCmd"_STRID, "IdRelease"_STRID, "IdState"_STRID, "IdPub"_STRID, "Weight"_STRID, "Holder"_STRID};
    const SFBInterfaceSpec cFBInterfaceSpec = {
        .mEINames = cEventInputNames,
        .mEITypeNames = cEventInputTypeIds,
        .mEONames = cEventOutputNames,
        .mEOTypeNames = cEventOutputTypeIds,
        .mDINames = cDataInputNames,
        .mDONames = cDataOutputNames,
        .mDIONames = {},
        .mSocketNames = {},
        .mPlugNames = {},
    };

    const auto cInternalsNames = std::array{"Publish"_STRID, "Beat"_STRID, "LastHolder"_STRID, "Pending"_STRID, "OffPending"_STRID, "L_Weight"_STRID};
  }

  DEFINE_FIRMWARE_FB(FORTE_EL_Scale, "filling::EL_Scale"_STRID, TypeHash)

  FORTE_EL_Scale::FORTE_EL_Scale(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CBasicFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cInternalsNames),
      var_Publish(0_BOOL),
      var_Beat(0_USINT),
      var_LastHolder(u""_WSTRING),
      var_Pending(0_BOOL),
      var_OffPending(0_BOOL),
      var_L_Weight(0_LREAL),
      var_Module(u""_WSTRING),
      var_Name(u""_WSTRING),
      var_UaRoot(u""_WSTRING),
      var_C_Holder(u""_WSTRING),
      var_C_Release(0_BOOL),
      var_R_Holder(u""_WSTRING),
      var_I_Weight(0_LREAL),
      var_ModuleState(0_USINT),
      var_IdCmd(u""_WSTRING),
      var_IdRelease(u""_WSTRING),
      var_IdState(u""_WSTRING),
      var_IdPub(u""_WSTRING),
      var_Weight(0_LREAL),
      var_Holder(u""_WSTRING),
      conn_INITO(*this, 0),
      conn_DRIVE(*this, 1),
      conn_STATE(*this, 2),
      conn_Module(nullptr),
      conn_Name(nullptr),
      conn_UaRoot(nullptr),
      conn_C_Holder(nullptr),
      conn_C_Release(nullptr),
      conn_R_Holder(nullptr),
      conn_I_Weight(nullptr),
      conn_ModuleState(nullptr),
      conn_IdCmd(*this, 0, var_IdCmd),
      conn_IdRelease(*this, 1, var_IdRelease),
      conn_IdState(*this, 2, var_IdState),
      conn_IdPub(*this, 3, var_IdPub),
      conn_Weight(*this, 4, var_Weight),
      conn_Holder(*this, 5, var_Holder) {
  }

  void FORTE_EL_Scale::setInitialValues() {
    CBasicFB::setInitialValues();
    var_Publish = 0_BOOL;
    var_Beat = 0_USINT;
    var_LastHolder = u""_WSTRING;
    var_Pending = 0_BOOL;
    var_OffPending = 0_BOOL;
    var_L_Weight = 0_LREAL;
    var_Module = u""_WSTRING;
    var_Name = u""_WSTRING;
    var_UaRoot = u""_WSTRING;
    var_C_Holder = u""_WSTRING;
    var_C_Release = 0_BOOL;
    var_R_Holder = u""_WSTRING;
    var_I_Weight = 0_LREAL;
    var_ModuleState = 0_USINT;
    var_IdCmd = u""_WSTRING;
    var_IdRelease = u""_WSTRING;
    var_IdState = u""_WSTRING;
    var_IdPub = u""_WSTRING;
    var_Weight = 0_LREAL;
    var_Holder = u""_WSTRING;
  }

  void FORTE_EL_Scale::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
    do {
      switch(mECCState) {
        case scmStateSTART:
          if(scmEventINITID == paEIID) enterStateInit(paECET);
          else
          if(scmEventSAMPLEID == paEIID) enterStateSample(paECET);
          else
          if(scmEventREFRESHID == paEIID) enterStateRefresh(paECET);
          else
          if((scmEventCMDID == paEIID) && (func_OR<CIEC_BOOL>(func_EQ(var_Holder, u""_WSTRING), func_EQ(var_C_Holder, var_Holder)))) enterStateCmd(paECET);
          else
          if((scmEventRELEASEID == paEIID) && (func_AND<CIEC_BOOL>(func_EQ(var_R_Holder, var_Holder), func_NE(var_Holder, u""_WSTRING)))) enterStateOff(paECET);
          else
          if((scmEventMOD_CHGID == paEIID) && (func_OR<CIEC_BOOL>(func_EQ(var_ModuleState, 8_USINT), func_EQ(var_ModuleState, 9_USINT)))) enterStateOff(paECET);
          else return; //no transition cleared
          break;
        case scmStateInit:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStateSample:
          if(var_Publish) enterStatePublish(paECET);
          else
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStatePublish:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStateRefresh:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStateCmd:
          if(1) enterStateBreak(paECET);
          else return; //no transition cleared
          break;
        case scmStateOff:
          if(1) enterStateBreak(paECET);
          else return; //no transition cleared
          break;
        case scmStateBreak:
          if(1) enterStateBreakW(paECET);
          else return; //no transition cleared
          break;
        case scmStateMake:
          if(1) enterStateMakeW(paECET);
          else return; //no transition cleared
          break;
        case scmStateBreakW:
          if(scmEventDRIVENID == paEIID) enterStateMake(paECET);
          else
          if(scmEventCMDID == paEIID) enterStateQueueB(paECET);
          else
          if((scmEventRELEASEID == paEIID) && (func_AND<CIEC_BOOL>(func_EQ(var_R_Holder, var_Holder), func_NE(var_Holder, u""_WSTRING)))) enterStateOffB(paECET);
          else
          if((scmEventMOD_CHGID == paEIID) && (func_OR<CIEC_BOOL>(func_EQ(var_ModuleState, 8_USINT), func_EQ(var_ModuleState, 9_USINT)))) enterStateOffB(paECET);
          else return; //no transition cleared
          break;
        case scmStateMakeW:
          if(scmEventDRIVENID == paEIID) enterStateSettled(paECET);
          else
          if(scmEventCMDID == paEIID) enterStateQueueM(paECET);
          else
          if((scmEventRELEASEID == paEIID) && (func_AND<CIEC_BOOL>(func_EQ(var_R_Holder, var_Holder), func_NE(var_Holder, u""_WSTRING)))) enterStateOffM(paECET);
          else
          if((scmEventMOD_CHGID == paEIID) && (func_OR<CIEC_BOOL>(func_EQ(var_ModuleState, 8_USINT), func_EQ(var_ModuleState, 9_USINT)))) enterStateOffM(paECET);
          else return; //no transition cleared
          break;
        case scmStateQueueB:
          if(1) enterStateBreakW(paECET);
          else return; //no transition cleared
          break;
        case scmStateOffB:
          if(1) enterStateBreakW(paECET);
          else return; //no transition cleared
          break;
        case scmStateQueueM:
          if(1) enterStateMakeW(paECET);
          else return; //no transition cleared
          break;
        case scmStateOffM:
          if(1) enterStateMakeW(paECET);
          else return; //no transition cleared
          break;
        case scmStateCmdPend:
          if(func_OR<CIEC_BOOL>(func_EQ(var_Holder, u""_WSTRING), func_EQ(var_C_Holder, var_Holder))) enterStateCmd(paECET);
          else
          if(1) enterStateReport(paECET);
          else return; //no transition cleared
          break;
        case scmStateSettled:
          if(var_OffPending) enterStateOff(paECET);
          else
          if(var_Pending) enterStateCmdPend(paECET);
          else
          if(1) enterStateReport(paECET);
          else return; //no transition cleared
          break;
        case scmStateReport:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        default:
          DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 18.", mECCState.operator TForteUInt16 ());
          mECCState = 0; // 0 is always the initial state
          return;
      }
      paEIID = cgInvalidEventID; // we have to clear the event after the first check in order to ensure correct behavior
    } while(true);
  }

  void FORTE_EL_Scale::enterStateSTART(CEventChainExecutionThread *const) {
    mECCState = scmStateSTART;
  }

  void FORTE_EL_Scale::enterStateInit(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateInit;
    alg_Alg_Init();
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_EL_Scale::enterStateSample(CEventChainExecutionThread *const) {
    mECCState = scmStateSample;
    alg_Alg_Sample();
  }

  void FORTE_EL_Scale::enterStatePublish(CEventChainExecutionThread *const paECET) {
    mECCState = scmStatePublish;
    alg_Alg_Publish();
    sendOutputEvent(scmEventSTATEID, paECET);
  }

  void FORTE_EL_Scale::enterStateRefresh(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateRefresh;
    sendOutputEvent(scmEventDRIVEID, paECET);
  }

  void FORTE_EL_Scale::enterStateCmd(CEventChainExecutionThread *const) {
    mECCState = scmStateCmd;
    alg_Alg_Cmd();
  }

  void FORTE_EL_Scale::enterStateOff(CEventChainExecutionThread *const) {
    mECCState = scmStateOff;
    alg_Alg_Off();
  }

  void FORTE_EL_Scale::enterStateBreak(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateBreak;
    sendOutputEvent(scmEventDRIVEID, paECET);
  }

  void FORTE_EL_Scale::enterStateMake(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateMake;
    sendOutputEvent(scmEventDRIVEID, paECET);
  }

  void FORTE_EL_Scale::enterStateBreakW(CEventChainExecutionThread *const) {
    mECCState = scmStateBreakW;
  }

  void FORTE_EL_Scale::enterStateMakeW(CEventChainExecutionThread *const) {
    mECCState = scmStateMakeW;
  }

  void FORTE_EL_Scale::enterStateQueueB(CEventChainExecutionThread *const) {
    mECCState = scmStateQueueB;
    alg_Alg_QueueB();
  }

  void FORTE_EL_Scale::enterStateOffB(CEventChainExecutionThread *const) {
    mECCState = scmStateOffB;
    alg_Alg_OffB();
  }

  void FORTE_EL_Scale::enterStateQueueM(CEventChainExecutionThread *const) {
    mECCState = scmStateQueueM;
    alg_Alg_QueueM();
  }

  void FORTE_EL_Scale::enterStateOffM(CEventChainExecutionThread *const) {
    mECCState = scmStateOffM;
    alg_Alg_OffM();
  }

  void FORTE_EL_Scale::enterStateCmdPend(CEventChainExecutionThread *const) {
    mECCState = scmStateCmdPend;
    alg_Alg_CmdPend();
  }

  void FORTE_EL_Scale::enterStateSettled(CEventChainExecutionThread *const) {
    mECCState = scmStateSettled;
  }

  void FORTE_EL_Scale::enterStateReport(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateReport;
    alg_Alg_Report();
    sendOutputEvent(scmEventSTATEID, paECET);
  }

  void FORTE_EL_Scale::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, var_Module, conn_Module);
        readData(1, var_Name, conn_Name);
        readData(2, var_UaRoot, conn_UaRoot);
        break;
      }
      case scmEventCMDID: {
        readData(3, var_C_Holder, conn_C_Holder);
        readData(4, var_C_Release, conn_C_Release);
        break;
      }
      case scmEventRELEASEID: {
        readData(5, var_R_Holder, conn_R_Holder);
        break;
      }
      case scmEventSAMPLEID: {
        readData(6, var_I_Weight, conn_I_Weight);
        break;
      }
      case scmEventMOD_CHGID: {
        readData(7, var_ModuleState, conn_ModuleState);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_EL_Scale::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(8, var_IdCmd, conn_IdCmd);
        writeData(9, var_IdRelease, conn_IdRelease);
        writeData(10, var_IdState, conn_IdState);
        writeData(11, var_IdPub, conn_IdPub);
        break;
      }
      case scmEventSTATEID: {
        writeData(12, var_Weight, conn_Weight);
        writeData(13, var_Holder, conn_Holder);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_EL_Scale::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Module;
      case 1: return &var_Name;
      case 2: return &var_UaRoot;
      case 3: return &var_C_Holder;
      case 4: return &var_C_Release;
      case 5: return &var_R_Holder;
      case 6: return &var_I_Weight;
      case 7: return &var_ModuleState;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_EL_Scale::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_IdCmd;
      case 1: return &var_IdRelease;
      case 2: return &var_IdState;
      case 3: return &var_IdPub;
      case 4: return &var_Weight;
      case 5: return &var_Holder;
    }
    return nullptr;
  }

  CEventConnection *FORTE_EL_Scale::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_DRIVE;
      case 2: return &conn_STATE;
    }
    return nullptr;
  }

  CDataConnection **FORTE_EL_Scale::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Module;
      case 1: return &conn_Name;
      case 2: return &conn_UaRoot;
      case 3: return &conn_C_Holder;
      case 4: return &conn_C_Release;
      case 5: return &conn_R_Holder;
      case 6: return &conn_I_Weight;
      case 7: return &conn_ModuleState;
    }
    return nullptr;
  }

  CDataConnection *FORTE_EL_Scale::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_IdCmd;
      case 1: return &conn_IdRelease;
      case 2: return &conn_IdState;
      case 3: return &conn_IdPub;
      case 4: return &conn_Weight;
      case 5: return &conn_Holder;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_EL_Scale::getVarInternal(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Publish;
      case 1: return &var_Beat;
      case 2: return &var_LastHolder;
      case 3: return &var_Pending;
      case 4: return &var_OffPending;
      case 5: return &var_L_Weight;
    }
    return nullptr;
  }

  void FORTE_EL_Scale::alg_Alg_Init(void) {

    #line 2 "EL_Scale.fbt"
    var_IdCmd = func_CONCAT(func_CONCAT(func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/"_WSTRING), var_Name), u"/cmd]"_WSTRING);
    #line 3 "EL_Scale.fbt"
    var_IdRelease = func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/release]"_WSTRING);
    #line 4 "EL_Scale.fbt"
    var_IdState = func_CONCAT(func_CONCAT(func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/"_WSTRING), var_Name), u"/state]"_WSTRING);
    #line 5 "EL_Scale.fbt"
    var_IdPub = func_CONCAT(func_CONCAT(func_CONCAT(func_CONCAT(func_CONCAT(u"opc_ua[WRITE;"_WSTRING, var_UaRoot), u"/Equipment/"_WSTRING), var_Name), u"/Weight"_WSTRING), u"]"_WSTRING);
  }

  void FORTE_EL_Scale::alg_Alg_Sample(void) {

    #line 9 "EL_Scale.fbt"
    var_Weight = var_I_Weight;
    #line 10 "EL_Scale.fbt"
    var_Publish = func_OR<CIEC_BOOL>(func_OR<CIEC_BOOL>(func_NE(var_Weight, var_L_Weight), func_NE(var_Holder, var_LastHolder)), func_GE(var_Beat, 20_USINT));
    #line 11 "EL_Scale.fbt"
    var_Beat = func_ADD<CIEC_USINT>(var_Beat, 1_USINT);
  }

  void FORTE_EL_Scale::alg_Alg_Publish(void) {

    #line 15 "EL_Scale.fbt"
    var_L_Weight = var_Weight;
    #line 16 "EL_Scale.fbt"
    var_LastHolder = var_Holder;
    #line 17 "EL_Scale.fbt"
    var_Beat = 0_USINT;
  }

  void FORTE_EL_Scale::alg_Alg_Cmd(void) {

    #line 21 "EL_Scale.fbt"
    var_Holder = var_C_Holder;
    #line 22 "EL_Scale.fbt"
    if (var_C_Release) {
      #line 23 "EL_Scale.fbt"
      var_Holder = u""_WSTRING;
    }
  }

  void FORTE_EL_Scale::alg_Alg_Off(void) {

    #line 28 "EL_Scale.fbt"
    var_Holder = u""_WSTRING;
    #line 29 "EL_Scale.fbt"
    var_OffPending = false_BOOL;
  }

  void FORTE_EL_Scale::alg_Alg_QueueB(void) {

    #line 33 "EL_Scale.fbt"
    var_Pending = true_BOOL;
  }

  void FORTE_EL_Scale::alg_Alg_OffB(void) {

    #line 37 "EL_Scale.fbt"
    var_OffPending = true_BOOL;
  }

  void FORTE_EL_Scale::alg_Alg_QueueM(void) {

    #line 41 "EL_Scale.fbt"
    var_Pending = true_BOOL;
  }

  void FORTE_EL_Scale::alg_Alg_OffM(void) {

    #line 45 "EL_Scale.fbt"
    var_OffPending = true_BOOL;
  }

  void FORTE_EL_Scale::alg_Alg_CmdPend(void) {

    #line 49 "EL_Scale.fbt"
    var_Pending = false_BOOL;
  }

  void FORTE_EL_Scale::alg_Alg_Report(void) {

    #line 53 "EL_Scale.fbt"
    var_LastHolder = var_Holder;
    #line 54 "EL_Scale.fbt"
    var_Beat = 0_USINT;
  }

}