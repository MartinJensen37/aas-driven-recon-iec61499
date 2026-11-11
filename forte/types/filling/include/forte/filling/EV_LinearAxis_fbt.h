/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: EV_LinearAxis
 *** Description: Names the equipment's two channels, and unpacks its state channel into named values (its inputs and who holds it) for a skill. Technical: Names LinearAxis's channels; typed view of its state channel (inputs and holder)
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/simplefb.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"

namespace forte::filling {
  class FORTE_EV_LinearAxis final : public CSimpleFB {
      DECLARE_FIRMWARE_FB(FORTE_EV_LinearAxis)

    private:
      static const TEventID scmEventINITOID = 0;
      static const TEventID scmEventCNFID = 1;
      static const TEventID scmEventINITID = 0;
      static const TEventID scmEventREQID = 1;

      CIEC_ANY *getVarInternal(size_t) override;

      void alg_INIT(void);
      void alg_REQ(void);

      void enterStateINIT(CEventChainExecutionThread *const paECET);
      void enterStateREQ(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_EV_LinearAxis(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_WSTRING var_Module;
      CIEC_BOOL var_I_AtHome;
      CIEC_LREAL var_I_ActualPosition;
      CIEC_BOOL var_I_Homed;
      CIEC_BOOL var_I_Moving;
      CIEC_WSTRING var_I_Holder;

      CIEC_BOOL var_AtHome;
      CIEC_LREAL var_ActualPosition;
      CIEC_BOOL var_Homed;
      CIEC_BOOL var_Moving;
      CIEC_WSTRING var_Holder;
      CIEC_WSTRING var_IdState;
      CIEC_WSTRING var_IdCmd;

      CEventConnection conn_INITO;
      CEventConnection conn_CNF;

      CDataConnection *conn_Module;
      CDataConnection *conn_I_AtHome;
      CDataConnection *conn_I_ActualPosition;
      CDataConnection *conn_I_Homed;
      CDataConnection *conn_I_Moving;
      CDataConnection *conn_I_Holder;

      COutDataConnection<CIEC_BOOL> conn_AtHome;
      COutDataConnection<CIEC_LREAL> conn_ActualPosition;
      COutDataConnection<CIEC_BOOL> conn_Homed;
      COutDataConnection<CIEC_BOOL> conn_Moving;
      COutDataConnection<CIEC_WSTRING> conn_Holder;
      COutDataConnection<CIEC_WSTRING> conn_IdState;
      COutDataConnection<CIEC_WSTRING> conn_IdCmd;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_INIT(const CIEC_WSTRING &paModule, const CIEC_BOOL &paI_AtHome, const CIEC_LREAL &paI_ActualPosition, const CIEC_BOOL &paI_Homed, const CIEC_BOOL &paI_Moving, const CIEC_WSTRING &paI_Holder, CAnyBitOutputParameter<CIEC_BOOL> paAtHome, COutputParameter<CIEC_LREAL> paActualPosition, CAnyBitOutputParameter<CIEC_BOOL> paHomed, CAnyBitOutputParameter<CIEC_BOOL> paMoving, COutputParameter<CIEC_WSTRING> paHolder, COutputParameter<CIEC_WSTRING> paIdState, COutputParameter<CIEC_WSTRING> paIdCmd) {
        COutputGuard guard_AtHome(paAtHome);
        COutputGuard guard_ActualPosition(paActualPosition);
        COutputGuard guard_Homed(paHomed);
        COutputGuard guard_Moving(paMoving);
        COutputGuard guard_Holder(paHolder);
        COutputGuard guard_IdState(paIdState);
        COutputGuard guard_IdCmd(paIdCmd);
        var_Module = paModule;
        var_I_AtHome = paI_AtHome;
        var_I_ActualPosition = paI_ActualPosition;
        var_I_Homed = paI_Homed;
        var_I_Moving = paI_Moving;
        var_I_Holder = paI_Holder;
        executeEvent(scmEventINITID, nullptr);
        *paAtHome = var_AtHome;
        *paActualPosition = var_ActualPosition;
        *paHomed = var_Homed;
        *paMoving = var_Moving;
        *paHolder = var_Holder;
        *paIdState = var_IdState;
        *paIdCmd = var_IdCmd;
      }

      void evt_REQ(const CIEC_WSTRING &paModule, const CIEC_BOOL &paI_AtHome, const CIEC_LREAL &paI_ActualPosition, const CIEC_BOOL &paI_Homed, const CIEC_BOOL &paI_Moving, const CIEC_WSTRING &paI_Holder, CAnyBitOutputParameter<CIEC_BOOL> paAtHome, COutputParameter<CIEC_LREAL> paActualPosition, CAnyBitOutputParameter<CIEC_BOOL> paHomed, CAnyBitOutputParameter<CIEC_BOOL> paMoving, COutputParameter<CIEC_WSTRING> paHolder, COutputParameter<CIEC_WSTRING> paIdState, COutputParameter<CIEC_WSTRING> paIdCmd) {
        COutputGuard guard_AtHome(paAtHome);
        COutputGuard guard_ActualPosition(paActualPosition);
        COutputGuard guard_Homed(paHomed);
        COutputGuard guard_Moving(paMoving);
        COutputGuard guard_Holder(paHolder);
        COutputGuard guard_IdState(paIdState);
        COutputGuard guard_IdCmd(paIdCmd);
        var_Module = paModule;
        var_I_AtHome = paI_AtHome;
        var_I_ActualPosition = paI_ActualPosition;
        var_I_Homed = paI_Homed;
        var_I_Moving = paI_Moving;
        var_I_Holder = paI_Holder;
        executeEvent(scmEventREQID, nullptr);
        *paAtHome = var_AtHome;
        *paActualPosition = var_ActualPosition;
        *paHomed = var_Homed;
        *paMoving = var_Moving;
        *paHolder = var_Holder;
        *paIdState = var_IdState;
        *paIdCmd = var_IdCmd;
      }
  };
}

