/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: MOD_StateLogic
 *** Description: The PackML state machine itself: Reset, Start, Stop, Abort and Clear take it from state to state (MOD_StateGate has already checked who sent them, and that PackML allows them now); while Stopping it waits until no skill runs any more. Technical: PackML module state machine: RESET, START, STOP, ABORT, CLEAR (decided by MOD_StateGate); runs the Resetting and Stopping procedures; Stopping waits until no skill is active
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/MOD_StateLogic_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/forte_st_util.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:PAiRIVtqObjeXFmFBR9_A3_CIznYFf0YfFXyp7cCvg11GPXmIVSXaFVlPM8tzA4SdJeGYlW3mNp48OeTUu6d2Q=="sv;

    const auto cEventInputNames = std::array{"RESET"_STRID, "START"_STRID, "STOP"_STRID, "ABORT"_STRID, "CLEAR"_STRID, "ACT"_STRID, "RESETTING_DONE"_STRID, "RESETTING_FAILED"_STRID, "STOPPING_DONE"_STRID, "STOPPING_FAILED"_STRID, "STOP_TIMEOUT"_STRID};
    const auto cEventOutputNames = std::array{"CNF"_STRID, "RUN_RESETTING"_STRID, "RUN_STOPPING"_STRID, "WD_START"_STRID, "WD_STOP"_STRID};
    const auto cDataInputNames = std::array{"AllIdle"_STRID};
    const auto cDataOutputNames = std::array{"State"_STRID};
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
  }

  DEFINE_FIRMWARE_FB(FORTE_MOD_StateLogic, "modlib::MOD_StateLogic"_STRID, TypeHash)

  FORTE_MOD_StateLogic::FORTE_MOD_StateLogic(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CBasicFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_AllIdle(true_BOOL),
      var_State(2_USINT),
      conn_CNF(*this, 0),
      conn_RUN_RESETTING(*this, 1),
      conn_RUN_STOPPING(*this, 2),
      conn_WD_START(*this, 3),
      conn_WD_STOP(*this, 4),
      conn_AllIdle(nullptr),
      conn_State(*this, 0, var_State) {
  }

  void FORTE_MOD_StateLogic::setInitialValues() {
    CBasicFB::setInitialValues();
    var_AllIdle = true_BOOL;
    var_State = 2_USINT;
  }

  void FORTE_MOD_StateLogic::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
    do {
      switch(mECCState) {
        case scmStateStopped:
          if(scmEventRESETID == paEIID) enterStateResetting(paECET);
          else
          if(scmEventABORTID == paEIID) enterStateAborting(paECET);
          else return; //no transition cleared
          break;
        case scmStateResetting:
          if(1) enterStateResettingW(paECET);
          else return; //no transition cleared
          break;
        case scmStateResettingW:
          if(scmEventSTOPID == paEIID) enterStateStopping(paECET);
          else
          if(scmEventABORTID == paEIID) enterStateAborting(paECET);
          else
          if(scmEventRESETTING_DONEID == paEIID) enterStateIdle(paECET);
          else
          if(scmEventRESETTING_FAILEDID == paEIID) enterStateAborting(paECET);
          else return; //no transition cleared
          break;
        case scmStateIdle:
          if(scmEventSTARTID == paEIID) enterStateStarting(paECET);
          else
          if(scmEventSTOPID == paEIID) enterStateStopping(paECET);
          else
          if(scmEventABORTID == paEIID) enterStateAborting(paECET);
          else return; //no transition cleared
          break;
        case scmStateStarting:
          if(1) enterStateExecute(paECET);
          else return; //no transition cleared
          break;
        case scmStateExecute:
          if(scmEventSTOPID == paEIID) enterStateStopping(paECET);
          else
          if(scmEventABORTID == paEIID) enterStateAborting(paECET);
          else return; //no transition cleared
          break;
        case scmStateStopping:
          if(1) enterStateStoppingW(paECET);
          else return; //no transition cleared
          break;
        case scmStateStoppingW:
          if(scmEventABORTID == paEIID) enterStateAborting(paECET);
          else
          if(var_AllIdle) enterStateStopProc(paECET);
          else
          if(scmEventSTOP_TIMEOUTID == paEIID) enterStateAborting(paECET);
          else return; //no transition cleared
          break;
        case scmStateStopProc:
          if(1) enterStateStopProcW(paECET);
          else return; //no transition cleared
          break;
        case scmStateStopProcW:
          if(scmEventABORTID == paEIID) enterStateAborting(paECET);
          else
          if(scmEventSTOPPING_DONEID == paEIID) enterStateStopped(paECET);
          else
          if(scmEventSTOPPING_FAILEDID == paEIID) enterStateAborting(paECET);
          else return; //no transition cleared
          break;
        case scmStateAborting:
          if(1) enterStateAborted(paECET);
          else return; //no transition cleared
          break;
        case scmStateAborted:
          if(scmEventCLEARID == paEIID) enterStateClearing(paECET);
          else return; //no transition cleared
          break;
        case scmStateClearing:
          if(1) enterStateStopped(paECET);
          else return; //no transition cleared
          break;
        default:
          DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 13.", mECCState.operator TForteUInt16 ());
          mECCState = 0; // 0 is always the initial state
          return;
      }
      paEIID = cgInvalidEventID; // we have to clear the event after the first check in order to ensure correct behavior
    } while(true);
  }

  void FORTE_MOD_StateLogic::enterStateStopped(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateStopped;
    alg_Alg_Stopped();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_MOD_StateLogic::enterStateResetting(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateResetting;
    alg_Alg_Resetting();
    sendOutputEvent(scmEventCNFID, paECET);
    sendOutputEvent(scmEventRUN_RESETTINGID, paECET);
  }

  void FORTE_MOD_StateLogic::enterStateResettingW(CEventChainExecutionThread *const) {
    mECCState = scmStateResettingW;
  }

  void FORTE_MOD_StateLogic::enterStateIdle(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateIdle;
    alg_Alg_Idle();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_MOD_StateLogic::enterStateStarting(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateStarting;
    alg_Alg_Starting();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_MOD_StateLogic::enterStateExecute(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateExecute;
    alg_Alg_Execute();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_MOD_StateLogic::enterStateStopping(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateStopping;
    alg_Alg_Stopping();
    sendOutputEvent(scmEventCNFID, paECET);
    sendOutputEvent(scmEventWD_STARTID, paECET);
  }

  void FORTE_MOD_StateLogic::enterStateStoppingW(CEventChainExecutionThread *const) {
    mECCState = scmStateStoppingW;
  }

  void FORTE_MOD_StateLogic::enterStateStopProc(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateStopProc;
    sendOutputEvent(scmEventWD_STOPID, paECET);
    sendOutputEvent(scmEventRUN_STOPPINGID, paECET);
  }

  void FORTE_MOD_StateLogic::enterStateStopProcW(CEventChainExecutionThread *const) {
    mECCState = scmStateStopProcW;
  }

  void FORTE_MOD_StateLogic::enterStateAborting(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateAborting;
    alg_Alg_Aborting();
    sendOutputEvent(scmEventCNFID, paECET);
    sendOutputEvent(scmEventWD_STOPID, paECET);
  }

  void FORTE_MOD_StateLogic::enterStateAborted(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateAborted;
    alg_Alg_Aborted();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_MOD_StateLogic::enterStateClearing(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateClearing;
    alg_Alg_Clearing();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_MOD_StateLogic::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventACTID: {
        readData(0, var_AllIdle, conn_AllIdle);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_MOD_StateLogic::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventCNFID: {
        writeData(1, var_State, conn_State);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_MOD_StateLogic::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_AllIdle;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_MOD_StateLogic::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_State;
    }
    return nullptr;
  }

  CEventConnection *FORTE_MOD_StateLogic::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_CNF;
      case 1: return &conn_RUN_RESETTING;
      case 2: return &conn_RUN_STOPPING;
      case 3: return &conn_WD_START;
      case 4: return &conn_WD_STOP;
    }
    return nullptr;
  }

  CDataConnection **FORTE_MOD_StateLogic::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_AllIdle;
    }
    return nullptr;
  }

  CDataConnection *FORTE_MOD_StateLogic::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_State;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_MOD_StateLogic::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_MOD_StateLogic::alg_Alg_Stopped(void) {

    #line 2 "MOD_StateLogic.fbt"
    var_State = 2_USINT;
  }

  void FORTE_MOD_StateLogic::alg_Alg_Resetting(void) {

    #line 6 "MOD_StateLogic.fbt"
    var_State = 15_USINT;
  }

  void FORTE_MOD_StateLogic::alg_Alg_Idle(void) {

    #line 10 "MOD_StateLogic.fbt"
    var_State = 4_USINT;
  }

  void FORTE_MOD_StateLogic::alg_Alg_Starting(void) {

    #line 14 "MOD_StateLogic.fbt"
    var_State = 3_USINT;
  }

  void FORTE_MOD_StateLogic::alg_Alg_Execute(void) {

    #line 18 "MOD_StateLogic.fbt"
    var_State = 6_USINT;
  }

  void FORTE_MOD_StateLogic::alg_Alg_Stopping(void) {

    #line 22 "MOD_StateLogic.fbt"
    var_State = 7_USINT;
  }

  void FORTE_MOD_StateLogic::alg_Alg_Aborting(void) {

    #line 26 "MOD_StateLogic.fbt"
    var_State = 8_USINT;
  }

  void FORTE_MOD_StateLogic::alg_Alg_Aborted(void) {

    #line 30 "MOD_StateLogic.fbt"
    var_State = 9_USINT;
  }

  void FORTE_MOD_StateLogic::alg_Alg_Clearing(void) {

    #line 34 "MOD_StateLogic.fbt"
    var_State = 1_USINT;
  }

}