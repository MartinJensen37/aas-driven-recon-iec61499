/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SKILL_Param_UINT
 *** Description: One parameter of a skill: keeps its default, checks a value a client sends with Start against the limits, and holds the value for the run. Technical: Skill parameter (UINT): default, range check of a Start argument, latching for one run
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/SKILL_Param_UINT_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/forte_st_util.h"
#include "forte/iec61131_functions/func_AND.h"
#include "forte/iec61131_functions/func_GE.h"
#include "forte/iec61131_functions/func_LE.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:PbmixfsmpBv7r7DEXoWVyJZPM9yQd2-X9oyBQ8LwXUVSw7LTjDKsrBtTfahkYJ1JGmoU5Ba_4BSUci2zmII3Cw=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "CHECK"_STRID, "LATCH"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "CHECKED"_STRID, "LATCHED"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"Default"_STRID, "Lower"_STRID, "Upper"_STRID, "Requested"_STRID, "PreviousInRange"_STRID, "CalledByClient"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_SKILL_Param_UINT, "modlib::SKILL_Param_UINT"_STRID, TypeHash)

  FORTE_SKILL_Param_UINT::FORTE_SKILL_Param_UINT(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CSimpleFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_Default(0_UINT),
      var_Lower(0_UINT),
      var_Upper(65535_UINT),
      var_Requested(0_UINT),
      var_PreviousInRange(true_BOOL),
      var_CalledByClient(0_BOOL),
      var_Value(0_UINT),
      var_AllInRange(0_BOOL),
      conn_INITO(*this, 0),
      conn_CHECKED(*this, 1),
      conn_LATCHED(*this, 2),
      conn_Default(nullptr),
      conn_Lower(nullptr),
      conn_Upper(nullptr),
      conn_Requested(nullptr),
      conn_PreviousInRange(nullptr),
      conn_CalledByClient(nullptr),
      conn_Value(*this, 0, var_Value),
      conn_AllInRange(*this, 1, var_AllInRange) {
  }

  void FORTE_SKILL_Param_UINT::setInitialValues() {
    CSimpleFB::setInitialValues();
    var_Default = 0_UINT;
    var_Lower = 0_UINT;
    var_Upper = 65535_UINT;
    var_Requested = 0_UINT;
    var_PreviousInRange = true_BOOL;
    var_CalledByClient = 0_BOOL;
    var_Value = 0_UINT;
    var_AllInRange = 0_BOOL;
  }

  void FORTE_SKILL_Param_UINT::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
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

  void FORTE_SKILL_Param_UINT::enterStateINIT(CEventChainExecutionThread *const paECET) {
    alg_INIT();
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_SKILL_Param_UINT::enterStateCHECK(CEventChainExecutionThread *const paECET) {
    alg_CHECK();
    sendOutputEvent(scmEventCHECKEDID, paECET);
  }

  void FORTE_SKILL_Param_UINT::enterStateLATCH(CEventChainExecutionThread *const paECET) {
    alg_LATCH();
    sendOutputEvent(scmEventLATCHEDID, paECET);
  }

  void FORTE_SKILL_Param_UINT::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, var_Default, conn_Default);
        readData(1, var_Lower, conn_Lower);
        readData(2, var_Upper, conn_Upper);
        break;
      }
      case scmEventCHECKID: {
        readData(3, var_Requested, conn_Requested);
        readData(4, var_PreviousInRange, conn_PreviousInRange);
        break;
      }
      case scmEventLATCHID: {
        readData(5, var_CalledByClient, conn_CalledByClient);
        readData(0, var_Default, conn_Default);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_SKILL_Param_UINT::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(6, var_Value, conn_Value);
        break;
      }
      case scmEventCHECKEDID: {
        writeData(7, var_AllInRange, conn_AllInRange);
        break;
      }
      case scmEventLATCHEDID: {
        writeData(6, var_Value, conn_Value);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_SKILL_Param_UINT::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Default;
      case 1: return &var_Lower;
      case 2: return &var_Upper;
      case 3: return &var_Requested;
      case 4: return &var_PreviousInRange;
      case 5: return &var_CalledByClient;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SKILL_Param_UINT::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Value;
      case 1: return &var_AllInRange;
    }
    return nullptr;
  }

  CEventConnection *FORTE_SKILL_Param_UINT::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_CHECKED;
      case 2: return &conn_LATCHED;
    }
    return nullptr;
  }

  CDataConnection **FORTE_SKILL_Param_UINT::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Default;
      case 1: return &conn_Lower;
      case 2: return &conn_Upper;
      case 3: return &conn_Requested;
      case 4: return &conn_PreviousInRange;
      case 5: return &conn_CalledByClient;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SKILL_Param_UINT::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Value;
      case 1: return &conn_AllInRange;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SKILL_Param_UINT::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_SKILL_Param_UINT::alg_INIT(void) {

    #line 2 "SKILL_Param_UINT.fbt"
    var_Value = var_Default;
  }

  void FORTE_SKILL_Param_UINT::alg_CHECK(void) {

    #line 6 "SKILL_Param_UINT.fbt"
    var_AllInRange = func_AND<CIEC_BOOL>(func_AND<CIEC_BOOL>(var_PreviousInRange, func_GE(var_Requested, var_Lower)), func_LE(var_Requested, var_Upper));
  }

  void FORTE_SKILL_Param_UINT::alg_LATCH(void) {

    #line 10 "SKILL_Param_UINT.fbt"
    if (var_CalledByClient) {
      #line 11 "SKILL_Param_UINT.fbt"
      var_Value = var_Requested;
    }
    else {
      #line 13 "SKILL_Param_UINT.fbt"
      var_Value = var_Default;
    }
  }

}