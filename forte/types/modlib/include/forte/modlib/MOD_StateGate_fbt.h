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

#pragma once

#include "forte/basicfb.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"

namespace forte::modlib {
  class FORTE_MOD_StateGate final : public CBasicFB {
      DECLARE_FIRMWARE_FB(FORTE_MOD_StateGate)

    private:
      static const TEventID scmEventRESET_RSPID = 0;
      static const TEventID scmEventSTART_RSPID = 1;
      static const TEventID scmEventSTOP_RSPID = 2;
      static const TEventID scmEventABORT_RSPID = 3;
      static const TEventID scmEventCLEAR_RSPID = 4;
      static const TEventID scmEventGO_RESETID = 5;
      static const TEventID scmEventGO_STARTID = 6;
      static const TEventID scmEventGO_STOPID = 7;
      static const TEventID scmEventGO_ABORTID = 8;
      static const TEventID scmEventGO_CLEARID = 9;
      static const TEventID scmEventRESET_REQID = 0;
      static const TEventID scmEventSTART_REQID = 1;
      static const TEventID scmEventSTOP_REQID = 2;
      static const TEventID scmEventABORT_REQID = 3;
      static const TEventID scmEventCLEAR_REQID = 4;
      static const TEventID scmEventOWNER_CHGID = 5;
      static const TEventID scmEventSTATE_CHGID = 6;

      CIEC_BOOL var_Owned;

      CIEC_ANY *getVarInternal(size_t) override;

      void alg_Alg_ChkReset(void);
      void alg_Alg_ChkStart(void);
      void alg_Alg_ChkStop(void);
      void alg_Alg_ChkAbort(void);
      void alg_Alg_ChkClear(void);

      static const TForteInt16 scmStateWait = 0;
      static const TForteInt16 scmStateChkReset = 1;
      static const TForteInt16 scmStateGoReset = 2;
      static const TForteInt16 scmStateChkStart = 3;
      static const TForteInt16 scmStateGoStart = 4;
      static const TForteInt16 scmStateChkStop = 5;
      static const TForteInt16 scmStateGoStop = 6;
      static const TForteInt16 scmStateChkAbort = 7;
      static const TForteInt16 scmStateGoAbort = 8;
      static const TForteInt16 scmStateChkClear = 9;
      static const TForteInt16 scmStateGoClear = 10;

