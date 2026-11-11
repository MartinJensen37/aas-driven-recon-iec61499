/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: EP_Scale
 *** Description: The equipment as its skills see it, the same in every skill that uses it: plays a command (its output values, phase by phase) on the equipment's command channel, and gives the equipment's newest state. Technical: Scale as its skills see it: a command on the socket Skill (AEquipment: SEND, PLAYED when all phases are out) goes out on its command channel; STATE gives its inputs and holder
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/filling/EP_Scale_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/forte_st_util.h"
#include "forte/modlib/AEquipment_adp.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::filling {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:4qv2XLFHtwqfm2MutVGgRiDNSg4dJcy2grOt5E7V6IH9TbSiqcOOlqKzvNBIzeHW23lQVOXU-32p_z_sdn7ZrQ=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "STATE"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"Module"_STRID};
    const auto cDataOutputNames = std::array{"Weight"_STRID, "EqHolder"_STRID};
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
      {"EqState"_STRID, "RD_1"_STRID, "EqView"_STRID, "I_Weight"_STRID},
      {"EqState"_STRID, "RD_2"_STRID, "EqView"_STRID, "I_Holder"_STRID},
      {"EqView"_STRID, "Weight"_STRID, {}, "Weight"_STRID},
      {"EqView"_STRID, "Holder"_STRID, {}, "EqHolder"_STRID},
      {"Skill"_STRID, "Holder"_STRID, "Driver"_STRID, "Holder"_STRID},
      {"Skill"_STRID, "Command"_STRID, "Driver"_STRID, "Command"_STRID},
      {"Skill"_STRID, "Release"_STRID, "Driver"_STRID, "Release"_STRID},
      {"Driver"_STRID, "O_Holder"_STRID, "EqCmd"_STRID, "SD_1"_STRID},
      {"Driver"_STRID, "O_Release"_STRID, "EqCmd"_STRID, "SD_2"_STRID},
      {"Driver"_STRID, "PhaseDT"_STRID, "PhaseT"_STRID, "DT"_STRID},
    });

    const SCFB_FBNData cFBNData = {
      .mEventConnections = cEventConnections,
      .mDataConnections = cDataConnections,
      .mAdapterConnections = {},
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_EP_Scale, "filling::EP_Scale"_STRID, TypeHash)

  FORTE_EP_Scale::FORTE_EP_Scale(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CCompositeFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cFBNData),
      fb_EqView("EqView"_STRID, *this),
      fb_EqState("EqState"_STRID, "iec61499::net::SUBSCRIBE_2", *this),
      fb_Driver("Driver"_STRID, *this),
      fb_PhaseT("PhaseT"_STRID, *this),
      fb_EqCmd("EqCmd"_STRID, "iec61499::net::PUBLISH_2", *this),
      var_Skill("Skill"_STRID, *this, forte::cgCFBParentAdapterlistIDMarker),
      conn_INITO(*this, 0),
      conn_STATE(*this, 1),
      conn_Module(nullptr),
      conn_Weight(*this, 0, 0_LREAL),
      conn_EqHolder(*this, 1, u""_WSTRING),
      conn_if2in_Module(*this, 0, u""_WSTRING) {
  };

  void FORTE_EP_Scale::setInitialValues() {
    CCompositeFB::setInitialValues();
    conn_if2in_Module.getValue() = u""_WSTRING;
    fb_EqView->conn_Weight.getValue() = 0_LREAL;
    fb_EqView->conn_Holder.getValue() = u""_WSTRING;
  }

  void FORTE_EP_Scale::setFBNetworkInitialValues() {
    if (auto v = fb_EqState->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
    if (auto v = fb_EqCmd->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
  }

  void FORTE_EP_Scale::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, conn_if2in_Module.getValue(), conn_Module);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_EP_Scale::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventSTATEID: {
        writeData(1, fb_EqView->conn_Weight.getValue(), conn_Weight);
        writeData(2, fb_EqView->conn_Holder.getValue(), conn_EqHolder);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_EP_Scale::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module.getValue();
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_EP_Scale::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &fb_EqView->conn_Weight.getValue();
      case 1: return &fb_EqView->conn_Holder.getValue();
    }
    return nullptr;
  }

  forte::ISocketPin *FORTE_EP_Scale::getSocketPinUnchecked(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Skill;
    }
    return nullptr;
  }

  CEventConnection *FORTE_EP_Scale::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_STATE;
    }
    return nullptr;
  }

  CDataConnection **FORTE_EP_Scale::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Module;
    }
    return nullptr;
  }

  CDataConnection *FORTE_EP_Scale::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Weight;
      case 1: return &conn_EqHolder;
    }
    return nullptr;
  }

  CDataConnection *FORTE_EP_Scale::getIf2InConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module;
    }
    return nullptr;
  }

}