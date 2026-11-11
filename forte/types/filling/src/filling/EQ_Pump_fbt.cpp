/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: EQ_Pump
 *** Description: An equipment block: the only block that touches this equipment's pins. Skills send it what to switch over a local channel; it switches the outputs (off first, then on), reads the inputs every cycle and reports them to the skills and to OPC UA. One skill holds it at a time; on release or when the module aborts it switches everything off. Technical: Filling pump; none is wired yet, so it has no outputs and dispensing is a time at the station's flow rate; equipment IO: owns its IO points, writes the output values its holder sends, reads its inputs every cycle and reports changes
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/filling/EQ_Pump_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_wstring.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::filling {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:2In6NyBhnXhDLzbVpzTopWjUIY8WHu3kItpsHo7CfUdNtGOYamlshIzSaocalBNJaky1HIdhYBpww69bsvlp4A=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID};
    const auto cDataInputNames = std::array{"Module"_STRID, "Name"_STRID, "UaRoot"_STRID, "UaEnable"_STRID, "CycleTime"_STRID};

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
      {{}, "INIT"_STRID, "Logic"_STRID, "INIT"_STRID},
      {"Logic"_STRID, "INITO"_STRID, "Mode"_STRID, "INIT"_STRID},
      {"Mode"_STRID, "INITO"_STRID, "SubCmd"_STRID, "INIT"_STRID},
      {"SubCmd"_STRID, "INITO"_STRID, "SubRelease"_STRID, "INIT"_STRID},
      {"SubRelease"_STRID, "INITO"_STRID, "PubState"_STRID, "INIT"_STRID},
      {"PubState"_STRID, "INITO"_STRID, "Cycle"_STRID, "START"_STRID},
      {"PubState"_STRID, "INITO"_STRID, {}, "INITO"_STRID},
      {"SubCmd"_STRID, "IND"_STRID, "Logic"_STRID, "CMD"_STRID},
      {"SubRelease"_STRID, "IND"_STRID, "Logic"_STRID, "RELEASE"_STRID},
      {"Mode"_STRID, "CHG"_STRID, "Logic"_STRID, "MOD_CHG"_STRID},
      {"Cycle"_STRID, "EO"_STRID, "Logic"_STRID, "REFRESH"_STRID},
      {"Cycle"_STRID, "EO"_STRID, "Logic"_STRID, "SAMPLE"_STRID},
      {"Logic"_STRID, "STATE"_STRID, "PubState"_STRID, "REQ"_STRID},
      {"Logic"_STRID, "DRIVE"_STRID, "Logic"_STRID, "DRIVEN"_STRID},
    });

    const auto cDataConnections = std::to_array<SCFB_FBConnectionData>({
      {{}, "Module"_STRID, "Logic"_STRID, "Module"_STRID},
      {{}, "Name"_STRID, "Logic"_STRID, "Name"_STRID},
      {{}, "Module"_STRID, "Mode"_STRID, "Module"_STRID},
      {"Logic"_STRID, "IdCmd"_STRID, "SubCmd"_STRID, "ID"_STRID},
      {"Logic"_STRID, "IdRelease"_STRID, "SubRelease"_STRID, "ID"_STRID},
      {"Logic"_STRID, "IdState"_STRID, "PubState"_STRID, "ID"_STRID},
      {{}, "CycleTime"_STRID, "Cycle"_STRID, "DT"_STRID},
      {"SubCmd"_STRID, "RD_1"_STRID, "Logic"_STRID, "C_Holder"_STRID},
      {"SubCmd"_STRID, "RD_2"_STRID, "Logic"_STRID, "C_Release"_STRID},
      {"SubRelease"_STRID, "RD_1"_STRID, "Logic"_STRID, "R_Holder"_STRID},
      {"Mode"_STRID, "State"_STRID, "Logic"_STRID, "ModuleState"_STRID},
      {"Logic"_STRID, "Holder"_STRID, "PubState"_STRID, "SD_1"_STRID},
    });

    const SCFB_FBNData cFBNData = {
      .mEventConnections = cEventConnections,
      .mDataConnections = cDataConnections,
      .mAdapterConnections = {},
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_EQ_Pump, "filling::EQ_Pump"_STRID, TypeHash)

  FORTE_EQ_Pump::FORTE_EQ_Pump(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CCompositeFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cFBNData),
      fb_Logic("Logic"_STRID, *this),
      fb_Cycle("Cycle"_STRID, *this),
      fb_Mode("Mode"_STRID, *this),
      fb_SubCmd("SubCmd"_STRID, "iec61499::net::SUBSCRIBE_2", *this),
      fb_SubRelease("SubRelease"_STRID, "iec61499::net::SUBSCRIBE_1", *this),
      fb_PubState("PubState"_STRID, "iec61499::net::PUBLISH_1", *this),
      conn_INITO(*this, 0),
      conn_Module(nullptr),
      conn_Name(nullptr),
      conn_UaRoot(nullptr),
      conn_UaEnable(nullptr),
      conn_CycleTime(nullptr),
      conn_if2in_Module(*this, 0, u""_WSTRING),
      conn_if2in_Name(*this, 1, u"Pump"_WSTRING),
      conn_if2in_UaRoot(*this, 2, u""_WSTRING),
      conn_if2in_UaEnable(*this, 3, 0_BOOL),
      conn_if2in_CycleTime(*this, 4, 50000000_TIME) {
  };

  void FORTE_EQ_Pump::setInitialValues() {
    CCompositeFB::setInitialValues();
    conn_if2in_Module.getValue() = u""_WSTRING;
    conn_if2in_Name.getValue() = u"Pump"_WSTRING;
    conn_if2in_UaRoot.getValue() = u""_WSTRING;
    conn_if2in_UaEnable.getValue() = 0_BOOL;
    conn_if2in_CycleTime.getValue() = 50000000_TIME;
  }

  void FORTE_EQ_Pump::setFBNetworkInitialValues() {
    if (auto v = fb_SubCmd->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
    if (auto v = fb_SubRelease->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
    if (auto v = fb_PubState->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
  }

  void FORTE_EQ_Pump::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, conn_if2in_Module.getValue(), conn_Module);
        readData(1, conn_if2in_Name.getValue(), conn_Name);
        readData(2, conn_if2in_UaRoot.getValue(), conn_UaRoot);
        readData(3, conn_if2in_UaEnable.getValue(), conn_UaEnable);
        readData(4, conn_if2in_CycleTime.getValue(), conn_CycleTime);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_EQ_Pump::writeOutputData(TEventID) {
    // nothing to do
  }

  CIEC_ANY *FORTE_EQ_Pump::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module.getValue();
      case 1: return &conn_if2in_Name.getValue();
      case 2: return &conn_if2in_UaRoot.getValue();
      case 3: return &conn_if2in_UaEnable.getValue();
      case 4: return &conn_if2in_CycleTime.getValue();
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_EQ_Pump::getDO(size_t) {
    return nullptr;
  }

  CEventConnection *FORTE_EQ_Pump::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
    }
    return nullptr;
  }

  CDataConnection **FORTE_EQ_Pump::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Module;
      case 1: return &conn_Name;
      case 2: return &conn_UaRoot;
      case 3: return &conn_UaEnable;
      case 4: return &conn_CycleTime;
    }
    return nullptr;
  }

  CDataConnection *FORTE_EQ_Pump::getDOConUnchecked(TPortId) {
    return nullptr;
  }

  CDataConnection *FORTE_EQ_Pump::getIf2InConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module;
      case 1: return &conn_if2in_Name;
      case 2: return &conn_if2in_UaRoot;
      case 3: return &conn_if2in_UaEnable;
      case 4: return &conn_if2in_CycleTime;
    }
    return nullptr;
  }

}