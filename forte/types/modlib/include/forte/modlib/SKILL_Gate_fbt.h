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

#pragma once

#include "forte/basicfb.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"

namespace forte::modlib {
  class FORTE_SKILL_Gate final : public CBasicFB {
      DECLARE_FIRMWARE_FB(FORTE_SKILL_Gate)

    private:
      static const TEventID scmEventSTART_RSPID = 0;
      static const TEventID scmEventSTOP_RSPID = 1;
      static const TEventID scmEventABORT_RSPID = 2;
      static const TEventID scmEventRESET_RSPID = 3;
      static const TEventID scmEventGO_STARTID = 4;
      static const TEventID scmEventGO_HALTID = 5;
      static const TEventID scmEventGO_ABORTID = 6;
      static const TEventID scmEventGO_RESETID = 7;
      static const TEventID scmEventSTART_REQID = 0;
      static const TEventID scmEventSTOP_REQID = 1;
      static const TEventID scmEventABORT_REQID = 2;
      static const TEventID scmEventRESET_REQID = 3;
      static const TEventID scmEventOWNER_CHGID = 4;
      static const TEventID scmEventMOD_CHGID = 5;
      static const TEventID scmEventSKILL_CHGID = 6;
      static const TEventID scmEventSTARTID = 7;
      static const TEventID scmEventHALTID = 8;
      static const TEventID scmEventABORTID = 9;
      static const TEventID scmEventRESETID = 10;

      CIEC_BOOL var_Owned;

      CIEC_ANY *getVarInternal(size_t) override;

      void alg_Alg_ChkStart(void);
      void alg_Alg_ChkStop(void);
      void alg_Alg_ChkAbort(void);
      void alg_Alg_ChkReset(void);
      void alg_Alg_ClientStart(void);
      void alg_Alg_ParentStart(void);

      static const TForteInt16 scmStateWait = 0;
      static const TForteInt16 scmStateChkStart = 1;
      static const TForteInt16 scmStateChkStop = 2;
      static const TForteInt16 scmStateChkAbort = 3;
      static const TForteInt16 scmStateChkReset = 4;
      static const TForteInt16 scmStateClientStart = 5;
      static const TForteInt16 scmStateParentStart = 6;
      static const TForteInt16 scmStateGoHalt = 7;
      static const TForteInt16 scmStateGoAbort = 8;
      static const TForteInt16 scmStateGoReset = 9;

