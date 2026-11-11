/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: IO_AI
 *** Description: One analog input (a weight, a pressure). Its Address says where it is read: an IO handle, a Modbus register, or simulated. Technical: Analog input; Address: 'gpio[chip:line(:pull_up|:pull_down)(:active_low)]' or 'pwm[chip:channel:period_ns]' a Raspberry Pi's line, set up here; 'modbus[...]' a Modbus CLIENT ID; 'sim' simulated; another name a local IO handle set up elsewhere (IW PARAMS); empty: not connected (QO = FALSE)
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/cfb.h"
#include "forte/typelib.h"
#include "forte/datatypes/forte_any_variant.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_string.h"
#include "forte/datatypes/forte_word.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/eclipse4diac/io/IW_fbt.h"
#include "forte/forte_st_util.h"
#include "forte/iec61499/net/GEN_CLIENT_fbt.h"
#include "forte/modlib/IO_RouteAI_fbt.h"

namespace forte::modlib {
  class FORTE_IO_AI final : public CCompositeFB {
      DECLARE_FIRMWARE_FB(FORTE_IO_AI)

    private:
      static const TEventID scmEventINITOID = 0;
      static const TEventID scmEventCNFID = 1;
      static const TEventID scmEventINITID = 0;
      static const TEventID scmEventREQID = 1;

      CInternalFB<forte::modlib::FORTE_IO_RouteAI> fb_Route;
      CInternalFB<forte::eclipse4diac::io::FORTE_IW> fb_Local;
      CInternalFB<forte::iec61499::net::GEN_CLIENT> fb_Bus;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_IO_AI(StringId paInstanceNameId, CFBContainer &paContainer);

      CEventConnection conn_INITO;
      CEventConnection conn_CNF;

      CDataConnection *conn_Address;
      CDataConnection *conn_SimValue;
      CDataConnection *conn_Scale;

      COutDataConnection<CIEC_BOOL> conn_QO;
      COutDataConnection<CIEC_LREAL> conn_IN;

      COutDataConnection<CIEC_STRING> conn_if2in_Address;
      COutDataConnection<CIEC_LREAL> conn_if2in_SimValue;
      COutDataConnection<CIEC_LREAL> conn_if2in_Scale;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;
      CDataConnection *getIf2InConUnchecked(TPortId) override;
  };
}

