/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SKILL_Merge
 *** Description: Where the two branches of a decision meet again: either branch's end goes on. Technical: Where the branches of a decision meet: EI1 or EI2 gives EO
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/SKILL_Merge_fbt.h"

#include "forte/datatypes/forte_bool.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:Z8VH-bojBQVdBLTOTuM7Z0_yPYNikyyS8d4XOQ0TQp8p564xDEyjGsRTjmC7QcoHGzl6W-ZXW_IJKolKT8cUHQ=="sv;

    const auto cEventInputNames = std::array{"EI1"_STRID, "EI2"_STRID};
    const auto cEventOutputNames = std::array{"EO"_STRID};
    const SFBInterfaceSpec cFBInterfaceSpec = {
        .mEINames = cEventInputNames,
        .mEITypeNames = {},
        .mEONames = cEventOutputNames,
        .mEOTypeNames = {},
        .mDINames = {},
        .mDONames = {},
        .mDIONames = {},
        .mSocketNames = {},
        .mPlugNames = {},
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_SKILL_Merge, "modlib::SKILL_Merge"_STRID, TypeHash)

  FORTE_SKILL_Merge::FORTE_SKILL_Merge(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CBasicFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      conn_EO(*this, 0) {
  }

  void FORTE_SKILL_Merge::setInitialValues() {
    CBasicFB::setInitialValues();
  }

  void FORTE_SKILL_Merge::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
    do {
      switch(mECCState) {
        case scmStateSTART:
          if(scmEventEI1ID == paEIID) enterStateOne(paECET);
          else
          if(scmEventEI2ID == paEIID) enterStateTwo(paECET);
          else return; //no transition cleared
          break;
        case scmStateOne:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStateTwo:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        default:
          DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 3.", mECCState.operator TForteUInt16 ());
          mECCState = 0; // 0 is always the initial state
          return;
      }
      paEIID = cgInvalidEventID; // we have to clear the event after the first check in order to ensure correct behavior
    } while(true);
  }

  void FORTE_SKILL_Merge::enterStateSTART(CEventChainExecutionThread *const) {
    mECCState = scmStateSTART;
  }

  void FORTE_SKILL_Merge::enterStateOne(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateOne;
    sendOutputEvent(scmEventEOID, paECET);
  }

  void FORTE_SKILL_Merge::enterStateTwo(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateTwo;
    sendOutputEvent(scmEventEOID, paECET);
  }

  void FORTE_SKILL_Merge::readInputData(TEventID) {
    // nothing to do
  }

  void FORTE_SKILL_Merge::writeOutputData(TEventID) {
    // nothing to do
  }

  CIEC_ANY *FORTE_SKILL_Merge::getDI(size_t) {
    return nullptr;
  }

  CIEC_ANY *FORTE_SKILL_Merge::getDO(size_t) {
    return nullptr;
  }

  CEventConnection *FORTE_SKILL_Merge::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_EO;
    }
    return nullptr;
  }

  CDataConnection **FORTE_SKILL_Merge::getDIConUnchecked(TPortId) {
    return nullptr;
  }

  CDataConnection *FORTE_SKILL_Merge::getDOConUnchecked(TPortId) {
    return nullptr;
  }

  CIEC_ANY *FORTE_SKILL_Merge::getVarInternal(size_t) {
    return nullptr;
  }

}