/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SKILL_NoEquipment
 *** Description: Stands in for the equipment of a primitive that has none (one that only waits): plays every command at once. Technical: Stands in for the equipment of a primitive that has none: answers every SEND with PLAYED at once
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/basicfb.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/modlib/AEquipment_adp.h"

namespace forte::modlib {
  class FORTE_SKILL_NoEquipment final : public CBasicFB {
      DECLARE_FIRMWARE_FB(FORTE_SKILL_NoEquipment)

    private:

      CIEC_ANY *getVarInternal(size_t) override;

      static const TForteInt16 scmStateWait = 0;
      static const TForteInt16 scmStatePlayed = 1;

      void enterStateWait(CEventChainExecutionThread *const paECET);
      void enterStatePlayed(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_SKILL_NoEquipment(StringId paInstanceNameId, CFBContainer &paContainer);

      forte::CSocketPin<forte::modlib::FORTE_AEquipment_Socket> var_Skill;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      forte::ISocketPin *getSocketPinUnchecked(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;
  };
}

