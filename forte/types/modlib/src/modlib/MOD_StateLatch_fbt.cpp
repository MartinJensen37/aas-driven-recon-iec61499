/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: MOD_StateLatch
 *** Description: Keeps the last module state heard on the state channel. Technical: Local channel IDs of the PackML state and its refresh query; types and forwards the received PackML state
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/MOD_StateLatch_fbt.h"

#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"
#include "forte/iec61131_functions/func_CONCAT.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:Ef7zYTt71gtdUvaJ2ACYzm5Oblnp7enqGMyB3NovgqlzU9TP-OXuO3fKvK7AouuyFsGjgrqoJGAIVK-s3FmDcg=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "REQ"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "CNF"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"Module"_STRID, "Received"_STRID};
    const auto cDataOutputNames = std::array{"IdSub"_STRID, "IdQuery"_STRID, "State"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_MOD_StateLatch, "modlib::MOD_StateLatch"_STRID, TypeHash)

  FORTE_MOD_StateLatch::FORTE_MOD_StateLatch(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CSimpleFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_Module(u""_WSTRING),
      var_Received(0_USINT),
      var_IdSub(u""_WSTRING),
      var_IdQuery(u""_WSTRING),
      var_State(0_USINT),
      conn_INITO(*this, 0),
      conn_CNF(*this, 1),
      conn_Module(nullptr),
      conn_Received(nullptr),
      conn_IdSub(*this, 0, var_IdSub),
      conn_IdQuery(*this, 1, var_IdQuery),
      conn_State(*this, 2, var_State) {
  }

  void FORTE_MOD_StateLatch::setInitialValues() {
    CSimpleFB::setInitialValues();
    var_Module = u""_WSTRING;
    var_Received = 0_USINT;
    var_IdSub = u""_WSTRING;
    var_IdQuery = u""_WSTRING;
    var_State = 0_USINT;
  }

  void FORTE_MOD_StateLatch::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
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

  void FORTE_MOD_StateLatch::enterStateINIT(CEventChainExecutionThread *const paECET) {
    alg_INIT();
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_MOD_StateLatch::enterStateREQ(CEventChainExecutionThread *const paECET) {
    alg_REQ();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_MOD_StateLatch::readInputData(const TEventID paEIID) {
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

  void FORTE_MOD_StateLatch::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(2, var_IdSub, conn_IdSub);
        writeData(3, var_IdQuery, conn_IdQuery);
        break;
      }
      case scmEventCNFID: {
        writeData(4, var_State, conn_State);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_MOD_StateLatch::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Module;
      case 1: return &var_Received;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_MOD_StateLatch::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_IdSub;
      case 1: return &var_IdQuery;
      case 2: return &var_State;
    }
    return nullptr;
  }

  CEventConnection *FORTE_MOD_StateLatch::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_CNF;
    }
    return nullptr;
  }

  CDataConnection **FORTE_MOD_StateLatch::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Module;
      case 1: return &conn_Received;
    }
    return nullptr;
  }

  CDataConnection *FORTE_MOD_StateLatch::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_IdSub;
      case 1: return &conn_IdQuery;
      case 2: return &conn_State;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_MOD_StateLatch::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_MOD_StateLatch::alg_INIT(void) {

    #line 2 "MOD_StateLatch.fbt"
    var_IdSub = func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/state]"_WSTRING);
    #line 3 "MOD_StateLatch.fbt"
    var_IdQuery = func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/state/query]"_WSTRING);
  }

  void FORTE_MOD_StateLatch::alg_REQ(void) {

    #line 7 "MOD_StateLatch.fbt"
    var_State = var_Received;
  }

}