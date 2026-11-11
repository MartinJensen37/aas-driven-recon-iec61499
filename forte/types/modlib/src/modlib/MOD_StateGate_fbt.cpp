/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: MOD_StateGate
 *** Description: The module's front desk inside MOD_StateManager: answers Reset, Start, Stop, Abort or Clear at once (only from the module's owner, only in a state PackML allows it in) and passes an accepted command on to MOD_StateLogic. Technical: Decides the module commands Reset/Start/Stop/Abort/Clear: only from the occupation owner (5 NotPermitted) and only in a state PackML allows them in (4 NotReady); passes an accepted one on to MOD_StateLogic
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/MOD_StateGate_fbt.h"

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
    constexpr std::string_view TypeHash ="v2:SHA3-512:QseoRcx83F6vqSHGJiEcqUfFO1BH_ivg-gRdnHF5_JRpCo89cUWwYEtM9T8-N9nIYGhtxmR3sNLR03HeqzcTsg=="sv;

    const auto cEventInputNames = std::array{"RESET_REQ"_STRID, "START_REQ"_STRID, "STOP_REQ"_STRID, "ABORT_REQ"_STRID, "CLEAR_REQ"_STRID, "OWNER_CHG"_STRID, "STATE_CHG"_STRID};
    const auto cEventOutputNames = std::array{"RESET_RSP"_STRID, "START_RSP"_STRID, "STOP_RSP"_STRID, "ABORT_RSP"_STRID, "CLEAR_RSP"_STRID, "GO_RESET"_STRID, "GO_START"_STRID, "GO_STOP"_STRID, "GO_ABORT"_STRID, "GO_CLEAR"_STRID};
    const auto cDataInputNames = std::array{"ResetSession"_STRID, "StartSession"_STRID, "StopSession"_STRID, "AbortSession"_STRID, "ClearSession"_STRID, "Owner"_STRID, "State"_STRID};
    const auto cDataOutputNames = std::array{"Accepted"_STRID, "ErrorID"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_MOD_StateGate, "modlib::MOD_StateGate"_STRID, TypeHash)

  FORTE_MOD_StateGate::FORTE_MOD_StateGate(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CBasicFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cInternalsNames),
      var_Owned(0_BOOL),
      var_ResetSession(u""_WSTRING),
      var_StartSession(u""_WSTRING),
      var_StopSession(u""_WSTRING),
      var_AbortSession(u""_WSTRING),
      var_ClearSession(u""_WSTRING),
      var_Owner(u""_WSTRING),
      var_State(2_USINT),
      var_Accepted(0_BOOL),
      var_ErrorID(0_UINT),
      conn_RESET_RSP(*this, 0),
      conn_START_RSP(*this, 1),
      conn_STOP_RSP(*this, 2),
      conn_ABORT_RSP(*this, 3),
      conn_CLEAR_RSP(*this, 4),
      conn_GO_RESET(*this, 5),
      conn_GO_START(*this, 6),
      conn_GO_STOP(*this, 7),
      conn_GO_ABORT(*this, 8),
      conn_GO_CLEAR(*this, 9),
      conn_ResetSession(nullptr),
      conn_StartSession(nullptr),
      conn_StopSession(nullptr),
      conn_AbortSession(nullptr),
      conn_ClearSession(nullptr),
      conn_Owner(nullptr),
      conn_State(nullptr),
      conn_Accepted(*this, 0, var_Accepted),
      conn_ErrorID(*this, 1, var_ErrorID) {
  }

  void FORTE_MOD_StateGate::setInitialValues() {
    CBasicFB::setInitialValues();
    var_Owned = 0_BOOL;
    var_ResetSession = u""_WSTRING;
    var_StartSession = u""_WSTRING;
    var_StopSession = u""_WSTRING;
    var_AbortSession = u""_WSTRING;
    var_ClearSession = u""_WSTRING;
    var_Owner = u""_WSTRING;
    var_State = 2_USINT;
    var_Accepted = 0_BOOL;
    var_ErrorID = 0_UINT;
  }

  void FORTE_MOD_StateGate::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
    do {
      switch(mECCState) {
        case scmStateWait:
          if(scmEventRESET_REQID == paEIID) enterStateChkReset(paECET);
          else
          if(scmEventSTART_REQID == paEIID) enterStateChkStart(paECET);
          else
          if(scmEventSTOP_REQID == paEIID) enterStateChkStop(paECET);
          else
          if(scmEventABORT_REQID == paEIID) enterStateChkAbort(paECET);
          else
          if(scmEventCLEAR_REQID == paEIID) enterStateChkClear(paECET);
          else return; //no transition cleared
          break;
        case scmStateChkReset:
          if(var_Accepted) enterStateGoReset(paECET);
          else
          if(1) enterStateWait(paECET);
          else return; //no transition cleared
          break;
        case scmStateGoReset:
          if(1) enterStateWait(paECET);
          else return; //no transition cleared
          break;
        case scmStateChkStart:
          if(var_Accepted) enterStateGoStart(paECET);
          else
          if(1) enterStateWait(paECET);
          else return; //no transition cleared
          break;
        case scmStateGoStart:
          if(1) enterStateWait(paECET);
          else return; //no transition cleared
          break;
        case scmStateChkStop:
          if(var_Accepted) enterStateGoStop(paECET);
          else
          if(1) enterStateWait(paECET);
          else return; //no transition cleared
          break;
        case scmStateGoStop:
          if(1) enterStateWait(paECET);
          else return; //no transition cleared
          break;
        case scmStateChkAbort:
          if(var_Accepted) enterStateGoAbort(paECET);
          else
          if(1) enterStateWait(paECET);
          else return; //no transition cleared
          break;
        case scmStateGoAbort:
          if(1) enterStateWait(paECET);
          else return; //no transition cleared
          break;
        case scmStateChkClear:
          if(var_Accepted) enterStateGoClear(paECET);
          else
          if(1) enterStateWait(paECET);
          else return; //no transition cleared
          break;
        case scmStateGoClear:
          if(1) enterStateWait(paECET);
          else return; //no transition cleared
          break;
        default:
          DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 11.", mECCState.operator TForteUInt16 ());
          mECCState = 0; // 0 is always the initial state
          return;
      }
      paEIID = cgInvalidEventID; // we have to clear the event after the first check in order to ensure correct behavior
    } while(true);
  }

  void FORTE_MOD_StateGate::enterStateWait(CEventChainExecutionThread *const) {
    mECCState = scmStateWait;
  }

  void FORTE_MOD_StateGate::enterStateChkReset(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateChkReset;
    alg_Alg_ChkReset();
    sendOutputEvent(scmEventRESET_RSPID, paECET);
  }

  void FORTE_MOD_StateGate::enterStateGoReset(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateGoReset;
    sendOutputEvent(scmEventGO_RESETID, paECET);
  }

  void FORTE_MOD_StateGate::enterStateChkStart(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateChkStart;
    alg_Alg_ChkStart();
    sendOutputEvent(scmEventSTART_RSPID, paECET);
  }

  void FORTE_MOD_StateGate::enterStateGoStart(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateGoStart;
    sendOutputEvent(scmEventGO_STARTID, paECET);
  }

  void FORTE_MOD_StateGate::enterStateChkStop(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateChkStop;
    alg_Alg_ChkStop();
    sendOutputEvent(scmEventSTOP_RSPID, paECET);
  }

  void FORTE_MOD_StateGate::enterStateGoStop(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateGoStop;
    sendOutputEvent(scmEventGO_STOPID, paECET);
  }

  void FORTE_MOD_StateGate::enterStateChkAbort(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateChkAbort;
    alg_Alg_ChkAbort();
    sendOutputEvent(scmEventABORT_RSPID, paECET);
  }

  void FORTE_MOD_StateGate::enterStateGoAbort(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateGoAbort;
    sendOutputEvent(scmEventGO_ABORTID, paECET);
  }

  void FORTE_MOD_StateGate::enterStateChkClear(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateChkClear;
    alg_Alg_ChkClear();
    sendOutputEvent(scmEventCLEAR_RSPID, paECET);
  }

  void FORTE_MOD_StateGate::enterStateGoClear(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateGoClear;
    sendOutputEvent(scmEventGO_CLEARID, paECET);
  }

  void FORTE_MOD_StateGate::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventRESET_REQID: {
        readData(0, var_ResetSession, conn_ResetSession);
        break;
      }
      case scmEventSTART_REQID: {
        readData(1, var_StartSession, conn_StartSession);
        break;
      }
      case scmEventSTOP_REQID: {
        readData(2, var_StopSession, conn_StopSession);
        break;
      }
      case scmEventABORT_REQID: {
        readData(3, var_AbortSession, conn_AbortSession);
        break;
      }
      case scmEventCLEAR_REQID: {
        readData(4, var_ClearSession, conn_ClearSession);
        break;
      }
      case scmEventOWNER_CHGID: {
        readData(5, var_Owner, conn_Owner);
        break;
      }
      case scmEventSTATE_CHGID: {
        readData(6, var_State, conn_State);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_MOD_StateGate::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventRESET_RSPID: {
        writeData(7, var_Accepted, conn_Accepted);
        writeData(8, var_ErrorID, conn_ErrorID);
        break;
      }
      case scmEventSTART_RSPID: {
        writeData(7, var_Accepted, conn_Accepted);
        writeData(8, var_ErrorID, conn_ErrorID);
        break;
      }
      case scmEventSTOP_RSPID: {
        writeData(7, var_Accepted, conn_Accepted);
        writeData(8, var_ErrorID, conn_ErrorID);
        break;
      }
      case scmEventABORT_RSPID: {
        writeData(7, var_Accepted, conn_Accepted);
        writeData(8, var_ErrorID, conn_ErrorID);
        break;
      }
      case scmEventCLEAR_RSPID: {
        writeData(7, var_Accepted, conn_Accepted);
        writeData(8, var_ErrorID, conn_ErrorID);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_MOD_StateGate::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_ResetSession;
      case 1: return &var_StartSession;
      case 2: return &var_StopSession;
      case 3: return &var_AbortSession;
      case 4: return &var_ClearSession;
      case 5: return &var_Owner;
      case 6: return &var_State;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_MOD_StateGate::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Accepted;
      case 1: return &var_ErrorID;
    }
    return nullptr;
  }

  CEventConnection *FORTE_MOD_StateGate::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_RESET_RSP;
      case 1: return &conn_START_RSP;
      case 2: return &conn_STOP_RSP;
      case 3: return &conn_ABORT_RSP;
      case 4: return &conn_CLEAR_RSP;
      case 5: return &conn_GO_RESET;
      case 6: return &conn_GO_START;
      case 7: return &conn_GO_STOP;
      case 8: return &conn_GO_ABORT;
      case 9: return &conn_GO_CLEAR;
    }
    return nullptr;
  }

  CDataConnection **FORTE_MOD_StateGate::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_ResetSession;
      case 1: return &conn_StartSession;
      case 2: return &conn_StopSession;
      case 3: return &conn_AbortSession;
      case 4: return &conn_ClearSession;
      case 5: return &conn_Owner;
      case 6: return &conn_State;
    }
    return nullptr;
  }

  CDataConnection *FORTE_MOD_StateGate::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Accepted;
      case 1: return &conn_ErrorID;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_MOD_StateGate::getVarInternal(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Owned;
    }
    return nullptr;
  }

  void FORTE_MOD_StateGate::alg_Alg_ChkReset(void) {

    #line 2 "MOD_StateGate.fbt"
    var_Owned = func_AND<CIEC_BOOL>(func_EQ(var_ResetSession, var_Owner), func_NE(var_Owner, u""_WSTRING));
    #line 3 "MOD_StateGate.fbt"
    var_Accepted = func_AND<CIEC_BOOL>(var_Owned, func_EQ(var_State, 2_USINT));
    #line 4 "MOD_StateGate.fbt"
    if (func_NOT<CIEC_BOOL>(var_Owned)) {
      #line 5 "MOD_StateGate.fbt"
      var_ErrorID = 5_UINT;
    }
    else if (func_NOT<CIEC_BOOL>(var_Accepted)) {
      #line 7 "MOD_StateGate.fbt"
      var_ErrorID = 4_UINT;
    }
    else {
      #line 9 "MOD_StateGate.fbt"
      var_ErrorID = 0_UINT;
    }
  }

  void FORTE_MOD_StateGate::alg_Alg_ChkStart(void) {

    #line 14 "MOD_StateGate.fbt"
    var_Owned = func_AND<CIEC_BOOL>(func_EQ(var_StartSession, var_Owner), func_NE(var_Owner, u""_WSTRING));
    #line 15 "MOD_StateGate.fbt"
    var_Accepted = func_AND<CIEC_BOOL>(var_Owned, func_EQ(var_State, 4_USINT));
    #line 16 "MOD_StateGate.fbt"
    if (func_NOT<CIEC_BOOL>(var_Owned)) {
      #line 17 "MOD_StateGate.fbt"
      var_ErrorID = 5_UINT;
    }
    else if (func_NOT<CIEC_BOOL>(var_Accepted)) {
      #line 19 "MOD_StateGate.fbt"
      var_ErrorID = 4_UINT;
    }
    else {
      #line 21 "MOD_StateGate.fbt"
      var_ErrorID = 0_UINT;
    }
  }

  void FORTE_MOD_StateGate::alg_Alg_ChkStop(void) {

    #line 26 "MOD_StateGate.fbt"
    var_Owned = func_AND<CIEC_BOOL>(func_EQ(var_StopSession, var_Owner), func_NE(var_Owner, u""_WSTRING));
    #line 27 "MOD_StateGate.fbt"
    var_Accepted = func_AND<CIEC_BOOL>(var_Owned, func_OR<CIEC_BOOL>(func_OR<CIEC_BOOL>(func_EQ(var_State, 4_USINT), func_EQ(var_State, 6_USINT)), func_EQ(var_State, 15_USINT)));
    #line 28 "MOD_StateGate.fbt"
    if (func_NOT<CIEC_BOOL>(var_Owned)) {
      #line 29 "MOD_StateGate.fbt"
      var_ErrorID = 5_UINT;
    }
    else if (func_NOT<CIEC_BOOL>(var_Accepted)) {
      #line 31 "MOD_StateGate.fbt"
      var_ErrorID = 4_UINT;
    }
    else {
      #line 33 "MOD_StateGate.fbt"
      var_ErrorID = 0_UINT;
    }
  }

  void FORTE_MOD_StateGate::alg_Alg_ChkAbort(void) {

    #line 38 "MOD_StateGate.fbt"
    var_Owned = func_AND<CIEC_BOOL>(func_EQ(var_AbortSession, var_Owner), func_NE(var_Owner, u""_WSTRING));
    #line 39 "MOD_StateGate.fbt"
    var_Accepted = func_AND<CIEC_BOOL>(var_Owned, func_OR<CIEC_BOOL>(func_OR<CIEC_BOOL>(func_OR<CIEC_BOOL>(func_OR<CIEC_BOOL>(func_EQ(var_State, 2_USINT), func_EQ(var_State, 4_USINT)), func_EQ(var_State, 6_USINT)), func_EQ(var_State, 7_USINT)), func_EQ(var_State, 15_USINT)));
    #line 40 "MOD_StateGate.fbt"
    if (func_NOT<CIEC_BOOL>(var_Owned)) {
      #line 41 "MOD_StateGate.fbt"
      var_ErrorID = 5_UINT;
    }
    else if (func_NOT<CIEC_BOOL>(var_Accepted)) {
      #line 43 "MOD_StateGate.fbt"
      var_ErrorID = 4_UINT;
    }
    else {
      #line 45 "MOD_StateGate.fbt"
      var_ErrorID = 0_UINT;
    }
  }

  void FORTE_MOD_StateGate::alg_Alg_ChkClear(void) {

    #line 50 "MOD_StateGate.fbt"
    var_Owned = func_AND<CIEC_BOOL>(func_EQ(var_ClearSession, var_Owner), func_NE(var_Owner, u""_WSTRING));
    #line 51 "MOD_StateGate.fbt"
    var_Accepted = func_AND<CIEC_BOOL>(var_Owned, func_EQ(var_State, 9_USINT));
    #line 52 "MOD_StateGate.fbt"
    if (func_NOT<CIEC_BOOL>(var_Owned)) {
      #line 53 "MOD_StateGate.fbt"
      var_ErrorID = 5_UINT;
    }
    else if (func_NOT<CIEC_BOOL>(var_Accepted)) {
      #line 55 "MOD_StateGate.fbt"
      var_ErrorID = 4_UINT;
    }
    else {
      #line 57 "MOD_StateGate.fbt"
      var_ErrorID = 0_UINT;
    }
  }

}