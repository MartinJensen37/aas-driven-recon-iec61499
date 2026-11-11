/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SKILL_FailMerge
 *** Description: Joins two failure events (with their error codes) into one, because a data input can only be wired once. Technical: Merges two failure events with their error codes into one
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/SKILL_FailMerge_fbt.h"

#include "forte/datatypes/forte_uint.h"
#include "forte/forte_st_util.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:HAOanwTuHv7XqkcRRGrtM_pkhASlS6peJEf2SMCXgNpi3IChEi3pfpaV8_JgB9FWwHWbDlKS1SBYj2RZSnMjzg=="sv;

    const auto cEventInputNames = std::array{"FAIL_1"_STRID, "FAIL_2"_STRID};
    const auto cEventOutputNames = std::array{"FAIL"_STRID};
    const auto cDataInputNames = std::array{"Error1"_STRID, "Error2"_STRID};
    const auto cDataOutputNames = std::array{"Error"_STRID};
    const SFBInterfaceSpec cFBInterfaceSpec = {
        .mEINames = cEventInputNames,
        .mEITypeNames = {},
        .mEONames = cEventOutputNames,
        .mEOTypeNames = {},
        .mDINames = cDataInputNames,
        .mDONames = cDataOutputNames,
        .mDIONames = {},
        .mSocketNames = {},
        .mPlugNames = {},
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_SKILL_FailMerge, "modlib::SKILL_FailMerge"_STRID, TypeHash)

  FORTE_SKILL_FailMerge::FORTE_SKILL_FailMerge(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CSimpleFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_Error1(0_UINT),
      var_Error2(0_UINT),
      var_Error(0_UINT),
      conn_FAIL(*this, 0),
      conn_Error1(nullptr),
      conn_Error2(nullptr),
      conn_Error(*this, 0, var_Error) {
  }

  void FORTE_SKILL_FailMerge::setInitialValues() {
    CSimpleFB::setInitialValues();
    var_Error1 = 0_UINT;
    var_Error2 = 0_UINT;
    var_Error = 0_UINT;
  }

  void FORTE_SKILL_FailMerge::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
    switch(paEIID) {
      case scmEventFAIL_1ID:
        enterStateFAIL_1(paECET);
        break;
      case scmEventFAIL_2ID:
        enterStateFAIL_2(paECET);
        break;
      default:
        break;
    }
  }

  void FORTE_SKILL_FailMerge::enterStateFAIL_1(CEventChainExecutionThread *const paECET) {
    alg_FAIL_1();
    sendOutputEvent(scmEventFAILID, paECET);
  }

  void FORTE_SKILL_FailMerge::enterStateFAIL_2(CEventChainExecutionThread *const paECET) {
    alg_FAIL_2();
    sendOutputEvent(scmEventFAILID, paECET);
  }

  void FORTE_SKILL_FailMerge::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventFAIL_1ID: {
        readData(0, var_Error1, conn_Error1);
        break;
      }
      case scmEventFAIL_2ID: {
        readData(1, var_Error2, conn_Error2);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_SKILL_FailMerge::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventFAILID: {
        writeData(2, var_Error, conn_Error);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_SKILL_FailMerge::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Error1;
      case 1: return &var_Error2;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SKILL_FailMerge::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Error;
    }
    return nullptr;
  }

  CEventConnection *FORTE_SKILL_FailMerge::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_FAIL;
    }
    return nullptr;
  }

  CDataConnection **FORTE_SKILL_FailMerge::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Error1;
      case 1: return &conn_Error2;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SKILL_FailMerge::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Error;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SKILL_FailMerge::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_SKILL_FailMerge::alg_FAIL_1(void) {

    #line 2 "SKILL_FailMerge.fbt"
    var_Error = var_Error1;
  }

  void FORTE_SKILL_FailMerge::alg_FAIL_2(void) {

    #line 6 "SKILL_FailMerge.fbt"
    var_Error = var_Error2;
  }

}