/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SKILL_RunLogic
 *** Description: The state machine of SKILL_Run: the precondition, waiting for the equipment, the command, the end condition, the timeout, the closing command. Technical: One run of a skill primitive: Pre, then the equipment free (0.5 s grace), Command until Post or the timer (Timed), Inv over it, StopCommand at the end, played before the end is reported
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/SKILL_RunLogic_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_time.h"
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
    constexpr std::string_view TypeHash ="v2:SHA3-512:jBLgqTNRnQXmAF6F5XKSclWDRpgyTvpR67wz-34n4rkDiAEp23ECHAQXCOjnTVBtCgql5Zkp4HIvjHeRPJXvUg=="sv;

    const auto cEventInputNames = std::array{"START"_STRID, "SAMPLE"_STRID, "HALT"_STRID, "ABORT"_STRID, "TIMER"_STRID, "WAIT_OVER"_STRID, "PLAYED"_STRID};
    const auto cEventOutputNames = std::array{"DONE"_STRID, "FAILED"_STRID, "HALTED"_STRID, "TIMER_START"_STRID, "TIMER_STOP"_STRID, "WAIT_START"_STRID, "WAIT_STOP"_STRID, "CMD"_STRID, "EQ_FREE"_STRID};
    const auto cDataInputNames = std::array{"Holder"_STRID, "ReleaseAfter"_STRID, "Pre"_STRID, "Post"_STRID, "Inv"_STRID, "Timed"_STRID, "RunTime"_STRID, "Command"_STRID, "Arg"_STRID, "StopCommand"_STRID, "EqHolder"_STRID};
    const auto cDataOutputNames = std::array{"ErrorID"_STRID, "TimerDT"_STRID, "C_Holder"_STRID, "C_Command"_STRID, "C_Arg"_STRID, "C_Release"_STRID, "EquipmentFree"_STRID};
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

    const auto cInternalsNames = std::array{"Outcome"_STRID};
  }

  DEFINE_FIRMWARE_FB(FORTE_SKILL_RunLogic, "modlib::SKILL_RunLogic"_STRID, TypeHash)

  FORTE_SKILL_RunLogic::FORTE_SKILL_RunLogic(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CBasicFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cInternalsNames),
      var_Outcome(0_USINT),
      var_Holder(u""_WSTRING),
      var_ReleaseAfter(0_BOOL),
      var_Pre(0_BOOL),
      var_Post(0_BOOL),
      var_Inv(true_BOOL),
      var_Timed(0_BOOL),
      var_RunTime(0_TIME),
      var_Command(0_USINT),
      var_Arg(0_LREAL),
      var_StopCommand(0_USINT),
      var_EqHolder(u""_WSTRING),
      var_ErrorID(0_UINT),
      var_TimerDT(0_TIME),
      var_C_Holder(u""_WSTRING),
      var_C_Command(0_USINT),
      var_C_Arg(0_LREAL),
      var_C_Release(0_BOOL),
      var_EquipmentFree(0_BOOL),
      conn_DONE(*this, 0),
      conn_FAILED(*this, 1),
      conn_HALTED(*this, 2),
      conn_TIMER_START(*this, 3),
      conn_TIMER_STOP(*this, 4),
      conn_WAIT_START(*this, 5),
      conn_WAIT_STOP(*this, 6),
      conn_CMD(*this, 7),
      conn_EQ_FREE(*this, 8),
      conn_Holder(nullptr),
      conn_ReleaseAfter(nullptr),
      conn_Pre(nullptr),
      conn_Post(nullptr),
      conn_Inv(nullptr),
      conn_Timed(nullptr),
      conn_RunTime(nullptr),
      conn_Command(nullptr),
      conn_Arg(nullptr),
      conn_StopCommand(nullptr),
      conn_EqHolder(nullptr),
      conn_ErrorID(*this, 0, var_ErrorID),
      conn_TimerDT(*this, 1, var_TimerDT),
      conn_C_Holder(*this, 2, var_C_Holder),
      conn_C_Command(*this, 3, var_C_Command),
      conn_C_Arg(*this, 4, var_C_Arg),
      conn_C_Release(*this, 5, var_C_Release),
      conn_EquipmentFree(*this, 6, var_EquipmentFree) {
  }

  void FORTE_SKILL_RunLogic::setInitialValues() {
    CBasicFB::setInitialValues();
    var_Outcome = 0_USINT;
    var_Holder = u""_WSTRING;
    var_ReleaseAfter = 0_BOOL;
    var_Pre = 0_BOOL;
    var_Post = 0_BOOL;
    var_Inv = true_BOOL;
    var_Timed = 0_BOOL;
    var_RunTime = 0_TIME;
    var_Command = 0_USINT;
    var_Arg = 0_LREAL;
    var_StopCommand = 0_USINT;
    var_EqHolder = u""_WSTRING;
    var_ErrorID = 0_UINT;
    var_TimerDT = 0_TIME;
    var_C_Holder = u""_WSTRING;
    var_C_Command = 0_USINT;
    var_C_Arg = 0_LREAL;
    var_C_Release = 0_BOOL;
    var_EquipmentFree = 0_BOOL;
  }

  void FORTE_SKILL_RunLogic::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
    do {
      switch(mECCState) {
        case scmStateIdle:
          if(scmEventSTARTID == paEIID) enterStateCheck(paECET);
          else
          if(scmEventSAMPLEID == paEIID) enterStateSample(paECET);
          else return; //no transition cleared
          break;
        case scmStateCheck:
          if(func_NOT<CIEC_BOOL>(var_Pre)) enterStateReject(paECET);
          else
          if(func_AND<CIEC_BOOL>(func_NE(var_EqHolder, u""_WSTRING), func_NE(var_EqHolder, var_Holder))) enterStateWaitFree(paECET);
          else
          if(func_AND<CIEC_BOOL>(var_Post, func_NOT<CIEC_BOOL>(var_Timed))) enterStateAlreadyDone(paECET);
          else
          if(1) enterStateRun(paECET);
          else return; //no transition cleared
          break;
        case scmStateReject:
          if(1) enterStateIdle(paECET);
          else return; //no transition cleared
          break;
        case scmStateSample:
          if(1) enterStateIdle(paECET);
          else return; //no transition cleared
          break;
        case scmStateBusy:
          if(1) enterStateIdle(paECET);
          else return; //no transition cleared
          break;
        case scmStateWaitFree:
          if(1) enterStateWaitW(paECET);
          else return; //no transition cleared
          break;
        case scmStateWaitW:
          if((scmEventSAMPLEID == paEIID) && (func_NOT<CIEC_BOOL>(func_AND<CIEC_BOOL>(func_NE(var_EqHolder, u""_WSTRING), func_NE(var_EqHolder, var_Holder))))) enterStateRecheck(paECET);
          else
          if(scmEventWAIT_OVERID == paEIID) enterStateBusy(paECET);
          else
          if(scmEventHALTID == paEIID) enterStateIdle(paECET);
          else
          if(scmEventABORTID == paEIID) enterStateIdle(paECET);
          else return; //no transition cleared
          break;
        case scmStateRecheck:
          if(1) enterStateCheck(paECET);
          else return; //no transition cleared
          break;
        case scmStateAlreadyDone:
          if(1) enterStateIdle(paECET);
          else return; //no transition cleared
          break;
        case scmStateRun:
          if(1) enterStateRunning(paECET);
          else return; //no transition cleared
          break;
        case scmStateRunSample:
          if(1) enterStateRunning(paECET);
          else return; //no transition cleared
          break;
        case scmStateUnsafe:
          if(1) enterStateEnding(paECET);
          else return; //no transition cleared
          break;
        case scmStateLost:
          if(1) enterStateIdle(paECET);
          else return; //no transition cleared
          break;
        case scmStateDone:
          if(1) enterStateEnding(paECET);
          else return; //no transition cleared
          break;
        case scmStateTimedOut:
          if(1) enterStateEnding(paECET);
          else return; //no transition cleared
          break;
        case scmStateHalt:
          if(1) enterStateEnding(paECET);
          else return; //no transition cleared
          break;
        case scmStateAbort:
          if(1) enterStateEnding(paECET);
          else return; //no transition cleared
          break;
        case scmStateEnding:
          if((scmEventPLAYEDID == paEIID) && (func_EQ(var_Outcome, 1_USINT))) enterStateEndDone(paECET);
          else
          if((scmEventPLAYEDID == paEIID) && (func_EQ(var_Outcome, 2_USINT))) enterStateEndFailed(paECET);
          else
          if((scmEventPLAYEDID == paEIID) && (func_EQ(var_Outcome, 3_USINT))) enterStateEndHalted(paECET);
          else
          if(scmEventPLAYEDID == paEIID) enterStateIdle(paECET);
          else
          if(scmEventABORTID == paEIID) enterStateAbort(paECET);
          else return; //no transition cleared
          break;
        case scmStateEndDone:
          if(1) enterStateIdle(paECET);
          else return; //no transition cleared
          break;
        case scmStateEndFailed:
          if(1) enterStateIdle(paECET);
          else return; //no transition cleared
          break;
        case scmStateEndHalted:
          if(1) enterStateIdle(paECET);
          else return; //no transition cleared
          break;
        case scmStateRunning:
          if((scmEventSAMPLEID == paEIID) && (func_NOT<CIEC_BOOL>(var_Inv))) enterStateUnsafe(paECET);
          else
          if((scmEventSAMPLEID == paEIID) && (func_AND<CIEC_BOOL>(func_NE(var_EqHolder, u""_WSTRING), func_NE(var_EqHolder, var_Holder)))) enterStateLost(paECET);
          else
          if((scmEventSAMPLEID == paEIID) && (func_AND<CIEC_BOOL>(var_Post, func_NOT<CIEC_BOOL>(var_Timed)))) enterStateDone(paECET);
          else
          if((scmEventTIMERID == paEIID) && (var_Timed)) enterStateDone(paECET);
          else
          if(scmEventTIMERID == paEIID) enterStateTimedOut(paECET);
          else
          if(scmEventSAMPLEID == paEIID) enterStateRunSample(paECET);
          else
          if(scmEventHALTID == paEIID) enterStateHalt(paECET);
          else
          if(scmEventABORTID == paEIID) enterStateAbort(paECET);
          else return; //no transition cleared
          break;
        default:
          DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 22.", mECCState.operator TForteUInt16 ());
          mECCState = 0; // 0 is always the initial state
          return;
      }
      paEIID = cgInvalidEventID; // we have to clear the event after the first check in order to ensure correct behavior
    } while(true);
  }

  void FORTE_SKILL_RunLogic::enterStateIdle(CEventChainExecutionThread *const) {
    mECCState = scmStateIdle;
  }

  void FORTE_SKILL_RunLogic::enterStateCheck(CEventChainExecutionThread *const) {
    mECCState = scmStateCheck;
  }

  void FORTE_SKILL_RunLogic::enterStateReject(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateReject;
    alg_Alg_Reject();
    sendOutputEvent(scmEventFAILEDID, paECET);
  }

  void FORTE_SKILL_RunLogic::enterStateSample(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateSample;
    alg_Alg_Sample();
    sendOutputEvent(scmEventEQ_FREEID, paECET);
  }

  void FORTE_SKILL_RunLogic::enterStateBusy(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateBusy;
    alg_Alg_Busy();
    sendOutputEvent(scmEventFAILEDID, paECET);
  }

  void FORTE_SKILL_RunLogic::enterStateWaitFree(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateWaitFree;
    sendOutputEvent(scmEventWAIT_STARTID, paECET);
  }

  void FORTE_SKILL_RunLogic::enterStateWaitW(CEventChainExecutionThread *const) {
    mECCState = scmStateWaitW;
  }

  void FORTE_SKILL_RunLogic::enterStateRecheck(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateRecheck;
    sendOutputEvent(scmEventWAIT_STOPID, paECET);
  }

  void FORTE_SKILL_RunLogic::enterStateAlreadyDone(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateAlreadyDone;
    sendOutputEvent(scmEventDONEID, paECET);
  }

  void FORTE_SKILL_RunLogic::enterStateRun(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateRun;
    alg_Alg_Run();
    sendOutputEvent(scmEventCMDID, paECET);
    sendOutputEvent(scmEventTIMER_STARTID, paECET);
  }

  void FORTE_SKILL_RunLogic::enterStateRunSample(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateRunSample;
    alg_Alg_Sample();
    sendOutputEvent(scmEventEQ_FREEID, paECET);
  }

  void FORTE_SKILL_RunLogic::enterStateUnsafe(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateUnsafe;
    alg_Alg_Unsafe();
    sendOutputEvent(scmEventCMDID, paECET);
    sendOutputEvent(scmEventTIMER_STOPID, paECET);
  }

  void FORTE_SKILL_RunLogic::enterStateLost(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateLost;
    alg_Alg_Busy();
    sendOutputEvent(scmEventTIMER_STOPID, paECET);
    sendOutputEvent(scmEventFAILEDID, paECET);
  }

  void FORTE_SKILL_RunLogic::enterStateDone(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateDone;
    alg_Alg_Done();
    sendOutputEvent(scmEventCMDID, paECET);
    sendOutputEvent(scmEventTIMER_STOPID, paECET);
  }

  void FORTE_SKILL_RunLogic::enterStateTimedOut(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateTimedOut;
    alg_Alg_TimedOut();
    sendOutputEvent(scmEventCMDID, paECET);
  }

  void FORTE_SKILL_RunLogic::enterStateHalt(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateHalt;
    alg_Alg_Halt();
    sendOutputEvent(scmEventCMDID, paECET);
    sendOutputEvent(scmEventTIMER_STOPID, paECET);
  }

  void FORTE_SKILL_RunLogic::enterStateAbort(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateAbort;
    alg_Alg_Abort();
    sendOutputEvent(scmEventCMDID, paECET);
    sendOutputEvent(scmEventTIMER_STOPID, paECET);
  }

  void FORTE_SKILL_RunLogic::enterStateEnding(CEventChainExecutionThread *const) {
    mECCState = scmStateEnding;
  }

  void FORTE_SKILL_RunLogic::enterStateEndDone(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateEndDone;
    sendOutputEvent(scmEventDONEID, paECET);
  }

  void FORTE_SKILL_RunLogic::enterStateEndFailed(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateEndFailed;
    sendOutputEvent(scmEventFAILEDID, paECET);
  }

  void FORTE_SKILL_RunLogic::enterStateEndHalted(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateEndHalted;
    sendOutputEvent(scmEventHALTEDID, paECET);
  }

  void FORTE_SKILL_RunLogic::enterStateRunning(CEventChainExecutionThread *const) {
    mECCState = scmStateRunning;
  }

  void FORTE_SKILL_RunLogic::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventSTARTID: {
        readData(0, var_Holder, conn_Holder);
        readData(1, var_ReleaseAfter, conn_ReleaseAfter);
        readData(2, var_Pre, conn_Pre);
        readData(3, var_Post, conn_Post);
        readData(5, var_Timed, conn_Timed);
        readData(6, var_RunTime, conn_RunTime);
        readData(7, var_Command, conn_Command);
        readData(8, var_Arg, conn_Arg);
        readData(9, var_StopCommand, conn_StopCommand);
        break;
      }
      case scmEventSAMPLEID: {
        readData(0, var_Holder, conn_Holder);
        readData(3, var_Post, conn_Post);
        readData(4, var_Inv, conn_Inv);
        readData(10, var_EqHolder, conn_EqHolder);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_SKILL_RunLogic::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventFAILEDID: {
        writeData(11, var_ErrorID, conn_ErrorID);
        break;
      }
      case scmEventHALTEDID: {
        writeData(11, var_ErrorID, conn_ErrorID);
        break;
      }
      case scmEventTIMER_STARTID: {
        writeData(12, var_TimerDT, conn_TimerDT);
        break;
      }
      case scmEventCMDID: {
        writeData(13, var_C_Holder, conn_C_Holder);
        writeData(14, var_C_Command, conn_C_Command);
        writeData(15, var_C_Arg, conn_C_Arg);
        writeData(16, var_C_Release, conn_C_Release);
        break;
      }
      case scmEventEQ_FREEID: {
        writeData(17, var_EquipmentFree, conn_EquipmentFree);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_SKILL_RunLogic::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Holder;
      case 1: return &var_ReleaseAfter;
      case 2: return &var_Pre;
      case 3: return &var_Post;
      case 4: return &var_Inv;
      case 5: return &var_Timed;
      case 6: return &var_RunTime;
      case 7: return &var_Command;
      case 8: return &var_Arg;
      case 9: return &var_StopCommand;
      case 10: return &var_EqHolder;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SKILL_RunLogic::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_ErrorID;
      case 1: return &var_TimerDT;
      case 2: return &var_C_Holder;
      case 3: return &var_C_Command;
      case 4: return &var_C_Arg;
      case 5: return &var_C_Release;
      case 6: return &var_EquipmentFree;
    }
    return nullptr;
  }

  CEventConnection *FORTE_SKILL_RunLogic::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_DONE;
      case 1: return &conn_FAILED;
      case 2: return &conn_HALTED;
      case 3: return &conn_TIMER_START;
      case 4: return &conn_TIMER_STOP;
      case 5: return &conn_WAIT_START;
      case 6: return &conn_WAIT_STOP;
      case 7: return &conn_CMD;
      case 8: return &conn_EQ_FREE;
    }
    return nullptr;
  }

  CDataConnection **FORTE_SKILL_RunLogic::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Holder;
      case 1: return &conn_ReleaseAfter;
      case 2: return &conn_Pre;
      case 3: return &conn_Post;
      case 4: return &conn_Inv;
      case 5: return &conn_Timed;
      case 6: return &conn_RunTime;
      case 7: return &conn_Command;
      case 8: return &conn_Arg;
      case 9: return &conn_StopCommand;
      case 10: return &conn_EqHolder;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SKILL_RunLogic::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_ErrorID;
      case 1: return &conn_TimerDT;
      case 2: return &conn_C_Holder;
      case 3: return &conn_C_Command;
      case 4: return &conn_C_Arg;
      case 5: return &conn_C_Release;
      case 6: return &conn_EquipmentFree;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SKILL_RunLogic::getVarInternal(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Outcome;
    }
    return nullptr;
  }

  void FORTE_SKILL_RunLogic::alg_Alg_Reject(void) {

    #line 2 "SKILL_RunLogic.fbt"
    var_ErrorID = 1_UINT;
  }

  void FORTE_SKILL_RunLogic::alg_Alg_Sample(void) {

    #line 6 "SKILL_RunLogic.fbt"
    var_EquipmentFree = func_OR<CIEC_BOOL>(func_EQ(var_EqHolder, u""_WSTRING), func_EQ(var_EqHolder, var_Holder));
  }

  void FORTE_SKILL_RunLogic::alg_Alg_Busy(void) {

    #line 10 "SKILL_RunLogic.fbt"
    var_ErrorID = 6_UINT;
  }

  void FORTE_SKILL_RunLogic::alg_Alg_Run(void) {

    #line 14 "SKILL_RunLogic.fbt"
    var_C_Holder = var_Holder;
    #line 15 "SKILL_RunLogic.fbt"
    var_C_Command = var_Command;
    #line 16 "SKILL_RunLogic.fbt"
    var_C_Arg = var_Arg;
    #line 17 "SKILL_RunLogic.fbt"
    var_C_Release = false_BOOL;
    #line 18 "SKILL_RunLogic.fbt"
    var_TimerDT = var_RunTime;
  }

  void FORTE_SKILL_RunLogic::alg_Alg_Unsafe(void) {

    #line 22 "SKILL_RunLogic.fbt"
    var_C_Holder = var_Holder;
    #line 23 "SKILL_RunLogic.fbt"
    var_C_Command = 0_USINT;
    #line 24 "SKILL_RunLogic.fbt"
    var_C_Arg = var_Arg;
    #line 25 "SKILL_RunLogic.fbt"
    var_C_Release = var_ReleaseAfter;
    #line 26 "SKILL_RunLogic.fbt"
    var_ErrorID = 2_UINT;
    #line 27 "SKILL_RunLogic.fbt"
    var_Outcome = 2_USINT;
  }

  void FORTE_SKILL_RunLogic::alg_Alg_Done(void) {

    #line 31 "SKILL_RunLogic.fbt"
    var_C_Holder = var_Holder;
    #line 32 "SKILL_RunLogic.fbt"
    var_C_Command = var_StopCommand;
    #line 33 "SKILL_RunLogic.fbt"
    var_C_Arg = var_Arg;
    #line 34 "SKILL_RunLogic.fbt"
    var_C_Release = var_ReleaseAfter;
    #line 35 "SKILL_RunLogic.fbt"
    var_Outcome = 1_USINT;
  }

  void FORTE_SKILL_RunLogic::alg_Alg_TimedOut(void) {

    #line 39 "SKILL_RunLogic.fbt"
    var_C_Holder = var_Holder;
    #line 40 "SKILL_RunLogic.fbt"
    var_C_Command = 0_USINT;
    #line 41 "SKILL_RunLogic.fbt"
    var_C_Arg = var_Arg;
    #line 42 "SKILL_RunLogic.fbt"
    var_C_Release = var_ReleaseAfter;
    #line 43 "SKILL_RunLogic.fbt"
    var_ErrorID = 3_UINT;
    #line 44 "SKILL_RunLogic.fbt"
    var_Outcome = 2_USINT;
  }

  void FORTE_SKILL_RunLogic::alg_Alg_Halt(void) {

    #line 48 "SKILL_RunLogic.fbt"
    var_C_Holder = var_Holder;
    #line 49 "SKILL_RunLogic.fbt"
    var_C_Command = var_StopCommand;
    #line 50 "SKILL_RunLogic.fbt"
    var_C_Arg = var_Arg;
    #line 51 "SKILL_RunLogic.fbt"
    var_C_Release = var_ReleaseAfter;
    #line 52 "SKILL_RunLogic.fbt"
    var_ErrorID = 7_UINT;
    #line 53 "SKILL_RunLogic.fbt"
    var_Outcome = 3_USINT;
  }

  void FORTE_SKILL_RunLogic::alg_Alg_Abort(void) {

    #line 57 "SKILL_RunLogic.fbt"
    var_C_Holder = var_Holder;
    #line 58 "SKILL_RunLogic.fbt"
    var_C_Command = 0_USINT;
    #line 59 "SKILL_RunLogic.fbt"
    var_C_Arg = var_Arg;
    #line 60 "SKILL_RunLogic.fbt"
    var_C_Release = true_BOOL;
    #line 61 "SKILL_RunLogic.fbt"
    var_Outcome = 0_USINT;
  }

}