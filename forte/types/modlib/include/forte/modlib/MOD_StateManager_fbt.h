/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: MOD_StateManager
 *** Description: The module's PackML state: Stopped, Resetting, Idle, Execute, Stopping, Aborted. The owner changes it with the OPC UA methods Reset, Start, Stop, Abort and Clear. It runs the Resetting and Stopping procedures and publishes the state for clients and for every block. Technical: Module state manager: OPC UA methods Reset/Start/Stop/Abort/Clear(Session) answer [Accepted, ErrorID]; publishes the PackML State over OPC UA and on the module's state channel; RUN_RESETTING and RUN_STOPPING start the procedures, which answer with *_DONE or *_FAILED
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/cfb.h"
#include "forte/typelib.h"
#include "forte/datatypes/forte_any_variant.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_int.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/iec61499/events/E_DELAY_fbt.h"
#include "forte/iec61499/net/GEN_PUBLISH_fbt.h"
#include "forte/iec61499/net/GEN_SERVER_fbt.h"
#include "forte/iec61499/net/GEN_SUBSCRIBE_fbt.h"
#include "forte/modlib/MOD_ActivityCount_fbt.h"
#include "forte/modlib/MOD_OwnerView_fbt.h"
#include "forte/modlib/MOD_StateGate_fbt.h"
#include "forte/modlib/MOD_StateIds_fbt.h"
#include "forte/modlib/MOD_StateLogic_fbt.h"

namespace forte::modlib {
  class FORTE_MOD_StateManager final : public CCompositeFB {
      DECLARE_FIRMWARE_FB(FORTE_MOD_StateManager)

    private:
      static const TEventID scmEventINITOID = 0;
      static const TEventID scmEventRUN_RESETTINGID = 1;
      static const TEventID scmEventRUN_STOPPINGID = 2;
      static const TEventID scmEventINITID = 0;
      static const TEventID scmEventRESETTING_DONEID = 1;
      static const TEventID scmEventRESETTING_FAILEDID = 2;
      static const TEventID scmEventSTOPPING_DONEID = 3;
      static const TEventID scmEventSTOPPING_FAILEDID = 4;

      CInternalFB<forte::modlib::FORTE_MOD_StateIds> fb_Ids;
      CInternalFB<forte::modlib::FORTE_MOD_OwnerView> fb_Owner;
      CInternalFB<forte::iec61499::net::GEN_SERVER> fb_Reset;
      CInternalFB<forte::iec61499::net::GEN_SERVER> fb_Start;
      CInternalFB<forte::iec61499::net::GEN_SERVER> fb_Stop;
      CInternalFB<forte::iec61499::net::GEN_SERVER> fb_Abort;
      CInternalFB<forte::iec61499::net::GEN_SERVER> fb_Clear;
      CInternalFB<forte::modlib::FORTE_MOD_StateGate> fb_Gate;
      CInternalFB<forte::modlib::FORTE_MOD_StateLogic> fb_Logic;
      CInternalFB<forte::iec61499::net::GEN_PUBLISH> fb_PubUa;
      CInternalFB<forte::iec61499::net::GEN_PUBLISH> fb_PubState;
      CInternalFB<forte::iec61499::net::GEN_SUBSCRIBE> fb_SubQuery;
      CInternalFB<forte::iec61499::net::GEN_SUBSCRIBE> fb_SubAct;
      CInternalFB<forte::modlib::FORTE_MOD_ActivityCount> fb_Count;
      CInternalFB<forte::iec61499::events::FORTE_E_DELAY> fb_Wd;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;
      void setFBNetworkInitialValues() override;

    public:
      FORTE_MOD_StateManager(StringId paInstanceNameId, CFBContainer &paContainer);

      CEventConnection conn_INITO;
      CEventConnection conn_RUN_RESETTING;
      CEventConnection conn_RUN_STOPPING;

      CDataConnection *conn_Module;
      CDataConnection *conn_UaRoot;
      CDataConnection *conn_UaEnable;
      CDataConnection *conn_StopTimeout;

      COutDataConnection<CIEC_WSTRING> conn_if2in_Module;
      COutDataConnection<CIEC_WSTRING> conn_if2in_UaRoot;
      COutDataConnection<CIEC_BOOL> conn_if2in_UaEnable;
      COutDataConnection<CIEC_TIME> conn_if2in_StopTimeout;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;
      CDataConnection *getIf2InConUnchecked(TPortId) override;
  };
}

