/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: EV_Pump
 *** Description: Names the equipment's two channels, and unpacks its state channel into named values (its inputs and who holds it) for a skill. Technical: Names Pump's channels; typed view of its state channel (inputs and holder)
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/filling/EV_Pump_fbt.h"

#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"
#include "forte/iec61131_functions/func_CONCAT.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::filling {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:HFtIAtAeO3cjURtjPD25W4LEoS3G3fLtf07nbJz1UpCjhkeLp5iWeoColvk6lBPH6HEPHWxcehpTXxJtbrglCA=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "REQ"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "CNF"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"Module"_STRID, "I_Holder"_STRID};
    const auto cDataOutputNames = std::array{"Holder"_STRID, "IdState"_STRID, "IdCmd"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_EV_Pump, "filling::EV_Pump"_STRID, TypeHash)

  FORTE_EV_Pump::FORTE_EV_Pump(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CSimpleFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_Module(u""_WSTRING),
      var_I_Holder(u""_WSTRING),
      var_Holder(u""_WSTRING),
      var_IdState(u""_WSTRING),
      var_IdCmd(u""_WSTRING),
      conn_INITO(*this, 0),
      conn_CNF(*this, 1),
      conn_Module(nullptr),
      conn_I_Holder(nullptr),
      conn_Holder(*this, 0, var_Holder),
      conn_IdState(*this, 1, var_IdState),
      conn_IdCmd(*this, 2, var_IdCmd) {
  }

  void FORTE_EV_Pump::setInitialValues() {
    CSimpleFB::setInitialValues();
    var_Module = u""_WSTRING;
    var_I_Holder = u""_WSTRING;
    var_Holder = u""_WSTRING;
    var_IdState = u""_WSTRING;
    var_IdCmd = u""_WSTRING;
  }

  void FORTE_EV_Pump::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
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

  void FORTE_EV_Pump::enterStateINIT(CEventChainExecutionThread *const paECET) {
    alg_INIT();
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_EV_Pump::enterStateREQ(CEventChainExecutionThread *const paECET) {
    alg_REQ();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_EV_Pump::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, var_Module, conn_Module);
        break;
      }
      case scmEventREQID: {
        readData(1, var_I_Holder, conn_I_Holder);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_EV_Pump::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(3, var_IdState, conn_IdState);
        writeData(4, var_IdCmd, conn_IdCmd);
        break;
      }
      case scmEventCNFID: {
        writeData(2, var_Holder, conn_Holder);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_EV_Pump::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Module;
      case 1: return &var_I_Holder;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_EV_Pump::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Holder;
      case 1: return &var_IdState;
      case 2: return &var_IdCmd;
    }
    return nullptr;
  }

  CEventConnection *FORTE_EV_Pump::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_CNF;
    }
    return nullptr;
  }

  CDataConnection **FORTE_EV_Pump::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Module;
      case 1: return &conn_I_Holder;
    }
    return nullptr;
  }

  CDataConnection *FORTE_EV_Pump::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Holder;
      case 1: return &conn_IdState;
      case 2: return &conn_IdCmd;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_EV_Pump::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_EV_Pump::alg_INIT(void) {

    #line 2 "EV_Pump.fbt"
    var_IdState = func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/Pump/state]"_WSTRING);
    #line 3 "EV_Pump.fbt"
    var_IdCmd = func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/Pump/cmd]"_WSTRING);
  }

  void FORTE_EV_Pump::alg_REQ(void) {

    #line 7 "EV_Pump.fbt"
    var_Holder = var_I_Holder;
  }

}