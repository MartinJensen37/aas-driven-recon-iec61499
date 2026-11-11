/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SKILL_Gate
 *** Description: The front desk of a skill, inside SKILL_Core: answers a client's Start, Stop, Abort or Reset at once (only the module's owner; Start only with the module in Execute, the skill not running, the values in range and the equipment free) and passes an accepted command on to SKILL_Control, as a parent's command is passed on. Technical: Decides a client's Start/Stop/Abort/Reset (owner only; Start only in module Execute, not running, parameters in range, equipment free) and passes accepted ones and a parent's on as GO_START, GO_HALT, GO_ABORT, GO_RESET to SKILL_Control
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/SKILL_Gate_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"
#include "forte/iec61131_functions/func_AND.h"
#include "forte/iec61131_functions/func_EQ.h"
#include "forte/iec61131_functions/func_NE.h"
#include "forte/iec61131_functions/func_NOT.h"
#include "forte/iec61131_functions/func_OR.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:MJbWK6ft8dm52wHsM6s-C4UxSa169gAQjo3FWB3WwwhuHWl6AaYXv1ZBxCwjfCEsesBWJoO44vBRRlgWEeMfYA=="sv;

    const auto cEventInputNames = std::array{"START_REQ"_STRID, "STOP_REQ"_STRID, "ABORT_REQ"_STRID, "RESET_REQ"_STRID, "OWNER_CHG"_STRID, "MOD_CHG"_STRID, "SKILL_CHG"_STRID, "START"_STRID, "HALT"_STRID, "ABORT"_STRID, "RESET"_STRID};
    const auto cEventOutputNames = std::array{"START_RSP"_STRID, "STOP_RSP"_STRID, "ABORT_RSP"_STRID, "RESET_RSP"_STRID, "GO_START"_STRID, "GO_HALT"_STRID, "GO_ABORT"_STRID, "GO_RESET"_STRID};
    const auto cDataInputNames = std::array{"Session"_STRID, "ParamsInRange"_STRID, "EquipmentFree"_STRID, "StopSession"_STRID, "AbortSession"_STRID, "ResetSession"_STRID, "Owner"_STRID, "ModuleState"_STRID, "State"_STRID};
    const auto cDataOutputNames = std::array{"Accepted"_STRID, "ResponseError"_STRID, "ByClient"_STRID};
    const SFBInterfaceSpec cFBInterfaceSpec = {
        .mEINames = cEventInputNames,
        .mEITypeNames = {},
        .mEONames = cEventOutputNames,
        .mEOTypeNames = {},
        .mDINames = cDataInputNames,
        .mDONames = cDataOutputNames,
        .mDIONames = {},
        .mSocketNames = {},
        .mPlugNames = {},
    };

    const auto cInternalsNames = std::array{"Owned"_STRID};
  }

  DEFINE_FIRMWARE_FB(FORTE_SKILL_Gate, "modlib::SKILL_Gate"_STRID, TypeHash)

  FORTE_SKILL_Gate::FORTE_SKILL_Gate(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CBasicFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cInternalsNames),
      var_Owned(0_BOOL),
      var_Session(u""_WSTRING),
      var_ParamsInRange(0_BOOL),
      var_EquipmentFree(0_BOOL),
      var_StopSession(u""_WSTRING),
      var_AbortSession(u""_WSTRING),
      var_ResetSession(u""_WSTRING),
      var_Owner(u""_WSTRING),
      var_ModuleState(0_USINT),
      var_State(0_USINT),
      var_Accepted(0_BOOL),
      var_ResponseError(0_UINT),
      var_ByClient(0_BOOL),
      conn_START_RSP(*this, 0),
      conn_STOP_RSP(*this, 1),
      conn_ABORT_RSP(*this, 2),
      conn_RESET_RSP(*this, 3),
      conn_GO_START(*this, 4),
      conn_GO_HALT(*this, 5),
      conn_GO_ABORT(*this, 6),
      conn_GO_RESET(*this, 7),
      conn_Session(nullptr),
      conn_ParamsInRange(nullptr),
      conn_EquipmentFree(nullptr),
      conn_StopSession(nullptr),
      conn_AbortSession(nullptr),
      conn_ResetSession(nullptr),
      conn_Owner(nullptr),
      conn_ModuleState(nullptr),
      conn_State(nullptr),
      conn_Accepted(*this, 0, var_Accepted),
      conn_ResponseError(*this, 1, var_ResponseError),
      conn_ByClient(*this, 2, var_ByClient) {
  }

  void FORTE_SKILL_Gate::setInitialValues() {
    CBasicFB::setInitialValues();
    var_Owned = 0_BOOL;
    var_Session = u""_WSTRING;
    var_ParamsInRange = 0_BOOL;
    var_EquipmentFree = 0_BOOL;
    var_StopSession = u""_WSTRING;
    var_AbortSession = u""_WSTRING;
    var_ResetSession = u""_WSTRING;
    var_Owner = u""_WSTRING;
    var_ModuleState = 0_USINT;
    var_State = 0_USINT;
    var_Accepted = 0_BOOL;
    var_ResponseError = 0_UINT;
    var_ByClient = 0_BOOL;
  }

  void FORTE_SKILL_Gate::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
    do {
      switch(mECCState) {
        case scmStateWait:
          if(scmEventSTART_REQID == paEIID) enterStateChkStart(paECET);
          else
          if(scmEventSTOP_REQID == paEIID) enterStateChkStop(paECET);
          else
          if(scmEventABORT_REQID == paEIID) enterStateChkAbort(paECET);
          else
          if(scmEventRESET_REQID == paEIID) enterStateChkReset(paECET);
          else
          if(scmEventSTARTID == paEIID) enterStateParentStart(paECET);
          else
          if(scmEventHALTID == paEIID) enterStateGoHalt(paECET);
          else
          if(scmEventABORTID == paEIID) enterStateGoAbort(paECET);
          else
          if(scmEventRESETID == paEIID) enterStateGoReset(paECET);
          else
          if((scmEventMOD_CHGID == paEIID) && (func_AND<CIEC_BOOL>(func_OR<CIEC_BOOL>(func_EQ(var_ModuleState, 8_USINT), func_EQ(var_ModuleState, 9_USINT)), func_NE(var_State, 5_USINT)))) enterStateGoAbort(paECET);
          else
          if((scmEventMOD_CHGID == paEIID) && (func_AND<CIEC_BOOL>(func_AND<CIEC_BOOL>(func_EQ(var_ModuleState, 7_USINT), func_EQ(var_State, 1_USINT)), var_ByClient))) enterStateGoHalt(paECET);
          else
          if((scmEventMOD_CHGID == paEIID) && (func_AND<CIEC_BOOL>(func_OR<CIEC_BOOL>(func_EQ(var_ModuleState, 1_USINT), func_EQ(var_ModuleState, 2_USINT)), func_EQ(var_State, 5_USINT)))) enterStateGoReset(paECET);
          else return; //no transition cleared
          break;
        case scmStateChkStart:
          if(var_Accepted) enterStateClientStart(paECET);
          else
          if(1) enterStateWait(paECET);
          else return; //no transition cleared
          break;
        case scmStateChkStop:
          if(var_Accepted) enterStateGoHalt(paECET);
          else
          if(1) enterStateWait(paECET);
          else return; //no transition cleared
          break;
        case scmStateChkAbort:
          if(var_Accepted) enterStateGoAbort(paECET);
          else
          if(1) enterStateWait(paECET);
          else return; //no transition cleared
          break;
        case scmStateChkReset:
          if(var_Accepted) enterStateGoReset(paECET);
          else
          if(1) enterStateWait(paECET);
          else return; //no transition cleared
          break;
        case scmStateClientStart:
          if(1) enterStateWait(paECET);
          else return; //no transition cleared
          break;
        case scmStateParentStart:
          if(1) enterStateWait(paECET);
          else return; //no transition cleared
          break;
        case scmStateGoHalt:
          if(1) enterStateWait(paECET);
          else return; //no transition cleared
          break;
        case scmStateGoAbort:
          if(1) enterStateWait(paECET);
          else return; //no transition cleared
          break;
        case scmStateGoReset:
          if(1) enterStateWait(paECET);
          else return; //no transition cleared
          break;
        default:
          DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 10.", mECCState.operator TForteUInt16 ());
          mECCState = 0; // 0 is always the initial state
          return;
      }
      paEIID = cgInvalidEventID; // we have to clear the event after the first check in order to ensure correct behavior
    } while(true);
  }

  void FORTE_SKILL_Gate::enterStateWait(CEventChainExecutionThread *const) {
    mECCState = scmStateWait;
  }

  void FORTE_SKILL_Gate::enterStateChkStart(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateChkStart;
    alg_Alg_ChkStart();
    sendOutputEvent(scmEventSTART_RSPID, paECET);
  }

  void FORTE_SKILL_Gate::enterStateChkStop(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateChkStop;
    alg_Alg_ChkStop();
    sendOutputEvent(scmEventSTOP_RSPID, paECET);
  }

  void FORTE_SKILL_Gate::enterStateChkAbort(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateChkAbort;
    alg_Alg_ChkAbort();
    sendOutputEvent(scmEventABORT_RSPID, paECET);
  }

  void FORTE_SKILL_Gate::enterStateChkReset(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateChkReset;
    alg_Alg_ChkReset();
    sendOutputEvent(scmEventRESET_RSPID, paECET);
  }

  void FORTE_SKILL_Gate::enterStateClientStart(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateClientStart;
    alg_Alg_ClientStart();
    sendOutputEvent(scmEventGO_STARTID, paECET);
  }

  void FORTE_SKILL_Gate::enterStateParentStart(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateParentStart;
    alg_Alg_ParentStart();
    sendOutputEvent(scmEventGO_STARTID, paECET);
  }

  void FORTE_SKILL_Gate::enterStateGoHalt(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateGoHalt;
    sendOutputEvent(scmEventGO_HALTID, paECET);
  }

  void FORTE_SKILL_Gate::enterStateGoAbort(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateGoAbort;
    sendOutputEvent(scmEventGO_ABORTID, paECET);
  }

  void FORTE_SKILL_Gate::enterStateGoReset(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateGoReset;
    sendOutputEvent(scmEventGO_RESETID, paECET);
  }

  void FORTE_SKILL_Gate::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventSTART_REQID: {
        readData(0, var_Session, conn_Session);
        readData(1, var_ParamsInRange, conn_ParamsInRange);
        readData(2, var_EquipmentFree, conn_EquipmentFree);
        break;
      }
      case scmEventSTOP_REQID: {
        readData(3, var_StopSession, conn_StopSession);
        break;
      }
      case scmEventABORT_REQID: {
        readData(4, var_AbortSession, conn_AbortSession);
        break;
      }
      case scmEventRESET_REQID: {
        readData(5, var_ResetSession, conn_ResetSession);
        break;
      }
      case scmEventOWNER_CHGID: {
        readData(6, var_Owner, conn_Owner);
        break;
      }
      case scmEventMOD_CHGID: {
        readData(7, var_ModuleState, conn_ModuleState);
        break;
      }
      case scmEventSKILL_CHGID: {
        readData(8, var_State, conn_State);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_SKILL_Gate::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventSTART_RSPID: {
        writeData(9, var_Accepted, conn_Accepted);
        writeData(10, var_ResponseError, conn_ResponseError);
        break;
      }
      case scmEventSTOP_RSPID: {
        writeData(9, var_Accepted, conn_Accepted);
        writeData(10, var_ResponseError, conn_ResponseError);
        break;
      }
      case scmEventABORT_RSPID: {
        writeData(9, var_Accepted, conn_Accepted);
        writeData(10, var_ResponseError, conn_ResponseError);
        break;
      }
      case scmEventRESET_RSPID: {
        writeData(9, var_Accepted, conn_Accepted);
        writeData(10, var_ResponseError, conn_ResponseError);
        break;
      }
      case scmEventGO_STARTID: {
        writeData(11, var_ByClient, conn_ByClient);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_SKILL_Gate::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Session;
      case 1: return &var_ParamsInRange;
      case 2: return &var_EquipmentFree;
      case 3: return &var_StopSession;
      case 4: return &var_AbortSession;
      case 5: return &var_ResetSession;
      case 6: return &var_Owner;
      case 7: return &var_ModuleState;
      case 8: return &var_State;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SKILL_Gate::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Accepted;
      case 1: return &var_ResponseError;
      case 2: return &var_ByClient;
    }
    return nullptr;
  }

  CEventConnection *FORTE_SKILL_Gate::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_START_RSP;
      case 1: return &conn_STOP_RSP;
      case 2: return &conn_ABORT_RSP;
      case 3: return &conn_RESET_RSP;
      case 4: return &conn_GO_START;
      case 5: return &conn_GO_HALT;
      case 6: return &conn_GO_ABORT;
      case 7: return &conn_GO_RESET;
    }
    return nullptr;
  }

  CDataConnection **FORTE_SKILL_Gate::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Session;
      case 1: return &conn_ParamsInRange;
      case 2: return &conn_EquipmentFree;
      case 3: return &conn_StopSession;
      case 4: return &conn_AbortSession;
      case 5: return &conn_ResetSession;
      case 6: return &conn_Owner;
      case 7: return &conn_ModuleState;
      case 8: return &conn_State;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SKILL_Gate::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Accepted;
      case 1: return &conn_ResponseError;
      case 2: return &conn_ByClient;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SKILL_Gate::getVarInternal(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Owned;
    }
    return nullptr;
  }

  void FORTE_SKILL_Gate::alg_Alg_ChkStart(void) {

    #line 2 "SKILL_Gate.fbt"
    var_Owned = func_AND<CIEC_BOOL>(func_EQ(var_Session, var_Owner), func_NE(var_Owner, u""_WSTRING));
    #line 3 "SKILL_Gate.fbt"
    var_Accepted = false_BOOL;
    #line 4 "SKILL_Gate.fbt"
    if (func_NOT<CIEC_BOOL>(var_Owned)) {
      #line 5 "SKILL_Gate.fbt"
      var_ResponseError = 5_UINT;
    }
    else if (func_NE(var_ModuleState, 6_USINT)) {
      #line 7 "SKILL_Gate.fbt"
      var_ResponseError = 4_UINT;
    }
    else if (func_OR<CIEC_BOOL>(func_EQ(var_State, 1_USINT), func_EQ(var_State, 2_USINT))) {
      #line 9 "SKILL_Gate.fbt"
      var_ResponseError = 6_UINT;
    }
    else if (func_EQ(var_State, 5_USINT)) {
      #line 11 "SKILL_Gate.fbt"
      var_ResponseError = 4_UINT;
    }
    else if (func_NOT<CIEC_BOOL>(var_ParamsInRange)) {
      #line 13 "SKILL_Gate.fbt"
      var_ResponseError = 8_UINT;
    }
    else if (func_NOT<CIEC_BOOL>(var_EquipmentFree)) {
      #line 15 "SKILL_Gate.fbt"
      var_ResponseError = 6_UINT;
    }
    else {
      #line 17 "SKILL_Gate.fbt"
      var_Accepted = true_BOOL;
      #line 18 "SKILL_Gate.fbt"
      var_ResponseError = 0_UINT;
    }
  }

  void FORTE_SKILL_Gate::alg_Alg_ChkStop(void) {

    #line 23 "SKILL_Gate.fbt"
    var_Owned = func_AND<CIEC_BOOL>(func_EQ(var_StopSession, var_Owner), func_NE(var_Owner, u""_WSTRING));
    #line 24 "SKILL_Gate.fbt"
    var_Accepted = func_AND<CIEC_BOOL>(var_Owned, func_EQ(var_State, 1_USINT));
    #line 25 "SKILL_Gate.fbt"
    if (func_NOT<CIEC_BOOL>(var_Owned)) {
      #line 26 "SKILL_Gate.fbt"
      var_ResponseError = 5_UINT;
    }
    else if (func_NOT<CIEC_BOOL>(var_Accepted)) {
      #line 28 "SKILL_Gate.fbt"
      var_ResponseError = 4_UINT;
    }
    else {
      #line 30 "SKILL_Gate.fbt"
      var_ResponseError = 0_UINT;
    }
  }

  void FORTE_SKILL_Gate::alg_Alg_ChkAbort(void) {

    #line 35 "SKILL_Gate.fbt"
    var_Owned = func_AND<CIEC_BOOL>(func_EQ(var_AbortSession, var_Owner), func_NE(var_Owner, u""_WSTRING));
    #line 36 "SKILL_Gate.fbt"
    var_Accepted = func_AND<CIEC_BOOL>(var_Owned, func_NE(var_State, 5_USINT));
    #line 37 "SKILL_Gate.fbt"
    if (func_NOT<CIEC_BOOL>(var_Owned)) {
      #line 38 "SKILL_Gate.fbt"
      var_ResponseError = 5_UINT;
    }
    else if (func_NOT<CIEC_BOOL>(var_Accepted)) {
      #line 40 "SKILL_Gate.fbt"
      var_ResponseError = 4_UINT;
    }
    else {
      #line 42 "SKILL_Gate.fbt"
      var_ResponseError = 0_UINT;
    }
  }

  void FORTE_SKILL_Gate::alg_Alg_ChkReset(void) {

    #line 47 "SKILL_Gate.fbt"
    var_Owned = func_AND<CIEC_BOOL>(func_EQ(var_ResetSession, var_Owner), func_NE(var_Owner, u""_WSTRING));
    #line 48 "SKILL_Gate.fbt"
    var_Accepted = func_AND<CIEC_BOOL>(var_Owned, func_EQ(var_State, 5_USINT));
    #line 49 "SKILL_Gate.fbt"
    if (func_NOT<CIEC_BOOL>(var_Owned)) {
      #line 50 "SKILL_Gate.fbt"
      var_ResponseError = 5_UINT;
    }
    else if (func_NOT<CIEC_BOOL>(var_Accepted)) {
      #line 52 "SKILL_Gate.fbt"
      var_ResponseError = 4_UINT;
    }
    else {
      #line 54 "SKILL_Gate.fbt"
      var_ResponseError = 0_UINT;
    }
  }

  void FORTE_SKILL_Gate::alg_Alg_ClientStart(void) {

    #line 59 "SKILL_Gate.fbt"
    var_ByClient = true_BOOL;
  }

  void FORTE_SKILL_Gate::alg_Alg_ParentStart(void) {

    #line 63 "SKILL_Gate.fbt"
    var_ByClient = false_BOOL;
  }

}