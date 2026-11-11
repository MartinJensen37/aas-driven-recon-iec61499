/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: MOD_OccupationIds
 *** Description: Builds the OPC UA addresses (Occupy, Release, Occupied) and the local channel names of the occupation from the module's name and OPC UA root. Technical: OPC UA and local channel IDs of the occupation
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/simplefb.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"

namespace forte::modlib {
  class FORTE_MOD_OccupationIds final : public CSimpleFB {
      DECLARE_FIRMWARE_FB(FORTE_MOD_OccupationIds)

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
      FORTE_MOD_OccupationIds(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_WSTRING var_Module;
      CIEC_WSTRING var_UaRoot;

      CIEC_WSTRING var_IdOccupy;
      CIEC_WSTRING var_IdRelease;
      CIEC_WSTRING var_IdPub;
      CIEC_WSTRING var_IdOwner;
      CIEC_WSTRING var_IdQuery;

      CEventConnection conn_INITO;

      CDataConnection *conn_Module;
      CDataConnection *conn_UaRoot;

      COutDataConnection<CIEC_WSTRING> conn_IdOccupy;
      COutDataConnection<CIEC_WSTRING> conn_IdRelease;
      COutDataConnection<CIEC_WSTRING> conn_IdPub;
      COutDataConnection<CIEC_WSTRING> conn_IdOwner;
      COutDataConnection<CIEC_WSTRING> conn_IdQuery;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_INIT(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paUaRoot, COutputParameter<CIEC_WSTRING> paIdOccupy, COutputParameter<CIEC_WSTRING> paIdRelease, COutputParameter<CIEC_WSTRING> paIdPub, COutputParameter<CIEC_WSTRING> paIdOwner, COutputParameter<CIEC_WSTRING> paIdQuery) {
        COutputGuard guard_IdOccupy(paIdOccupy);
        COutputGuard guard_IdRelease(paIdRelease);
        COutputGuard guard_IdPub(paIdPub);
        COutputGuard guard_IdOwner(paIdOwner);
        COutputGuard guard_IdQuery(paIdQuery);
        var_Module = paModule;
        var_UaRoot = paUaRoot;
        executeEvent(scmEventINITID, nullptr);
        *paIdOccupy = var_IdOccupy;
        *paIdRelease = var_IdRelease;
        *paIdPub = var_IdPub;
        *paIdOwner = var_IdOwner;
        *paIdQuery = var_IdQuery;
      }

      void operator()(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paUaRoot, COutputParameter<CIEC_WSTRING> paIdOccupy, COutputParameter<CIEC_WSTRING> paIdRelease, COutputParameter<CIEC_WSTRING> paIdPub, COutputParameter<CIEC_WSTRING> paIdOwner, COutputParameter<CIEC_WSTRING> paIdQuery) {
        evt_INIT(std::forward<const CIEC_WSTRING &>(paModule), std::forward<const CIEC_WSTRING &>(paUaRoot), std::forward<COutputParameter<CIEC_WSTRING>>(paIdOccupy), std::forward<COutputParameter<CIEC_WSTRING>>(paIdRelease), std::forward<COutputParameter<CIEC_WSTRING>>(paIdPub), std::forward<COutputParameter<CIEC_WSTRING>>(paIdOwner), std::forward<COutputParameter<CIEC_WSTRING>>(paIdQuery));
      }
  };
}

