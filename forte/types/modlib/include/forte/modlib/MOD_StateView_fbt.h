/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: MOD_StateView
 *** Description: Tells the block it sits in the module's PackML state, and asks for it once at start. Technical: The module's PackML state from its local channel; asks for the current value at INIT
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/cfb.h"
#include "forte/typelib.h"
#include "forte/datatypes/forte_any_variant.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"
#include "forte/iec61499/net/GEN_PUBLISH_fbt.h"
#include "forte/iec61499/net/GEN_SUBSCRIBE_fbt.h"
#include "forte/modlib/MOD_StateLatch_fbt.h"

namespace forte::modlib {
  class FORTE_MOD_StateView final : public CCompositeFB {
      DECLARE_FIRMWARE_FB(FORTE_MOD_StateView)

    private:
      static const TEventID scmEventINITOID = 0;
      static const TEventID scmEventCHGID = 1;
      static const TEventID scmEventINITID = 0;

      CInternalFB<forte::modlib::FORTE_MOD_StateLatch> fb_Latch;
      CInternalFB<forte::iec61499::net::GEN_SUBSCRIBE> fb_Listen;
      CInternalFB<forte::iec61499::net::GEN_PUBLISH> fb_Query;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;
      void setFBNetworkInitialValues() override;

    public:
      FORTE_MOD_StateView(StringId paInstanceNameId, CFBContainer &paContainer);

      CEventConnection conn_INITO;
      CEventConnection conn_CHG;

      CDataConnection *conn_Module;

      COutDataConnection<CIEC_USINT> conn_State;

      COutDataConnection<CIEC_WSTRING> conn_if2in_Module;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;
      CDataConnection *getIf2InConUnchecked(TPortId) override;
  };
}

