/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SKILL_Core
 *** Description: The part every skill shares: its state machine (Idle, Running, Stopping, Succeeded, Failed, Aborted), the OPC UA methods Stop, Abort and Reset, and the State and ErrorID it publishes. It checks a client's Start (the caller holds the occupation, the module is in Execute, the skill is not running, the values are in range, the equipment is free) and then starts the skill's own logic. Technical: Skill core: state machine, OPC UA Stop/Abort/Reset(Session) -> [Accepted, ErrorID], State and ErrorID published, activity counted; the Start method (with the skill's parameters) is wired to START_REQ and START_RSP; RUN starts the execution, SUCCESS or FAILURE(ErrorID) ends it
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
#include "forte/forte_st_util.h"
#include "forte/iec61499/events/E_DELAY_fbt.h"
#include "forte/iec61499/net/GEN_PUBLISH_fbt.h"
#include "forte/iec61499/net/GEN_SERVER_fbt.h"
#include "forte/modlib/MOD_OwnerView_fbt.h"
#include "forte/modlib/MOD_StateView_fbt.h"
#include "forte/modlib/SKILL_Control_fbt.h"
#include "forte/modlib/SKILL_Gate_fbt.h"

namespace forte::modlib {
  class FORTE_SKILL_Core final : public CCompositeFB {
      DECLARE_FIRMWARE_FB(FORTE_SKILL_Core)

    private:
      static const TEventID scmEventINITOID = 0;
      static const TEventID scmEventSTART_RSPID = 1;
      static const TEventID scmEventRUNID = 2;
      static const TEventID scmEventHALT_SEQID = 3;
      static const TEventID scmEventABORT_SEQID = 4;
      static const TEventID scmEventRESET_SEQID = 5;
      static const TEventID scmEventRUN_STOPPINGID = 6;
      static const TEventID scmEventSUCCESSID = 7;
      static const TEventID scmEventFAILUREID = 8;
      static const TEventID scmEventINITID = 0;
      static const TEventID scmEventSTART_REQID = 1;
      static const TEventID scmEventSTARTID = 2;
      static const TEventID scmEventHALTID = 3;
      static const TEventID scmEventABORTID = 4;
      static const TEventID scmEventRESETID = 5;
      static const TEventID scmEventEXECUTE_DONEID = 6;
      static const TEventID scmEventEXECUTE_FAILEDID = 7;
      static const TEventID scmEventSTOPPING_DONEID = 8;

      CInternalFB<forte::modlib::FORTE_SKILL_Gate> fb_Gate;
      CInternalFB<forte::modlib::FORTE_SKILL_Control> fb_Control;
      CInternalFB<forte::modlib::FORTE_MOD_OwnerView> fb_Owner;
      CInternalFB<forte::modlib::FORTE_MOD_StateView> fb_Mode;
      CInternalFB<forte::iec61499::net::GEN_SERVER> fb_UaStop;
      CInternalFB<forte::iec61499::net::GEN_SERVER> fb_UaAbort;
      CInternalFB<forte::iec61499::net::GEN_SERVER> fb_UaReset;
      CInternalFB<forte::iec61499::net::GEN_PUBLISH> fb_PubState;
      CInternalFB<forte::iec61499::net::GEN_PUBLISH> fb_Act;
      CInternalFB<forte::iec61499::events::FORTE_E_DELAY> fb_ToIdle;
      CInternalFB<forte::iec61499::net::GEN_PUBLISH> fb_PubRelease;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;
      void setFBNetworkInitialValues() override;

    public:
      FORTE_SKILL_Core(StringId paInstanceNameId, CFBContainer &paContainer);

      CEventConnection conn_INITO;
      CEventConnection conn_START_RSP;
      CEventConnection conn_RUN;
      CEventConnection conn_HALT_SEQ;
      CEventConnection conn_ABORT_SEQ;
      CEventConnection conn_RESET_SEQ;
      CEventConnection conn_RUN_STOPPING;
      CEventConnection conn_SUCCESS;
      CEventConnection conn_FAILURE;

      CDataConnection *conn_Module;
      CDataConnection *conn_UaRoot;
      CDataConnection *conn_UaPath;
      CDataConnection *conn_UaEnable;
      CDataConnection *conn_Methods;
      CDataConnection *conn_Holder;
      CDataConnection *conn_ReleaseAll;
      CDataConnection *conn_Session;
      CDataConnection *conn_ParamsInRange;
      CDataConnection *conn_EquipmentFree;
      CDataConnection *conn_ExecuteError;

      COutDataConnection<CIEC_WSTRING> conn_StartMethodId;
      COutDataConnection<CIEC_BOOL> conn_Accepted;
      COutDataConnection<CIEC_UINT> conn_StartError;
      COutDataConnection<CIEC_BOOL> conn_CalledByClient;
      COutDataConnection<CIEC_USINT> conn_State;
      COutDataConnection<CIEC_UINT> conn_ErrorID;

      COutDataConnection<CIEC_WSTRING> conn_if2in_Module;
      COutDataConnection<CIEC_WSTRING> conn_if2in_UaRoot;
      COutDataConnection<CIEC_WSTRING> conn_if2in_UaPath;
      COutDataConnection<CIEC_BOOL> conn_if2in_UaEnable;
      COutDataConnection<CIEC_BOOL> conn_if2in_Methods;
      COutDataConnection<CIEC_WSTRING> conn_if2in_Holder;
      COutDataConnection<CIEC_BOOL> conn_if2in_ReleaseAll;
      COutDataConnection<CIEC_WSTRING> conn_if2in_Session;
      COutDataConnection<CIEC_BOOL> conn_if2in_ParamsInRange;
      COutDataConnection<CIEC_BOOL> conn_if2in_EquipmentFree;
      COutDataConnection<CIEC_UINT> conn_if2in_ExecuteError;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;
      CDataConnection *getIf2InConUnchecked(TPortId) override;
  };
}

