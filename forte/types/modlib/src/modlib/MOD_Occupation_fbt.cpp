/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: MOD_Occupation
 *** Description: Who may command the module. A client first calls the OPC UA method Occupy with a session id it chose; until it calls Release, only commands carrying that session id are accepted. Publishes Occupied (never the id) and tells every block of the module who the owner is. Technical: Module occupation: OPC UA methods Occupy(Session) and Release(Session) answer [Accepted, ErrorID]; publishes Occupied (never the session ID) and shares the owner on a local channel
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/MOD_Occupation_fbt.h"

#include "forte/datatypes/forte_bool.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:ZO4_aVm7rBLg0oYI92_3cKDwLm9ZqvWrWKNY57qT0Jn49Fv8G_gFz0k-vh_nW4sJA2tRL4pSV4_hR1jfP4DkmQ=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID};
    const auto cDataInputNames = std::array{"Module"_STRID, "UaRoot"_STRID, "UaEnable"_STRID};

    const SFBInterfaceSpec cFBInterfaceSpec = {
        .mEINames = cEventInputNames,
        .mEITypeNames = cEventInputTypeIds,
        .mEONames = cEventOutputNames,
        .mEOTypeNames = cEventOutputTypeIds,
        .mDINames = cDataInputNames,
        .mDONames = {},
        .mDIONames = {},
        .mSocketNames = {},
        .mPlugNames = {},
    };

    const auto cEventConnections = std::to_array<SCFB_FBConnectionData>({
      {{}, "INIT"_STRID, "Ids"_STRID, "INIT"_STRID},
      {"Ids"_STRID, "INITO"_STRID, "Occupy"_STRID, "INIT"_STRID},
      {"Occupy"_STRID, "INITO"_STRID, "Release"_STRID, "INIT"_STRID},
      {"Release"_STRID, "INITO"_STRID, "PubOwner"_STRID, "INIT"_STRID},
      {"PubOwner"_STRID, "INITO"_STRID, "SubQuery"_STRID, "INIT"_STRID},
      {"SubQuery"_STRID, "INITO"_STRID, "PubUa"_STRID, "INIT"_STRID},
      {"PubUa"_STRID, "INITO"_STRID, "PubUa"_STRID, "REQ"_STRID},
      {"PubUa"_STRID, "INITO"_STRID, {}, "INITO"_STRID},
      {"Occupy"_STRID, "IND"_STRID, "Logic"_STRID, "OCCUPY_REQ"_STRID},
      {"Logic"_STRID, "OCCUPY_RSP"_STRID, "Occupy"_STRID, "RSP"_STRID},
      {"Release"_STRID, "IND"_STRID, "Logic"_STRID, "RELEASE_REQ"_STRID},
      {"Logic"_STRID, "RELEASE_RSP"_STRID, "Release"_STRID, "RSP"_STRID},
      {"SubQuery"_STRID, "IND"_STRID, "Logic"_STRID, "QUERY_REQ"_STRID},
      {"Logic"_STRID, "CHG"_STRID, "PubOwner"_STRID, "REQ"_STRID},
      {"Logic"_STRID, "CHG"_STRID, "PubUa"_STRID, "REQ"_STRID},
    });

    const auto cDataConnections = std::to_array<SCFB_FBConnectionData>({
      {{}, "Module"_STRID, "Ids"_STRID, "Module"_STRID},
      {{}, "UaRoot"_STRID, "Ids"_STRID, "UaRoot"_STRID},
      {{}, "UaEnable"_STRID, "Occupy"_STRID, "QI"_STRID},
      {{}, "UaEnable"_STRID, "Release"_STRID, "QI"_STRID},
      {{}, "UaEnable"_STRID, "PubUa"_STRID, "QI"_STRID},
      {"Ids"_STRID, "IdOccupy"_STRID, "Occupy"_STRID, "ID"_STRID},
      {"Ids"_STRID, "IdRelease"_STRID, "Release"_STRID, "ID"_STRID},
      {"Ids"_STRID, "IdPub"_STRID, "PubUa"_STRID, "ID"_STRID},
      {"Ids"_STRID, "IdOwner"_STRID, "PubOwner"_STRID, "ID"_STRID},
      {"Ids"_STRID, "IdQuery"_STRID, "SubQuery"_STRID, "ID"_STRID},
      {"Occupy"_STRID, "RD_1"_STRID, "Logic"_STRID, "OccupySession"_STRID},
      {"Logic"_STRID, "Accepted"_STRID, "Occupy"_STRID, "SD_1"_STRID},
      {"Logic"_STRID, "ErrorID"_STRID, "Occupy"_STRID, "SD_2"_STRID},
      {"Release"_STRID, "RD_1"_STRID, "Logic"_STRID, "ReleaseSession"_STRID},
      {"Logic"_STRID, "Accepted"_STRID, "Release"_STRID, "SD_1"_STRID},
      {"Logic"_STRID, "ErrorID"_STRID, "Release"_STRID, "SD_2"_STRID},
      {"Logic"_STRID, "Owner"_STRID, "PubOwner"_STRID, "SD_1"_STRID},
      {"Logic"_STRID, "Occupied"_STRID, "PubUa"_STRID, "SD_1"_STRID},
    });

    const SCFB_FBNData cFBNData = {
      .mEventConnections = cEventConnections,
      .mDataConnections = cDataConnections,
      .mAdapterConnections = {},
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_MOD_Occupation, "modlib::MOD_Occupation"_STRID, TypeHash)

  FORTE_MOD_Occupation::FORTE_MOD_Occupation(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CCompositeFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cFBNData),
      fb_Ids("Ids"_STRID, *this),
      fb_Occupy("Occupy"_STRID, "iec61499::net::SERVER_2_1", *this),
      fb_Release("Release"_STRID, "iec61499::net::SERVER_2_1", *this),
      fb_Logic("Logic"_STRID, *this),
      fb_PubOwner("PubOwner"_STRID, "iec61499::net::PUBLISH_1", *this),
      fb_SubQuery("SubQuery"_STRID, "iec61499::net::SUBSCRIBE_0", *this),
      fb_PubUa("PubUa"_STRID, "iec61499::net::PUBLISH_1", *this),
      conn_INITO(*this, 0),
      conn_Module(nullptr),
      conn_UaRoot(nullptr),
      conn_UaEnable(nullptr),
      conn_if2in_Module(*this, 0, u""_WSTRING),
      conn_if2in_UaRoot(*this, 1, u""_WSTRING),
      conn_if2in_UaEnable(*this, 2, 0_BOOL) {
  };

  void FORTE_MOD_Occupation::setInitialValues() {
    CCompositeFB::setInitialValues();
    conn_if2in_Module.getValue() = u""_WSTRING;
    conn_if2in_UaRoot.getValue() = u""_WSTRING;
    conn_if2in_UaEnable.getValue() = 0_BOOL;
  }

  void FORTE_MOD_Occupation::setFBNetworkInitialValues() {
    if (auto v = fb_PubOwner->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
    if (auto v = fb_SubQuery->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
  }

  void FORTE_MOD_Occupation::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, conn_if2in_Module.getValue(), conn_Module);
        readData(1, conn_if2in_UaRoot.getValue(), conn_UaRoot);
        readData(2, conn_if2in_UaEnable.getValue(), conn_UaEnable);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_MOD_Occupation::writeOutputData(TEventID) {
    // nothing to do
  }

  CIEC_ANY *FORTE_MOD_Occupation::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module.getValue();
      case 1: return &conn_if2in_UaRoot.getValue();
      case 2: return &conn_if2in_UaEnable.getValue();
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_MOD_Occupation::getDO(size_t) {
    return nullptr;
  }

  CEventConnection *FORTE_MOD_Occupation::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
    }
    return nullptr;
  }

  CDataConnection **FORTE_MOD_Occupation::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Module;
      case 1: return &conn_UaRoot;
      case 2: return &conn_UaEnable;
    }
    return nullptr;
  }

  CDataConnection *FORTE_MOD_Occupation::getDOConUnchecked(TPortId) {
    return nullptr;
  }

  CDataConnection *FORTE_MOD_Occupation::getIf2InConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module;
      case 1: return &conn_if2in_UaRoot;
      case 2: return &conn_if2in_UaEnable;
    }
    return nullptr;
  }

}