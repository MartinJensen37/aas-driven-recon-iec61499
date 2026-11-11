/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: MOD_OwnerLatch
 *** Description: Keeps the last owner heard on the owner channel. Technical: Local channel IDs of the occupation owner and its refresh query; types and forwards the received occupation owner
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/MOD_OwnerLatch_fbt.h"

#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"
#include "forte/iec61131_functions/func_CONCAT.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:nLHU1X2gl-4aKpGXMjMrXZlosmCszqZnDe93Pz9s6HjvRetJfuA1Cm6ON6S2xSiXlEpnn19tG4lh3dInQxgWYQ=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "REQ"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "CNF"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"Module"_STRID, "Received"_STRID};
    const auto cDataOutputNames = std::array{"IdSub"_STRID, "IdQuery"_STRID, "Owner"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_MOD_OwnerLatch, "modlib::MOD_OwnerLatch"_STRID, TypeHash)

  FORTE_MOD_OwnerLatch::FORTE_MOD_OwnerLatch(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CSimpleFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_Module(u""_WSTRING),
      var_Received(u""_WSTRING),
      var_IdSub(u""_WSTRING),
      var_IdQuery(u""_WSTRING),
      var_Owner(u""_WSTRING),
      conn_INITO(*this, 0),
      conn_CNF(*this, 1),
      conn_Module(nullptr),
      conn_Received(nullptr),
      conn_IdSub(*this, 0, var_IdSub),
      conn_IdQuery(*this, 1, var_IdQuery),
      conn_Owner(*this, 2, var_Owner) {
  }

  void FORTE_MOD_OwnerLatch::setInitialValues() {
    CSimpleFB::setInitialValues();
    var_Module = u""_WSTRING;
    var_Received = u""_WSTRING;
    var_IdSub = u""_WSTRING;
    var_IdQuery = u""_WSTRING;
    var_Owner = u""_WSTRING;
  }

  void FORTE_MOD_OwnerLatch::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
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

  void FORTE_MOD_OwnerLatch::enterStateINIT(CEventChainExecutionThread *const paECET) {
    alg_INIT();
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_MOD_OwnerLatch::enterStateREQ(CEventChainExecutionThread *const paECET) {
    alg_REQ();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_MOD_OwnerLatch::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, var_Module, conn_Module);
        break;
      }
      case scmEventREQID: {
        readData(1, var_Received, conn_Received);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_MOD_OwnerLatch::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(2, var_IdSub, conn_IdSub);
        writeData(3, var_IdQuery, conn_IdQuery);
        break;
      }
      case scmEventCNFID: {
        writeData(4, var_Owner, conn_Owner);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_MOD_OwnerLatch::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Module;
      case 1: return &var_Received;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_MOD_OwnerLatch::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_IdSub;
      case 1: return &var_IdQuery;
      case 2: return &var_Owner;
    }
    return nullptr;
  }

  CEventConnection *FORTE_MOD_OwnerLatch::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_CNF;
    }
    return nullptr;
  }

  CDataConnection **FORTE_MOD_OwnerLatch::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Module;
      case 1: return &conn_Received;
    }
    return nullptr;
  }

  CDataConnection *FORTE_MOD_OwnerLatch::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_IdSub;
      case 1: return &conn_IdQuery;
      case 2: return &conn_Owner;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_MOD_OwnerLatch::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_MOD_OwnerLatch::alg_INIT(void) {

    #line 2 "MOD_OwnerLatch.fbt"
    var_IdSub = func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/owner]"_WSTRING);
    #line 3 "MOD_OwnerLatch.fbt"
    var_IdQuery = func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/owner/query]"_WSTRING);
  }

  void FORTE_MOD_OwnerLatch::alg_REQ(void) {

    #line 7 "MOD_OwnerLatch.fbt"
    var_Owner = var_Received;
  }

}