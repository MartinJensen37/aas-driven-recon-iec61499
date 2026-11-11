/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SKILL_Join3
 *** Description: Ends a block of steps that run side by side: done when every branch is done; if one fails, the others are halted and the block fails. Technical: Ends a parallel block of 3 branches: DONE when all are done; on the first failure HALT to the others, then FAILED with its error once all have ended
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/basicfb.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/forte_st_util.h"

namespace forte::modlib {
  class FORTE_SKILL_Join3 final : public CBasicFB {
      DECLARE_FIRMWARE_FB(FORTE_SKILL_Join3)

    private:
      static const TEventID scmEventDONEID = 0;
      static const TEventID scmEventFAILEDID = 1;
      static const TEventID scmEventHALTID = 2;
      static const TEventID scmEventSTARTID = 0;
      static const TEventID scmEventDONE_1ID = 1;
      static const TEventID scmEventDONE_2ID = 2;
      static const TEventID scmEventDONE_3ID = 3;
      static const TEventID scmEventFAILED_1ID = 4;
      static const TEventID scmEventFAILED_2ID = 5;
      static const TEventID scmEventFAILED_3ID = 6;

      CIEC_BOOL var_Ended1;
      CIEC_BOOL var_Ended2;
      CIEC_BOOL var_Ended3;
      CIEC_BOOL var_AnyFailed;
      CIEC_UINT var_First;

      CIEC_ANY *getVarInternal(size_t) override;

      void alg_Alg_Reset(void);
      void alg_Alg_Fail(void);
      void alg_Alg_Done1(void);
      void alg_Alg_First1(void);
      void alg_Alg_Later1(void);
      void alg_Alg_Done2(void);
      void alg_Alg_First2(void);
      void alg_Alg_Later2(void);
      void alg_Alg_Done3(void);
      void alg_Alg_First3(void);
      void alg_Alg_Later3(void);

      static const TForteInt16 scmStateSTART = 0;
      static const TForteInt16 scmStateReset = 1;
      static const TForteInt16 scmStateCheck = 2;
      static const TForteInt16 scmStateDone = 3;
      static const TForteInt16 scmStateFail = 4;
      static const TForteInt16 scmStateDone1 = 5;
      static const TForteInt16 scmStateFirst1 = 6;
      static const TForteInt16 scmStateLater1 = 7;
      static const TForteInt16 scmStateDone2 = 8;
      static const TForteInt16 scmStateFirst2 = 9;
      static const TForteInt16 scmStateLater2 = 10;
      static const TForteInt16 scmStateDone3 = 11;
      static const TForteInt16 scmStateFirst3 = 12;
      static const TForteInt16 scmStateLater3 = 13;

      void enterStateSTART(CEventChainExecutionThread *const paECET);
      void enterStateReset(CEventChainExecutionThread *const paECET);
      void enterStateCheck(CEventChainExecutionThread *const paECET);
      void enterStateDone(CEventChainExecutionThread *const paECET);
      void enterStateFail(CEventChainExecutionThread *const paECET);
      void enterStateDone1(CEventChainExecutionThread *const paECET);
      void enterStateFirst1(CEventChainExecutionThread *const paECET);
      void enterStateLater1(CEventChainExecutionThread *const paECET);
      void enterStateDone2(CEventChainExecutionThread *const paECET);
      void enterStateFirst2(CEventChainExecutionThread *const paECET);
      void enterStateLater2(CEventChainExecutionThread *const paECET);
      void enterStateDone3(CEventChainExecutionThread *const paECET);
      void enterStateFirst3(CEventChainExecutionThread *const paECET);
      void enterStateLater3(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_SKILL_Join3(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_UINT var_Error1;
      CIEC_UINT var_Error2;
      CIEC_UINT var_Error3;

      CIEC_UINT var_Error;

      CEventConnection conn_DONE;
      CEventConnection conn_FAILED;
      CEventConnection conn_HALT;

      CDataConnection *conn_Error1;
      CDataConnection *conn_Error2;
      CDataConnection *conn_Error3;

      COutDataConnection<CIEC_UINT> conn_Error;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_START(const CIEC_UINT &paError1, const CIEC_UINT &paError2, const CIEC_UINT &paError3, COutputParameter<CIEC_UINT> paError) {
        COutputGuard guard_Error(paError);
        var_Error1 = paError1;
        var_Error2 = paError2;
        var_Error3 = paError3;
        executeEvent(scmEventSTARTID, nullptr);
        *paError = var_Error;
      }

      void evt_DONE_1(const CIEC_UINT &paError1, const CIEC_UINT &paError2, const CIEC_UINT &paError3, COutputParameter<CIEC_UINT> paError) {
        COutputGuard guard_Error(paError);
        var_Error1 = paError1;
        var_Error2 = paError2;
        var_Error3 = paError3;
        executeEvent(scmEventDONE_1ID, nullptr);
        *paError = var_Error;
      }

      void evt_DONE_2(const CIEC_UINT &paError1, const CIEC_UINT &paError2, const CIEC_UINT &paError3, COutputParameter<CIEC_UINT> paError) {
        COutputGuard guard_Error(paError);
        var_Error1 = paError1;
        var_Error2 = paError2;
        var_Error3 = paError3;
        executeEvent(scmEventDONE_2ID, nullptr);
        *paError = var_Error;
      }

      void evt_DONE_3(const CIEC_UINT &paError1, const CIEC_UINT &paError2, const CIEC_UINT &paError3, COutputParameter<CIEC_UINT> paError) {
        COutputGuard guard_Error(paError);
        var_Error1 = paError1;
        var_Error2 = paError2;
        var_Error3 = paError3;
        executeEvent(scmEventDONE_3ID, nullptr);
        *paError = var_Error;
      }

      void evt_FAILED_1(const CIEC_UINT &paError1, const CIEC_UINT &paError2, const CIEC_UINT &paError3, COutputParameter<CIEC_UINT> paError) {
        COutputGuard guard_Error(paError);
        var_Error1 = paError1;
        var_Error2 = paError2;
        var_Error3 = paError3;
        executeEvent(scmEventFAILED_1ID, nullptr);
        *paError = var_Error;
      }

      void evt_FAILED_2(const CIEC_UINT &paError1, const CIEC_UINT &paError2, const CIEC_UINT &paError3, COutputParameter<CIEC_UINT> paError) {
        COutputGuard guard_Error(paError);
        var_Error1 = paError1;
        var_Error2 = paError2;
        var_Error3 = paError3;
        executeEvent(scmEventFAILED_2ID, nullptr);
        *paError = var_Error;
      }

      void evt_FAILED_3(const CIEC_UINT &paError1, const CIEC_UINT &paError2, const CIEC_UINT &paError3, COutputParameter<CIEC_UINT> paError) {
        COutputGuard guard_Error(paError);
        var_Error1 = paError1;
        var_Error2 = paError2;
        var_Error3 = paError3;
        executeEvent(scmEventFAILED_3ID, nullptr);
        *paError = var_Error;
      }
  };
}

