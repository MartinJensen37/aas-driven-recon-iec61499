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

#pragma once

#include "forte/basicfb.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_int.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"

namespace forte::modlib {
  class FORTE_SKILL_Control final : public CBasicFB {
      DECLARE_FIRMWARE_FB(FORTE_SKILL_Control)

    private:
      static const TEventID scmEventINITOID = 0;
      static const TEventID scmEventPUBID = 1;
      static const TEventID scmEventRUNID = 2;
      static const TEventID scmEventHALT_SEQID = 3;
      static const TEventID scmEventABORT_SEQID = 4;
      static const TEventID scmEventRESET_SEQID = 5;
      static const TEventID scmEventRUN_STOPPINGID = 6;
      static const TEventID scmEventSUCCESSID = 7;
      static const TEventID scmEventFAILUREID = 8;
      static const TEventID scmEventRELEASEID = 9;
      static const TEventID scmEventACTID = 10;
      static const TEventID scmEventTO_IDLE_STARTID = 11;
      static const TEventID scmEventTO_IDLE_STOPID = 12;
      static const TEventID scmEventINITID = 0;
      static const TEventID scmEventSTARTID = 1;
      static const TEventID scmEventHALTID = 2;
      static const TEventID scmEventABORTID = 3;
      static const TEventID scmEventRESETID = 4;
      static const TEventID scmEventEXECUTE_DONEID = 5;
      static const TEventID scmEventEXECUTE_FAILEDID = 6;
      static const TEventID scmEventSTOPPING_DONEID = 7;
      static const TEventID scmEventTO_IDLEID = 8;

      CIEC_BOOL var_Active;

      CIEC_ANY *getVarInternal(size_t) override;

      void alg_Alg_Init(void);
      void alg_Alg_Idle(void);
      void alg_Alg_Running(void);
      void alg_Alg_Stopping(void);
      void alg_Alg_StopProc(void);
      void alg_Alg_Succeeded(void);
      void alg_Alg_Failed(void);
      void alg_Alg_Aborted(void);
      void alg_Alg_Go(void);
      void alg_Alg_Succeed(void);
      void alg_Alg_Fail(void);
      void alg_Alg_Interrupted(void);
      void alg_Alg_AbortActive(void);
      void alg_Alg_StartRefused(void);

      static const TForteInt16 scmStateSTART = 0;
      static const TForteInt16 scmStateInit = 1;
      static const TForteInt16 scmStateIdle = 2;
      static const TForteInt16 scmStateRunning = 3;
      static const TForteInt16 scmStateStopping = 4;
      static const TForteInt16 scmStateStopProc = 5;
      static const TForteInt16 scmStateSucceeded = 6;
      static const TForteInt16 scmStateFailed = 7;
      static const TForteInt16 scmStateAborted = 8;
      static const TForteInt16 scmStateGo = 9;
      static const TForteInt16 scmStateHalt = 10;
      static const TForteInt16 scmStateRunStop = 11;
      static const TForteInt16 scmStateSucceed = 12;
      static const TForteInt16 scmStateFail = 13;
      static const TForteInt16 scmStateInterrupted = 14;
      static const TForteInt16 scmStateAbortChk = 15;
      static const TForteInt16 scmStateAbortActive = 16;
      static const TForteInt16 scmStateAbortIdle = 17;
      static const TForteInt16 scmStateStartRefused = 18;
      static const TForteInt16 scmStateResetOk = 19;

