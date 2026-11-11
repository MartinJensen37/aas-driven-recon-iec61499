/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: MOD_StateManager
 *** Description: The module's PackML state: Stopped, Resetting, Idle, Execute, Stopping, Aborted. The owner changes it with the OPC UA methods Reset, Start, Stop, Abort and Clear. It runs the Resetting and Stopping procedures and publishes the state for clients and for every block. Technical: Module state manager: OPC UA methods Reset/Start/Stop/Abort/Clear(Session) answer [Accepted, ErrorID]; publishes the PackML State over OPC UA and on the module's state channel; RUN_RESETTING and RUN_STOPPING start the procedures, which answer with *_DONE or *_FAILED
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/MOD_StateManager_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_time.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:NsIwHUchCxSA9h2-fLRvpqPn7-DxMnJOkk49IbP6iHYS7592DOGCRqRsPXCm1lfmCawm4TOJhCWobcr-Bg9u5A=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "RESETTING_DONE"_STRID, "RESETTING_FAILED"_STRID, "STOPPING_DONE"_STRID, "STOPPING_FAILED"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "RUN_RESETTING"_STRID, "RUN_STOPPING"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"Module"_STRID, "UaRoot"_STRID, "UaEnable"_STRID, "StopTimeout"_STRID};

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
      {"Ids"_STRID, "INITO"_STRID, "Owner"_STRID, "INIT"_STRID},
      {"Owner"_STRID, "INITO"_STRID, "Reset"_STRID, "INIT"_STRID},
      {"Reset"_STRID, "INITO"_STRID, "Start"_STRID, "INIT"_STRID},
      {"Start"_STRID, "INITO"_STRID, "Stop"_STRID, "INIT"_STRID},
      {"Stop"_STRID, "INITO"_STRID, "Abort"_STRID, "INIT"_STRID},
      {"Abort"_STRID, "INITO"_STRID, "Clear"_STRID, "INIT"_STRID},
      {"Clear"_STRID, "INITO"_STRID, "PubUa"_STRID, "INIT"_STRID},
      {"PubUa"_STRID, "INITO"_STRID, "PubState"_STRID, "INIT"_STRID},
      {"PubState"_STRID, "INITO"_STRID, "SubQuery"_STRID, "INIT"_STRID},
      {"SubQuery"_STRID, "INITO"_STRID, "SubAct"_STRID, "INIT"_STRID},
      {"SubAct"_STRID, "INITO"_STRID, "PubUa"_STRID, "REQ"_STRID},
      {"SubAct"_STRID, "INITO"_STRID, "PubState"_STRID, "REQ"_STRID},
      {"SubAct"_STRID, "INITO"_STRID, {}, "INITO"_STRID},
      {"Owner"_STRID, "CHG"_STRID, "Gate"_STRID, "OWNER_CHG"_STRID},
      {"Reset"_STRID, "IND"_STRID, "Gate"_STRID, "RESET_REQ"_STRID},
      {"Gate"_STRID, "RESET_RSP"_STRID, "Reset"_STRID, "RSP"_STRID},
      {"Gate"_STRID, "GO_RESET"_STRID, "Logic"_STRID, "RESET"_STRID},
      {"Start"_STRID, "IND"_STRID, "Gate"_STRID, "START_REQ"_STRID},
      {"Gate"_STRID, "START_RSP"_STRID, "Start"_STRID, "RSP"_STRID},
      {"Gate"_STRID, "GO_START"_STRID, "Logic"_STRID, "START"_STRID},
      {"Stop"_STRID, "IND"_STRID, "Gate"_STRID, "STOP_REQ"_STRID},
      {"Gate"_STRID, "STOP_RSP"_STRID, "Stop"_STRID, "RSP"_STRID},
      {"Gate"_STRID, "GO_STOP"_STRID, "Logic"_STRID, "STOP"_STRID},
      {"Abort"_STRID, "IND"_STRID, "Gate"_STRID, "ABORT_REQ"_STRID},
      {"Gate"_STRID, "ABORT_RSP"_STRID, "Abort"_STRID, "RSP"_STRID},
      {"Gate"_STRID, "GO_ABORT"_STRID, "Logic"_STRID, "ABORT"_STRID},
      {"Clear"_STRID, "IND"_STRID, "Gate"_STRID, "CLEAR_REQ"_STRID},
      {"Gate"_STRID, "CLEAR_RSP"_STRID, "Clear"_STRID, "RSP"_STRID},
      {"Gate"_STRID, "GO_CLEAR"_STRID, "Logic"_STRID, "CLEAR"_STRID},
      {"Logic"_STRID, "CNF"_STRID, "PubUa"_STRID, "REQ"_STRID},
      {"Logic"_STRID, "CNF"_STRID, "PubState"_STRID, "REQ"_STRID},
      {"Logic"_STRID, "CNF"_STRID, "Gate"_STRID, "STATE_CHG"_STRID},
      {"SubQuery"_STRID, "IND"_STRID, "PubState"_STRID, "REQ"_STRID},
      {"SubAct"_STRID, "IND"_STRID, "Count"_STRID, "ACT"_STRID},
      {"Count"_STRID, "CHG"_STRID, "Logic"_STRID, "ACT"_STRID},
      {"Logic"_STRID, "WD_START"_STRID, "Wd"_STRID, "START"_STRID},
      {"Logic"_STRID, "WD_STOP"_STRID, "Wd"_STRID, "STOP"_STRID},
      {"Wd"_STRID, "EO"_STRID, "Logic"_STRID, "STOP_TIMEOUT"_STRID},
      {"Logic"_STRID, "RUN_RESETTING"_STRID, {}, "RUN_RESETTING"_STRID},
      {"Logic"_STRID, "RUN_STOPPING"_STRID, {}, "RUN_STOPPING"_STRID},
      {{}, "RESETTING_DONE"_STRID, "Logic"_STRID, "RESETTING_DONE"_STRID},
      {{}, "RESETTING_FAILED"_STRID, "Logic"_STRID, "RESETTING_FAILED"_STRID},
      {{}, "STOPPING_DONE"_STRID, "Logic"_STRID, "STOPPING_DONE"_STRID},
      {{}, "STOPPING_FAILED"_STRID, "Logic"_STRID, "STOPPING_FAILED"_STRID},
    });

    const auto cDataConnections = std::to_array<SCFB_FBConnectionData>({
      {{}, "Module"_STRID, "Ids"_STRID, "Module"_STRID},
      {{}, "Module"_STRID, "Owner"_STRID, "Module"_STRID},
      {{}, "UaRoot"_STRID, "Ids"_STRID, "UaRoot"_STRID},
      {{}, "UaEnable"_STRID, "Reset"_STRID, "QI"_STRID},
      {{}, "UaEnable"_STRID, "Start"_STRID, "QI"_STRID},
      {{}, "UaEnable"_STRID, "Stop"_STRID, "QI"_STRID},
      {{}, "UaEnable"_STRID, "Abort"_STRID, "QI"_STRID},
      {{}, "UaEnable"_STRID, "Clear"_STRID, "QI"_STRID},
      {{}, "UaEnable"_STRID, "PubUa"_STRID, "QI"_STRID},
      {{}, "StopTimeout"_STRID, "Wd"_STRID, "DT"_STRID},
      {"Owner"_STRID, "Owner"_STRID, "Gate"_STRID, "Owner"_STRID},
      {"Ids"_STRID, "IdReset"_STRID, "Reset"_STRID, "ID"_STRID},
      {"Reset"_STRID, "RD_1"_STRID, "Gate"_STRID, "ResetSession"_STRID},
      {"Gate"_STRID, "Accepted"_STRID, "Reset"_STRID, "SD_1"_STRID},
      {"Gate"_STRID, "ErrorID"_STRID, "Reset"_STRID, "SD_2"_STRID},
      {"Ids"_STRID, "IdStart"_STRID, "Start"_STRID, "ID"_STRID},
      {"Start"_STRID, "RD_1"_STRID, "Gate"_STRID, "StartSession"_STRID},
      {"Gate"_STRID, "Accepted"_STRID, "Start"_STRID, "SD_1"_STRID},
      {"Gate"_STRID, "ErrorID"_STRID, "Start"_STRID, "SD_2"_STRID},
      {"Ids"_STRID, "IdStop"_STRID, "Stop"_STRID, "ID"_STRID},
      {"Stop"_STRID, "RD_1"_STRID, "Gate"_STRID, "StopSession"_STRID},
      {"Gate"_STRID, "Accepted"_STRID, "Stop"_STRID, "SD_1"_STRID},
      {"Gate"_STRID, "ErrorID"_STRID, "Stop"_STRID, "SD_2"_STRID},
      {"Ids"_STRID, "IdAbort"_STRID, "Abort"_STRID, "ID"_STRID},
      {"Abort"_STRID, "RD_1"_STRID, "Gate"_STRID, "AbortSession"_STRID},
      {"Gate"_STRID, "Accepted"_STRID, "Abort"_STRID, "SD_1"_STRID},
      {"Gate"_STRID, "ErrorID"_STRID, "Abort"_STRID, "SD_2"_STRID},
      {"Ids"_STRID, "IdClear"_STRID, "Clear"_STRID, "ID"_STRID},
      {"Clear"_STRID, "RD_1"_STRID, "Gate"_STRID, "ClearSession"_STRID},
      {"Gate"_STRID, "Accepted"_STRID, "Clear"_STRID, "SD_1"_STRID},
      {"Gate"_STRID, "ErrorID"_STRID, "Clear"_STRID, "SD_2"_STRID},
      {"Ids"_STRID, "IdPub"_STRID, "PubUa"_STRID, "ID"_STRID},
      {"Ids"_STRID, "IdState"_STRID, "PubState"_STRID, "ID"_STRID},
      {"Ids"_STRID, "IdQuery"_STRID, "SubQuery"_STRID, "ID"_STRID},
      {"Ids"_STRID, "IdAct"_STRID, "SubAct"_STRID, "ID"_STRID},
      {"Logic"_STRID, "State"_STRID, "PubUa"_STRID, "SD_1"_STRID},
      {"Logic"_STRID, "State"_STRID, "PubState"_STRID, "SD_1"_STRID},
      {"Logic"_STRID, "State"_STRID, "Gate"_STRID, "State"_STRID},
      {"SubAct"_STRID, "RD_1"_STRID, "Count"_STRID, "Delta"_STRID},
      {"Count"_STRID, "AllIdle"_STRID, "Logic"_STRID, "AllIdle"_STRID},
    });

    const SCFB_FBNData cFBNData = {
      .mEventConnections = cEventConnections,
      .mDataConnections = cDataConnections,
      .mAdapterConnections = {},
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_MOD_StateManager, "modlib::MOD_StateManager"_STRID, TypeHash)

  FORTE_MOD_StateManager::FORTE_MOD_StateManager(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CCompositeFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cFBNData),
      fb_Ids("Ids"_STRID, *this),
      fb_Owner("Owner"_STRID, *this),
      fb_Reset("Reset"_STRID, "iec61499::net::SERVER_2_1", *this),
      fb_Start("Start"_STRID, "iec61499::net::SERVER_2_1", *this),
      fb_Stop("Stop"_STRID, "iec61499::net::SERVER_2_1", *this),
      fb_Abort("Abort"_STRID, "iec61499::net::SERVER_2_1", *this),
      fb_Clear("Clear"_STRID, "iec61499::net::SERVER_2_1", *this),
      fb_Gate("Gate"_STRID, *this),
      fb_Logic("Logic"_STRID, *this),
      fb_PubUa("PubUa"_STRID, "iec61499::net::PUBLISH_1", *this),
      fb_PubState("PubState"_STRID, "iec61499::net::PUBLISH_1", *this),
      fb_SubQuery("SubQuery"_STRID, "iec61499::net::SUBSCRIBE_0", *this),
      fb_SubAct("SubAct"_STRID, "iec61499::net::SUBSCRIBE_1", *this),
      fb_Count("Count"_STRID, *this),
      fb_Wd("Wd"_STRID, *this),
      conn_INITO(*this, 0),
      conn_RUN_RESETTING(*this, 1),
      conn_RUN_STOPPING(*this, 2),
      conn_Module(nullptr),
      conn_UaRoot(nullptr),
      conn_UaEnable(nullptr),
      conn_StopTimeout(nullptr),
      conn_if2in_Module(*this, 0, u""_WSTRING),
      conn_if2in_UaRoot(*this, 1, u""_WSTRING),
      conn_if2in_UaEnable(*this, 2, 0_BOOL),
      conn_if2in_StopTimeout(*this, 3, 10000000000_TIME) {
  };

  void FORTE_MOD_StateManager::setInitialValues() {
    CCompositeFB::setInitialValues();
    conn_if2in_Module.getValue() = u""_WSTRING;
    conn_if2in_UaRoot.getValue() = u""_WSTRING;
    conn_if2in_UaEnable.getValue() = 0_BOOL;
    conn_if2in_StopTimeout.getValue() = 10000000000_TIME;
  }

  void FORTE_MOD_StateManager::setFBNetworkInitialValues() {
    if (auto v = fb_PubState->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
    if (auto v = fb_SubQuery->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
    if (auto v = fb_SubAct->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
  }

  void FORTE_MOD_StateManager::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, conn_if2in_Module.getValue(), conn_Module);
        readData(1, conn_if2in_UaRoot.getValue(), conn_UaRoot);
        readData(2, conn_if2in_UaEnable.getValue(), conn_UaEnable);
        readData(3, conn_if2in_StopTimeout.getValue(), conn_StopTimeout);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_MOD_StateManager::writeOutputData(TEventID) {
    // nothing to do
  }

  CIEC_ANY *FORTE_MOD_StateManager::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module.getValue();
      case 1: return &conn_if2in_UaRoot.getValue();
      case 2: return &conn_if2in_UaEnable.getValue();
      case 3: return &conn_if2in_StopTimeout.getValue();
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_MOD_StateManager::getDO(size_t) {
    return nullptr;
  }

  CEventConnection *FORTE_MOD_StateManager::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_RUN_RESETTING;
      case 2: return &conn_RUN_STOPPING;
    }
    return nullptr;
  }

  CDataConnection **FORTE_MOD_StateManager::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Module;
      case 1: return &conn_UaRoot;
      case 2: return &conn_UaEnable;
      case 3: return &conn_StopTimeout;
    }
    return nullptr;
  }

  CDataConnection *FORTE_MOD_StateManager::getDOConUnchecked(TPortId) {
    return nullptr;
  }

  CDataConnection *FORTE_MOD_StateManager::getIf2InConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module;
      case 1: return &conn_if2in_UaRoot;
      case 2: return &conn_if2in_UaEnable;
      case 3: return &conn_if2in_StopTimeout;
    }
    return nullptr;
  }

}