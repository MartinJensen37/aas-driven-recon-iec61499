/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: EC_Pump
 *** Description: The equipment's command table: turns a command's name (Up, Down, Run, ...) into the output values to switch, phase by phase with their times. Technical: Commands of Pump as output values, in timed phases: Idle=0, Run=1
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/basicfb.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"

namespace forte::filling {
  class FORTE_EC_Pump final : public CBasicFB {
      DECLARE_FIRMWARE_FB(FORTE_EC_Pump)

    private:
      static const TEventID scmEventOUTID = 0;
      static const TEventID scmEventPHASE_STARTID = 1;
      static const TEventID scmEventPHASE_STOPID = 2;
      static const TEventID scmEventPLAYEDID = 3;
      static const TEventID scmEventPLAYID = 0;
      static const TEventID scmEventPHASE_TID = 1;

      CIEC_USINT var_Phase;
      CIEC_BOOL var_Timed;

      CIEC_ANY *getVarInternal(size_t) override;

      void alg_Alg_Play(void);
      void alg_Alg_Next(void);
      void alg_Alg_Send(void);

      static const TForteInt16 scmStateSTART = 0;
      static const TForteInt16 scmStatePlay = 1;
      static const TForteInt16 scmStateNext = 2;
      static const TForteInt16 scmStateSend = 3;
      static const TForteInt16 scmStateHold = 4;
      static const TForteInt16 scmStatePlayed = 5;

      void enterStateSTART(CEventChainExecutionThread *const paECET);
      void enterStatePlay(CEventChainExecutionThread *const paECET);
      void enterStateNext(CEventChainExecutionThread *const paECET);
      void enterStateSend(CEventChainExecutionThread *const paECET);
      void enterStateHold(CEventChainExecutionThread *const paECET);
      void enterStatePlayed(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_EC_Pump(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_WSTRING var_Holder;
      CIEC_USINT var_Command;
      CIEC_BOOL var_Release;

      CIEC_WSTRING var_O_Holder;
      CIEC_BOOL var_O_Release;
      CIEC_TIME var_PhaseDT;

      CEventConnection conn_OUT;
      CEventConnection conn_PHASE_START;
      CEventConnection conn_PHASE_STOP;
      CEventConnection conn_PLAYED;

      CDataConnection *conn_Holder;
      CDataConnection *conn_Command;
      CDataConnection *conn_Release;

      COutDataConnection<CIEC_WSTRING> conn_O_Holder;
      COutDataConnection<CIEC_BOOL> conn_O_Release;
      COutDataConnection<CIEC_TIME> conn_PhaseDT;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_PLAY(const CIEC_WSTRING &paHolder, const CIEC_USINT &paCommand, const CIEC_BOOL &paRelease, COutputParameter<CIEC_WSTRING> paO_Holder, CAnyBitOutputParameter<CIEC_BOOL> paO_Release, COutputParameter<CIEC_TIME> paPhaseDT) {
        COutputGuard guard_O_Holder(paO_Holder);
        COutputGuard guard_O_Release(paO_Release);
        COutputGuard guard_PhaseDT(paPhaseDT);
        var_Holder = paHolder;
        var_Command = paCommand;
        var_Release = paRelease;
        executeEvent(scmEventPLAYID, nullptr);
        *paO_Holder = var_O_Holder;
        *paO_Release = var_O_Release;
        *paPhaseDT = var_PhaseDT;
      }

      void evt_PHASE_T(const CIEC_WSTRING &paHolder, const CIEC_USINT &paCommand, const CIEC_BOOL &paRelease, COutputParameter<CIEC_WSTRING> paO_Holder, CAnyBitOutputParameter<CIEC_BOOL> paO_Release, COutputParameter<CIEC_TIME> paPhaseDT) {
        COutputGuard guard_O_Holder(paO_Holder);
        COutputGuard guard_O_Release(paO_Release);
        COutputGuard guard_PhaseDT(paPhaseDT);
        var_Holder = paHolder;
        var_Command = paCommand;
        var_Release = paRelease;
        executeEvent(scmEventPHASE_TID, nullptr);
        *paO_Holder = var_O_Holder;
        *paO_Release = var_O_Release;
        *paPhaseDT = var_PhaseDT;
      }
  };
}

