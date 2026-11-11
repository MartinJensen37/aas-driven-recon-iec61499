/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: MOD_StateView
 *** Description: Tells the block it sits in the module's PackML state, and asks for it once at start. Technical: The module's PackML state from its local channel; asks for the current value at INIT
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/MOD_StateView_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/forte_st_util.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:y5WeqemdKq901OkH6Wzei5tmInbAdfPZC4PTPKjIvyIpSzpy3Dc1AorSph7C6NzYj7s4Mr0uv4svSmT5jFzLEQ=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "CHG"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"Module"_STRID};
    const auto cDataOutputNames = std::array{"State"_STRID};

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
      {"Latch"_STRID, "State"_STRID, {}, "State"_STRID},
    });

    const SCFB_FBNData cFBNData = {
      .mEventConnections = cEventConnections,
      .mDataConnections = cDataConnections,
      .mAdapterConnections = {},
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_MOD_StateView, "modlib::MOD_StateView"_STRID, TypeHash)

  FORTE_MOD_StateView::FORTE_MOD_StateView(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CCompositeFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cFBNData),
      fb_Latch("Latch"_STRID, *this),
      fb_Listen("Listen"_STRID, "iec61499::net::SUBSCRIBE_1", *this),
      fb_Query("Query"_STRID, "iec61499::net::PUBLISH_0", *this),
      conn_INITO(*this, 0),
      conn_CHG(*this, 1),
      conn_Module(nullptr),
      conn_State(*this, 0, 0_USINT),
      conn_if2in_Module(*this, 0, u""_WSTRING) {
  };

  void FORTE_MOD_StateView::setInitialValues() {
    CCompositeFB::setInitialValues();
    conn_if2in_Module.getValue() = u""_WSTRING;
    fb_Latch->conn_State.getValue() = 0_USINT;
  }

  void FORTE_MOD_StateView::setFBNetworkInitialValues() {
    if (auto v = fb_Listen->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
    if (auto v = fb_Query->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
  }

  void FORTE_MOD_StateView::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, conn_if2in_Module.getValue(), conn_Module);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_MOD_StateView::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventCHGID: {
        writeData(1, fb_Latch->conn_State.getValue(), conn_State);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_MOD_StateView::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module.getValue();
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_MOD_StateView::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &fb_Latch->conn_State.getValue();
    }
    return nullptr;
  }

  CEventConnection *FORTE_MOD_StateView::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_CHG;
    }
    return nullptr;
  }

  CDataConnection **FORTE_MOD_StateView::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Module;
    }
    return nullptr;
  }

  CDataConnection *FORTE_MOD_StateView::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_State;
    }
    return nullptr;
  }

  CDataConnection *FORTE_MOD_StateView::getIf2InConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module;
    }
    return nullptr;
  }

}