/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SKILL_FailMerge
 *** Description: Joins two failure events (with their error codes) into one, because a data input can only be wired once. Technical: Merges two failure events with their error codes into one
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/simplefb.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/forte_st_util.h"

namespace forte::modlib {
  class FORTE_SKILL_FailMerge final : public CSimpleFB {
      DECLARE_FIRMWARE_FB(FORTE_SKILL_FailMerge)

    private:
      static const TEventID scmEventFAILID = 0;
      static const TEventID scmEventFAIL_1ID = 0;
      static const TEventID scmEventFAIL_2ID = 1;

      CIEC_ANY *getVarInternal(size_t) override;

      void alg_FAIL_1(void);
      void alg_FAIL_2(void);

      void enterStateFAIL_1(CEventChainExecutionThread *const paECET);
      void enterStateFAIL_2(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_SKILL_FailMerge(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_UINT var_Error1;
      CIEC_UINT var_Error2;

      CIEC_UINT var_Error;

      CEventConnection conn_FAIL;

      CDataConnection *conn_Error1;
      CDataConnection *conn_Error2;

      COutDataConnection<CIEC_UINT> conn_Error;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_FAIL_1(const CIEC_UINT &paError1, const CIEC_UINT &paError2, COutputParameter<CIEC_UINT> paError) {
        COutputGuard guard_Error(paError);
        var_Error1 = paError1;
        var_Error2 = paError2;
        executeEvent(scmEventFAIL_1ID, nullptr);
        *paError = var_Error;
      }

      void evt_FAIL_2(const CIEC_UINT &paError1, const CIEC_UINT &paError2, COutputParameter<CIEC_UINT> paError) {
        COutputGuard guard_Error(paError);
        var_Error1 = paError1;
        var_Error2 = paError2;
        executeEvent(scmEventFAIL_2ID, nullptr);
        *paError = var_Error;
      }
  };
}

