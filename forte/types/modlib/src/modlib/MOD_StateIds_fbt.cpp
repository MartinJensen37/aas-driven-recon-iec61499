/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: MOD_StateIds
 *** Description: Builds the OPC UA addresses (Module/Reset ... Module/State) and the local channel names of the state manager. Technical: OPC UA and local channel IDs of the module state manager
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/MOD_StateIds_fbt.h"

#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"
#include "forte/iec61131_functions/func_CONCAT.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:NEp5sDrvnOulvdUeJyejReUPvUQZHkFT61eiUoafF6iBiaM3zg6qi8j4joehiinUAqwh-kDdUOm3kFa1437Hcw=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID};
    const auto cDataInputNames = std::array{"Module"_STRID, "UaRoot"_STRID};
    const auto cDataOutputNames = std::array{"IdReset"_STRID, "IdStart"_STRID, "IdStop"_STRID, "IdAbort"_STRID, "IdClear"_STRID, "IdPub"_STRID, "IdState"_STRID, "IdQuery"_STRID, "IdAct"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_MOD_StateIds, "modlib::MOD_StateIds"_STRID, TypeHash)

  FORTE_MOD_StateIds::FORTE_MOD_StateIds(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CSimpleFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_Module(u""_WSTRING),
      var_UaRoot(u""_WSTRING),
      var_IdReset(u""_WSTRING),
      var_IdStart(u""_WSTRING),
      var_IdStop(u""_WSTRING),
      var_IdAbort(u""_WSTRING),
      var_IdClear(u""_WSTRING),
      var_IdPub(u""_WSTRING),
      var_IdState(u""_WSTRING),
      var_IdQuery(u""_WSTRING),
      var_IdAct(u""_WSTRING),
      conn_INITO(*this, 0),
      conn_Module(nullptr),
      conn_UaRoot(nullptr),
      conn_IdReset(*this, 0, var_IdReset),
      conn_IdStart(*this, 1, var_IdStart),
      conn_IdStop(*this, 2, var_IdStop),
      conn_IdAbort(*this, 3, var_IdAbort),
      conn_IdClear(*this, 4, var_IdClear),
      conn_IdPub(*this, 5, var_IdPub),
      conn_IdState(*this, 6, var_IdState),
      conn_IdQuery(*this, 7, var_IdQuery),
      conn_IdAct(*this, 8, var_IdAct) {
  }

  void FORTE_MOD_StateIds::setInitialValues() {
    CSimpleFB::setInitialValues();
    var_Module = u""_WSTRING;
    var_UaRoot = u""_WSTRING;
    var_IdReset = u""_WSTRING;
    var_IdStart = u""_WSTRING;
    var_IdStop = u""_WSTRING;
    var_IdAbort = u""_WSTRING;
    var_IdClear = u""_WSTRING;
    var_IdPub = u""_WSTRING;
    var_IdState = u""_WSTRING;
    var_IdQuery = u""_WSTRING;
    var_IdAct = u""_WSTRING;
  }

  void FORTE_MOD_StateIds::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
    switch(paEIID) {
      case scmEventINITID:
        enterStateINIT(paECET);
        break;
      default:
        break;
    }
  }

  void FORTE_MOD_StateIds::enterStateINIT(CEventChainExecutionThread *const paECET) {
    alg_INIT();
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_MOD_StateIds::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, var_Module, conn_Module);
        readData(1, var_UaRoot, conn_UaRoot);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_MOD_StateIds::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(2, var_IdReset, conn_IdReset);
        writeData(3, var_IdStart, conn_IdStart);
        writeData(4, var_IdStop, conn_IdStop);
        writeData(5, var_IdAbort, conn_IdAbort);
        writeData(6, var_IdClear, conn_IdClear);
        writeData(7, var_IdPub, conn_IdPub);
        writeData(8, var_IdState, conn_IdState);
        writeData(9, var_IdQuery, conn_IdQuery);
        writeData(10, var_IdAct, conn_IdAct);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_MOD_StateIds::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Module;
      case 1: return &var_UaRoot;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_MOD_StateIds::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_IdReset;
      case 1: return &var_IdStart;
      case 2: return &var_IdStop;
      case 3: return &var_IdAbort;
      case 4: return &var_IdClear;
      case 5: return &var_IdPub;
      case 6: return &var_IdState;
      case 7: return &var_IdQuery;
      case 8: return &var_IdAct;
    }
    return nullptr;
  }

  CEventConnection *FORTE_MOD_StateIds::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
    }
    return nullptr;
  }

  CDataConnection **FORTE_MOD_StateIds::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Module;
      case 1: return &conn_UaRoot;
    }
    return nullptr;
  }

  CDataConnection *FORTE_MOD_StateIds::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_IdReset;
      case 1: return &conn_IdStart;
      case 2: return &conn_IdStop;
      case 3: return &conn_IdAbort;
      case 4: return &conn_IdClear;
      case 5: return &conn_IdPub;
      case 6: return &conn_IdState;
      case 7: return &conn_IdQuery;
      case 8: return &conn_IdAct;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_MOD_StateIds::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_MOD_StateIds::alg_INIT(void) {

    #line 2 "MOD_StateIds.fbt"
    var_IdReset = func_CONCAT(func_CONCAT(func_CONCAT(u"opc_ua[CREATE_METHOD;"_WSTRING, func_CONCAT(var_UaRoot, u"/Module/"_WSTRING)), u"Reset"_WSTRING), u"]"_WSTRING);
    #line 3 "MOD_StateIds.fbt"
    var_IdStart = func_CONCAT(func_CONCAT(func_CONCAT(u"opc_ua[CREATE_METHOD;"_WSTRING, func_CONCAT(var_UaRoot, u"/Module/"_WSTRING)), u"Start"_WSTRING), u"]"_WSTRING);
    #line 4 "MOD_StateIds.fbt"
    var_IdStop = func_CONCAT(func_CONCAT(func_CONCAT(u"opc_ua[CREATE_METHOD;"_WSTRING, func_CONCAT(var_UaRoot, u"/Module/"_WSTRING)), u"Stop"_WSTRING), u"]"_WSTRING);
    #line 5 "MOD_StateIds.fbt"
    var_IdAbort = func_CONCAT(func_CONCAT(func_CONCAT(u"opc_ua[CREATE_METHOD;"_WSTRING, func_CONCAT(var_UaRoot, u"/Module/"_WSTRING)), u"Abort"_WSTRING), u"]"_WSTRING);
    #line 6 "MOD_StateIds.fbt"
    var_IdClear = func_CONCAT(func_CONCAT(func_CONCAT(u"opc_ua[CREATE_METHOD;"_WSTRING, func_CONCAT(var_UaRoot, u"/Module/"_WSTRING)), u"Clear"_WSTRING), u"]"_WSTRING);
    #line 7 "MOD_StateIds.fbt"
    var_IdPub = func_CONCAT(func_CONCAT(func_CONCAT(u"opc_ua[WRITE;"_WSTRING, func_CONCAT(var_UaRoot, u"/Module/"_WSTRING)), u"State"_WSTRING), u"]"_WSTRING);
    #line 8 "MOD_StateIds.fbt"
    var_IdState = func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/state]"_WSTRING);
    #line 9 "MOD_StateIds.fbt"
    var_IdQuery = func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/state/query]"_WSTRING);
    #line 10 "MOD_StateIds.fbt"
    var_IdAct = func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/activity]"_WSTRING);
  }

}