/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: EV_LinearAxis
 *** Description: Names the equipment's two channels, and unpacks its state channel into named values (its inputs and who holds it) for a skill. Technical: Names LinearAxis's channels; typed view of its state channel (inputs and holder)
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/filling/EV_LinearAxis_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"
#include "forte/iec61131_functions/func_CONCAT.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::filling {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:VzU8sOWVXa0FrIRALH6S3705opn0fGa01Jg388VY0muWStJPSoruKMloMYSSgeYEaxEm-ZJNUJToYV9kDMCCRg=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "REQ"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "CNF"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"Module"_STRID, "I_AtHome"_STRID, "I_ActualPosition"_STRID, "I_Homed"_STRID, "I_Moving"_STRID, "I_Holder"_STRID};
    const auto cDataOutputNames = std::array{"AtHome"_STRID, "ActualPosition"_STRID, "Homed"_STRID, "Moving"_STRID, "Holder"_STRID, "IdState"_STRID, "IdCmd"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_EV_LinearAxis, "filling::EV_LinearAxis"_STRID, TypeHash)

  FORTE_EV_LinearAxis::FORTE_EV_LinearAxis(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CSimpleFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_Module(u""_WSTRING),
      var_I_AtHome(0_BOOL),
      var_I_ActualPosition(0_LREAL),
      var_I_Homed(0_BOOL),
      var_I_Moving(0_BOOL),
      var_I_Holder(u""_WSTRING),
      var_AtHome(0_BOOL),
      var_ActualPosition(0_LREAL),
      var_Homed(0_BOOL),
      var_Moving(0_BOOL),
      var_Holder(u""_WSTRING),
      var_IdState(u""_WSTRING),
      var_IdCmd(u""_WSTRING),
      conn_INITO(*this, 0),
      conn_CNF(*this, 1),
      conn_Module(nullptr),
      conn_I_AtHome(nullptr),
      conn_I_ActualPosition(nullptr),
      conn_I_Homed(nullptr),
      conn_I_Moving(nullptr),
      conn_I_Holder(nullptr),
      conn_AtHome(*this, 0, var_AtHome),
      conn_ActualPosition(*this, 1, var_ActualPosition),
      conn_Homed(*this, 2, var_Homed),
      conn_Moving(*this, 3, var_Moving),
      conn_Holder(*this, 4, var_Holder),
      conn_IdState(*this, 5, var_IdState),
      conn_IdCmd(*this, 6, var_IdCmd) {
  }

  void FORTE_EV_LinearAxis::setInitialValues() {
    CSimpleFB::setInitialValues();
    var_Module = u""_WSTRING;
    var_I_AtHome = 0_BOOL;
    var_I_ActualPosition = 0_LREAL;
    var_I_Homed = 0_BOOL;
    var_I_Moving = 0_BOOL;
    var_I_Holder = u""_WSTRING;
    var_AtHome = 0_BOOL;
    var_ActualPosition = 0_LREAL;
    var_Homed = 0_BOOL;
    var_Moving = 0_BOOL;
    var_Holder = u""_WSTRING;
    var_IdState = u""_WSTRING;
    var_IdCmd = u""_WSTRING;
  }

  void FORTE_EV_LinearAxis::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
    switch(paEIID) {
      case scmEventINITID:
        enterStateINIT(paECET);
        break;
      case scmEventREQID:
        enterStateREQ(paECET);
        break;
      default:
        break;
    }
  }

  void FORTE_EV_LinearAxis::enterStateINIT(CEventChainExecutionThread *const paECET) {
    alg_INIT();
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_EV_LinearAxis::enterStateREQ(CEventChainExecutionThread *const paECET) {
    alg_REQ();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_EV_LinearAxis::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, var_Module, conn_Module);
        break;
      }
      case scmEventREQID: {
        readData(1, var_I_AtHome, conn_I_AtHome);
        readData(2, var_I_ActualPosition, conn_I_ActualPosition);
        readData(3, var_I_Homed, conn_I_Homed);
        readData(4, var_I_Moving, conn_I_Moving);
        readData(5, var_I_Holder, conn_I_Holder);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_EV_LinearAxis::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(11, var_IdState, conn_IdState);
        writeData(12, var_IdCmd, conn_IdCmd);
        break;
      }
      case scmEventCNFID: {
        writeData(6, var_AtHome, conn_AtHome);
        writeData(7, var_ActualPosition, conn_ActualPosition);
        writeData(8, var_Homed, conn_Homed);
        writeData(9, var_Moving, conn_Moving);
        writeData(10, var_Holder, conn_Holder);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_EV_LinearAxis::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Module;
      case 1: return &var_I_AtHome;
      case 2: return &var_I_ActualPosition;
      case 3: return &var_I_Homed;
      case 4: return &var_I_Moving;
      case 5: return &var_I_Holder;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_EV_LinearAxis::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_AtHome;
      case 1: return &var_ActualPosition;
      case 2: return &var_Homed;
      case 3: return &var_Moving;
      case 4: return &var_Holder;
      case 5: return &var_IdState;
      case 6: return &var_IdCmd;
    }
    return nullptr;
  }

  CEventConnection *FORTE_EV_LinearAxis::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_CNF;
    }
    return nullptr;
  }

  CDataConnection **FORTE_EV_LinearAxis::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Module;
      case 1: return &conn_I_AtHome;
      case 2: return &conn_I_ActualPosition;
      case 3: return &conn_I_Homed;
      case 4: return &conn_I_Moving;
      case 5: return &conn_I_Holder;
    }
    return nullptr;
  }

  CDataConnection *FORTE_EV_LinearAxis::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_AtHome;
      case 1: return &conn_ActualPosition;
      case 2: return &conn_Homed;
      case 3: return &conn_Moving;
      case 4: return &conn_Holder;
      case 5: return &conn_IdState;
      case 6: return &conn_IdCmd;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_EV_LinearAxis::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_EV_LinearAxis::alg_INIT(void) {

    #line 2 "EV_LinearAxis.fbt"
    var_IdState = func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/LinearAxis/state]"_WSTRING);
    #line 3 "EV_LinearAxis.fbt"
    var_IdCmd = func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/LinearAxis/cmd]"_WSTRING);
  }

  void FORTE_EV_LinearAxis::alg_REQ(void) {

    #line 7 "EV_LinearAxis.fbt"
    var_AtHome = var_I_AtHome;
    #line 8 "EV_LinearAxis.fbt"
    var_ActualPosition = var_I_ActualPosition;
    #line 9 "EV_LinearAxis.fbt"
    var_Homed = var_I_Homed;
    #line 10 "EV_LinearAxis.fbt"
    var_Moving = var_I_Moving;
    #line 11 "EV_LinearAxis.fbt"
    var_Holder = var_I_Holder;
  }

}