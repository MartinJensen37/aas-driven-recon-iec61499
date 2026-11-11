/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: MOD_ActivityCount
 *** Description: Counts the skills that are running: every skill says +1 when it starts and -1 when it ends. Technical: Number of running skills from the +1/-1 activity channel
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/MOD_ActivityCount_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_int.h"
#include "forte/forte_st_util.h"
#include "forte/iec61131_functions/func_ADD.h"
#include "forte/iec61131_functions/func_EQ.h"
#include "forte/iec61131_functions/func_LT.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:oopB1bTc13hNznnAgkONAl0wE8sb_lvzyPY1IwtcVf1fnjXbzRCxq5UHBRHuokXqdo3JKt_0wbI191zHrFkTRw=="sv;

    const auto cEventInputNames = std::array{"ACT"_STRID};
    const auto cEventOutputNames = std::array{"CHG"_STRID};
    const auto cDataInputNames = std::array{"Delta"_STRID};
    const auto cDataOutputNames = std::array{"Active"_STRID, "AllIdle"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_MOD_ActivityCount, "modlib::MOD_ActivityCount"_STRID, TypeHash)

  FORTE_MOD_ActivityCount::FORTE_MOD_ActivityCount(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CSimpleFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_Delta(0_INT),
      var_Active(0_INT),
      var_AllIdle(true_BOOL),
      conn_CHG(*this, 0),
      conn_Delta(nullptr),
      conn_Active(*this, 0, var_Active),
      conn_AllIdle(*this, 1, var_AllIdle) {
  }

  void FORTE_MOD_ActivityCount::setInitialValues() {
    CSimpleFB::setInitialValues();
    var_Delta = 0_INT;
    var_Active = 0_INT;
    var_AllIdle = true_BOOL;
  }

  void FORTE_MOD_ActivityCount::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
    switch(paEIID) {
      case scmEventACTID:
        enterStateACT(paECET);
        break;
      default:
        break;
    }
  }

  void FORTE_MOD_ActivityCount::enterStateACT(CEventChainExecutionThread *const paECET) {
    alg_ACT();
    sendOutputEvent(scmEventCHGID, paECET);
  }

  void FORTE_MOD_ActivityCount::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventACTID: {
        readData(0, var_Delta, conn_Delta);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_MOD_ActivityCount::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventCHGID: {
        writeData(1, var_Active, conn_Active);
        writeData(2, var_AllIdle, conn_AllIdle);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_MOD_ActivityCount::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Delta;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_MOD_ActivityCount::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Active;
      case 1: return &var_AllIdle;
    }
    return nullptr;
  }

  CEventConnection *FORTE_MOD_ActivityCount::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_CHG;
    }
    return nullptr;
  }

  CDataConnection **FORTE_MOD_ActivityCount::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Delta;
    }
    return nullptr;
  }

  CDataConnection *FORTE_MOD_ActivityCount::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Active;
      case 1: return &conn_AllIdle;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_MOD_ActivityCount::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_MOD_ActivityCount::alg_ACT(void) {

    #line 2 "MOD_ActivityCount.fbt"
    var_Active = func_ADD<CIEC_INT>(var_Active, var_Delta);
    #line 3 "MOD_ActivityCount.fbt"
    if (func_LT(var_Active, 0_INT)) {
      #line 4 "MOD_ActivityCount.fbt"
      var_Active = 0_INT;
    }
    #line 6 "MOD_ActivityCount.fbt"
    var_AllIdle = func_EQ(var_Active, 0_INT);
  }

}