/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: EP_LinearAxis
 *** Description: The equipment as its skills see it, the same in every skill that uses it: plays a command (its output values, phase by phase) on the equipment's command channel, and gives the equipment's newest state. Technical: LinearAxis as its skills see it: a command on the socket Skill (AEquipment: SEND, PLAYED when all phases are out) goes out on its command channel; STATE gives its inputs and holder
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/cfb.h"
#include "forte/typelib.h"
#include "forte/datatypes/forte_any_variant.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/filling/EC_LinearAxis_fbt.h"
#include "forte/filling/EV_LinearAxis_fbt.h"
#include "forte/forte_st_util.h"
#include "forte/iec61499/events/E_DELAY_fbt.h"
#include "forte/iec61499/net/GEN_PUBLISH_fbt.h"
#include "forte/iec61499/net/GEN_SUBSCRIBE_fbt.h"
#include "forte/modlib/AEquipment_adp.h"

namespace forte::filling {
  class FORTE_EP_LinearAxis final : public CCompositeFB {
      DECLARE_FIRMWARE_FB(FORTE_EP_LinearAxis)

    private:
      static const TEventID scmEventINITOID = 0;
      static const TEventID scmEventSTATEID = 1;
      static const TEventID scmEventINITID = 0;

      CInternalFB<forte::filling::FORTE_EV_LinearAxis> fb_EqView;
      CInternalFB<forte::iec61499::net::GEN_SUBSCRIBE> fb_EqState;
      CInternalFB<forte::filling::FORTE_EC_LinearAxis> fb_Driver;
      CInternalFB<forte::iec61499::events::FORTE_E_DELAY> fb_PhaseT;
      CInternalFB<forte::iec61499::net::GEN_PUBLISH> fb_EqCmd;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;
      void setFBNetworkInitialValues() override;

    public:
      FORTE_EP_LinearAxis(StringId paInstanceNameId, CFBContainer &paContainer);

      forte::CSocketPin<forte::modlib::FORTE_AEquipment_Socket> var_Skill;

      CEventConnection conn_INITO;
      CEventConnection conn_STATE;

      CDataConnection *conn_Module;

      COutDataConnection<CIEC_BOOL> conn_AtHome;
      COutDataConnection<CIEC_LREAL> conn_ActualPosition;
      COutDataConnection<CIEC_BOOL> conn_Homed;
      COutDataConnection<CIEC_BOOL> conn_Moving;
      COutDataConnection<CIEC_WSTRING> conn_EqHolder;

      COutDataConnection<CIEC_WSTRING> conn_if2in_Module;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      forte::ISocketPin *getSocketPinUnchecked(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;
      CDataConnection *getIf2InConUnchecked(TPortId) override;
  };
}

