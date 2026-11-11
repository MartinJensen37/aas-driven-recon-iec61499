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

#pragma once

#include "forte/basicfb.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"

namespace forte::modlib {
  class FORTE_SKILL_RunLogic final : public CBasicFB {
      DECLARE_FIRMWARE_FB(FORTE_SKILL_RunLogic)

    private:
      static const TEventID scmEventDONEID = 0;
      static const TEventID scmEventFAILEDID = 1;
      static const TEventID scmEventHALTEDID = 2;
      static const TEventID scmEventTIMER_STARTID = 3;
      static const TEventID scmEventTIMER_STOPID = 4;
      static const TEventID scmEventWAIT_STARTID = 5;
      static const TEventID scmEventWAIT_STOPID = 6;
      static const TEventID scmEventCMDID = 7;
      static const TEventID scmEventEQ_FREEID = 8;
      static const TEventID scmEventSTARTID = 0;
      static const TEventID scmEventSAMPLEID = 1;
      static const TEventID scmEventHALTID = 2;
      static const TEventID scmEventABORTID = 3;
      static const TEventID scmEventTIMERID = 4;
      static const TEventID scmEventWAIT_OVERID = 5;
      static const TEventID scmEventPLAYEDID = 6;

      CIEC_USINT var_Outcome;

      CIEC_ANY *getVarInternal(size_t) override;

      void alg_Alg_Reject(void);
      void alg_Alg_Sample(void);
      void alg_Alg_Busy(void);
      void alg_Alg_Run(void);
      void alg_Alg_Unsafe(void);
      void alg_Alg_Done(void);
      void alg_Alg_TimedOut(void);
      void alg_Alg_Halt(void);
      void alg_Alg_Abort(void);

      static const TForteInt16 scmStateIdle = 0;
      static const TForteInt16 scmStateCheck = 1;
      static const TForteInt16 scmStateReject = 2;
      static const TForteInt16 scmStateSample = 3;
      static const TForteInt16 scmStateBusy = 4;
      static const TForteInt16 scmStateWaitFree = 5;
      static const TForteInt16 scmStateWaitW = 6;
      static const TForteInt16 scmStateRecheck = 7;
      static const TForteInt16 scmStateAlreadyDone = 8;
      static const TForteInt16 scmStateRun = 9;
      static const TForteInt16 scmStateRunSample = 10;
      static const TForteInt16 scmStateUnsafe = 11;
      static const TForteInt16 scmStateLost = 12;
      static const TForteInt16 scmStateDone = 13;
      static const TForteInt16 scmStateTimedOut = 14;
      static const TForteInt16 scmStateHalt = 15;
      static const TForteInt16 scmStateAbort = 16;
      static const TForteInt16 scmStateEnding = 17;
      static const TForteInt16 scmStateEndDone = 18;
      static const TForteInt16 scmStateEndFailed = 19;
      static const TForteInt16 scmStateEndHalted = 20;
      static const TForteInt16 scmStateRunning = 21;