      void enterStateWait(CEventChainExecutionThread *const paECET);
      void enterStateChkStart(CEventChainExecutionThread *const paECET);
      void enterStateChkStop(CEventChainExecutionThread *const paECET);
      void enterStateChkAbort(CEventChainExecutionThread *const paECET);
      void enterStateChkReset(CEventChainExecutionThread *const paECET);
      void enterStateClientStart(CEventChainExecutionThread *const paECET);
      void enterStateParentStart(CEventChainExecutionThread *const paECET);
      void enterStateGoHalt(CEventChainExecutionThread *const paECET);
      void enterStateGoAbort(CEventChainExecutionThread *const paECET);
      void enterStateGoReset(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_SKILL_Gate(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_WSTRING var_Session;
      CIEC_BOOL var_ParamsInRange;
      CIEC_BOOL var_EquipmentFree;
      CIEC_WSTRING var_StopSession;
      CIEC_WSTRING var_AbortSession;
      CIEC_WSTRING var_ResetSession;
      CIEC_WSTRING var_Owner;
      CIEC_USINT var_ModuleState;
      CIEC_USINT var_State;

      CIEC_BOOL var_Accepted;
      CIEC_UINT var_ResponseError;
      CIEC_BOOL var_ByClient;

      CEventConnection conn_START_RSP;
      CEventConnection conn_STOP_RSP;
      CEventConnection conn_ABORT_RSP;
      CEventConnection conn_RESET_RSP;
      CEventConnection conn_GO_START;
      CEventConnection conn_GO_HALT;
      CEventConnection conn_GO_ABORT;
      CEventConnection conn_GO_RESET;

      CDataConnection *conn_Session;
      CDataConnection *conn_ParamsInRange;
      CDataConnection *conn_EquipmentFree;
      CDataConnection *conn_StopSession;
      CDataConnection *conn_AbortSession;
      CDataConnection *conn_ResetSession;
      CDataConnection *conn_Owner;
      CDataConnection *conn_ModuleState;
      CDataConnection *conn_State;

      COutDataConnection<CIEC_BOOL> conn_Accepted;
      COutDataConnection<CIEC_UINT> conn_ResponseError;
      COutDataConnection<CIEC_BOOL> conn_ByClient;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_START_REQ(const CIEC_WSTRING &paSession, const CIEC_BOOL &paParamsInRange, const CIEC_BOOL &paEquipmentFree, const CIEC_WSTRING &paStopSession, const CIEC_WSTRING &paAbortSession, const CIEC_WSTRING &paResetSession, const CIEC_WSTRING &paOwner, const CIEC_USINT &paModuleState, const CIEC_USINT &paState, CAnyBitOutputParameter<CIEC_BOOL> paAccepted, COutputParameter<CIEC_UINT> paResponseError, CAnyBitOutputParameter<CIEC_BOOL> paByClient) {
        COutputGuard guard_Accepted(paAccepted);
        COutputGuard guard_ResponseError(paResponseError);
        COutputGuard guard_ByClient(paByClient);
        var_Session = paSession;
        var_ParamsInRange = paParamsInRange;
        var_EquipmentFree = paEquipmentFree;
        var_StopSession = paStopSession;
        var_AbortSession = paAbortSession;
        var_ResetSession = paResetSession;
        var_Owner = paOwner;
        var_ModuleState = paModuleState;
        var_State = paState;
        executeEvent(scmEventSTART_REQID, nullptr);
        *paAccepted = var_Accepted;
        *paResponseError = var_ResponseError;
        *paByClient = var_ByClient;
      }

      void evt_STOP_REQ(const CIEC_WSTRING &paSession, const CIEC_BOOL &paParamsInRange, const CIEC_BOOL &paEquipmentFree, const CIEC_WSTRING &paStopSession, const CIEC_WSTRING &paAbortSession, const CIEC_WSTRING &paResetSession, const CIEC_WSTRING &paOwner, const CIEC_USINT &paModuleState, const CIEC_USINT &paState, CAnyBitOutputParameter<CIEC_BOOL> paAccepted, COutputParameter<CIEC_UINT> paResponseError, CAnyBitOutputParameter<CIEC_BOOL> paByClient) {
        COutputGuard guard_Accepted(paAccepted);
        COutputGuard guard_ResponseError(paResponseError);
        COutputGuard guard_ByClient(paByClient);
        var_Session = paSession;
        var_ParamsInRange = paParamsInRange;
        var_EquipmentFree = paEquipmentFree;
        var_StopSession = paStopSession;
        var_AbortSession = paAbortSession;
        var_ResetSession = paResetSession;
        var_Owner = paOwner;
        var_ModuleState = paModuleState;
        var_State = paState;
        executeEvent(scmEventSTOP_REQID, nullptr);
        *paAccepted = var_Accepted;
        *paResponseError = var_ResponseError;
        *paByClient = var_ByClient;
      }

      void evt_ABORT_REQ(const CIEC_WSTRING &paSession, const CIEC_BOOL &paParamsInRange, const CIEC_BOOL &paEquipmentFree, const CIEC_WSTRING &paStopSession, const CIEC_WSTRING &paAbortSession, const CIEC_WSTRING &paResetSession, const CIEC_WSTRING &paOwner, const CIEC_USINT &paModuleState, const CIEC_USINT &paState, CAnyBitOutputParameter<CIEC_BOOL> paAccepted, COutputParameter<CIEC_UINT> paResponseError, CAnyBitOutputParameter<CIEC_BOOL> paByClient) {
        COutputGuard guard_Accepted(paAccepted);
        COutputGuard guard_ResponseError(paResponseError);
        COutputGuard guard_ByClient(paByClient);
        var_Session = paSession;
        var_ParamsInRange = paParamsInRange;
        var_EquipmentFree = paEquipmentFree;
        var_StopSession = paStopSession;
        var_AbortSession = paAbortSession;
        var_ResetSession = paResetSession;
        var_Owner = paOwner;
        var_ModuleState = paModuleState;
        var_State = paState;
        executeEvent(scmEventABORT_REQID, nullptr);
        *paAccepted = var_Accepted;
        *paResponseError = var_ResponseError;
        *paByClient = var_ByClient;
      }

      void evt_RESET_REQ(const CIEC_WSTRING &paSession, const CIEC_BOOL &paParamsInRange, const CIEC_BOOL &paEquipmentFree, const CIEC_WSTRING &paStopSession, const CIEC_WSTRING &paAbortSession, const CIEC_WSTRING &paResetSession, const CIEC_WSTRING &paOwner, const CIEC_USINT &paModuleState, const CIEC_USINT &paState, CAnyBitOutputParameter<CIEC_BOOL> paAccepted, COutputParameter<CIEC_UINT> paResponseError, CAnyBitOutputParameter<CIEC_BOOL> paByClient) {
        COutputGuard guard_Accepted(paAccepted);
        COutputGuard guard_ResponseError(paResponseError);
        COutputGuard guard_ByClient(paByClient);
        var_Session = paSession;
        var_ParamsInRange = paParamsInRange;
        var_EquipmentFree = paEquipmentFree;
        var_StopSession = paStopSession;
        var_AbortSession = paAbortSession;
        var_ResetSession = paResetSession;
        var_Owner = paOwner;
        var_ModuleState = paModuleState;
        var_State = paState;
        executeEvent(scmEventRESET_REQID, nullptr);
        *paAccepted = var_Accepted;
        *paResponseError = var_ResponseError;
        *paByClient = var_ByClient;
      }

      void evt_OWNER_CHG(const CIEC_WSTRING &paSession, const CIEC_BOOL &paParamsInRange, const CIEC_BOOL &paEquipmentFree, const CIEC_WSTRING &paStopSession, const CIEC_WSTRING &paAbortSession, const CIEC_WSTRING &paResetSession, const CIEC_WSTRING &paOwner, const CIEC_USINT &paModuleState, const CIEC_USINT &paState, CAnyBitOutputParameter<CIEC_BOOL> paAccepted, COutputParameter<CIEC_UINT> paResponseError, CAnyBitOutputParameter<CIEC_BOOL> paByClient) {
        COutputGuard guard_Accepted(paAccepted);
        COutputGuard guard_ResponseError(paResponseError);
        COutputGuard guard_ByClient(paByClient);
        var_Session = paSession;
        var_ParamsInRange = paParamsInRange;
        var_EquipmentFree = paEquipmentFree;
        var_StopSession = paStopSession;
        var_AbortSession = paAbortSession;
        var_ResetSession = paResetSession;
        var_Owner = paOwner;
        var_ModuleState = paModuleState;
        var_State = paState;
        executeEvent(scmEventOWNER_CHGID, nullptr);
        *paAccepted = var_Accepted;
        *paResponseError = var_ResponseError;
        *paByClient = var_ByClient;
      }

      void evt_MOD_CHG(const CIEC_WSTRING &paSession, const CIEC_BOOL &paParamsInRange, const CIEC_BOOL &paEquipmentFree, const CIEC_WSTRING &paStopSession, const CIEC_WSTRING &paAbortSession, const CIEC_WSTRING &paResetSession, const CIEC_WSTRING &paOwner, const CIEC_USINT &paModuleState, const CIEC_USINT &paState, CAnyBitOutputParameter<CIEC_BOOL> paAccepted, COutputParameter<CIEC_UINT> paResponseError, CAnyBitOutputParameter<CIEC_BOOL> paByClient) {
        COutputGuard guard_Accepted(paAccepted);
        COutputGuard guard_ResponseError(paResponseError);
        COutputGuard guard_ByClient(paByClient);
        var_Session = paSession;
        var_ParamsInRange = paParamsInRange;
        var_EquipmentFree = paEquipmentFree;
        var_StopSession = paStopSession;
        var_AbortSession = paAbortSession;
        var_ResetSession = paResetSession;
        var_Owner = paOwner;
        var_ModuleState = paModuleState;
        var_State = paState;
        executeEvent(scmEventMOD_CHGID, nullptr);
        *paAccepted = var_Accepted;
        *paResponseError = var_ResponseError;
        *paByClient = var_ByClient;
      }

      void evt_SKILL_CHG(const CIEC_WSTRING &paSession, const CIEC_BOOL &paParamsInRange, const CIEC_BOOL &paEquipmentFree, const CIEC_WSTRING &paStopSession, const CIEC_WSTRING &paAbortSession, const CIEC_WSTRING &paResetSession, const CIEC_WSTRING &paOwner, const CIEC_USINT &paModuleState, const CIEC_USINT &paState, CAnyBitOutputParameter<CIEC_BOOL> paAccepted, COutputParameter<CIEC_UINT> paResponseError, CAnyBitOutputParameter<CIEC_BOOL> paByClient) {
        COutputGuard guard_Accepted(paAccepted);
        COutputGuard guard_ResponseError(paResponseError);
        COutputGuard guard_ByClient(paByClient);
        var_Session = paSession;
        var_ParamsInRange = paParamsInRange;
        var_EquipmentFree = paEquipmentFree;
        var_StopSession = paStopSession;
        var_AbortSession = paAbortSession;
        var_ResetSession = paResetSession;
        var_Owner = paOwner;
        var_ModuleState = paModuleState;
        var_State = paState;
        executeEvent(scmEventSKILL_CHGID, nullptr);
        *paAccepted = var_Accepted;
        *paResponseError = var_ResponseError;
        *paByClient = var_ByClient;
      }

      void evt_START(const CIEC_WSTRING &paSession, const CIEC_BOOL &paParamsInRange, const CIEC_BOOL &paEquipmentFree, const CIEC_WSTRING &paStopSession, const CIEC_WSTRING &paAbortSession, const CIEC_WSTRING &paResetSession, const CIEC_WSTRING &paOwner, const CIEC_USINT &paModuleState, const CIEC_USINT &paState, CAnyBitOutputParameter<CIEC_BOOL> paAccepted, COutputParameter<CIEC_UINT> paResponseError, CAnyBitOutputParameter<CIEC_BOOL> paByClient) {
        COutputGuard guard_Accepted(paAccepted);
        COutputGuard guard_ResponseError(paResponseError);
        COutputGuard guard_ByClient(paByClient);
        var_Session = paSession;
        var_ParamsInRange = paParamsInRange;
        var_EquipmentFree = paEquipmentFree;
        var_StopSession = paStopSession;
        var_AbortSession = paAbortSession;
        var_ResetSession = paResetSession;
        var_Owner = paOwner;
        var_ModuleState = paModuleState;
        var_State = paState;
        executeEvent(scmEventSTARTID, nullptr);
        *paAccepted = var_Accepted;
        *paResponseError = var_ResponseError;
        *paByClient = var_ByClient;
      }

      void evt_HALT(const CIEC_WSTRING &paSession, const CIEC_BOOL &paParamsInRange, const CIEC_BOOL &paEquipmentFree, const CIEC_WSTRING &paStopSession, const CIEC_WSTRING &paAbortSession, const CIEC_WSTRING &paResetSession, const CIEC_WSTRING &paOwner, const CIEC_USINT &paModuleState, const CIEC_USINT &paState, CAnyBitOutputParameter<CIEC_BOOL> paAccepted, COutputParameter<CIEC_UINT> paResponseError, CAnyBitOutputParameter<CIEC_BOOL> paByClient) {
        COutputGuard guard_Accepted(paAccepted);
        COutputGuard guard_ResponseError(paResponseError);
        COutputGuard guard_ByClient(paByClient);
        var_Session = paSession;
        var_ParamsInRange = paParamsInRange;
        var_EquipmentFree = paEquipmentFree;
        var_StopSession = paStopSession;
        var_AbortSession = paAbortSession;
        var_ResetSession = paResetSession;
        var_Owner = paOwner;
        var_ModuleState = paModuleState;
        var_State = paState;
        executeEvent(scmEventHALTID, nullptr);
        *paAccepted = var_Accepted;
        *paResponseError = var_ResponseError;
        *paByClient = var_ByClient;
      }

      void evt_ABORT(const CIEC_WSTRING &paSession, const CIEC_BOOL &paParamsInRange, const CIEC_BOOL &paEquipmentFree, const CIEC_WSTRING &paStopSession, const CIEC_WSTRING &paAbortSession, const CIEC_WSTRING &paResetSession, const CIEC_WSTRING &paOwner, const CIEC_USINT &paModuleState, const CIEC_USINT &paState, CAnyBitOutputParameter<CIEC_BOOL> paAccepted, COutputParameter<CIEC_UINT> paResponseError, CAnyBitOutputParameter<CIEC_BOOL> paByClient) {
        COutputGuard guard_Accepted(paAccepted);
        COutputGuard guard_ResponseError(paResponseError);
        COutputGuard guard_ByClient(paByClient);
        var_Session = paSession;
        var_ParamsInRange = paParamsInRange;
        var_EquipmentFree = paEquipmentFree;
        var_StopSession = paStopSession;
        var_AbortSession = paAbortSession;
        var_ResetSession = paResetSession;
        var_Owner = paOwner;
        var_ModuleState = paModuleState;
        var_State = paState;
        executeEvent(scmEventABORTID, nullptr);
        *paAccepted = var_Accepted;
        *paResponseError = var_ResponseError;
        *paByClient = var_ByClient;
      }

      void evt_RESET(const CIEC_WSTRING &paSession, const CIEC_BOOL &paParamsInRange, const CIEC_BOOL &paEquipmentFree, const CIEC_WSTRING &paStopSession, const CIEC_WSTRING &paAbortSession, const CIEC_WSTRING &paResetSession, const CIEC_WSTRING &paOwner, const CIEC_USINT &paModuleState, const CIEC_USINT &paState, CAnyBitOutputParameter<CIEC_BOOL> paAccepted, COutputParameter<CIEC_UINT> paResponseError, CAnyBitOutputParameter<CIEC_BOOL> paByClient) {
        COutputGuard guard_Accepted(paAccepted);
        COutputGuard guard_ResponseError(paResponseError);
        COutputGuard guard_ByClient(paByClient);
        var_Session = paSession;
        var_ParamsInRange = paParamsInRange;
        var_EquipmentFree = paEquipmentFree;
        var_StopSession = paStopSession;
        var_AbortSession = paAbortSession;
        var_ResetSession = paResetSession;
        var_Owner = paOwner;
        var_ModuleState = paModuleState;
        var_State = paState;
        executeEvent(scmEventRESETID, nullptr);
        *paAccepted = var_Accepted;
        *paResponseError = var_ResponseError;
        *paByClient = var_ByClient;
      }
  };
}

