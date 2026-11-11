/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SKILL_Control
 *** Description: The skill's state machine inside SKILL_Core: what Start, Stop, Abort and Reset do in each state. A client's command reaches it only once SKILL_Gate has accepted it, so here a command is the same from a client or from a parent. Technical: Skill state machine: START, HALT, ABORT, RESET (a client's already decided by SKILL_Gate); Idle 0, Running 1, Stopping 2, Succeeded 3, Failed 4, Aborted 5; RUN starts the execution (CalledByClient: with the Start arguments, else with the parent's values)
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/SKILL_Control_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_int.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"
#include "forte/iec61131_functions/func_CONCAT.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:gg-aRzQZ_DSwTFY0ODKB58bH_Vk5foIyBYz4Rr1yC9g79Dm-fqnW3w68Ug2DcRYG2hcr1CVERWqVIeCJd3j3Yw=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "START"_STRID, "HALT"_STRID, "ABORT"_STRID, "RESET"_STRID, "EXECUTE_DONE"_STRID, "EXECUTE_FAILED"_STRID, "STOPPING_DONE"_STRID, "TO_IDLE"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "PUB"_STRID, "RUN"_STRID, "HALT_SEQ"_STRID, "ABORT_SEQ"_STRID, "RESET_SEQ"_STRID, "RUN_STOPPING"_STRID, "SUCCESS"_STRID, "FAILURE"_STRID, "RELEASE"_STRID, "ACT"_STRID, "TO_IDLE_START"_STRID, "TO_IDLE_STOP"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"Module"_STRID, "UaRoot"_STRID, "UaPath"_STRID, "ByClient"_STRID, "ExecuteError"_STRID};
    const auto cDataOutputNames = std::array{"StartMethodId"_STRID, "StopMethodId"_STRID, "AbortMethodId"_STRID, "ResetMethodId"_STRID, "StateId"_STRID, "ActivityId"_STRID, "ReleaseId"_STRID, "State"_STRID, "ErrorID"_STRID, "ActivityDelta"_STRID, "CalledByClient"_STRID};
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

    const auto cInternalsNames = std::array{"Active"_STRID};
  }

  DEFINE_FIRMWARE_FB(FORTE_SKILL_Control, "modlib::SKILL_Control"_STRID, TypeHash)

  FORTE_SKILL_Control::FORTE_SKILL_Control(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CBasicFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cInternalsNames),
      var_Active(0_BOOL),
      var_Module(u""_WSTRING),
      var_UaRoot(u""_WSTRING),
      var_UaPath(u""_WSTRING),
      var_ByClient(0_BOOL),
      var_ExecuteError(0_UINT),
      var_StartMethodId(u""_WSTRING),
      var_StopMethodId(u""_WSTRING),
      var_AbortMethodId(u""_WSTRING),
      var_ResetMethodId(u""_WSTRING),
      var_StateId(u""_WSTRING),
      var_ActivityId(u""_WSTRING),
      var_ReleaseId(u""_WSTRING),
      var_State(0_USINT),
      var_ErrorID(0_UINT),
      var_ActivityDelta(0_INT),
      var_CalledByClient(0_BOOL),
      conn_INITO(*this, 0),
      conn_PUB(*this, 1),
      conn_RUN(*this, 2),
      conn_HALT_SEQ(*this, 3),
      conn_ABORT_SEQ(*this, 4),
      conn_RESET_SEQ(*this, 5),
      conn_RUN_STOPPING(*this, 6),
      conn_SUCCESS(*this, 7),
      conn_FAILURE(*this, 8),
      conn_RELEASE(*this, 9),
      conn_ACT(*this, 10),
      conn_TO_IDLE_START(*this, 11),
      conn_TO_IDLE_STOP(*this, 12),
      conn_Module(nullptr),
      conn_UaRoot(nullptr),
      conn_UaPath(nullptr),
      conn_ByClient(nullptr),
      conn_ExecuteError(nullptr),
      conn_StartMethodId(*this, 0, var_StartMethodId),
      conn_StopMethodId(*this, 1, var_StopMethodId),
      conn_AbortMethodId(*this, 2, var_AbortMethodId),
      conn_ResetMethodId(*this, 3, var_ResetMethodId),
      conn_StateId(*this, 4, var_StateId),
      conn_ActivityId(*this, 5, var_ActivityId),
      conn_ReleaseId(*this, 6, var_ReleaseId),
      conn_State(*this, 7, var_State),
      conn_ErrorID(*this, 8, var_ErrorID),
      conn_ActivityDelta(*this, 9, var_ActivityDelta),
      conn_CalledByClient(*this, 10, var_CalledByClient) {
  }

  void FORTE_SKILL_Control::setInitialValues() {
    CBasicFB::setInitialValues();
    var_Active = 0_BOOL;
    var_Module = u""_WSTRING;
    var_UaRoot = u""_WSTRING;
    var_UaPath = u""_WSTRING;
    var_ByClient = 0_BOOL;
    var_ExecuteError = 0_UINT;
    var_StartMethodId = u""_WSTRING;
    var_StopMethodId = u""_WSTRING;
    var_AbortMethodId = u""_WSTRING;
    var_ResetMethodId = u""_WSTRING;
    var_StateId = u""_WSTRING;
    var_ActivityId = u""_WSTRING;
    var_ReleaseId = u""_WSTRING;
    var_State = 0_USINT;
    var_ErrorID = 0_UINT;
    var_ActivityDelta = 0_INT;
    var_CalledByClient = 0_BOOL;
  }

  void FORTE_SKILL_Control::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
    do {
      switch(mECCState) {
        case scmStateSTART:
          if(scmEventINITID == paEIID) enterStateInit(paECET);
          else return; //no transition cleared
          break;
        case scmStateInit:
          if(1) enterStateIdle(paECET);
          else return; //no transition cleared
          break;
        case scmStateIdle:
          if(scmEventSTARTID == paEIID) enterStateGo(paECET);
          else
          if(scmEventABORTID == paEIID) enterStateAbortChk(paECET);
          else return; //no transition cleared
          break;
        case scmStateRunning:
          if(scmEventEXECUTE_DONEID == paEIID) enterStateSucceed(paECET);
          else
          if(scmEventEXECUTE_FAILEDID == paEIID) enterStateFail(paECET);
          else
          if(scmEventHALTID == paEIID) enterStateHalt(paECET);
          else
          if(scmEventABORTID == paEIID) enterStateAbortChk(paECET);
          else return; //no transition cleared
          break;
        case scmStateStopping:
          if(scmEventEXECUTE_DONEID == paEIID) enterStateRunStop(paECET);
          else
          if(scmEventEXECUTE_FAILEDID == paEIID) enterStateRunStop(paECET);
          else
          if(scmEventABORTID == paEIID) enterStateAbortChk(paECET);
          else return; //no transition cleared
          break;
        case scmStateStopProc:
          if(scmEventSTOPPING_DONEID == paEIID) enterStateInterrupted(paECET);
          else
          if(scmEventABORTID == paEIID) enterStateAbortChk(paECET);
          else return; //no transition cleared
          break;
        case scmStateSucceeded:
          if(scmEventSTARTID == paEIID) enterStateGo(paECET);
          else
          if(scmEventABORTID == paEIID) enterStateAbortChk(paECET);
          else
          if(scmEventTO_IDLEID == paEIID) enterStateIdle(paECET);
          else return; //no transition cleared
          break;
        case scmStateFailed:
          if(scmEventSTARTID == paEIID) enterStateGo(paECET);
          else
          if(scmEventABORTID == paEIID) enterStateAbortChk(paECET);
          else return; //no transition cleared
          break;
        case scmStateAborted:
          if(scmEventSTARTID == paEIID) enterStateStartRefused(paECET);
          else
          if(scmEventRESETID == paEIID) enterStateResetOk(paECET);
          else return; //no transition cleared
          break;
        case scmStateGo:
          if(1) enterStateRunning(paECET);
          else return; //no transition cleared
          break;
        case scmStateHalt:
          if(1) enterStateStopping(paECET);
          else return; //no transition cleared
          break;
        case scmStateRunStop:
          if(1) enterStateStopProc(paECET);
          else return; //no transition cleared
          break;
        case scmStateSucceed:
          if(1) enterStateSucceeded(paECET);
          else return; //no transition cleared
          break;
        case scmStateFail:
          if(1) enterStateFailed(paECET);
          else return; //no transition cleared
          break;
        case scmStateInterrupted:
          if(1) enterStateFailed(paECET);
          else return; //no transition cleared
          break;
        case scmStateAbortChk:
          if(var_Active) enterStateAbortActive(paECET);
          else
          if(1) enterStateAbortIdle(paECET);
          else return; //no transition cleared
          break;
        case scmStateAbortActive:
          if(1) enterStateAborted(paECET);
          else return; //no transition cleared
          break;
        case scmStateAbortIdle:
          if(1) enterStateAborted(paECET);
          else return; //no transition cleared
          break;
        case scmStateStartRefused:
          if(1) enterStateAborted(paECET);
          else return; //no transition cleared
          break;
        case scmStateResetOk:
          if(1) enterStateIdle(paECET);
          else return; //no transition cleared
          break;
        default:
          DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 20.", mECCState.operator TForteUInt16 ());
          mECCState = 0; // 0 is always the initial state
          return;
      }
      paEIID = cgInvalidEventID; // we have to clear the event after the first check in order to ensure correct behavior
    } while(true);
  }

  void FORTE_SKILL_Control::enterStateSTART(CEventChainExecutionThread *const) {
    mECCState = scmStateSTART;
  }

  void FORTE_SKILL_Control::enterStateInit(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateInit;
    alg_Alg_Init();
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_SKILL_Control::enterStateIdle(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateIdle;
    alg_Alg_Idle();
    sendOutputEvent(scmEventPUBID, paECET);
  }

  void FORTE_SKILL_Control::enterStateRunning(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateRunning;
    alg_Alg_Running();
    sendOutputEvent(scmEventPUBID, paECET);
  }

  void FORTE_SKILL_Control::enterStateStopping(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateStopping;
    alg_Alg_Stopping();
    sendOutputEvent(scmEventPUBID, paECET);
  }

  void FORTE_SKILL_Control::enterStateStopProc(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateStopProc;
    alg_Alg_StopProc();
    sendOutputEvent(scmEventPUBID, paECET);
  }

  void FORTE_SKILL_Control::enterStateSucceeded(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateSucceeded;
    alg_Alg_Succeeded();
    sendOutputEvent(scmEventPUBID, paECET);
    sendOutputEvent(scmEventTO_IDLE_STARTID, paECET);
  }

  void FORTE_SKILL_Control::enterStateFailed(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateFailed;
    alg_Alg_Failed();
    sendOutputEvent(scmEventPUBID, paECET);
  }

  void FORTE_SKILL_Control::enterStateAborted(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateAborted;
    alg_Alg_Aborted();
    sendOutputEvent(scmEventPUBID, paECET);
  }

  void FORTE_SKILL_Control::enterStateGo(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateGo;
    alg_Alg_Go();
    sendOutputEvent(scmEventACTID, paECET);
    sendOutputEvent(scmEventTO_IDLE_STOPID, paECET);
    sendOutputEvent(scmEventRUNID, paECET);
  }

  void FORTE_SKILL_Control::enterStateHalt(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateHalt;
    sendOutputEvent(scmEventHALT_SEQID, paECET);
  }

  void FORTE_SKILL_Control::enterStateRunStop(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateRunStop;
    sendOutputEvent(scmEventRUN_STOPPINGID, paECET);
  }

  void FORTE_SKILL_Control::enterStateSucceed(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateSucceed;
    alg_Alg_Succeed();
    sendOutputEvent(scmEventACTID, paECET);
    sendOutputEvent(scmEventRELEASEID, paECET);
    sendOutputEvent(scmEventSUCCESSID, paECET);
  }

  void FORTE_SKILL_Control::enterStateFail(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateFail;
    alg_Alg_Fail();
    sendOutputEvent(scmEventACTID, paECET);
    sendOutputEvent(scmEventRELEASEID, paECET);
    sendOutputEvent(scmEventFAILUREID, paECET);
  }

  void FORTE_SKILL_Control::enterStateInterrupted(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateInterrupted;
    alg_Alg_Interrupted();
    sendOutputEvent(scmEventACTID, paECET);
    sendOutputEvent(scmEventRELEASEID, paECET);
    sendOutputEvent(scmEventFAILUREID, paECET);
  }

  void FORTE_SKILL_Control::enterStateAbortChk(CEventChainExecutionThread *const) {
    mECCState = scmStateAbortChk;
  }

  void FORTE_SKILL_Control::enterStateAbortActive(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateAbortActive;
    alg_Alg_AbortActive();
    sendOutputEvent(scmEventABORT_SEQID, paECET);
    sendOutputEvent(scmEventACTID, paECET);
    sendOutputEvent(scmEventRELEASEID, paECET);
  }

  void FORTE_SKILL_Control::enterStateAbortIdle(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateAbortIdle;
    sendOutputEvent(scmEventABORT_SEQID, paECET);
  }

  void FORTE_SKILL_Control::enterStateStartRefused(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateStartRefused;
    alg_Alg_StartRefused();
    sendOutputEvent(scmEventFAILUREID, paECET);
  }

  void FORTE_SKILL_Control::enterStateResetOk(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateResetOk;
    sendOutputEvent(scmEventRESET_SEQID, paECET);
  }

  void FORTE_SKILL_Control::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, var_Module, conn_Module);
        readData(1, var_UaRoot, conn_UaRoot);
        readData(2, var_UaPath, conn_UaPath);
        break;
      }
      case scmEventSTARTID: {
        readData(3, var_ByClient, conn_ByClient);
        break;
      }
      case scmEventEXECUTE_FAILEDID: {
        readData(4, var_ExecuteError, conn_ExecuteError);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_SKILL_Control::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(5, var_StartMethodId, conn_StartMethodId);
        writeData(6, var_StopMethodId, conn_StopMethodId);
        writeData(7, var_AbortMethodId, conn_AbortMethodId);
        writeData(8, var_ResetMethodId, conn_ResetMethodId);
        writeData(9, var_StateId, conn_StateId);
        writeData(10, var_ActivityId, conn_ActivityId);
        writeData(11, var_ReleaseId, conn_ReleaseId);
        break;
      }
      case scmEventPUBID: {
        writeData(12, var_State, conn_State);
        writeData(13, var_ErrorID, conn_ErrorID);
        break;
      }
      case scmEventRUNID: {
        writeData(15, var_CalledByClient, conn_CalledByClient);
        break;
      }
      case scmEventFAILUREID: {
        writeData(13, var_ErrorID, conn_ErrorID);
        break;
      }
      case scmEventACTID: {
        writeData(14, var_ActivityDelta, conn_ActivityDelta);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_SKILL_Control::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Module;
      case 1: return &var_UaRoot;
      case 2: return &var_UaPath;
      case 3: return &var_ByClient;
      case 4: return &var_ExecuteError;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SKILL_Control::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_StartMethodId;
      case 1: return &var_StopMethodId;
      case 2: return &var_AbortMethodId;
      case 3: return &var_ResetMethodId;
      case 4: return &var_StateId;
      case 5: return &var_ActivityId;
      case 6: return &var_ReleaseId;
      case 7: return &var_State;
      case 8: return &var_ErrorID;
      case 9: return &var_ActivityDelta;
      case 10: return &var_CalledByClient;
    }
    return nullptr;
  }

  CEventConnection *FORTE_SKILL_Control::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_PUB;
      case 2: return &conn_RUN;
      case 3: return &conn_HALT_SEQ;
      case 4: return &conn_ABORT_SEQ;
      case 5: return &conn_RESET_SEQ;
      case 6: return &conn_RUN_STOPPING;
      case 7: return &conn_SUCCESS;
      case 8: return &conn_FAILURE;
      case 9: return &conn_RELEASE;
      case 10: return &conn_ACT;
      case 11: return &conn_TO_IDLE_START;
      case 12: return &conn_TO_IDLE_STOP;
    }
    return nullptr;
  }

  CDataConnection **FORTE_SKILL_Control::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Module;
      case 1: return &conn_UaRoot;
      case 2: return &conn_UaPath;
      case 3: return &conn_ByClient;
      case 4: return &conn_ExecuteError;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SKILL_Control::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_StartMethodId;
      case 1: return &conn_StopMethodId;
      case 2: return &conn_AbortMethodId;
      case 3: return &conn_ResetMethodId;
      case 4: return &conn_StateId;
      case 5: return &conn_ActivityId;
      case 6: return &conn_ReleaseId;
      case 7: return &conn_State;
      case 8: return &conn_ErrorID;
      case 9: return &conn_ActivityDelta;
      case 10: return &conn_CalledByClient;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SKILL_Control::getVarInternal(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Active;
    }
    return nullptr;
  }

  void FORTE_SKILL_Control::alg_Alg_Init(void) {

    #line 2 "SKILL_Control.fbt"
    var_StartMethodId = func_CONCAT(func_CONCAT(func_CONCAT(u"opc_ua[CREATE_METHOD;"_WSTRING, func_CONCAT(var_UaRoot, var_UaPath)), u"/Start"_WSTRING), u"]"_WSTRING);
    #line 3 "SKILL_Control.fbt"
    var_StopMethodId = func_CONCAT(func_CONCAT(func_CONCAT(u"opc_ua[CREATE_METHOD;"_WSTRING, func_CONCAT(var_UaRoot, var_UaPath)), u"/Stop"_WSTRING), u"]"_WSTRING);
    #line 4 "SKILL_Control.fbt"
    var_AbortMethodId = func_CONCAT(func_CONCAT(func_CONCAT(u"opc_ua[CREATE_METHOD;"_WSTRING, func_CONCAT(var_UaRoot, var_UaPath)), u"/Abort"_WSTRING), u"]"_WSTRING);
    #line 5 "SKILL_Control.fbt"
    var_ResetMethodId = func_CONCAT(func_CONCAT(func_CONCAT(u"opc_ua[CREATE_METHOD;"_WSTRING, func_CONCAT(var_UaRoot, var_UaPath)), u"/Reset"_WSTRING), u"]"_WSTRING);
    #line 6 "SKILL_Control.fbt"
    var_StateId = func_CONCAT(func_CONCAT(func_CONCAT(func_CONCAT(func_CONCAT(u"opc_ua[WRITE;"_WSTRING, func_CONCAT(var_UaRoot, var_UaPath)), u"/State;"_WSTRING), func_CONCAT(var_UaRoot, var_UaPath)), u"/ErrorID"_WSTRING), u"]"_WSTRING);
    #line 7 "SKILL_Control.fbt"
    var_ActivityId = func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/activity]"_WSTRING);
    #line 8 "SKILL_Control.fbt"
    var_ReleaseId = func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/release]"_WSTRING);
  }

  void FORTE_SKILL_Control::alg_Alg_Idle(void) {

    #line 12 "SKILL_Control.fbt"
    var_State = 0_USINT;
  }

  void FORTE_SKILL_Control::alg_Alg_Running(void) {

    #line 16 "SKILL_Control.fbt"
    var_State = 1_USINT;
  }

  void FORTE_SKILL_Control::alg_Alg_Stopping(void) {

    #line 20 "SKILL_Control.fbt"
    var_State = 2_USINT;
  }

  void FORTE_SKILL_Control::alg_Alg_StopProc(void) {

    #line 24 "SKILL_Control.fbt"
    var_State = 2_USINT;
  }

  void FORTE_SKILL_Control::alg_Alg_Succeeded(void) {

    #line 28 "SKILL_Control.fbt"
    var_State = 3_USINT;
  }

  void FORTE_SKILL_Control::alg_Alg_Failed(void) {

    #line 32 "SKILL_Control.fbt"
    var_State = 4_USINT;
  }

  void FORTE_SKILL_Control::alg_Alg_Aborted(void) {

    #line 36 "SKILL_Control.fbt"
    var_State = 5_USINT;
  }

  void FORTE_SKILL_Control::alg_Alg_Go(void) {

    #line 40 "SKILL_Control.fbt"
    var_Active = true_BOOL;
    #line 41 "SKILL_Control.fbt"
    var_ActivityDelta = 1_INT;
    #line 42 "SKILL_Control.fbt"
    var_ErrorID = 0_UINT;
    #line 43 "SKILL_Control.fbt"
    var_CalledByClient = var_ByClient;
  }

  void FORTE_SKILL_Control::alg_Alg_Succeed(void) {

    #line 47 "SKILL_Control.fbt"
    var_Active = false_BOOL;
    #line 48 "SKILL_Control.fbt"
    var_ActivityDelta = -1_INT;
    #line 49 "SKILL_Control.fbt"
    var_ErrorID = 0_UINT;
  }

  void FORTE_SKILL_Control::alg_Alg_Fail(void) {

    #line 53 "SKILL_Control.fbt"
    var_Active = false_BOOL;
    #line 54 "SKILL_Control.fbt"
    var_ActivityDelta = -1_INT;
    #line 55 "SKILL_Control.fbt"
    var_ErrorID = var_ExecuteError;
  }

  void FORTE_SKILL_Control::alg_Alg_Interrupted(void) {

    #line 59 "SKILL_Control.fbt"
    var_Active = false_BOOL;
    #line 60 "SKILL_Control.fbt"
    var_ActivityDelta = -1_INT;
    #line 61 "SKILL_Control.fbt"
    var_ErrorID = 7_UINT;
  }

  void FORTE_SKILL_Control::alg_Alg_AbortActive(void) {

    #line 65 "SKILL_Control.fbt"
    var_Active = false_BOOL;
    #line 66 "SKILL_Control.fbt"
    var_ActivityDelta = -1_INT;
    #line 67 "SKILL_Control.fbt"
    var_ErrorID = 7_UINT;
  }

  void FORTE_SKILL_Control::alg_Alg_StartRefused(void) {

    #line 71 "SKILL_Control.fbt"
    var_ErrorID = 4_UINT;
  }

}