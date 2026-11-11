/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: IO_AO
 *** Description: One analog output, also a PWM channel (the step pulses of a stepper motor, a motor's speed). Its Address says where it goes: a Raspberry Pi PWM channel, a Modbus register, or simulated. Technical: Analog output (raw = Bias + OUT * Gain, 0..65535; EN = FALSE writes 0); Address: 'gpio[chip:line(:pull_up|:pull_down)(:active_low)]' or 'pwm[chip:channel:period_ns]' a Raspberry Pi's line, set up here; 'modbus[...]' a Modbus CLIENT ID; 'sim' simulated; another name a local IO handle set up elsewhere (QW PARAMS); empty: not connected (QO = FALSE)
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
#include "forte/datatypes/forte_udint.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/datatypes/forte_word.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/eclipse4diac/io/QW_fbt.h"
#include "forte/eclipse4diac/io/pwmsysfs/PWMChip_fbt.h"
#include "forte/forte_st_util.h"
#include "forte/iec61499/net/GEN_CLIENT_fbt.h"
#include "forte/modlib/IO_RouteAO_fbt.h"

namespace forte::modlib {
  class FORTE_IO_AO final : public CCompositeFB {
      DECLARE_FIRMWARE_FB(FORTE_IO_AO)

    private:
      static const TEventID scmEventINITOID = 0;
      static const TEventID scmEventCNFID = 1;
      static const TEventID scmEventINITID = 0;
      static const TEventID scmEventREQID = 1;

      CInternalFB<forte::modlib::FORTE_IO_RouteAO> fb_Route;
      CInternalFB<forte::eclipse4diac::io::pwmsysfs::FORTE_PWMChip> fb_Line;
      CInternalFB<forte::eclipse4diac::io::FORTE_QW> fb_Local;
      CInternalFB<forte::iec61499::net::GEN_CLIENT> fb_Bus;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_IO_AO(StringId paInstanceNameId, CFBContainer &paContainer);

      CEventConnection conn_INITO;
      CEventConnection conn_CNF;

      CDataConnection *conn_Address;
      CDataConnection *conn_OUT;
      CDataConnection *conn_EN;
      CDataConnection *conn_Gain;
      CDataConnection *conn_Bias;

      COutDataConnection<CIEC_BOOL> conn_QO;

      COutDataConnection<CIEC_STRING> conn_if2in_Address;
      COutDataConnection<CIEC_LREAL> conn_if2in_OUT;
      COutDataConnection<CIEC_BOOL> conn_if2in_EN;
      COutDataConnection<CIEC_LREAL> conn_if2in_Gain;
      COutDataConnection<CIEC_LREAL> conn_if2in_Bias;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;
      CDataConnection *getIf2InConUnchecked(TPortId) override;
  };
}

