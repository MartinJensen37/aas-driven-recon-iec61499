/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: MOD_OwnerView
 *** Description: Tells the block it sits in who occupies the module, and asks for it once at start. Technical: The module's occupation owner from its local channel; asks for the current value at INIT
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/MOD_OwnerView_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/forte_st_util.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:VYWqCPFCHiwoyiP3dNBP6xahaCLxEH73LFVxO7MB_jLtgoed46ueRLor2RMGcLDg2lHQZL6YIgVt1ZYg74yKdQ=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "CHG"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"Module"_STRID};
    const auto cDataOutputNames = std::array{"Owner"_STRID};

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

    const auto cEventConnections = std::to_array<SCFB_FBConnectionData>({
      {{}, "INIT"_STRID, "Latch"_STRID, "INIT"_STRID},
      {"Latch"_STRID, "INITO"_STRID, "Listen"_STRID, "INIT"_STRID},
      {"Listen"_STRID, "INITO"_STRID, "Query"_STRID, "INIT"_STRID},
      {"Query"_STRID, "INITO"_STRID, "Query"_STRID, "REQ"_STRID},
      {"Query"_STRID, "INITO"_STRID, {}, "INITO"_STRID},
      {"Listen"_STRID, "IND"_STRID, "Latch"_STRID, "REQ"_STRID},
      {"Latch"_STRID, "CNF"_STRID, {}, "CHG"_STRID},
    });

    const auto cDataConnections = std::to_array<SCFB_FBConnectionData>({
      {{}, "Module"_STRID, "Latch"_STRID, "Module"_STRID},
      {"Latch"_STRID, "IdSub"_STRID, "Listen"_STRID, "ID"_STRID},
      {"Latch"_STRID, "IdQuery"_STRID, "Query"_STRID, "ID"_STRID},
      {"Listen"_STRID, "RD_1"_STRID, "Latch"_STRID, "Received"_STRID},
      {"Latch"_STRID, "Owner"_STRID, {}, "Owner"_STRID},
    });

    const SCFB_FBNData cFBNData = {
      .mEventConnections = cEventConnections,
      .mDataConnections = cDataConnections,
      .mAdapterConnections = {},
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_MOD_OwnerView, "modlib::MOD_OwnerView"_STRID, TypeHash)

  FORTE_MOD_OwnerView::FORTE_MOD_OwnerView(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CCompositeFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cFBNData),
      fb_Latch("Latch"_STRID, *this),
      fb_Listen("Listen"_STRID, "iec61499::net::SUBSCRIBE_1", *this),
      fb_Query("Query"_STRID, "iec61499::net::PUBLISH_0", *this),
      conn_INITO(*this, 0),
      conn_CHG(*this, 1),
      conn_Module(nullptr),
      conn_Owner(*this, 0, u""_WSTRING),
      conn_if2in_Module(*this, 0, u""_WSTRING) {
  };

  void FORTE_MOD_OwnerView::setInitialValues() {
    CCompositeFB::setInitialValues();
    conn_if2in_Module.getValue() = u""_WSTRING;
    fb_Latch->conn_Owner.getValue() = u""_WSTRING;
  }

  void FORTE_MOD_OwnerView::setFBNetworkInitialValues() {
    if (auto v = fb_Listen->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
    if (auto v = fb_Query->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
  }

  void FORTE_MOD_OwnerView::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, conn_if2in_Module.getValue(), conn_Module);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_MOD_OwnerView::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventCHGID: {
        writeData(1, fb_Latch->conn_Owner.getValue(), conn_Owner);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_MOD_OwnerView::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module.getValue();
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_MOD_OwnerView::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &fb_Latch->conn_Owner.getValue();
    }
    return nullptr;
  }

  CEventConnection *FORTE_MOD_OwnerView::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_CHG;
    }
    return nullptr;
  }

  CDataConnection **FORTE_MOD_OwnerView::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Module;
    }
    return nullptr;
  }

  CDataConnection *FORTE_MOD_OwnerView::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Owner;
    }
    return nullptr;
  }

  CDataConnection *FORTE_MOD_OwnerView::getIf2InConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module;
    }
    return nullptr;
  }

}