      void enterStateSTART(CEventChainExecutionThread *const paECET);
      void enterStateInit(CEventChainExecutionThread *const paECET);
      void enterStateIdle(CEventChainExecutionThread *const paECET);
      void enterStateRunning(CEventChainExecutionThread *const paECET);
      void enterStateStopping(CEventChainExecutionThread *const paECET);
      void enterStateStopProc(CEventChainExecutionThread *const paECET);
      void enterStateSucceeded(CEventChainExecutionThread *const paECET);
      void enterStateFailed(CEventChainExecutionThread *const paECET);
      void enterStateAborted(CEventChainExecutionThread *const paECET);
      void enterStateGo(CEventChainExecutionThread *const paECET);
      void enterStateHalt(CEventChainExecutionThread *const paECET);
      void enterStateRunStop(CEventChainExecutionThread *const paECET);
      void enterStateSucceed(CEventChainExecutionThread *const paECET);
      void enterStateFail(CEventChainExecutionThread *const paECET);
      void enterStateInterrupted(CEventChainExecutionThread *const paECET);
      void enterStateAbortChk(CEventChainExecutionThread *const paECET);
      void enterStateAbortActive(CEventChainExecutionThread *const paECET);
      void enterStateAbortIdle(CEventChainExecutionThread *const paECET);
      void enterStateStartRefused(CEventChainExecutionThread *const paECET);
      void enterStateResetOk(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_SKILL_Control(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_WSTRING var_Module;
      CIEC_WSTRING var_UaRoot;
      CIEC_WSTRING var_UaPath;
      CIEC_BOOL var_ByClient;
      CIEC_UINT var_ExecuteError;

      CIEC_WSTRING var_StartMethodId;
      CIEC_WSTRING var_StopMethodId;
      CIEC_WSTRING var_AbortMethodId;
      CIEC_WSTRING var_ResetMethodId;
      CIEC_WSTRING var_StateId;
      CIEC_WSTRING var_ActivityId;
      CIEC_WSTRING var_ReleaseId;
      CIEC_USINT var_State;
      CIEC_UINT var_ErrorID;
      CIEC_INT var_ActivityDelta;
      CIEC_BOOL var_CalledByClient;

      CEventConnection conn_INITO;
      CEventConnection conn_PUB;
      CEventConnection conn_RUN;
      CEventConnection conn_HALT_SEQ;
      CEventConnection conn_ABORT_SEQ;
      CEventConnection conn_RESET_SEQ;
      CEventConnection conn_RUN_STOPPING;
      CEventConnection conn_SUCCESS;
      CEventConnection conn_FAILURE;
      CEventConnection conn_RELEASE;
      CEventConnection conn_ACT;
      CEventConnection conn_TO_IDLE_START;
      CEventConnection conn_TO_IDLE_STOP;

      CDataConnection *conn_Module;
      CDataConnection *conn_UaRoot;
      CDataConnection *conn_UaPath;
      CDataConnection *conn_ByClient;
      CDataConnection *conn_ExecuteError;

      COutDataConnection<CIEC_WSTRING> conn_StartMethodId;
      COutDataConnection<CIEC_WSTRING> conn_StopMethodId;
      COutDataConnection<CIEC_WSTRING> conn_AbortMethodId;
      COutDataConnection<CIEC_WSTRING> conn_ResetMethodId;
      COutDataConnection<CIEC_WSTRING> conn_StateId;
      COutDataConnection<CIEC_WSTRING> conn_ActivityId;
      COutDataConnection<CIEC_WSTRING> conn_ReleaseId;
      COutDataConnection<CIEC_USINT> conn_State;
      COutDataConnection<CIEC_UINT> conn_ErrorID;
      COutDataConnection<CIEC_INT> conn_ActivityDelta;
      COutDataConnection<CIEC_BOOL> conn_CalledByClient;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_INIT(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paUaPath, const CIEC_BOOL &paByClient, const CIEC_UINT &paExecuteError, COutputParameter<CIEC_WSTRING> paStartMethodId, COutputParameter<CIEC_WSTRING> paStopMethodId, COutputParameter<CIEC_WSTRING> paAbortMethodId, COutputParameter<CIEC_WSTRING> paResetMethodId, COutputParameter<CIEC_WSTRING> paStateId, COutputParameter<CIEC_WSTRING> paActivityId, COutputParameter<CIEC_WSTRING> paReleaseId, COutputParameter<CIEC_USINT> paState, COutputParameter<CIEC_UINT> paErrorID, COutputParameter<CIEC_INT> paActivityDelta, CAnyBitOutputParameter<CIEC_BOOL> paCalledByClient) {
        COutputGuard guard_StartMethodId(paStartMethodId);
        COutputGuard guard_StopMethodId(paStopMethodId);
        COutputGuard guard_AbortMethodId(paAbortMethodId);
        COutputGuard guard_ResetMethodId(paResetMethodId);
        COutputGuard guard_StateId(paStateId);
        COutputGuard guard_ActivityId(paActivityId);
        COutputGuard guard_ReleaseId(paReleaseId);
        COutputGuard guard_State(paState);
        COutputGuard guard_ErrorID(paErrorID);
        COutputGuard guard_ActivityDelta(paActivityDelta);
        COutputGuard guard_CalledByClient(paCalledByClient);
        var_Module = paModule;
        var_UaRoot = paUaRoot;
        var_UaPath = paUaPath;
        var_ByClient = paByClient;
        var_ExecuteError = paExecuteError;
        executeEvent(scmEventINITID, nullptr);
        *paStartMethodId = var_StartMethodId;
        *paStopMethodId = var_StopMethodId;
        *paAbortMethodId = var_AbortMethodId;
        *paResetMethodId = var_ResetMethodId;
        *paStateId = var_StateId;
        *paActivityId = var_ActivityId;
        *paReleaseId = var_ReleaseId;
        *paState = var_State;
        *paErrorID = var_ErrorID;
        *paActivityDelta = var_ActivityDelta;
        *paCalledByClient = var_CalledByClient;
      }

      void evt_START(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paUaPath, const CIEC_BOOL &paByClient, const CIEC_UINT &paExecuteError, COutputParameter<CIEC_WSTRING> paStartMethodId, COutputParameter<CIEC_WSTRING> paStopMethodId, COutputParameter<CIEC_WSTRING> paAbortMethodId, COutputParameter<CIEC_WSTRING> paResetMethodId, COutputParameter<CIEC_WSTRING> paStateId, COutputParameter<CIEC_WSTRING> paActivityId, COutputParameter<CIEC_WSTRING> paReleaseId, COutputParameter<CIEC_USINT> paState, COutputParameter<CIEC_UINT> paErrorID, COutputParameter<CIEC_INT> paActivityDelta, CAnyBitOutputParameter<CIEC_BOOL> paCalledByClient) {
        COutputGuard guard_StartMethodId(paStartMethodId);
        COutputGuard guard_StopMethodId(paStopMethodId);
        COutputGuard guard_AbortMethodId(paAbortMethodId);
        COutputGuard guard_ResetMethodId(paResetMethodId);
        COutputGuard guard_StateId(paStateId);
        COutputGuard guard_ActivityId(paActivityId);
        COutputGuard guard_ReleaseId(paReleaseId);
        COutputGuard guard_State(paState);
        COutputGuard guard_ErrorID(paErrorID);
        COutputGuard guard_ActivityDelta(paActivityDelta);
        COutputGuard guard_CalledByClient(paCalledByClient);
        var_Module = paModule;
        var_UaRoot = paUaRoot;
        var_UaPath = paUaPath;
        var_ByClient = paByClient;
        var_ExecuteError = paExecuteError;
        executeEvent(scmEventSTARTID, nullptr);
        *paStartMethodId = var_StartMethodId;
        *paStopMethodId = var_StopMethodId;
        *paAbortMethodId = var_AbortMethodId;
        *paResetMethodId = var_ResetMethodId;
        *paStateId = var_StateId;
        *paActivityId = var_ActivityId;
        *paReleaseId = var_ReleaseId;
        *paState = var_State;
        *paErrorID = var_ErrorID;
        *paActivityDelta = var_ActivityDelta;
        *paCalledByClient = var_CalledByClient;
      }

      void evt_HALT(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paUaPath, const CIEC_BOOL &paByClient, const CIEC_UINT &paExecuteError, COutputParameter<CIEC_WSTRING> paStartMethodId, COutputParameter<CIEC_WSTRING> paStopMethodId, COutputParameter<CIEC_WSTRING> paAbortMethodId, COutputParameter<CIEC_WSTRING> paResetMethodId, COutputParameter<CIEC_WSTRING> paStateId, COutputParameter<CIEC_WSTRING> paActivityId, COutputParameter<CIEC_WSTRING> paReleaseId, COutputParameter<CIEC_USINT> paState, COutputParameter<CIEC_UINT> paErrorID, COutputParameter<CIEC_INT> paActivityDelta, CAnyBitOutputParameter<CIEC_BOOL> paCalledByClient) {
        COutputGuard guard_StartMethodId(paStartMethodId);
        COutputGuard guard_StopMethodId(paStopMethodId);
        COutputGuard guard_AbortMethodId(paAbortMethodId);
        COutputGuard guard_ResetMethodId(paResetMethodId);
        COutputGuard guard_StateId(paStateId);
        COutputGuard guard_ActivityId(paActivityId);
        COutputGuard guard_ReleaseId(paReleaseId);
        COutputGuard guard_State(paState);
        COutputGuard guard_ErrorID(paErrorID);
        COutputGuard guard_ActivityDelta(paActivityDelta);
        COutputGuard guard_CalledByClient(paCalledByClient);
        var_Module = paModule;
        var_UaRoot = paUaRoot;
        var_UaPath = paUaPath;
        var_ByClient = paByClient;
        var_ExecuteError = paExecuteError;
        executeEvent(scmEventHALTID, nullptr);
        *paStartMethodId = var_StartMethodId;
        *paStopMethodId = var_StopMethodId;
        *paAbortMethodId = var_AbortMethodId;
        *paResetMethodId = var_ResetMethodId;
        *paStateId = var_StateId;
        *paActivityId = var_ActivityId;
        *paReleaseId = var_ReleaseId;
        *paState = var_State;
        *paErrorID = var_ErrorID;
        *paActivityDelta = var_ActivityDelta;
        *paCalledByClient = var_CalledByClient;
      }

      void evt_ABORT(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paUaPath, const CIEC_BOOL &paByClient, const CIEC_UINT &paExecuteError, COutputParameter<CIEC_WSTRING> paStartMethodId, COutputParameter<CIEC_WSTRING> paStopMethodId, COutputParameter<CIEC_WSTRING> paAbortMethodId, COutputParameter<CIEC_WSTRING> paResetMethodId, COutputParameter<CIEC_WSTRING> paStateId, COutputParameter<CIEC_WSTRING> paActivityId, COutputParameter<CIEC_WSTRING> paReleaseId, COutputParameter<CIEC_USINT> paState, COutputParameter<CIEC_UINT> paErrorID, COutputParameter<CIEC_INT> paActivityDelta, CAnyBitOutputParameter<CIEC_BOOL> paCalledByClient) {
        COutputGuard guard_StartMethodId(paStartMethodId);
        COutputGuard guard_StopMethodId(paStopMethodId);
        COutputGuard guard_AbortMethodId(paAbortMethodId);
        COutputGuard guard_ResetMethodId(paResetMethodId);
        COutputGuard guard_StateId(paStateId);
        COutputGuard guard_ActivityId(paActivityId);
        COutputGuard guard_ReleaseId(paReleaseId);
        COutputGuard guard_State(paState);
        COutputGuard guard_ErrorID(paErrorID);
        COutputGuard guard_ActivityDelta(paActivityDelta);
        COutputGuard guard_CalledByClient(paCalledByClient);
        var_Module = paModule;
        var_UaRoot = paUaRoot;
        var_UaPath = paUaPath;
        var_ByClient = paByClient;
        var_ExecuteError = paExecuteError;
        executeEvent(scmEventABORTID, nullptr);
        *paStartMethodId = var_StartMethodId;
        *paStopMethodId = var_StopMethodId;
        *paAbortMethodId = var_AbortMethodId;
        *paResetMethodId = var_ResetMethodId;
        *paStateId = var_StateId;
        *paActivityId = var_ActivityId;
        *paReleaseId = var_ReleaseId;
        *paState = var_State;
        *paErrorID = var_ErrorID;
        *paActivityDelta = var_ActivityDelta;
        *paCalledByClient = var_CalledByClient;
      }

      void evt_RESET(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paUaPath, const CIEC_BOOL &paByClient, const CIEC_UINT &paExecuteError, COutputParameter<CIEC_WSTRING> paStartMethodId, COutputParameter<CIEC_WSTRING> paStopMethodId, COutputParameter<CIEC_WSTRING> paAbortMethodId, COutputParameter<CIEC_WSTRING> paResetMethodId, COutputParameter<CIEC_WSTRING> paStateId, COutputParameter<CIEC_WSTRING> paActivityId, COutputParameter<CIEC_WSTRING> paReleaseId, COutputParameter<CIEC_USINT> paState, COutputParameter<CIEC_UINT> paErrorID, COutputParameter<CIEC_INT> paActivityDelta, CAnyBitOutputParameter<CIEC_BOOL> paCalledByClient) {
        COutputGuard guard_StartMethodId(paStartMethodId);
        COutputGuard guard_StopMethodId(paStopMethodId);
        COutputGuard guard_AbortMethodId(paAbortMethodId);
        COutputGuard guard_ResetMethodId(paResetMethodId);
        COutputGuard guard_StateId(paStateId);
        COutputGuard guard_ActivityId(paActivityId);
        COutputGuard guard_ReleaseId(paReleaseId);
        COutputGuard guard_State(paState);
        COutputGuard guard_ErrorID(paErrorID);
        COutputGuard guard_ActivityDelta(paActivityDelta);
        COutputGuard guard_CalledByClient(paCalledByClient);
        var_Module = paModule;
        var_UaRoot = paUaRoot;
        var_UaPath = paUaPath;
        var_ByClient = paByClient;
        var_ExecuteError = paExecuteError;
        executeEvent(scmEventRESETID, nullptr);
        *paStartMethodId = var_StartMethodId;
        *paStopMethodId = var_StopMethodId;
        *paAbortMethodId = var_AbortMethodId;
        *paResetMethodId = var_ResetMethodId;
        *paStateId = var_StateId;
        *paActivityId = var_ActivityId;
        *paReleaseId = var_ReleaseId;
        *paState = var_State;
        *paErrorID = var_ErrorID;
        *paActivityDelta = var_ActivityDelta;
        *paCalledByClient = var_CalledByClient;
      }

      void evt_EXECUTE_DONE(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paUaPath, const CIEC_BOOL &paByClient, const CIEC_UINT &paExecuteError, COutputParameter<CIEC_WSTRING> paStartMethodId, COutputParameter<CIEC_WSTRING> paStopMethodId, COutputParameter<CIEC_WSTRING> paAbortMethodId, COutputParameter<CIEC_WSTRING> paResetMethodId, COutputParameter<CIEC_WSTRING> paStateId, COutputParameter<CIEC_WSTRING> paActivityId, COutputParameter<CIEC_WSTRING> paReleaseId, COutputParameter<CIEC_USINT> paState, COutputParameter<CIEC_UINT> paErrorID, COutputParameter<CIEC_INT> paActivityDelta, CAnyBitOutputParameter<CIEC_BOOL> paCalledByClient) {
        COutputGuard guard_StartMethodId(paStartMethodId);
        COutputGuard guard_StopMethodId(paStopMethodId);
        COutputGuard guard_AbortMethodId(paAbortMethodId);
        COutputGuard guard_ResetMethodId(paResetMethodId);
        COutputGuard guard_StateId(paStateId);
        COutputGuard guard_ActivityId(paActivityId);
        COutputGuard guard_ReleaseId(paReleaseId);
        COutputGuard guard_State(paState);
        COutputGuard guard_ErrorID(paErrorID);
        COutputGuard guard_ActivityDelta(paActivityDelta);
        COutputGuard guard_CalledByClient(paCalledByClient);
        var_Module = paModule;
        var_UaRoot = paUaRoot;
        var_UaPath = paUaPath;
        var_ByClient = paByClient;
        var_ExecuteError = paExecuteError;
        executeEvent(scmEventEXECUTE_DONEID, nullptr);
        *paStartMethodId = var_StartMethodId;
        *paStopMethodId = var_StopMethodId;
        *paAbortMethodId = var_AbortMethodId;
        *paResetMethodId = var_ResetMethodId;
        *paStateId = var_StateId;
        *paActivityId = var_ActivityId;
        *paReleaseId = var_ReleaseId;
        *paState = var_State;
        *paErrorID = var_ErrorID;
        *paActivityDelta = var_ActivityDelta;
        *paCalledByClient = var_CalledByClient;
      }

      void evt_EXECUTE_FAILED(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paUaPath, const CIEC_BOOL &paByClient, const CIEC_UINT &paExecuteError, COutputParameter<CIEC_WSTRING> paStartMethodId, COutputParameter<CIEC_WSTRING> paStopMethodId, COutputParameter<CIEC_WSTRING> paAbortMethodId, COutputParameter<CIEC_WSTRING> paResetMethodId, COutputParameter<CIEC_WSTRING> paStateId, COutputParameter<CIEC_WSTRING> paActivityId, COutputParameter<CIEC_WSTRING> paReleaseId, COutputParameter<CIEC_USINT> paState, COutputParameter<CIEC_UINT> paErrorID, COutputParameter<CIEC_INT> paActivityDelta, CAnyBitOutputParameter<CIEC_BOOL> paCalledByClient) {
        COutputGuard guard_StartMethodId(paStartMethodId);
        COutputGuard guard_StopMethodId(paStopMethodId);
        COutputGuard guard_AbortMethodId(paAbortMethodId);
        COutputGuard guard_ResetMethodId(paResetMethodId);
        COutputGuard guard_StateId(paStateId);
        COutputGuard guard_ActivityId(paActivityId);
        COutputGuard guard_ReleaseId(paReleaseId);
        COutputGuard guard_State(paState);
        COutputGuard guard_ErrorID(paErrorID);
        COutputGuard guard_ActivityDelta(paActivityDelta);
        COutputGuard guard_CalledByClient(paCalledByClient);
        var_Module = paModule;
        var_UaRoot = paUaRoot;
        var_UaPath = paUaPath;
        var_ByClient = paByClient;
        var_ExecuteError = paExecuteError;
        executeEvent(scmEventEXECUTE_FAILEDID, nullptr);
        *paStartMethodId = var_StartMethodId;
        *paStopMethodId = var_StopMethodId;
        *paAbortMethodId = var_AbortMethodId;
        *paResetMethodId = var_ResetMethodId;
        *paStateId = var_StateId;
        *paActivityId = var_ActivityId;
        *paReleaseId = var_ReleaseId;
        *paState = var_State;
        *paErrorID = var_ErrorID;
        *paActivityDelta = var_ActivityDelta;
        *paCalledByClient = var_CalledByClient;
      }

      void evt_STOPPING_DONE(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paUaPath, const CIEC_BOOL &paByClient, const CIEC_UINT &paExecuteError, COutputParameter<CIEC_WSTRING> paStartMethodId, COutputParameter<CIEC_WSTRING> paStopMethodId, COutputParameter<CIEC_WSTRING> paAbortMethodId, COutputParameter<CIEC_WSTRING> paResetMethodId, COutputParameter<CIEC_WSTRING> paStateId, COutputParameter<CIEC_WSTRING> paActivityId, COutputParameter<CIEC_WSTRING> paReleaseId, COutputParameter<CIEC_USINT> paState, COutputParameter<CIEC_UINT> paErrorID, COutputParameter<CIEC_INT> paActivityDelta, CAnyBitOutputParameter<CIEC_BOOL> paCalledByClient) {
        COutputGuard guard_StartMethodId(paStartMethodId);
        COutputGuard guard_StopMethodId(paStopMethodId);
        COutputGuard guard_AbortMethodId(paAbortMethodId);
        COutputGuard guard_ResetMethodId(paResetMethodId);
        COutputGuard guard_StateId(paStateId);
        COutputGuard guard_ActivityId(paActivityId);
        COutputGuard guard_ReleaseId(paReleaseId);
        COutputGuard guard_State(paState);
        COutputGuard guard_ErrorID(paErrorID);
        COutputGuard guard_ActivityDelta(paActivityDelta);
        COutputGuard guard_CalledByClient(paCalledByClient);
        var_Module = paModule;
        var_UaRoot = paUaRoot;
        var_UaPath = paUaPath;
        var_ByClient = paByClient;
        var_ExecuteError = paExecuteError;
        executeEvent(scmEventSTOPPING_DONEID, nullptr);
        *paStartMethodId = var_StartMethodId;
        *paStopMethodId = var_StopMethodId;
        *paAbortMethodId = var_AbortMethodId;
        *paResetMethodId = var_ResetMethodId;
        *paStateId = var_StateId;
        *paActivityId = var_ActivityId;
        *paReleaseId = var_ReleaseId;
        *paState = var_State;
        *paErrorID = var_ErrorID;
        *paActivityDelta = var_ActivityDelta;
        *paCalledByClient = var_CalledByClient;
      }

      void evt_TO_IDLE(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paUaPath, const CIEC_BOOL &paByClient, const CIEC_UINT &paExecuteError, COutputParameter<CIEC_WSTRING> paStartMethodId, COutputParameter<CIEC_WSTRING> paStopMethodId, COutputParameter<CIEC_WSTRING> paAbortMethodId, COutputParameter<CIEC_WSTRING> paResetMethodId, COutputParameter<CIEC_WSTRING> paStateId, COutputParameter<CIEC_WSTRING> paActivityId, COutputParameter<CIEC_WSTRING> paReleaseId, COutputParameter<CIEC_USINT> paState, COutputParameter<CIEC_UINT> paErrorID, COutputParameter<CIEC_INT> paActivityDelta, CAnyBitOutputParameter<CIEC_BOOL> paCalledByClient) {
        COutputGuard guard_StartMethodId(paStartMethodId);
        COutputGuard guard_StopMethodId(paStopMethodId);
        COutputGuard guard_AbortMethodId(paAbortMethodId);
        COutputGuard guard_ResetMethodId(paResetMethodId);
        COutputGuard guard_StateId(paStateId);
        COutputGuard guard_ActivityId(paActivityId);
        COutputGuard guard_ReleaseId(paReleaseId);
        COutputGuard guard_State(paState);
        COutputGuard guard_ErrorID(paErrorID);
        COutputGuard guard_ActivityDelta(paActivityDelta);
        COutputGuard guard_CalledByClient(paCalledByClient);
        var_Module = paModule;
        var_UaRoot = paUaRoot;
        var_UaPath = paUaPath;
        var_ByClient = paByClient;
        var_ExecuteError = paExecuteError;
        executeEvent(scmEventTO_IDLEID, nullptr);
        *paStartMethodId = var_StartMethodId;
        *paStopMethodId = var_StopMethodId;
        *paAbortMethodId = var_AbortMethodId;
        *paResetMethodId = var_ResetMethodId;
        *paStateId = var_StateId;
        *paActivityId = var_ActivityId;
        *paReleaseId = var_ReleaseId;
        *paState = var_State;
        *paErrorID = var_ErrorID;
        *paActivityDelta = var_ActivityDelta;
        *paCalledByClient = var_CalledByClient;
      }
  };
}