      void enterStateIdle(CEventChainExecutionThread *const paECET);
      void enterStateCheck(CEventChainExecutionThread *const paECET);
      void enterStateReject(CEventChainExecutionThread *const paECET);
      void enterStateSample(CEventChainExecutionThread *const paECET);
      void enterStateBusy(CEventChainExecutionThread *const paECET);
      void enterStateWaitFree(CEventChainExecutionThread *const paECET);
      void enterStateWaitW(CEventChainExecutionThread *const paECET);
      void enterStateRecheck(CEventChainExecutionThread *const paECET);
      void enterStateAlreadyDone(CEventChainExecutionThread *const paECET);
      void enterStateRun(CEventChainExecutionThread *const paECET);
      void enterStateRunSample(CEventChainExecutionThread *const paECET);
      void enterStateUnsafe(CEventChainExecutionThread *const paECET);
      void enterStateLost(CEventChainExecutionThread *const paECET);
      void enterStateDone(CEventChainExecutionThread *const paECET);
      void enterStateTimedOut(CEventChainExecutionThread *const paECET);
      void enterStateHalt(CEventChainExecutionThread *const paECET);
      void enterStateAbort(CEventChainExecutionThread *const paECET);
      void enterStateEnding(CEventChainExecutionThread *const paECET);
      void enterStateEndDone(CEventChainExecutionThread *const paECET);
      void enterStateEndFailed(CEventChainExecutionThread *const paECET);
      void enterStateEndHalted(CEventChainExecutionThread *const paECET);
      void enterStateRunning(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_SKILL_RunLogic(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_WSTRING var_Holder;
      CIEC_BOOL var_ReleaseAfter;
      CIEC_BOOL var_Pre;
      CIEC_BOOL var_Post;
      CIEC_BOOL var_Inv;
      CIEC_BOOL var_Timed;
      CIEC_TIME var_RunTime;
      CIEC_USINT var_Command;
      CIEC_LREAL var_Arg;
      CIEC_USINT var_StopCommand;
      CIEC_WSTRING var_EqHolder;

      CIEC_UINT var_ErrorID;
      CIEC_TIME var_TimerDT;
      CIEC_WSTRING var_C_Holder;
      CIEC_USINT var_C_Command;
      CIEC_LREAL var_C_Arg;
      CIEC_BOOL var_C_Release;
      CIEC_BOOL var_EquipmentFree;

      CEventConnection conn_DONE;
      CEventConnection conn_FAILED;
      CEventConnection conn_HALTED;
      CEventConnection conn_TIMER_START;
      CEventConnection conn_TIMER_STOP;
      CEventConnection conn_WAIT_START;
      CEventConnection conn_WAIT_STOP;
      CEventConnection conn_CMD;
      CEventConnection conn_EQ_FREE;

      CDataConnection *conn_Holder;
      CDataConnection *conn_ReleaseAfter;
      CDataConnection *conn_Pre;
      CDataConnection *conn_Post;
      CDataConnection *conn_Inv;
      CDataConnection *conn_Timed;
      CDataConnection *conn_RunTime;
      CDataConnection *conn_Command;
      CDataConnection *conn_Arg;
      CDataConnection *conn_StopCommand;
      CDataConnection *conn_EqHolder;

      COutDataConnection<CIEC_UINT> conn_ErrorID;
      COutDataConnection<CIEC_TIME> conn_TimerDT;
      COutDataConnection<CIEC_WSTRING> conn_C_Holder;
      COutDataConnection<CIEC_USINT> conn_C_Command;
      COutDataConnection<CIEC_LREAL> conn_C_Arg;
      COutDataConnection<CIEC_BOOL> conn_C_Release;
      COutDataConnection<CIEC_BOOL> conn_EquipmentFree;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_START(const CIEC_WSTRING &paHolder, const CIEC_BOOL &paReleaseAfter, const CIEC_BOOL &paPre, const CIEC_BOOL &paPost, const CIEC_BOOL &paInv, const CIEC_BOOL &paTimed, const CIEC_TIME &paRunTime, const CIEC_USINT &paCommand, const CIEC_LREAL &paArg, const CIEC_USINT &paStopCommand, const CIEC_WSTRING &paEqHolder, COutputParameter<CIEC_UINT> paErrorID, COutputParameter<CIEC_TIME> paTimerDT, COutputParameter<CIEC_WSTRING> paC_Holder, COutputParameter<CIEC_USINT> paC_Command, COutputParameter<CIEC_LREAL> paC_Arg, CAnyBitOutputParameter<CIEC_BOOL> paC_Release, CAnyBitOutputParameter<CIEC_BOOL> paEquipmentFree) {
        COutputGuard guard_ErrorID(paErrorID);
        COutputGuard guard_TimerDT(paTimerDT);
        COutputGuard guard_C_Holder(paC_Holder);
        COutputGuard guard_C_Command(paC_Command);
        COutputGuard guard_C_Arg(paC_Arg);
        COutputGuard guard_C_Release(paC_Release);
        COutputGuard guard_EquipmentFree(paEquipmentFree);
        var_Holder = paHolder;
        var_ReleaseAfter = paReleaseAfter;
        var_Pre = paPre;
        var_Post = paPost;
        var_Inv = paInv;
        var_Timed = paTimed;
        var_RunTime = paRunTime;
        var_Command = paCommand;
        var_Arg = paArg;
        var_StopCommand = paStopCommand;
        var_EqHolder = paEqHolder;
        executeEvent(scmEventSTARTID, nullptr);
        *paErrorID = var_ErrorID;
        *paTimerDT = var_TimerDT;
        *paC_Holder = var_C_Holder;
        *paC_Command = var_C_Command;
        *paC_Arg = var_C_Arg;
        *paC_Release = var_C_Release;
        *paEquipmentFree = var_EquipmentFree;
      }

      void evt_SAMPLE(const CIEC_WSTRING &paHolder, const CIEC_BOOL &paReleaseAfter, const CIEC_BOOL &paPre, const CIEC_BOOL &paPost, const CIEC_BOOL &paInv, const CIEC_BOOL &paTimed, const CIEC_TIME &paRunTime, const CIEC_USINT &paCommand, const CIEC_LREAL &paArg, const CIEC_USINT &paStopCommand, const CIEC_WSTRING &paEqHolder, COutputParameter<CIEC_UINT> paErrorID, COutputParameter<CIEC_TIME> paTimerDT, COutputParameter<CIEC_WSTRING> paC_Holder, COutputParameter<CIEC_USINT> paC_Command, COutputParameter<CIEC_LREAL> paC_Arg, CAnyBitOutputParameter<CIEC_BOOL> paC_Release, CAnyBitOutputParameter<CIEC_BOOL> paEquipmentFree) {
        COutputGuard guard_ErrorID(paErrorID);
        COutputGuard guard_TimerDT(paTimerDT);
        COutputGuard guard_C_Holder(paC_Holder);
        COutputGuard guard_C_Command(paC_Command);
        COutputGuard guard_C_Arg(paC_Arg);
        COutputGuard guard_C_Release(paC_Release);
        COutputGuard guard_EquipmentFree(paEquipmentFree);
        var_Holder = paHolder;
        var_ReleaseAfter = paReleaseAfter;
        var_Pre = paPre;
        var_Post = paPost;
        var_Inv = paInv;
        var_Timed = paTimed;
        var_RunTime = paRunTime;
        var_Command = paCommand;
        var_Arg = paArg;
        var_StopCommand = paStopCommand;
        var_EqHolder = paEqHolder;
        executeEvent(scmEventSAMPLEID, nullptr);
        *paErrorID = var_ErrorID;
        *paTimerDT = var_TimerDT;
        *paC_Holder = var_C_Holder;
        *paC_Command = var_C_Command;
        *paC_Arg = var_C_Arg;
        *paC_Release = var_C_Release;
        *paEquipmentFree = var_EquipmentFree;
      }

      void evt_HALT(const CIEC_WSTRING &paHolder, const CIEC_BOOL &paReleaseAfter, const CIEC_BOOL &paPre, const CIEC_BOOL &paPost, const CIEC_BOOL &paInv, const CIEC_BOOL &paTimed, const CIEC_TIME &paRunTime, const CIEC_USINT &paCommand, const CIEC_LREAL &paArg, const CIEC_USINT &paStopCommand, const CIEC_WSTRING &paEqHolder, COutputParameter<CIEC_UINT> paErrorID, COutputParameter<CIEC_TIME> paTimerDT, COutputParameter<CIEC_WSTRING> paC_Holder, COutputParameter<CIEC_USINT> paC_Command, COutputParameter<CIEC_LREAL> paC_Arg, CAnyBitOutputParameter<CIEC_BOOL> paC_Release, CAnyBitOutputParameter<CIEC_BOOL> paEquipmentFree) {
        COutputGuard guard_ErrorID(paErrorID);
        COutputGuard guard_TimerDT(paTimerDT);
        COutputGuard guard_C_Holder(paC_Holder);
        COutputGuard guard_C_Command(paC_Command);
        COutputGuard guard_C_Arg(paC_Arg);
        COutputGuard guard_C_Release(paC_Release);
        COutputGuard guard_EquipmentFree(paEquipmentFree);
        var_Holder = paHolder;
        var_ReleaseAfter = paReleaseAfter;
        var_Pre = paPre;
        var_Post = paPost;
        var_Inv = paInv;
        var_Timed = paTimed;
        var_RunTime = paRunTime;
        var_Command = paCommand;
        var_Arg = paArg;
        var_StopCommand = paStopCommand;
        var_EqHolder = paEqHolder;
        executeEvent(scmEventHALTID, nullptr);
        *paErrorID = var_ErrorID;
        *paTimerDT = var_TimerDT;
        *paC_Holder = var_C_Holder;
        *paC_Command = var_C_Command;
        *paC_Arg = var_C_Arg;
        *paC_Release = var_C_Release;
        *paEquipmentFree = var_EquipmentFree;
      }

      void evt_ABORT(const CIEC_WSTRING &paHolder, const CIEC_BOOL &paReleaseAfter, const CIEC_BOOL &paPre, const CIEC_BOOL &paPost, const CIEC_BOOL &paInv, const CIEC_BOOL &paTimed, const CIEC_TIME &paRunTime, const CIEC_USINT &paCommand, const CIEC_LREAL &paArg, const CIEC_USINT &paStopCommand, const CIEC_WSTRING &paEqHolder, COutputParameter<CIEC_UINT> paErrorID, COutputParameter<CIEC_TIME> paTimerDT, COutputParameter<CIEC_WSTRING> paC_Holder, COutputParameter<CIEC_USINT> paC_Command, COutputParameter<CIEC_LREAL> paC_Arg, CAnyBitOutputParameter<CIEC_BOOL> paC_Release, CAnyBitOutputParameter<CIEC_BOOL> paEquipmentFree) {
        COutputGuard guard_ErrorID(paErrorID);
        COutputGuard guard_TimerDT(paTimerDT);
        COutputGuard guard_C_Holder(paC_Holder);
        COutputGuard guard_C_Command(paC_Command);
        COutputGuard guard_C_Arg(paC_Arg);
        COutputGuard guard_C_Release(paC_Release);
        COutputGuard guard_EquipmentFree(paEquipmentFree);
        var_Holder = paHolder;
        var_ReleaseAfter = paReleaseAfter;
        var_Pre = paPre;
        var_Post = paPost;
        var_Inv = paInv;
        var_Timed = paTimed;
        var_RunTime = paRunTime;
        var_Command = paCommand;
        var_Arg = paArg;
        var_StopCommand = paStopCommand;
        var_EqHolder = paEqHolder;
        executeEvent(scmEventABORTID, nullptr);
        *paErrorID = var_ErrorID;
        *paTimerDT = var_TimerDT;
        *paC_Holder = var_C_Holder;
        *paC_Command = var_C_Command;
        *paC_Arg = var_C_Arg;
        *paC_Release = var_C_Release;
        *paEquipmentFree = var_EquipmentFree;
      }

      void evt_TIMER(const CIEC_WSTRING &paHolder, const CIEC_BOOL &paReleaseAfter, const CIEC_BOOL &paPre, const CIEC_BOOL &paPost, const CIEC_BOOL &paInv, const CIEC_BOOL &paTimed, const CIEC_TIME &paRunTime, const CIEC_USINT &paCommand, const CIEC_LREAL &paArg, const CIEC_USINT &paStopCommand, const CIEC_WSTRING &paEqHolder, COutputParameter<CIEC_UINT> paErrorID, COutputParameter<CIEC_TIME> paTimerDT, COutputParameter<CIEC_WSTRING> paC_Holder, COutputParameter<CIEC_USINT> paC_Command, COutputParameter<CIEC_LREAL> paC_Arg, CAnyBitOutputParameter<CIEC_BOOL> paC_Release, CAnyBitOutputParameter<CIEC_BOOL> paEquipmentFree) {
        COutputGuard guard_ErrorID(paErrorID);
        COutputGuard guard_TimerDT(paTimerDT);
        COutputGuard guard_C_Holder(paC_Holder);
        COutputGuard guard_C_Command(paC_Command);
        COutputGuard guard_C_Arg(paC_Arg);
        COutputGuard guard_C_Release(paC_Release);
        COutputGuard guard_EquipmentFree(paEquipmentFree);
        var_Holder = paHolder;
        var_ReleaseAfter = paReleaseAfter;
        var_Pre = paPre;
        var_Post = paPost;
        var_Inv = paInv;
        var_Timed = paTimed;
        var_RunTime = paRunTime;
        var_Command = paCommand;
        var_Arg = paArg;
        var_StopCommand = paStopCommand;
        var_EqHolder = paEqHolder;
        executeEvent(scmEventTIMERID, nullptr);
        *paErrorID = var_ErrorID;
        *paTimerDT = var_TimerDT;
        *paC_Holder = var_C_Holder;
        *paC_Command = var_C_Command;
        *paC_Arg = var_C_Arg;
        *paC_Release = var_C_Release;
        *paEquipmentFree = var_EquipmentFree;
      }

      void evt_WAIT_OVER(const CIEC_WSTRING &paHolder, const CIEC_BOOL &paReleaseAfter, const CIEC_BOOL &paPre, const CIEC_BOOL &paPost, const CIEC_BOOL &paInv, const CIEC_BOOL &paTimed, const CIEC_TIME &paRunTime, const CIEC_USINT &paCommand, const CIEC_LREAL &paArg, const CIEC_USINT &paStopCommand, const CIEC_WSTRING &paEqHolder, COutputParameter<CIEC_UINT> paErrorID, COutputParameter<CIEC_TIME> paTimerDT, COutputParameter<CIEC_WSTRING> paC_Holder, COutputParameter<CIEC_USINT> paC_Command, COutputParameter<CIEC_LREAL> paC_Arg, CAnyBitOutputParameter<CIEC_BOOL> paC_Release, CAnyBitOutputParameter<CIEC_BOOL> paEquipmentFree) {
        COutputGuard guard_ErrorID(paErrorID);
        COutputGuard guard_TimerDT(paTimerDT);
        COutputGuard guard_C_Holder(paC_Holder);
        COutputGuard guard_C_Command(paC_Command);
        COutputGuard guard_C_Arg(paC_Arg);
        COutputGuard guard_C_Release(paC_Release);
        COutputGuard guard_EquipmentFree(paEquipmentFree);
        var_Holder = paHolder;
        var_ReleaseAfter = paReleaseAfter;
        var_Pre = paPre;
        var_Post = paPost;
        var_Inv = paInv;
        var_Timed = paTimed;
        var_RunTime = paRunTime;
        var_Command = paCommand;
        var_Arg = paArg;
        var_StopCommand = paStopCommand;
        var_EqHolder = paEqHolder;
        executeEvent(scmEventWAIT_OVERID, nullptr);
        *paErrorID = var_ErrorID;
        *paTimerDT = var_TimerDT;
        *paC_Holder = var_C_Holder;
        *paC_Command = var_C_Command;
        *paC_Arg = var_C_Arg;
        *paC_Release = var_C_Release;
        *paEquipmentFree = var_EquipmentFree;
      }

      void evt_PLAYED(const CIEC_WSTRING &paHolder, const CIEC_BOOL &paReleaseAfter, const CIEC_BOOL &paPre, const CIEC_BOOL &paPost, const CIEC_BOOL &paInv, const CIEC_BOOL &paTimed, const CIEC_TIME &paRunTime, const CIEC_USINT &paCommand, const CIEC_LREAL &paArg, const CIEC_USINT &paStopCommand, const CIEC_WSTRING &paEqHolder, COutputParameter<CIEC_UINT> paErrorID, COutputParameter<CIEC_TIME> paTimerDT, COutputParameter<CIEC_WSTRING> paC_Holder, COutputParameter<CIEC_USINT> paC_Command, COutputParameter<CIEC_LREAL> paC_Arg, CAnyBitOutputParameter<CIEC_BOOL> paC_Release, CAnyBitOutputParameter<CIEC_BOOL> paEquipmentFree) {
        COutputGuard guard_ErrorID(paErrorID);
        COutputGuard guard_TimerDT(paTimerDT);
        COutputGuard guard_C_Holder(paC_Holder);
        COutputGuard guard_C_Command(paC_Command);
        COutputGuard guard_C_Arg(paC_Arg);
        COutputGuard guard_C_Release(paC_Release);
        COutputGuard guard_EquipmentFree(paEquipmentFree);
        var_Holder = paHolder;
        var_ReleaseAfter = paReleaseAfter;
        var_Pre = paPre;
        var_Post = paPost;
        var_Inv = paInv;
        var_Timed = paTimed;
        var_RunTime = paRunTime;
        var_Command = paCommand;
        var_Arg = paArg;
        var_StopCommand = paStopCommand;
        var_EqHolder = paEqHolder;
        executeEvent(scmEventPLAYEDID, nullptr);
        *paErrorID = var_ErrorID;
        *paTimerDT = var_TimerDT;
        *paC_Holder = var_C_Holder;
        *paC_Command = var_C_Command;
        *paC_Arg = var_C_Arg;
        *paC_Release = var_C_Release;
        *paEquipmentFree = var_EquipmentFree;
      }
  };
}

