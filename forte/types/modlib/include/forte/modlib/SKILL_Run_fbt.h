/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SKILL_Run
 *** Description: One run of a skill primitive, the same for every primitive: waits until the equipment is free, checks the precondition, sends the command, then watches the conditions (or a timer) until the skill is done, has failed or has timed out, and sends the closing command. What the skill is comes in from its contract (SC_). Technical: One run of a skill primitive, the same for every primitive: what the skill is comes in from its contract (socket Contract, AContract); the command goes out to the equipment (plug Equipment, AEquipment)
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/cfb.h"
#include "forte/typelib.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"
#include "forte/iec61499/events/E_DELAY_fbt.h"
#include "forte/modlib/AContract_adp.h"
#include "forte/modlib/AEquipment_adp.h"
#include "forte/modlib/SKILL_RunLogic_fbt.h"

namespace forte::modlib {
  class FORTE_SKILL_Run final : public CCompositeFB {
      DECLARE_FIRMWARE_FB(FORTE_SKILL_Run)

    private:
      static const TEventID scmEventINITOID = 0;
      static const TEventID scmEventDONEID = 1;
      static const TEventID scmEventFAILEDID = 2;
      static const TEventID scmEventHALTEDID = 3;
      static const TEventID scmEventEQ_FREEID = 4;
      static const TEventID scmEventINITID = 0;
      static const TEventID scmEventHALTID = 1;
      static const TEventID scmEventABORTID = 2;

      CInternalFB<forte::modlib::FORTE_SKILL_RunLogic> fb_Logic;
      CInternalFB<forte::iec61499::events::FORTE_E_DELAY> fb_Timer;
      CInternalFB<forte::iec61499::events::FORTE_E_DELAY> fb_WaitT;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;
      void setFBNetworkInitialValues() override;

    public:
      FORTE_SKILL_Run(StringId paInstanceNameId, CFBContainer &paContainer);

      forte::CSocketPin<forte::modlib::FORTE_AContract_Socket> var_Contract;

      forte::CPlugPin<forte::modlib::FORTE_AEquipment_Plug> var_Equipment;

      CEventConnection conn_INITO;
      CEventConnection conn_DONE;
      CEventConnection conn_FAILED;
      CEventConnection conn_HALTED;
      CEventConnection conn_EQ_FREE;

      CDataConnection *conn_Holder;
      CDataConnection *conn_ReleaseAfter;

      COutDataConnection<CIEC_UINT> conn_ErrorID;
      COutDataConnection<CIEC_BOOL> conn_EquipmentFree;

      COutDataConnection<CIEC_WSTRING> conn_if2in_Holder;
      COutDataConnection<CIEC_BOOL> conn_if2in_ReleaseAfter;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      forte::ISocketPin *getSocketPinUnchecked(size_t) override;
      forte::IPlugPin *getPlugPinUnchecked(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;
      CDataConnection *getIf2InConUnchecked(TPortId) override;
  };
}

