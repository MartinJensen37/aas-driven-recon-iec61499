/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: MOD_Occupation
 *** Description: Who may command the module. A client first calls the OPC UA method Occupy with a session id it chose; until it calls Release, only commands carrying that session id are accepted. Publishes Occupied (never the id) and tells every block of the module who the owner is. Technical: Module occupation: OPC UA methods Occupy(Session) and Release(Session) answer [Accepted, ErrorID]; publishes Occupied (never the session ID) and shares the owner on a local channel
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/cfb.h"
#include "forte/typelib.h"
#include "forte/datatypes/forte_any_variant.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/iec61499/net/GEN_PUBLISH_fbt.h"
#include "forte/iec61499/net/GEN_SERVER_fbt.h"
#include "forte/iec61499/net/GEN_SUBSCRIBE_fbt.h"
#include "forte/modlib/MOD_OccupationIds_fbt.h"
#include "forte/modlib/MOD_OccupationLogic_fbt.h"

namespace forte::modlib {
  class FORTE_MOD_Occupation final : public CCompositeFB {
      DECLARE_FIRMWARE_FB(FORTE_MOD_Occupation)

    private:
      static const TEventID scmEventINITOID = 0;
      static const TEventID scmEventINITID = 0;

      CInternalFB<forte::modlib::FORTE_MOD_OccupationIds> fb_Ids;
      CInternalFB<forte::iec61499::net::GEN_SERVER> fb_Occupy;
      CInternalFB<forte::iec61499::net::GEN_SERVER> fb_Release;
      CInternalFB<forte::modlib::FORTE_MOD_OccupationLogic> fb_Logic;
      CInternalFB<forte::iec61499::net::GEN_PUBLISH> fb_PubOwner;
      CInternalFB<forte::iec61499::net::GEN_SUBSCRIBE> fb_SubQuery;
      CInternalFB<forte::iec61499::net::GEN_PUBLISH> fb_PubUa;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;
      void setFBNetworkInitialValues() override;

    public:
      FORTE_MOD_Occupation(StringId paInstanceNameId, CFBContainer &paContainer);

      CEventConnection conn_INITO;

      CDataConnection *conn_Module;
      CDataConnection *conn_UaRoot;
      CDataConnection *conn_UaEnable;

      COutDataConnection<CIEC_WSTRING> conn_if2in_Module;
      COutDataConnection<CIEC_WSTRING> conn_if2in_UaRoot;
      COutDataConnection<CIEC_BOOL> conn_if2in_UaEnable;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;
      CDataConnection *getIf2InConUnchecked(TPortId) override;
  };
}

