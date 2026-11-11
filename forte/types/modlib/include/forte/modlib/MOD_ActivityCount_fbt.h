/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: MOD_ActivityCount
 *** Description: Counts the skills that are running: every skill says +1 when it starts and -1 when it ends. Technical: Number of running skills from the +1/-1 activity channel
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/simplefb.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_int.h"
#include "forte/forte_st_util.h"

namespace forte::modlib {
  class FORTE_MOD_ActivityCount final : public CSimpleFB {
      DECLARE_FIRMWARE_FB(FORTE_MOD_ActivityCount)

    private:
      static const TEventID scmEventCHGID = 0;
      static const TEventID scmEventACTID = 0;

      CIEC_ANY *getVarInternal(size_t) override;

      void alg_ACT(void);

      void enterStateACT(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_MOD_ActivityCount(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_INT var_Delta;

      CIEC_INT var_Active;
      CIEC_BOOL var_AllIdle;

      CEventConnection conn_CHG;

      CDataConnection *conn_Delta;

      COutDataConnection<CIEC_INT> conn_Active;
      COutDataConnection<CIEC_BOOL> conn_AllIdle;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_ACT(const CIEC_INT &paDelta, COutputParameter<CIEC_INT> paActive, CAnyBitOutputParameter<CIEC_BOOL> paAllIdle) {
        COutputGuard guard_Active(paActive);
        COutputGuard guard_AllIdle(paAllIdle);
        var_Delta = paDelta;
        executeEvent(scmEventACTID, nullptr);
        *paActive = var_Active;
        *paAllIdle = var_AllIdle;
      }

      void operator()(const CIEC_INT &paDelta, COutputParameter<CIEC_INT> paActive, CAnyBitOutputParameter<CIEC_BOOL> paAllIdle) {
        evt_ACT(std::forward<const CIEC_INT &>(paDelta), std::forward<COutputParameter<CIEC_INT>>(paActive), std::forward<CAnyBitOutputParameter<CIEC_BOOL>>(paAllIdle));
      }
  };
}

