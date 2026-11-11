/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SC_MoveAxis
 *** Description: The contract of a skill primitive, the only part that is its own: which command it sends (and with what argument, and which when it ends), how long it may run, and three conditions on the equipment's signals and its parameters: when it may start, when it is done, what must hold while it runs. Technical: MoveAxis: Precondition Homed; LinearAxis.MoveTo until NOT Moving AND ABS(ActualPosition - Position) < 0.001; Invariant TRUE
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
#include "forte/forte_st_util.h"
#include "forte/modlib/AContract_adp.h"

namespace forte::filling {
  class FORTE_SC_MoveAxis final : public CBasicFB {
      DECLARE_FIRMWARE_FB(FORTE_SC_MoveAxis)

    private:
      static const TEventID scmEventINITOID = 0;
      static const TEventID scmEventINITID = 0;
      static const TEventID scmEventSTARTID = 1;
      static const TEventID scmEventSAMPLEID = 2;

      CIEC_ANY *getVarInternal(size_t) override;

      void alg_Alg_Init(void);
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
      FORTE_SC_MoveAxis(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_WSTRING var_UaRoot;
      CIEC_WSTRING var_UaPath;
      CIEC_LREAL var_Position;
      CIEC_TIME var_Timeout;
      CIEC_LREAL var_ActualPosition;
      CIEC_BOOL var_Homed;
      CIEC_BOOL var_Moving;
      CIEC_WSTRING var_EqHolder;

      CIEC_WSTRING var_IdParams;

      forte::CPlugPin<forte::modlib::FORTE_AContract_Plug> var_Run;

      CEventConnection conn_INITO;

      CDataConnection *conn_UaRoot;
      CDataConnection *conn_UaPath;
      CDataConnection *conn_Position;
      CDataConnection *conn_Timeout;
      CDataConnection *conn_ActualPosition;
      CDataConnection *conn_Homed;
      CDataConnection *conn_Moving;
      CDataConnection *conn_EqHolder;

      COutDataConnection<CIEC_WSTRING> conn_IdParams;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      forte::IPlugPin *getPlugPinUnchecked(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_INIT(const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paUaPath, const CIEC_LREAL &paPosition, const CIEC_TIME &paTimeout, const CIEC_LREAL &paActualPosition, const CIEC_BOOL &paHomed, const CIEC_BOOL &paMoving, const CIEC_WSTRING &paEqHolder, COutputParameter<CIEC_WSTRING> paIdParams) {
        COutputGuard guard_IdParams(paIdParams);
        var_UaRoot = paUaRoot;
        var_UaPath = paUaPath;
        var_Position = paPosition;
        var_Timeout = paTimeout;
        var_ActualPosition = paActualPosition;
        var_Homed = paHomed;
        var_Moving = paMoving;
        var_EqHolder = paEqHolder;
        executeEvent(scmEventINITID, nullptr);
        *paIdParams = var_IdParams;
      }

      void evt_START(const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paUaPath, const CIEC_LREAL &paPosition, const CIEC_TIME &paTimeout, const CIEC_LREAL &paActualPosition, const CIEC_BOOL &paHomed, const CIEC_BOOL &paMoving, const CIEC_WSTRING &paEqHolder, COutputParameter<CIEC_WSTRING> paIdParams) {
        COutputGuard guard_IdParams(paIdParams);
        var_UaRoot = paUaRoot;
        var_UaPath = paUaPath;
        var_Position = paPosition;
        var_Timeout = paTimeout;
        var_ActualPosition = paActualPosition;
        var_Homed = paHomed;
        var_Moving = paMoving;
        var_EqHolder = paEqHolder;
        executeEvent(scmEventSTARTID, nullptr);
        *paIdParams = var_IdParams;
      }

      void evt_SAMPLE(const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paUaPath, const CIEC_LREAL &paPosition, const CIEC_TIME &paTimeout, const CIEC_LREAL &paActualPosition, const CIEC_BOOL &paHomed, const CIEC_BOOL &paMoving, const CIEC_WSTRING &paEqHolder, COutputParameter<CIEC_WSTRING> paIdParams) {
        COutputGuard guard_IdParams(paIdParams);
        var_UaRoot = paUaRoot;
        var_UaPath = paUaPath;
        var_Position = paPosition;
        var_Timeout = paTimeout;
        var_ActualPosition = paActualPosition;
        var_Homed = paHomed;
        var_Moving = paMoving;
        var_EqHolder = paEqHolder;
        executeEvent(scmEventSAMPLEID, nullptr);
        *paIdParams = var_IdParams;
      }
  };
}

