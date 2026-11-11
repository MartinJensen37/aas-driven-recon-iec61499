/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SKILL_Merge
 *** Description: Where the two branches of a decision meet again: either branch's end goes on. Technical: Where the branches of a decision meet: EI1 or EI2 gives EO
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/basicfb.h"

namespace forte::modlib {
  class FORTE_SKILL_Merge final : public CBasicFB {
      DECLARE_FIRMWARE_FB(FORTE_SKILL_Merge)

    private:
      static const TEventID scmEventEOID = 0;
      static const TEventID scmEventEI1ID = 0;
      static const TEventID scmEventEI2ID = 1;

      CIEC_ANY *getVarInternal(size_t) override;

      static const TForteInt16 scmStateSTART = 0;
      static const TForteInt16 scmStateOne = 1;
      static const TForteInt16 scmStateTwo = 2;

      void enterStateSTART(CEventChainExecutionThread *const paECET);
      void enterStateOne(CEventChainExecutionThread *const paECET);
      void enterStateTwo(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_SKILL_Merge(StringId paInstanceNameId, CFBContainer &paContainer);

      CEventConnection conn_EO;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_EI1() {
        executeEvent(scmEventEI1ID, nullptr);
      }

      void evt_EI2() {
        executeEvent(scmEventEI2ID, nullptr);
      }
  };
}

