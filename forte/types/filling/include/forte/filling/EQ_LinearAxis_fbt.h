/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: EQ_LinearAxis
 *** Description: An equipment block: the only block that touches this equipment's pins. Skills send it what to switch over a local channel; it switches the outputs (off first, then on), reads the inputs every cycle and reports them to the skills and to OPC UA. One skill holds it at a time; on release or when the module aborts it switches everything off. Technical: Needle lift, a stepper motor through a step and direction driver, with a limit switch at the top (home); equipment IO: owns its IO points, writes the output values its holder sends, reads its inputs every cycle and reports changes
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
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/filling/EL_LinearAxis_fbt.h"
#include "forte/iec61499/events/E_CYCLE_fbt.h"
#include "forte/iec61499/events/E_DELAY_fbt.h"
#include "forte/iec61499/net/GEN_PUBLISH_fbt.h"
#include "forte/iec61499/net/GEN_SUBSCRIBE_fbt.h"
#include "forte/modlib/IO_AO_fbt.h"
#include "forte/modlib/IO_DI_fbt.h"
#include "forte/modlib/IO_DO_fbt.h"
#include "forte/modlib/MOD_StateView_fbt.h"

namespace forte::filling {
  class FORTE_EQ_LinearAxis final : public CCompositeFB {
      DECLARE_FIRMWARE_FB(FORTE_EQ_LinearAxis)

    private:
      static const TEventID scmEventINITOID = 0;
      static const TEventID scmEventINITID = 0;

      CInternalFB<forte::filling::FORTE_EL_LinearAxis> fb_Logic;
      CInternalFB<forte::iec61499::events::FORTE_E_CYCLE> fb_Cycle;
      CInternalFB<forte::iec61499::events::FORTE_E_DELAY> fb_MoveT;
      CInternalFB<forte::modlib::FORTE_MOD_StateView> fb_Mode;
      CInternalFB<forte::iec61499::net::GEN_SUBSCRIBE> fb_SubCmd;
      CInternalFB<forte::iec61499::net::GEN_SUBSCRIBE> fb_SubRelease;
      CInternalFB<forte::iec61499::net::GEN_PUBLISH> fb_PubState;
      CInternalFB<forte::iec61499::net::GEN_PUBLISH> fb_PubUa;
      CInternalFB<forte::modlib::FORTE_IO_DI> fb_In_AtHome;
      CInternalFB<forte::modlib::FORTE_IO_DO> fb_Out_Enable;
      CInternalFB<forte::modlib::FORTE_IO_DO> fb_Out_Down;
      CInternalFB<forte::modlib::FORTE_IO_AO> fb_Out_Step;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;
      void setFBNetworkInitialValues() override;

    public:
      FORTE_EQ_LinearAxis(StringId paInstanceNameId, CFBContainer &paContainer);

      CEventConnection conn_INITO;

      CDataConnection *conn_Module;
      CDataConnection *conn_Name;
      CDataConnection *conn_UaRoot;
      CDataConnection *conn_UaEnable;
      CDataConnection *conn_CycleTime;
      CDataConnection *conn_AtHome_Address;
      CDataConnection *conn_AtHome_Sim;
      CDataConnection *conn_Enable_Address;
      CDataConnection *conn_Down_Address;
      CDataConnection *conn_Step_Address;
      CDataConnection *conn_Step_Gain;
      CDataConnection *conn_Step_Bias;

      COutDataConnection<CIEC_WSTRING> conn_if2in_Module;
      COutDataConnection<CIEC_WSTRING> conn_if2in_Name;
      COutDataConnection<CIEC_WSTRING> conn_if2in_UaRoot;
      COutDataConnection<CIEC_BOOL> conn_if2in_UaEnable;
      COutDataConnection<CIEC_TIME> conn_if2in_CycleTime;
      COutDataConnection<CIEC_STRING> conn_if2in_AtHome_Address;
      COutDataConnection<CIEC_BOOL> conn_if2in_AtHome_Sim;
      COutDataConnection<CIEC_STRING> conn_if2in_Enable_Address;
      COutDataConnection<CIEC_STRING> conn_if2in_Down_Address;
      COutDataConnection<CIEC_STRING> conn_if2in_Step_Address;
      COutDataConnection<CIEC_LREAL> conn_if2in_Step_Gain;
      COutDataConnection<CIEC_LREAL> conn_if2in_Step_Bias;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;
      CDataConnection *getIf2InConUnchecked(TPortId) override;
  };
}

