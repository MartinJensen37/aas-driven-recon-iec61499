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

#pragma once

#include "forte/basicfb.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/forte_st_util.h"

namespace forte::modlib {
  class FORTE_MOD_StateLogic final : public CBasicFB {
      DECLARE_FIRMWARE_FB(FORTE_MOD_StateLogic)

    private:
      static const TEventID scmEventCNFID = 0;
      static const TEventID scmEventRUN_RESETTINGID = 1;
      static const TEventID scmEventRUN_STOPPINGID = 2;
      static const TEventID scmEventWD_STARTID = 3;
      static const TEventID scmEventWD_STOPID = 4;
      static const TEventID scmEventRESETID = 0;
      static const TEventID scmEventSTARTID = 1;
      static const TEventID scmEventSTOPID = 2;
      static const TEventID scmEventABORTID = 3;
      static const TEventID scmEventCLEARID = 4;
      static const TEventID scmEventACTID = 5;
      static const TEventID scmEventRESETTING_DONEID = 6;
      static const TEventID scmEventRESETTING_FAILEDID = 7;
      static const TEventID scmEventSTOPPING_DONEID = 8;
      static const TEventID scmEventSTOPPING_FAILEDID = 9;
      static const TEventID scmEventSTOP_TIMEOUTID = 10;

      CIEC_ANY *getVarInternal(size_t) override;

      void alg_Alg_Stopped(void);
      void alg_Alg_Resetting(void);
      void alg_Alg_Idle(void);
      void alg_Alg_Starting(void);
      void alg_Alg_Execute(void);
      void alg_Alg_Stopping(void);
      void alg_Alg_Aborting(void);
      void alg_Alg_Aborted(void);
      void alg_Alg_Clearing(void);

      static const TForteInt16 scmStateStopped = 0;
      static const TForteInt16 scmStateResetting = 1;
      static const TForteInt16 scmStateResettingW = 2;
      static const TForteInt16 scmStateIdle = 3;
      static const TForteInt16 scmStateStarting = 4;
      static const TForteInt16 scmStateExecute = 5;
      static const TForteInt16 scmStateStopping = 6;
      static const TForteInt16 scmStateStoppingW = 7;
      static const TForteInt16 scmStateStopProc = 8;
      static const TForteInt16 scmStateStopProcW = 9;
      static const TForteInt16 scmStateAborting = 10;
      static const TForteInt16 scmStateAborted = 11;
      static const TForteInt16 scmStateClearing = 12;

      void enterStateStopped(CEventChainExecutionThread *const paECET);
      void enterStateResetting(CEventChainExecutionThread *const paECET);
      void enterStateResettingW(CEventChainExecutionThread *const paECET);
      void enterStateIdle(CEventChainExecutionThread *const paECET);
      void enterStateStarting(CEventChainExecutionThread *const paECET);
      void enterStateExecute(CEventChainExecutionThread *const paECET);
      void enterStateStopping(CEventChainExecutionThread *const paECET);
      void enterStateStoppingW(CEventChainExecutionThread *const paECET);
      void enterStateStopProc(CEventChainExecutionThread *const paECET);
      void enterStateStopProcW(CEventChainExecutionThread *const paECET);
      void enterStateAborting(CEventChainExecutionThread *const paECET);
      void enterStateAborted(CEventChainExecutionThread *const paECET);
      void enterStateClearing(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_MOD_StateLogic(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_BOOL var_AllIdle;

      CIEC_USINT var_State;

      CEventConnection conn_CNF;
      CEventConnection conn_RUN_RESETTING;
      CEventConnection conn_RUN_STOPPING;
      CEventConnection conn_WD_START;
      CEventConnection conn_WD_STOP;

      CDataConnection *conn_AllIdle;

      COutDataConnection<CIEC_USINT> conn_State;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_RESET(const CIEC_BOOL &paAllIdle, COutputParameter<CIEC_USINT> paState) {
        COutputGuard guard_State(paState);
        var_AllIdle = paAllIdle;
        executeEvent(scmEventRESETID, nullptr);
        *paState = var_State;
      }

      void evt_START(const CIEC_BOOL &paAllIdle, COutputParameter<CIEC_USINT> paState) {
        COutputGuard guard_State(paState);
        var_AllIdle = paAllIdle;
        executeEvent(scmEventSTARTID, nullptr);
        *paState = var_State;
      }

      void evt_STOP(const CIEC_BOOL &paAllIdle, COutputParameter<CIEC_USINT> paState) {
        COutputGuard guard_State(paState);
        var_AllIdle = paAllIdle;
        executeEvent(scmEventSTOPID, nullptr);
        *paState = var_State;
      }

      void evt_ABORT(const CIEC_BOOL &paAllIdle, COutputParameter<CIEC_USINT> paState) {
        COutputGuard guard_State(paState);
        var_AllIdle = paAllIdle;
        executeEvent(scmEventABORTID, nullptr);
        *paState = var_State;
      }

      void evt_CLEAR(const CIEC_BOOL &paAllIdle, COutputParameter<CIEC_USINT> paState) {
        COutputGuard guard_State(paState);
        var_AllIdle = paAllIdle;
        executeEvent(scmEventCLEARID, nullptr);
        *paState = var_State;
      }

      void evt_ACT(const CIEC_BOOL &paAllIdle, COutputParameter<CIEC_USINT> paState) {
        COutputGuard guard_State(paState);
        var_AllIdle = paAllIdle;
        executeEvent(scmEventACTID, nullptr);
        *paState = var_State;
      }

      void evt_RESETTING_DONE(const CIEC_BOOL &paAllIdle, COutputParameter<CIEC_USINT> paState) {
        COutputGuard guard_State(paState);
        var_AllIdle = paAllIdle;
        executeEvent(scmEventRESETTING_DONEID, nullptr);
        *paState = var_State;
      }

      void evt_RESETTING_FAILED(const CIEC_BOOL &paAllIdle, COutputParameter<CIEC_USINT> paState) {
        COutputGuard guard_State(paState);
        var_AllIdle = paAllIdle;
        executeEvent(scmEventRESETTING_FAILEDID, nullptr);
        *paState = var_State;
      }

      void evt_STOPPING_DONE(const CIEC_BOOL &paAllIdle, COutputParameter<CIEC_USINT> paState) {
        COutputGuard guard_State(paState);
        var_AllIdle = paAllIdle;
        executeEvent(scmEventSTOPPING_DONEID, nullptr);
        *paState = var_State;
      }

      void evt_STOPPING_FAILED(const CIEC_BOOL &paAllIdle, COutputParameter<CIEC_USINT> paState) {
        COutputGuard guard_State(paState);
        var_AllIdle = paAllIdle;
        executeEvent(scmEventSTOPPING_FAILEDID, nullptr);
        *paState = var_State;
      }

      void evt_STOP_TIMEOUT(const CIEC_BOOL &paAllIdle, COutputParameter<CIEC_USINT> paState) {
        COutputGuard guard_State(paState);
        var_AllIdle = paAllIdle;
        executeEvent(scmEventSTOP_TIMEOUTID, nullptr);
        *paState = var_State;
      }
  };
}

