/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SC_Tare
 *** Description: The contract of a skill primitive, the only part that is its own: which command it sends (and with what argument, and which when it ends), how long it may run, and three conditions on the equipment's signals and its parameters: when it may start, when it is done, what must hold while it runs. Technical: Tare: Precondition TRUE; Scale.Tare until 2.0 s; Invariant TRUE
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/basicfb.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/modlib/AContract_adp.h"

namespace forte::filling {
  class FORTE_SC_Tare final : public CBasicFB {
      DECLARE_FIRMWARE_FB(FORTE_SC_Tare)

    private:
      static const TEventID scmEventINITOID = 0;
      static const TEventID scmEventINITID = 0;
      static const TEventID scmEventSTARTID = 1;
      static const TEventID scmEventSAMPLEID = 2;

      CIEC_ANY *getVarInternal(size_t) override;

      void alg_Alg_Start(void);
      void alg_Alg_Evaluate(void);
      void alg_Alg_Sample(void);

      static const TForteInt16 scmStateWait = 0;
      static const TForteInt16 scmStateInit = 1;
      static const TForteInt16 scmStateStart = 2;
      static const TForteInt16 scmStateStarted = 3;
      static const TForteInt16 scmStateSample = 4;
      static const TForteInt16 scmStateJudge = 5;

      void enterStateWait(CEventChainExecutionThread *const paECET);
      void enterStateInit(CEventChainExecutionThread *const paECET);
      void enterStateStart(CEventChainExecutionThread *const paECET);
      void enterStateStarted(CEventChainExecutionThread *const paECET);
      void enterStateSample(CEventChainExecutionThread *const paECET);
      void enterStateJudge(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_SC_Tare(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_WSTRING var_EqHolder;

      forte::CPlugPin<forte::modlib::FORTE_AContract_Plug> var_Run;

      CEventConnection conn_INITO;

      CDataConnection *conn_EqHolder;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      forte::IPlugPin *getPlugPinUnchecked(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_INIT(const CIEC_WSTRING &paEqHolder) {
        var_EqHolder = paEqHolder;
        executeEvent(scmEventINITID, nullptr);
      }

      void evt_START(const CIEC_WSTRING &paEqHolder) {
        var_EqHolder = paEqHolder;
        executeEvent(scmEventSTARTID, nullptr);
      }

      void evt_SAMPLE(const CIEC_WSTRING &paEqHolder) {
        var_EqHolder = paEqHolder;
        executeEvent(scmEventSAMPLEID, nullptr);
      }
  };
}

