/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SK_MoveAxis
 *** Description: A skill primitive: one action of one piece of equipment (move the axis, run the pump, weigh). It can be called on its own over OPC UA, or be a step of a bigger skill. Inside: SKILL_Core (state machine and OPC UA methods), a parameter block per parameter, SC_ (its contract: what this skill does and when it is done), SKILL_Run (one run, the same for every primitive) and EP_ (the equipment as the skill sees it). Technical: Skill primitive MoveAxis: Needle to Position, measured down from the limit switch; the direction follows from where it is (parameters: Position [mm] 0.0..60.0, default 0.0). OPC UA Start(Session, parameters...)/Stop/Abort/Reset(Session) -> [Accepted, ErrorID]; START/HALT/ABORT/RESET from a parent -> SUCCESS or FAILURE(ErrorID)
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
#include "forte/datatypes/forte_uint.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/filling/EP_LinearAxis_fbt.h"
#include "forte/filling/SC_MoveAxis_fbt.h"
#include "forte/forte_st_util.h"
#include "forte/iec61499/net/GEN_PUBLISH_fbt.h"
#include "forte/iec61499/net/GEN_SERVER_fbt.h"
#include "forte/modlib/SKILL_Core_fbt.h"
#include "forte/modlib/SKILL_Param_LREAL_fbt.h"
#include "forte/modlib/SKILL_Run_fbt.h"

namespace forte::filling {
  class FORTE_SK_MoveAxis final : public CCompositeFB {
      DECLARE_FIRMWARE_FB(FORTE_SK_MoveAxis)

    private:
      static const TEventID scmEventINITOID = 0;
      static const TEventID scmEventSUCCESSID = 1;
      static const TEventID scmEventFAILUREID = 2;
      static const TEventID scmEventINITID = 0;
      static const TEventID scmEventSTARTID = 1;
      static const TEventID scmEventHALTID = 2;
      static const TEventID scmEventABORTID = 3;
      static const TEventID scmEventRESETID = 4;

      CInternalFB<forte::modlib::FORTE_SKILL_Core> fb_Control;
      CInternalFB<forte::filling::FORTE_SC_MoveAxis> fb_Contract;
      CInternalFB<forte::iec61499::net::GEN_SERVER> fb_UaStart;
      CInternalFB<forte::modlib::FORTE_SKILL_Param_LREAL> fb_Par_Position;
      CInternalFB<forte::iec61499::net::GEN_PUBLISH> fb_PubParams;
      CInternalFB<forte::modlib::FORTE_SKILL_Run> fb_Run;
      CInternalFB<forte::filling::FORTE_EP_LinearAxis> fb_Port;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;
      void setFBNetworkInitialValues() override;

    public:
      FORTE_SK_MoveAxis(StringId paInstanceNameId, CFBContainer &paContainer);

      CEventConnection conn_INITO;
      CEventConnection conn_SUCCESS;
      CEventConnection conn_FAILURE;

      CDataConnection *conn_Module;
      CDataConnection *conn_UaRoot;
      CDataConnection *conn_UaPath;
      CDataConnection *conn_UaEnable;
      CDataConnection *conn_Methods;
      CDataConnection *conn_Holder;
      CDataConnection *conn_ReleaseAfter;
      CDataConnection *conn_Timeout;
      CDataConnection *conn_Position;

      COutDataConnection<CIEC_USINT> conn_State;
      COutDataConnection<CIEC_UINT> conn_ErrorID;

      COutDataConnection<CIEC_WSTRING> conn_if2in_Module;
      COutDataConnection<CIEC_WSTRING> conn_if2in_UaRoot;
      COutDataConnection<CIEC_WSTRING> conn_if2in_UaPath;
      COutDataConnection<CIEC_BOOL> conn_if2in_UaEnable;
      COutDataConnection<CIEC_BOOL> conn_if2in_Methods;
      COutDataConnection<CIEC_WSTRING> conn_if2in_Holder;
      COutDataConnection<CIEC_BOOL> conn_if2in_ReleaseAfter;
      COutDataConnection<CIEC_TIME> conn_if2in_Timeout;
      COutDataConnection<CIEC_LREAL> conn_if2in_Position;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;
      CDataConnection *getIf2InConUnchecked(TPortId) override;
  };
}

