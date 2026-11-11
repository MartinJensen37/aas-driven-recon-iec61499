/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: MOD_StateLatch
 *** Description: Keeps the last module state heard on the state channel. Technical: Local channel IDs of the PackML state and its refresh query; types and forwards the received PackML state
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/simplefb.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"

namespace forte::modlib {
  class FORTE_MOD_StateLatch final : public CSimpleFB {
      DECLARE_FIRMWARE_FB(FORTE_MOD_StateLatch)

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
      FORTE_MOD_StateLatch(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_WSTRING var_Module;
      CIEC_USINT var_Received;

      CIEC_WSTRING var_IdSub;
      CIEC_WSTRING var_IdQuery;
      CIEC_USINT var_State;

      CEventConnection conn_INITO;
      CEventConnection conn_CNF;

      CDataConnection *conn_Module;
      CDataConnection *conn_Received;

      COutDataConnection<CIEC_WSTRING> conn_IdSub;
      COutDataConnection<CIEC_WSTRING> conn_IdQuery;
      COutDataConnection<CIEC_USINT> conn_State;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_INIT(const CIEC_WSTRING &paModule, const CIEC_USINT &paReceived, COutputParameter<CIEC_WSTRING> paIdSub, COutputParameter<CIEC_WSTRING> paIdQuery, COutputParameter<CIEC_USINT> paState) {
        COutputGuard guard_IdSub(paIdSub);
        COutputGuard guard_IdQuery(paIdQuery);
        COutputGuard guard_State(paState);
        var_Module = paModule;
        var_Received = paReceived;
        executeEvent(scmEventINITID, nullptr);
        *paIdSub = var_IdSub;
        *paIdQuery = var_IdQuery;
        *paState = var_State;
      }

      void evt_REQ(const CIEC_WSTRING &paModule, const CIEC_USINT &paReceived, COutputParameter<CIEC_WSTRING> paIdSub, COutputParameter<CIEC_WSTRING> paIdQuery, COutputParameter<CIEC_USINT> paState) {
        COutputGuard guard_IdSub(paIdSub);
        COutputGuard guard_IdQuery(paIdQuery);
        COutputGuard guard_State(paState);
        var_Module = paModule;
        var_Received = paReceived;
        executeEvent(scmEventREQID, nullptr);
        *paIdSub = var_IdSub;
        *paIdQuery = var_IdQuery;
        *paState = var_State;
      }
  };
}

