/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SKILL_Param_BOOL
 *** Description: One parameter of a skill: keeps its default, checks a value a client sends with Start against the limits, and holds the value for the run. Technical: Skill parameter (BOOL): default, range check of a Start argument, latching for one run
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/SKILL_Param_BOOL_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/forte_st_util.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:B5ppnuxNHRQN7y7Y8xvtcrmBBkZqCMpPUcBFwScMIQIbauoB_4eTW_Q4eI9mcwjqHUHSOeFiTebpS3EQaoX5zw=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "CHECK"_STRID, "LATCH"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "CHECKED"_STRID, "LATCHED"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"Default"_STRID, "Requested"_STRID, "PreviousInRange"_STRID, "CalledByClient"_STRID};
    const auto cDataOutputNames = std::array{"Value"_STRID, "AllInRange"_STRID};
    const SFBInterfaceSpec cFBInterfaceSpec = {
        .mEINames = cEventInputNames,
        .mEITypeNames = cEventInputTypeIds,
        .mEONames = cEventOutputNames,
        .mEOTypeNames = cEventOutputTypeIds,
        .mDINames = cDataInputNames,
        .mDONames = cDataOutputNames,
        .mDIONames = {},
        .mSocketNames = {},
        .mPlugNames = {},
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_SKILL_Param_BOOL, "modlib::SKILL_Param_BOOL"_STRID, TypeHash)

  FORTE_SKILL_Param_BOOL::FORTE_SKILL_Param_BOOL(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CSimpleFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_Default(0_BOOL),
      var_Requested(0_BOOL),
      var_PreviousInRange(true_BOOL),
      var_CalledByClient(0_BOOL),
      var_Value(0_BOOL),
      var_AllInRange(0_BOOL),
      conn_INITO(*this, 0),
      conn_CHECKED(*this, 1),
      conn_LATCHED(*this, 2),
      conn_Default(nullptr),
      conn_Requested(nullptr),
      conn_PreviousInRange(nullptr),
      conn_CalledByClient(nullptr),
      conn_Value(*this, 0, var_Value),
      conn_AllInRange(*this, 1, var_AllInRange) {
  }

  void FORTE_SKILL_Param_BOOL::setInitialValues() {
    CSimpleFB::setInitialValues();
    var_Default = 0_BOOL;
    var_Requested = 0_BOOL;
    var_PreviousInRange = true_BOOL;
    var_CalledByClient = 0_BOOL;
    var_Value = 0_BOOL;
    var_AllInRange = 0_BOOL;
  }

  void FORTE_SKILL_Param_BOOL::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
    switch(paEIID) {
      case scmEventINITID:
        enterStateINIT(paECET);
        break;
      case scmEventCHECKID:
        enterStateCHECK(paECET);
        break;
      case scmEventLATCHID:
        enterStateLATCH(paECET);
        break;
      default:
        break;
    }
  }

  void FORTE_SKILL_Param_BOOL::enterStateINIT(CEventChainExecutionThread *const paECET) {
    alg_INIT();
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_SKILL_Param_BOOL::enterStateCHECK(CEventChainExecutionThread *const paECET) {
    alg_CHECK();
    sendOutputEvent(scmEventCHECKEDID, paECET);
  }

  void FORTE_SKILL_Param_BOOL::enterStateLATCH(CEventChainExecutionThread *const paECET) {
    alg_LATCH();
    sendOutputEvent(scmEventLATCHEDID, paECET);
  }

  void FORTE_SKILL_Param_BOOL::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, var_Default, conn_Default);
        break;
      }
      case scmEventCHECKID: {
        readData(1, var_Requested, conn_Requested);
        readData(2, var_PreviousInRange, conn_PreviousInRange);
        break;
      }
      case scmEventLATCHID: {
        readData(3, var_CalledByClient, conn_CalledByClient);
        readData(0, var_Default, conn_Default);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_SKILL_Param_BOOL::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(4, var_Value, conn_Value);
        break;
      }
      case scmEventCHECKEDID: {
        writeData(5, var_AllInRange, conn_AllInRange);
        break;
      }
      case scmEventLATCHEDID: {
        writeData(4, var_Value, conn_Value);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_SKILL_Param_BOOL::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Default;
      case 1: return &var_Requested;
      case 2: return &var_PreviousInRange;
      case 3: return &var_CalledByClient;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SKILL_Param_BOOL::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Value;
      case 1: return &var_AllInRange;
    }
    return nullptr;
  }

  CEventConnection *FORTE_SKILL_Param_BOOL::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_CHECKED;
      case 2: return &conn_LATCHED;
    }
    return nullptr;
  }

  CDataConnection **FORTE_SKILL_Param_BOOL::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Default;
      case 1: return &conn_Requested;
      case 2: return &conn_PreviousInRange;
      case 3: return &conn_CalledByClient;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SKILL_Param_BOOL::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Value;
      case 1: return &conn_AllInRange;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SKILL_Param_BOOL::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_SKILL_Param_BOOL::alg_INIT(void) {

    #line 2 "SKILL_Param_BOOL.fbt"
    var_Value = var_Default;
  }

  void FORTE_SKILL_Param_BOOL::alg_CHECK(void) {

    #line 6 "SKILL_Param_BOOL.fbt"
    var_AllInRange = var_PreviousInRange;
  }

  void FORTE_SKILL_Param_BOOL::alg_LATCH(void) {

    #line 10 "SKILL_Param_BOOL.fbt"
    if (var_CalledByClient) {
      #line 11 "SKILL_Param_BOOL.fbt"
      var_Value = var_Requested;
    }
    else {
      #line 13 "SKILL_Param_BOOL.fbt"
      var_Value = var_Default;
    }
  }

}