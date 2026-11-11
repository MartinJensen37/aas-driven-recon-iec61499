/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SKILL_Param_INT
 *** Description: One parameter of a skill: keeps its default, checks a value a client sends with Start against the limits, and holds the value for the run. Technical: Skill parameter (INT): default, range check of a Start argument, latching for one run
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/simplefb.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_int.h"
#include "forte/forte_st_util.h"

namespace forte::modlib {
  class FORTE_SKILL_Param_INT final : public CSimpleFB {
      DECLARE_FIRMWARE_FB(FORTE_SKILL_Param_INT)

    private:
      static const TEventID scmEventINITOID = 0;
      static const TEventID scmEventCHECKEDID = 1;
      static const TEventID scmEventLATCHEDID = 2;
      static const TEventID scmEventINITID = 0;
      static const TEventID scmEventCHECKID = 1;
      static const TEventID scmEventLATCHID = 2;

      CIEC_ANY *getVarInternal(size_t) override;

      void alg_INIT(void);
      void alg_CHECK(void);
      void alg_LATCH(void);

      void enterStateINIT(CEventChainExecutionThread *const paECET);
      void enterStateCHECK(CEventChainExecutionThread *const paECET);
      void enterStateLATCH(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_SKILL_Param_INT(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_INT var_Default;
      CIEC_INT var_Lower;
      CIEC_INT var_Upper;
      CIEC_INT var_Requested;
      CIEC_BOOL var_PreviousInRange;
      CIEC_BOOL var_CalledByClient;

      CIEC_INT var_Value;
      CIEC_BOOL var_AllInRange;

      CEventConnection conn_INITO;
      CEventConnection conn_CHECKED;
      CEventConnection conn_LATCHED;

      CDataConnection *conn_Default;
      CDataConnection *conn_Lower;
      CDataConnection *conn_Upper;
      CDataConnection *conn_Requested;
      CDataConnection *conn_PreviousInRange;
      CDataConnection *conn_CalledByClient;

      COutDataConnection<CIEC_INT> conn_Value;
      COutDataConnection<CIEC_BOOL> conn_AllInRange;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_INIT(const CIEC_INT &paDefault, const CIEC_INT &paLower, const CIEC_INT &paUpper, const CIEC_INT &paRequested, const CIEC_BOOL &paPreviousInRange, const CIEC_BOOL &paCalledByClient, COutputParameter<CIEC_INT> paValue, CAnyBitOutputParameter<CIEC_BOOL> paAllInRange) {
        COutputGuard guard_Value(paValue);
        COutputGuard guard_AllInRange(paAllInRange);
        var_Default = paDefault;
        var_Lower = paLower;
        var_Upper = paUpper;
        var_Requested = paRequested;
        var_PreviousInRange = paPreviousInRange;
        var_CalledByClient = paCalledByClient;
        executeEvent(scmEventINITID, nullptr);
        *paValue = var_Value;
        *paAllInRange = var_AllInRange;
      }

      void evt_CHECK(const CIEC_INT &paDefault, const CIEC_INT &paLower, const CIEC_INT &paUpper, const CIEC_INT &paRequested, const CIEC_BOOL &paPreviousInRange, const CIEC_BOOL &paCalledByClient, COutputParameter<CIEC_INT> paValue, CAnyBitOutputParameter<CIEC_BOOL> paAllInRange) {
        COutputGuard guard_Value(paValue);
        COutputGuard guard_AllInRange(paAllInRange);
        var_Default = paDefault;
        var_Lower = paLower;
        var_Upper = paUpper;
        var_Requested = paRequested;
        var_PreviousInRange = paPreviousInRange;
        var_CalledByClient = paCalledByClient;
        executeEvent(scmEventCHECKID, nullptr);
        *paValue = var_Value;
        *paAllInRange = var_AllInRange;
      }

      void evt_LATCH(const CIEC_INT &paDefault, const CIEC_INT &paLower, const CIEC_INT &paUpper, const CIEC_INT &paRequested, const CIEC_BOOL &paPreviousInRange, const CIEC_BOOL &paCalledByClient, COutputParameter<CIEC_INT> paValue, CAnyBitOutputParameter<CIEC_BOOL> paAllInRange) {
        COutputGuard guard_Value(paValue);
        COutputGuard guard_AllInRange(paAllInRange);
        var_Default = paDefault;
        var_Lower = paLower;
        var_Upper = paUpper;
        var_Requested = paRequested;
        var_PreviousInRange = paPreviousInRange;
        var_CalledByClient = paCalledByClient;
        executeEvent(scmEventLATCHID, nullptr);
        *paValue = var_Value;
        *paAllInRange = var_AllInRange;
      }
  };
}

