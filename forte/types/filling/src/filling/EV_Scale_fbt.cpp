/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: EV_Scale
 *** Description: Names the equipment's two channels, and unpacks its state channel into named values (its inputs and who holds it) for a skill. Technical: Names Scale's channels; typed view of its state channel (inputs and holder)
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/filling/EV_Scale_fbt.h"

#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"
#include "forte/iec61131_functions/func_CONCAT.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::filling {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:nMVQHqHXzSgcNeF3NlN-hCMinp9FJTbOJ_s1sNfnxzwRgMVuEcLtBXvSQy26ysvWuzS_XbYaQRCmJ5qjOeICHw=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "REQ"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "CNF"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"Module"_STRID, "I_Weight"_STRID, "I_Holder"_STRID};
    const auto cDataOutputNames = std::array{"Weight"_STRID, "Holder"_STRID, "IdState"_STRID, "IdCmd"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_EV_Scale, "filling::EV_Scale"_STRID, TypeHash)

  FORTE_EV_Scale::FORTE_EV_Scale(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CSimpleFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_Module(u""_WSTRING),
      var_I_Weight(0_LREAL),
      var_I_Holder(u""_WSTRING),
      var_Weight(0_LREAL),
      var_Holder(u""_WSTRING),
      var_IdState(u""_WSTRING),
      var_IdCmd(u""_WSTRING),
      conn_INITO(*this, 0),
      conn_CNF(*this, 1),
      conn_Module(nullptr),
      conn_I_Weight(nullptr),
      conn_I_Holder(nullptr),
      conn_Weight(*this, 0, var_Weight),
      conn_Holder(*this, 1, var_Holder),
      conn_IdState(*this, 2, var_IdState),
      conn_IdCmd(*this, 3, var_IdCmd) {
  }

  void FORTE_EV_Scale::setInitialValues() {
    CSimpleFB::setInitialValues();
    var_Module = u""_WSTRING;
    var_I_Weight = 0_LREAL;
    var_I_Holder = u""_WSTRING;
    var_Weight = 0_LREAL;
    var_Holder = u""_WSTRING;
    var_IdState = u""_WSTRING;
    var_IdCmd = u""_WSTRING;
  }

  void FORTE_EV_Scale::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
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

  void FORTE_EV_Scale::enterStateINIT(CEventChainExecutionThread *const paECET) {
    alg_INIT();
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_EV_Scale::enterStateREQ(CEventChainExecutionThread *const paECET) {
    alg_REQ();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_EV_Scale::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, var_Module, conn_Module);
        break;
      }
      case scmEventREQID: {
        readData(1, var_I_Weight, conn_I_Weight);
        readData(2, var_I_Holder, conn_I_Holder);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_EV_Scale::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(5, var_IdState, conn_IdState);
        writeData(6, var_IdCmd, conn_IdCmd);
        break;
      }
      case scmEventCNFID: {
        writeData(3, var_Weight, conn_Weight);
        writeData(4, var_Holder, conn_Holder);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_EV_Scale::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Module;
      case 1: return &var_I_Weight;
      case 2: return &var_I_Holder;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_EV_Scale::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Weight;
      case 1: return &var_Holder;
      case 2: return &var_IdState;
      case 3: return &var_IdCmd;
    }
    return nullptr;
  }

  CEventConnection *FORTE_EV_Scale::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_CNF;
    }
    return nullptr;
  }

  CDataConnection **FORTE_EV_Scale::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Module;
      case 1: return &conn_I_Weight;
      case 2: return &conn_I_Holder;
    }
    return nullptr;
  }

  CDataConnection *FORTE_EV_Scale::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Weight;
      case 1: return &conn_Holder;
      case 2: return &conn_IdState;
      case 3: return &conn_IdCmd;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_EV_Scale::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_EV_Scale::alg_INIT(void) {

    #line 2 "EV_Scale.fbt"
    var_IdState = func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/Scale/state]"_WSTRING);
    #line 3 "EV_Scale.fbt"
    var_IdCmd = func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/Scale/cmd]"_WSTRING);
  }

  void FORTE_EV_Scale::alg_REQ(void) {

    #line 7 "EV_Scale.fbt"
    var_Weight = var_I_Weight;
    #line 8 "EV_Scale.fbt"
    var_Holder = var_I_Holder;
  }

}