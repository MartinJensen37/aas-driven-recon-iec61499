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

#include "forte/modlib/SKILL_NoEquipment_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/modlib/AEquipment_adp.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:zHFskm0HD4Bzk5COngNOqKNcQssymTEDwz9burYZ_ahIBELfa02aEeOh7NY77pQCzkj2kwuffPHYTkWWc5fiNQ=="sv;

    const auto cSocketNameIds = std::array{"Skill"_STRID};
    const SFBInterfaceSpec cFBInterfaceSpec = {
        .mEINames = {},
        .mEITypeNames = {},
        .mEONames = {},
        .mEOTypeNames = {},
        .mDINames = {},
        .mDONames = {},
        .mDIONames = {},
        .mSocketNames = cSocketNameIds,
        .mPlugNames = {},
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_SKILL_NoEquipment, "modlib::SKILL_NoEquipment"_STRID, TypeHash)

  FORTE_SKILL_NoEquipment::FORTE_SKILL_NoEquipment(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CBasicFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_Skill("Skill"_STRID, *this, 0) {
  }

  void FORTE_SKILL_NoEquipment::setInitialValues() {
    CBasicFB::setInitialValues();
  }

  void FORTE_SKILL_NoEquipment::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
    do {
      switch(mECCState) {
        case scmStateWait:
          if(var_Skill->evt_SEND() == paEIID) enterStatePlayed(paECET);
          else return; //no transition cleared
          break;
        case scmStatePlayed:
          if(1) enterStateWait(paECET);
          else return; //no transition cleared
          break;
        default:
          DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 2.", mECCState.operator TForteUInt16 ());
          mECCState = 0; // 0 is always the initial state
          return;
      }
      paEIID = cgInvalidEventID; // we have to clear the event after the first check in order to ensure correct behavior
    } while(true);
  }

  void FORTE_SKILL_NoEquipment::enterStateWait(CEventChainExecutionThread *const) {
    mECCState = scmStateWait;
  }

  void FORTE_SKILL_NoEquipment::enterStatePlayed(CEventChainExecutionThread *const paECET) {
    mECCState = scmStatePlayed;
    sendAdapterEvent(*var_Skill, forte::modlib::FORTE_AEquipment::scmEventPLAYEDID, paECET);
  }

  void FORTE_SKILL_NoEquipment::readInputData(TEventID) {
    // nothing to do
  }

  void FORTE_SKILL_NoEquipment::writeOutputData(TEventID) {
    // nothing to do
  }

  CIEC_ANY *FORTE_SKILL_NoEquipment::getDI(size_t) {
    return nullptr;
  }

  CIEC_ANY *FORTE_SKILL_NoEquipment::getDO(size_t) {
    return nullptr;
  }

  forte::ISocketPin *FORTE_SKILL_NoEquipment::getSocketPinUnchecked(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Skill;
    }
    return nullptr;
  }

  CEventConnection *FORTE_SKILL_NoEquipment::getEOConUnchecked(TPortId) {
    return nullptr;
  }

  CDataConnection **FORTE_SKILL_NoEquipment::getDIConUnchecked(TPortId) {
    return nullptr;
  }

  CDataConnection *FORTE_SKILL_NoEquipment::getDOConUnchecked(TPortId) {
    return nullptr;
  }

  CIEC_ANY *FORTE_SKILL_NoEquipment::getVarInternal(size_t) {
    return nullptr;
  }

}