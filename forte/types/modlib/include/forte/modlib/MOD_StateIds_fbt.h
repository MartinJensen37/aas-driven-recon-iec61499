/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: MOD_StateIds
 *** Description: Builds the OPC UA addresses (Module/Reset ... Module/State) and the local channel names of the state manager. Technical: OPC UA and local channel IDs of the module state manager
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/simplefb.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"

namespace forte::modlib {
  class FORTE_MOD_StateIds final : public CSimpleFB {
      DECLARE_FIRMWARE_FB(FORTE_MOD_StateIds)

    private:
      static const TEventID scmEventINITOID = 0;
      static const TEventID scmEventINITID = 0;

      CIEC_ANY *getVarInternal(size_t) override;

      void alg_INIT(void);

      void enterStateINIT(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_MOD_StateIds(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_WSTRING var_Module;
      CIEC_WSTRING var_UaRoot;

      CIEC_WSTRING var_IdReset;
      CIEC_WSTRING var_IdStart;
      CIEC_WSTRING var_IdStop;
      CIEC_WSTRING var_IdAbort;
      CIEC_WSTRING var_IdClear;
      CIEC_WSTRING var_IdPub;
      CIEC_WSTRING var_IdState;
      CIEC_WSTRING var_IdQuery;
      CIEC_WSTRING var_IdAct;

      CEventConnection conn_INITO;

      CDataConnection *conn_Module;
      CDataConnection *conn_UaRoot;

      COutDataConnection<CIEC_WSTRING> conn_IdReset;
      COutDataConnection<CIEC_WSTRING> conn_IdStart;
      COutDataConnection<CIEC_WSTRING> conn_IdStop;
      COutDataConnection<CIEC_WSTRING> conn_IdAbort;
      COutDataConnection<CIEC_WSTRING> conn_IdClear;
      COutDataConnection<CIEC_WSTRING> conn_IdPub;
      COutDataConnection<CIEC_WSTRING> conn_IdState;
      COutDataConnection<CIEC_WSTRING> conn_IdQuery;
      COutDataConnection<CIEC_WSTRING> conn_IdAct;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_INIT(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paUaRoot, COutputParameter<CIEC_WSTRING> paIdReset, COutputParameter<CIEC_WSTRING> paIdStart, COutputParameter<CIEC_WSTRING> paIdStop, COutputParameter<CIEC_WSTRING> paIdAbort, COutputParameter<CIEC_WSTRING> paIdClear, COutputParameter<CIEC_WSTRING> paIdPub, COutputParameter<CIEC_WSTRING> paIdState, COutputParameter<CIEC_WSTRING> paIdQuery, COutputParameter<CIEC_WSTRING> paIdAct) {
        COutputGuard guard_IdReset(paIdReset);
        COutputGuard guard_IdStart(paIdStart);
        COutputGuard guard_IdStop(paIdStop);
        COutputGuard guard_IdAbort(paIdAbort);
        COutputGuard guard_IdClear(paIdClear);
        COutputGuard guard_IdPub(paIdPub);
        COutputGuard guard_IdState(paIdState);
        COutputGuard guard_IdQuery(paIdQuery);
        COutputGuard guard_IdAct(paIdAct);
        var_Module = paModule;
        var_UaRoot = paUaRoot;
        executeEvent(scmEventINITID, nullptr);
        *paIdReset = var_IdReset;
        *paIdStart = var_IdStart;
        *paIdStop = var_IdStop;
        *paIdAbort = var_IdAbort;
        *paIdClear = var_IdClear;
        *paIdPub = var_IdPub;
        *paIdState = var_IdState;
        *paIdQuery = var_IdQuery;
        *paIdAct = var_IdAct;
      }

      void operator()(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paUaRoot, COutputParameter<CIEC_WSTRING> paIdReset, COutputParameter<CIEC_WSTRING> paIdStart, COutputParameter<CIEC_WSTRING> paIdStop, COutputParameter<CIEC_WSTRING> paIdAbort, COutputParameter<CIEC_WSTRING> paIdClear, COutputParameter<CIEC_WSTRING> paIdPub, COutputParameter<CIEC_WSTRING> paIdState, COutputParameter<CIEC_WSTRING> paIdQuery, COutputParameter<CIEC_WSTRING> paIdAct) {
        evt_INIT(std::forward<const CIEC_WSTRING &>(paModule), std::forward<const CIEC_WSTRING &>(paUaRoot), std::forward<COutputParameter<CIEC_WSTRING>>(paIdReset), std::forward<COutputParameter<CIEC_WSTRING>>(paIdStart), std::forward<COutputParameter<CIEC_WSTRING>>(paIdStop), std::forward<COutputParameter<CIEC_WSTRING>>(paIdAbort), std::forward<COutputParameter<CIEC_WSTRING>>(paIdClear), std::forward<COutputParameter<CIEC_WSTRING>>(paIdPub), std::forward<COutputParameter<CIEC_WSTRING>>(paIdState), std::forward<COutputParameter<CIEC_WSTRING>>(paIdQuery), std::forward<COutputParameter<CIEC_WSTRING>>(paIdAct));
      }
  };
}