      void enterStateWait(CEventChainExecutionThread *const paECET);
      void enterStateChkReset(CEventChainExecutionThread *const paECET);
      void enterStateGoReset(CEventChainExecutionThread *const paECET);
      void enterStateChkStart(CEventChainExecutionThread *const paECET);
      void enterStateGoStart(CEventChainExecutionThread *const paECET);
      void enterStateChkStop(CEventChainExecutionThread *const paECET);
      void enterStateGoStop(CEventChainExecutionThread *const paECET);
      void enterStateChkAbort(CEventChainExecutionThread *const paECET);
      void enterStateGoAbort(CEventChainExecutionThread *const paECET);
      void enterStateChkClear(CEventChainExecutionThread *const paECET);
      void enterStateGoClear(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_MOD_StateGate(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_WSTRING var_ResetSession;
      CIEC_WSTRING var_StartSession;
      CIEC_WSTRING var_StopSession;
      CIEC_WSTRING var_AbortSession;
      CIEC_WSTRING var_ClearSession;
      CIEC_WSTRING var_Owner;
      CIEC_USINT var_State;

      CIEC_BOOL var_Accepted;
      CIEC_UINT var_ErrorID;

      CEventConnection conn_RESET_RSP;
      CEventConnection conn_START_RSP;
      CEventConnection conn_STOP_RSP;
      CEventConnection conn_ABORT_RSP;
      CEventConnection conn_CLEAR_RSP;
      CEventConnection conn_GO_RESET;
      CEventConnection conn_GO_START;
      CEventConnection conn_GO_STOP;
      CEventConnection conn_GO_ABORT;
      CEventConnection conn_GO_CLEAR;

      CDataConnection *conn_ResetSession;
      CDataConnection *conn_StartSession;
      CDataConnection *conn_StopSession;
      CDataConnection *conn_AbortSession;
      CDataConnection *conn_ClearSession;
      CDataConnection *conn_Owner;
      CDataConnection *conn_State;

      COutDataConnection<CIEC_BOOL> conn_Accepted;
      COutDataConnection<CIEC_UINT> conn_ErrorID;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_RESET_REQ(const CIEC_WSTRING &paResetSession, const CIEC_WSTRING &paStartSession, const CIEC_WSTRING &paStopSession, const CIEC_WSTRING &paAbortSession, const CIEC_WSTRING &paClearSession, const CIEC_WSTRING &paOwner, const CIEC_USINT &paState, CAnyBitOutputParameter<CIEC_BOOL> paAccepted, COutputParameter<CIEC_UINT> paErrorID) {
        COutputGuard guard_Accepted(paAccepted);
        COutputGuard guard_ErrorID(paErrorID);
        var_ResetSession = paResetSession;
        var_StartSession = paStartSession;
        var_StopSession = paStopSession;
        var_AbortSession = paAbortSession;
        var_ClearSession = paClearSession;
        var_Owner = paOwner;
        var_State = paState;
        executeEvent(scmEventRESET_REQID, nullptr);
        *paAccepted = var_Accepted;
        *paErrorID = var_ErrorID;
      }

      void evt_START_REQ(const CIEC_WSTRING &paResetSession, const CIEC_WSTRING &paStartSession, const CIEC_WSTRING &paStopSession, const CIEC_WSTRING &paAbortSession, const CIEC_WSTRING &paClearSession, const CIEC_WSTRING &paOwner, const CIEC_USINT &paState, CAnyBitOutputParameter<CIEC_BOOL> paAccepted, COutputParameter<CIEC_UINT> paErrorID) {
        COutputGuard guard_Accepted(paAccepted);
        COutputGuard guard_ErrorID(paErrorID);
        var_ResetSession = paResetSession;
        var_StartSession = paStartSession;
        var_StopSession = paStopSession;
        var_AbortSession = paAbortSession;
        var_ClearSession = paClearSession;
        var_Owner = paOwner;
        var_State = paState;
        executeEvent(scmEventSTART_REQID, nullptr);
        *paAccepted = var_Accepted;
        *paErrorID = var_ErrorID;
      }

      void evt_STOP_REQ(const CIEC_WSTRING &paResetSession, const CIEC_WSTRING &paStartSession, const CIEC_WSTRING &paStopSession, const CIEC_WSTRING &paAbortSession, const CIEC_WSTRING &paClearSession, const CIEC_WSTRING &paOwner, const CIEC_USINT &paState, CAnyBitOutputParameter<CIEC_BOOL> paAccepted, COutputParameter<CIEC_UINT> paErrorID) {
        COutputGuard guard_Accepted(paAccepted);
        COutputGuard guard_ErrorID(paErrorID);
        var_ResetSession = paResetSession;
        var_StartSession = paStartSession;
        var_StopSession = paStopSession;
        var_AbortSession = paAbortSession;
        var_ClearSession = paClearSession;
        var_Owner = paOwner;
        var_State = paState;
        executeEvent(scmEventSTOP_REQID, nullptr);
        *paAccepted = var_Accepted;
        *paErrorID = var_ErrorID;
      }

      void evt_ABORT_REQ(const CIEC_WSTRING &paResetSession, const CIEC_WSTRING &paStartSession, const CIEC_WSTRING &paStopSession, const CIEC_WSTRING &paAbortSession, const CIEC_WSTRING &paClearSession, const CIEC_WSTRING &paOwner, const CIEC_USINT &paState, CAnyBitOutputParameter<CIEC_BOOL> paAccepted, COutputParameter<CIEC_UINT> paErrorID) {
        COutputGuard guard_Accepted(paAccepted);
        COutputGuard guard_ErrorID(paErrorID);
        var_ResetSession = paResetSession;
        var_StartSession = paStartSession;
        var_StopSession = paStopSession;
        var_AbortSession = paAbortSession;
        var_ClearSession = paClearSession;
        var_Owner = paOwner;
        var_State = paState;
        executeEvent(scmEventABORT_REQID, nullptr);
        *paAccepted = var_Accepted;
        *paErrorID = var_ErrorID;
      }

      void evt_CLEAR_REQ(const CIEC_WSTRING &paResetSession, const CIEC_WSTRING &paStartSession, const CIEC_WSTRING &paStopSession, const CIEC_WSTRING &paAbortSession, const CIEC_WSTRING &paClearSession, const CIEC_WSTRING &paOwner, const CIEC_USINT &paState, CAnyBitOutputParameter<CIEC_BOOL> paAccepted, COutputParameter<CIEC_UINT> paErrorID) {
        COutputGuard guard_Accepted(paAccepted);
        COutputGuard guard_ErrorID(paErrorID);
        var_ResetSession = paResetSession;
        var_StartSession = paStartSession;
        var_StopSession = paStopSession;
        var_AbortSession = paAbortSession;
        var_ClearSession = paClearSession;
        var_Owner = paOwner;
        var_State = paState;
        executeEvent(scmEventCLEAR_REQID, nullptr);
        *paAccepted = var_Accepted;
        *paErrorID = var_ErrorID;
      }

      void evt_OWNER_CHG(const CIEC_WSTRING &paResetSession, const CIEC_WSTRING &paStartSession, const CIEC_WSTRING &paStopSession, const CIEC_WSTRING &paAbortSession, const CIEC_WSTRING &paClearSession, const CIEC_WSTRING &paOwner, const CIEC_USINT &paState, CAnyBitOutputParameter<CIEC_BOOL> paAccepted, COutputParameter<CIEC_UINT> paErrorID) {
        COutputGuard guard_Accepted(paAccepted);
        COutputGuard guard_ErrorID(paErrorID);
        var_ResetSession = paResetSession;
        var_StartSession = paStartSession;
        var_StopSession = paStopSession;
        var_AbortSession = paAbortSession;
        var_ClearSession = paClearSession;
        var_Owner = paOwner;
        var_State = paState;
        executeEvent(scmEventOWNER_CHGID, nullptr);
        *paAccepted = var_Accepted;
        *paErrorID = var_ErrorID;
      }

      void evt_STATE_CHG(const CIEC_WSTRING &paResetSession, const CIEC_WSTRING &paStartSession, const CIEC_WSTRING &paStopSession, const CIEC_WSTRING &paAbortSession, const CIEC_WSTRING &paClearSession, const CIEC_WSTRING &paOwner, const CIEC_USINT &paState, CAnyBitOutputParameter<CIEC_BOOL> paAccepted, COutputParameter<CIEC_UINT> paErrorID) {
        COutputGuard guard_Accepted(paAccepted);
        COutputGuard guard_ErrorID(paErrorID);
        var_ResetSession = paResetSession;
        var_StartSession = paStartSession;
        var_StopSession = paStopSession;
        var_AbortSession = paAbortSession;
        var_ClearSession = paClearSession;
        var_Owner = paOwner;
        var_State = paState;
        executeEvent(scmEventSTATE_CHGID, nullptr);
        *paAccepted = var_Accepted;
        *paErrorID = var_ErrorID;
      }
  };
}

