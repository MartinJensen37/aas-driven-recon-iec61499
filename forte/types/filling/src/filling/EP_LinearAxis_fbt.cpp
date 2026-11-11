/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: EP_LinearAxis
 *** Description: The equipment as its skills see it, the same in every skill that uses it: plays a command (its output values, phase by phase) on the equipment's command channel, and gives the equipment's newest state. Technical: LinearAxis as its skills see it: a command on the socket Skill (AEquipment: SEND, PLAYED when all phases are out) goes out on its command channel; STATE gives its inputs and holder
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/filling/EP_LinearAxis_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/forte_st_util.h"
#include "forte/modlib/AEquipment_adp.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::filling {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:JHeYb6RkLZgzyC1AMdjnTDcLgvdBzLCrDTRFbCwkVX8Wt6BaKmJ96SV-KdLBL_0piRDfZBa15cY0Gc7T1scpBA=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "STATE"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"Module"_STRID};
    const auto cDataOutputNames = std::array{"AtHome"_STRID, "ActualPosition"_STRID, "Homed"_STRID, "Moving"_STRID, "EqHolder"_STRID};
    const auto cSocketNameIds = std::array{"Skill"_STRID};

    const SFBInterfaceSpec cFBInterfaceSpec = {
        .mEINames = cEventInputNames,
        .mEITypeNames = cEventInputTypeIds,
        .mEONames = cEventOutputNames,
        .mEOTypeNames = cEventOutputTypeIds,
        .mDINames = cDataInputNames,
        .mDONames = cDataOutputNames,
        .mDIONames = {},
        .mSocketNames = cSocketNameIds,
        .mPlugNames = {},
    };

    const auto cEventConnections = std::to_array<SCFB_FBConnectionData>({
      {{}, "INIT"_STRID, "EqView"_STRID, "INIT"_STRID},
      {"EqView"_STRID, "INITO"_STRID, "EqState"_STRID, "INIT"_STRID},
      {"EqState"_STRID, "INITO"_STRID, "EqCmd"_STRID, "INIT"_STRID},
      {"EqCmd"_STRID, "INITO"_STRID, {}, "INITO"_STRID},
      {"EqState"_STRID, "IND"_STRID, "EqView"_STRID, "REQ"_STRID},
      {"EqView"_STRID, "CNF"_STRID, {}, "STATE"_STRID},
      {"Skill"_STRID, "SEND"_STRID, "Driver"_STRID, "PLAY"_STRID},
      {"Driver"_STRID, "OUT"_STRID, "EqCmd"_STRID, "REQ"_STRID},
      {"Driver"_STRID, "PHASE_START"_STRID, "PhaseT"_STRID, "START"_STRID},
      {"Driver"_STRID, "PHASE_STOP"_STRID, "PhaseT"_STRID, "STOP"_STRID},
      {"PhaseT"_STRID, "EO"_STRID, "Driver"_STRID, "PHASE_T"_STRID},
      {"Driver"_STRID, "PLAYED"_STRID, "Skill"_STRID, "PLAYED"_STRID},
    });

    const auto cDataConnections = std::to_array<SCFB_FBConnectionData>({
      {{}, "Module"_STRID, "EqView"_STRID, "Module"_STRID},
      {"EqView"_STRID, "IdState"_STRID, "EqState"_STRID, "ID"_STRID},
      {"EqView"_STRID, "IdCmd"_STRID, "EqCmd"_STRID, "ID"_STRID},
      {"EqState"_STRID, "RD_1"_STRID, "EqView"_STRID, "I_AtHome"_STRID},
      {"EqState"_STRID, "RD_2"_STRID, "EqView"_STRID, "I_ActualPosition"_STRID},
      {"EqState"_STRID, "RD_3"_STRID, "EqView"_STRID, "I_Homed"_STRID},
      {"EqState"_STRID, "RD_4"_STRID, "EqView"_STRID, "I_Moving"_STRID},
      {"EqState"_STRID, "RD_5"_STRID, "EqView"_STRID, "I_Holder"_STRID},
      {"EqView"_STRID, "AtHome"_STRID, {}, "AtHome"_STRID},
      {"EqView"_STRID, "ActualPosition"_STRID, {}, "ActualPosition"_STRID},
      {"EqView"_STRID, "Homed"_STRID, {}, "Homed"_STRID},
      {"EqView"_STRID, "Moving"_STRID, {}, "Moving"_STRID},
      {"EqView"_STRID, "Holder"_STRID, {}, "EqHolder"_STRID},
      {"Skill"_STRID, "Holder"_STRID, "Driver"_STRID, "Holder"_STRID},
      {"Skill"_STRID, "Command"_STRID, "Driver"_STRID, "Command"_STRID},
      {"Skill"_STRID, "Arg"_STRID, "Driver"_STRID, "Arg"_STRID},
      {"Skill"_STRID, "Release"_STRID, "Driver"_STRID, "Release"_STRID},
      {"Driver"_STRID, "O_Holder"_STRID, "EqCmd"_STRID, "SD_1"_STRID},
      {"Driver"_STRID, "O_Release"_STRID, "EqCmd"_STRID, "SD_2"_STRID},
      {"Driver"_STRID, "N_Enable"_STRID, "EqCmd"_STRID, "SD_3"_STRID},
      {"Driver"_STRID, "N_Down"_STRID, "EqCmd"_STRID, "SD_4"_STRID},
      {"Driver"_STRID, "N_Step"_STRID, "EqCmd"_STRID, "SD_5"_STRID},
      {"Driver"_STRID, "NE_Step"_STRID, "EqCmd"_STRID, "SD_6"_STRID},
      {"Driver"_STRID, "N_Move"_STRID, "EqCmd"_STRID, "SD_7"_STRID},
      {"Driver"_STRID, "N_Goal"_STRID, "EqCmd"_STRID, "SD_8"_STRID},
      {"Driver"_STRID, "PhaseDT"_STRID, "PhaseT"_STRID, "DT"_STRID},
    });

    const SCFB_FBNData cFBNData = {
      .mEventConnections = cEventConnections,
      .mDataConnections = cDataConnections,
      .mAdapterConnections = {},
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_EP_LinearAxis, "filling::EP_LinearAxis"_STRID, TypeHash)

  FORTE_EP_LinearAxis::FORTE_EP_LinearAxis(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CCompositeFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cFBNData),
      fb_EqView("EqView"_STRID, *this),
      fb_EqState("EqState"_STRID, "iec61499::net::SUBSCRIBE_5", *this),
      fb_Driver("Driver"_STRID, *this),
      fb_PhaseT("PhaseT"_STRID, *this),
      fb_EqCmd("EqCmd"_STRID, "iec61499::net::PUBLISH_8", *this),
      var_Skill("Skill"_STRID, *this, forte::cgCFBParentAdapterlistIDMarker),
      conn_INITO(*this, 0),
      conn_STATE(*this, 1),
      conn_Module(nullptr),
      conn_AtHome(*this, 0, 0_BOOL),
      conn_ActualPosition(*this, 1, 0_LREAL),
      conn_Homed(*this, 2, 0_BOOL),
      conn_Moving(*this, 3, 0_BOOL),
      conn_EqHolder(*this, 4, u""_WSTRING),
      conn_if2in_Module(*this, 0, u""_WSTRING) {
  };

  void FORTE_EP_LinearAxis::setInitialValues() {
    CCompositeFB::setInitialValues();
    conn_if2in_Module.getValue() = u""_WSTRING;
    fb_EqView->conn_AtHome.getValue() = 0_BOOL;
    fb_EqView->conn_ActualPosition.getValue() = 0_LREAL;
    fb_EqView->conn_Homed.getValue() = 0_BOOL;
    fb_EqView->conn_Moving.getValue() = 0_BOOL;
    fb_EqView->conn_Holder.getValue() = u""_WSTRING;
  }

  void FORTE_EP_LinearAxis::setFBNetworkInitialValues() {
    if (auto v = fb_EqState->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
    if (auto v = fb_EqCmd->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
  }

  void FORTE_EP_LinearAxis::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, conn_if2in_Module.getValue(), conn_Module);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_EP_LinearAxis::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventSTATEID: {
        writeData(1, fb_EqView->conn_AtHome.getValue(), conn_AtHome);
        writeData(2, fb_EqView->conn_ActualPosition.getValue(), conn_ActualPosition);
        writeData(3, fb_EqView->conn_Homed.getValue(), conn_Homed);
        writeData(4, fb_EqView->conn_Moving.getValue(), conn_Moving);
        writeData(5, fb_EqView->conn_Holder.getValue(), conn_EqHolder);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_EP_LinearAxis::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module.getValue();
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_EP_LinearAxis::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &fb_EqView->conn_AtHome.getValue();
      case 1: return &fb_EqView->conn_ActualPosition.getValue();
      case 2: return &fb_EqView->conn_Homed.getValue();
      case 3: return &fb_EqView->conn_Moving.getValue();
      case 4: return &fb_EqView->conn_Holder.getValue();
    }
    return nullptr;
  }

  forte::ISocketPin *FORTE_EP_LinearAxis::getSocketPinUnchecked(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Skill;
    }
    return nullptr;
  }

  CEventConnection *FORTE_EP_LinearAxis::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_STATE;
    }
    return nullptr;
  }

  CDataConnection **FORTE_EP_LinearAxis::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Module;
    }
    return nullptr;
  }

  CDataConnection *FORTE_EP_LinearAxis::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_AtHome;
      case 1: return &conn_ActualPosition;
      case 2: return &conn_Homed;
      case 3: return &conn_Moving;
      case 4: return &conn_EqHolder;
    }
    return nullptr;
  }

  CDataConnection *FORTE_EP_LinearAxis::getIf2InConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module;
    }
    return nullptr;
  }

}