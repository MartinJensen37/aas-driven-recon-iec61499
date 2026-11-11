/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: MOD_OccupationIds
 *** Description: Builds the OPC UA addresses (Occupy, Release, Occupied) and the local channel names of the occupation from the module's name and OPC UA root. Technical: OPC UA and local channel IDs of the occupation
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/MOD_OccupationIds_fbt.h"

#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"
#include "forte/iec61131_functions/func_CONCAT.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:3lNXSPjtU5WePxG9gYBWizvCbyqXNmzGBmOg6Iz2NCmnp09yPtuv07CsWBKhbwsqUvWxCRKwYP6pTDWAVqb0Ng=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID};
    const auto cDataInputNames = std::array{"Module"_STRID, "UaRoot"_STRID};
    const auto cDataOutputNames = std::array{"IdOccupy"_STRID, "IdRelease"_STRID, "IdPub"_STRID, "IdOwner"_STRID, "IdQuery"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_MOD_OccupationIds, "modlib::MOD_OccupationIds"_STRID, TypeHash)

  FORTE_MOD_OccupationIds::FORTE_MOD_OccupationIds(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CSimpleFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_Module(u""_WSTRING),
      var_UaRoot(u""_WSTRING),
      var_IdOccupy(u""_WSTRING),
      var_IdRelease(u""_WSTRING),
      var_IdPub(u""_WSTRING),
      var_IdOwner(u""_WSTRING),
      var_IdQuery(u""_WSTRING),
      conn_INITO(*this, 0),
      conn_Module(nullptr),
      conn_UaRoot(nullptr),
      conn_IdOccupy(*this, 0, var_IdOccupy),
      conn_IdRelease(*this, 1, var_IdRelease),
      conn_IdPub(*this, 2, var_IdPub),
      conn_IdOwner(*this, 3, var_IdOwner),
      conn_IdQuery(*this, 4, var_IdQuery) {
  }

  void FORTE_MOD_OccupationIds::setInitialValues() {
    CSimpleFB::setInitialValues();
    var_Module = u""_WSTRING;
    var_UaRoot = u""_WSTRING;
    var_IdOccupy = u""_WSTRING;
    var_IdRelease = u""_WSTRING;
    var_IdPub = u""_WSTRING;
    var_IdOwner = u""_WSTRING;
    var_IdQuery = u""_WSTRING;
  }

  void FORTE_MOD_OccupationIds::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
    switch(paEIID) {
      case scmEventINITID:
        enterStateINIT(paECET);
        break;
      default:
        break;
    }
  }

  void FORTE_MOD_OccupationIds::enterStateINIT(CEventChainExecutionThread *const paECET) {
    alg_INIT();
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_MOD_OccupationIds::readInputData(const TEventID paEIID) {
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

  void FORTE_MOD_OccupationIds::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(2, var_IdOccupy, conn_IdOccupy);
        writeData(3, var_IdRelease, conn_IdRelease);
        writeData(4, var_IdPub, conn_IdPub);
        writeData(5, var_IdOwner, conn_IdOwner);
        writeData(6, var_IdQuery, conn_IdQuery);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_MOD_OccupationIds::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Module;
      case 1: return &var_UaRoot;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_MOD_OccupationIds::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_IdOccupy;
      case 1: return &var_IdRelease;
      case 2: return &var_IdPub;
      case 3: return &var_IdOwner;
      case 4: return &var_IdQuery;
    }
    return nullptr;
  }

  CEventConnection *FORTE_MOD_OccupationIds::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
    }
    return nullptr;
  }

  CDataConnection **FORTE_MOD_OccupationIds::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Module;
      case 1: return &conn_UaRoot;
    }
    return nullptr;
  }

  CDataConnection *FORTE_MOD_OccupationIds::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_IdOccupy;
      case 1: return &conn_IdRelease;
      case 2: return &conn_IdPub;
      case 3: return &conn_IdOwner;
      case 4: return &conn_IdQuery;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_MOD_OccupationIds::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_MOD_OccupationIds::alg_INIT(void) {

    #line 2 "MOD_OccupationIds.fbt"
    var_IdOccupy = func_CONCAT(func_CONCAT(func_CONCAT(u"opc_ua[CREATE_METHOD;"_WSTRING, func_CONCAT(var_UaRoot, u"/Occupation/"_WSTRING)), u"Occupy"_WSTRING), u"]"_WSTRING);
    #line 3 "MOD_OccupationIds.fbt"
    var_IdRelease = func_CONCAT(func_CONCAT(func_CONCAT(u"opc_ua[CREATE_METHOD;"_WSTRING, func_CONCAT(var_UaRoot, u"/Occupation/"_WSTRING)), u"Release"_WSTRING), u"]"_WSTRING);
    #line 4 "MOD_OccupationIds.fbt"
    var_IdPub = func_CONCAT(func_CONCAT(func_CONCAT(u"opc_ua[WRITE;"_WSTRING, func_CONCAT(var_UaRoot, u"/Occupation/"_WSTRING)), u"Occupied"_WSTRING), u"]"_WSTRING);
    #line 5 "MOD_OccupationIds.fbt"
    var_IdOwner = func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/owner]"_WSTRING);
    #line 6 "MOD_OccupationIds.fbt"
    var_IdQuery = func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/owner/query]"_WSTRING);
  }

}