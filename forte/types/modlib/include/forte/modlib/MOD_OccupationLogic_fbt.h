/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: MOD_OccupationLogic
 *** Description: Decides Occupy and Release: occupy when free (or again by the owner), release only by the owner, and answer Accepted or an error code. Technical: Occupation by session ID: Occupy when free (or again by the owner), Release only by the owner
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/basicfb.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"

namespace forte::modlib {
  class FORTE_MOD_OccupationLogic final : public CBasicFB {
      DECLARE_FIRMWARE_FB(FORTE_MOD_OccupationLogic)

    private:
      static const TEventID scmEventOCCUPY_RSPID = 0;
      static const TEventID scmEventRELEASE_RSPID = 1;
      static const TEventID scmEventCHGID = 2;
      static const TEventID scmEventOCCUPY_REQID = 0;
      static const TEventID scmEventRELEASE_REQID = 1;
      static const TEventID scmEventQUERY_REQID = 2;

      CIEC_ANY *getVarInternal(size_t) override;

      void alg_Alg_Occupy(void);
      void alg_Alg_Release(void);

      static const TForteInt16 scmStateSTART = 0;
      static const TForteInt16 scmStateOccupy = 1;
      static const TForteInt16 scmStateRelease = 2;
      static const TForteInt16 scmStateQuery = 3;

      void enterStateSTART(CEventChainExecutionThread *const paECET);
      void enterStateOccupy(CEventChainExecutionThread *const paECET);
      void enterStateRelease(CEventChainExecutionThread *const paECET);
      void enterStateQuery(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_MOD_OccupationLogic(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_WSTRING var_OccupySession;
      CIEC_WSTRING var_ReleaseSession;

      CIEC_BOOL var_Accepted;
      CIEC_UINT var_ErrorID;
      CIEC_WSTRING var_Owner;
      CIEC_BOOL var_Occupied;

      CEventConnection conn_OCCUPY_RSP;
      CEventConnection conn_RELEASE_RSP;
      CEventConnection conn_CHG;

      CDataConnection *conn_OccupySession;
      CDataConnection *conn_ReleaseSession;

      COutDataConnection<CIEC_BOOL> conn_Accepted;
      COutDataConnection<CIEC_UINT> conn_ErrorID;
      COutDataConnection<CIEC_WSTRING> conn_Owner;
      COutDataConnection<CIEC_BOOL> conn_Occupied;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_OCCUPY_REQ(const CIEC_WSTRING &paOccupySession, const CIEC_WSTRING &paReleaseSession, CAnyBitOutputParameter<CIEC_BOOL> paAccepted, COutputParameter<CIEC_UINT> paErrorID, COutputParameter<CIEC_WSTRING> paOwner, CAnyBitOutputParameter<CIEC_BOOL> paOccupied) {
        COutputGuard guard_Accepted(paAccepted);
        COutputGuard guard_ErrorID(paErrorID);
        COutputGuard guard_Owner(paOwner);
        COutputGuard guard_Occupied(paOccupied);
        var_OccupySession = paOccupySession;
        var_ReleaseSession = paReleaseSession;
        executeEvent(scmEventOCCUPY_REQID, nullptr);
        *paAccepted = var_Accepted;
        *paErrorID = var_ErrorID;
        *paOwner = var_Owner;
        *paOccupied = var_Occupied;
      }

      void evt_RELEASE_REQ(const CIEC_WSTRING &paOccupySession, const CIEC_WSTRING &paReleaseSession, CAnyBitOutputParameter<CIEC_BOOL> paAccepted, COutputParameter<CIEC_UINT> paErrorID, COutputParameter<CIEC_WSTRING> paOwner, CAnyBitOutputParameter<CIEC_BOOL> paOccupied) {
        COutputGuard guard_Accepted(paAccepted);
        COutputGuard guard_ErrorID(paErrorID);
        COutputGuard guard_Owner(paOwner);
        COutputGuard guard_Occupied(paOccupied);
        var_OccupySession = paOccupySession;
        var_ReleaseSession = paReleaseSession;
        executeEvent(scmEventRELEASE_REQID, nullptr);
        *paAccepted = var_Accepted;
        *paErrorID = var_ErrorID;
        *paOwner = var_Owner;
        *paOccupied = var_Occupied;
      }

      void evt_QUERY_REQ(const CIEC_WSTRING &paOccupySession, const CIEC_WSTRING &paReleaseSession, CAnyBitOutputParameter<CIEC_BOOL> paAccepted, COutputParameter<CIEC_UINT> paErrorID, COutputParameter<CIEC_WSTRING> paOwner, CAnyBitOutputParameter<CIEC_BOOL> paOccupied) {
        COutputGuard guard_Accepted(paAccepted);
        COutputGuard guard_ErrorID(paErrorID);
        COutputGuard guard_Owner(paOwner);
        COutputGuard guard_Occupied(paOccupied);
        var_OccupySession = paOccupySession;
        var_ReleaseSession = paReleaseSession;
        executeEvent(scmEventQUERY_REQID, nullptr);
        *paAccepted = var_Accepted;
        *paErrorID = var_ErrorID;
        *paOwner = var_Owner;
        *paOccupied = var_Occupied;
      }
  };
}

