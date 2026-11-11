/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: EQ_Scale
 *** Description: An equipment block: the only block that touches this equipment's pins. Skills send it what to switch over a local channel; it switches the outputs (off first, then on), reads the inputs every cycle and reports them to the skills and to OPC UA. One skill holds it at a time; on release or when the module aborts it switches everything off. Technical: Scale; the hardware has none, so the weight is simulated; equipment IO: owns its IO points, writes the output values its holder sends, reads its inputs every cycle and reports changes
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/filling/EQ_Scale_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_wstring.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::filling {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:CDfaObcJ9LezNoteyGJpoC-rllzuFm_uhobgCMaWi4almpbY56-XV-z5BhxMX7_ByJaulDc_r202FRsvBvJpCQ=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID};
    const auto cDataInputNames = std::array{"Module"_STRID, "Name"_STRID, "UaRoot"_STRID, "UaEnable"_STRID, "CycleTime"_STRID, "Weight_Address"_STRID, "Weight_Sim"_STRID, "Weight_Scale"_STRID};

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
      {"PubState"_STRID, "INITO"_STRID, "PubUa"_STRID, "INIT"_STRID},
      {"PubUa"_STRID, "INITO"_STRID, "In_Weight"_STRID, "INIT"_STRID},
      {"In_Weight"_STRID, "INITO"_STRID, "Cycle"_STRID, "START"_STRID},
      {"In_Weight"_STRID, "INITO"_STRID, {}, "INITO"_STRID},
      {"SubCmd"_STRID, "IND"_STRID, "Logic"_STRID, "CMD"_STRID},
      {"SubRelease"_STRID, "IND"_STRID, "Logic"_STRID, "RELEASE"_STRID},
      {"Mode"_STRID, "CHG"_STRID, "Logic"_STRID, "MOD_CHG"_STRID},
      {"Cycle"_STRID, "EO"_STRID, "Logic"_STRID, "REFRESH"_STRID},
      {"Cycle"_STRID, "EO"_STRID, "In_Weight"_STRID, "REQ"_STRID},
      {"In_Weight"_STRID, "CNF"_STRID, "Logic"_STRID, "SAMPLE"_STRID},
      {"Logic"_STRID, "STATE"_STRID, "PubState"_STRID, "REQ"_STRID},
      {"Logic"_STRID, "STATE"_STRID, "PubUa"_STRID, "REQ"_STRID},
      {"Logic"_STRID, "DRIVE"_STRID, "Logic"_STRID, "DRIVEN"_STRID},
    });

    const auto cDataConnections = std::to_array<SCFB_FBConnectionData>({
      {{}, "Module"_STRID, "Logic"_STRID, "Module"_STRID},
      {{}, "Name"_STRID, "Logic"_STRID, "Name"_STRID},
      {{}, "UaRoot"_STRID, "Logic"_STRID, "UaRoot"_STRID},
      {{}, "Module"_STRID, "Mode"_STRID, "Module"_STRID},
      {"Logic"_STRID, "IdCmd"_STRID, "SubCmd"_STRID, "ID"_STRID},
      {"Logic"_STRID, "IdRelease"_STRID, "SubRelease"_STRID, "ID"_STRID},
      {"Logic"_STRID, "IdState"_STRID, "PubState"_STRID, "ID"_STRID},
      {"Logic"_STRID, "IdPub"_STRID, "PubUa"_STRID, "ID"_STRID},
      {{}, "UaEnable"_STRID, "PubUa"_STRID, "QI"_STRID},
      {{}, "CycleTime"_STRID, "Cycle"_STRID, "DT"_STRID},
      {"SubCmd"_STRID, "RD_1"_STRID, "Logic"_STRID, "C_Holder"_STRID},
      {"SubCmd"_STRID, "RD_2"_STRID, "Logic"_STRID, "C_Release"_STRID},
      {"SubRelease"_STRID, "RD_1"_STRID, "Logic"_STRID, "R_Holder"_STRID},
      {"Mode"_STRID, "State"_STRID, "Logic"_STRID, "ModuleState"_STRID},
      {{}, "Weight_Address"_STRID, "In_Weight"_STRID, "Address"_STRID},
      {{}, "Weight_Sim"_STRID, "In_Weight"_STRID, "SimValue"_STRID},
      {{}, "Weight_Scale"_STRID, "In_Weight"_STRID, "Scale"_STRID},
      {"In_Weight"_STRID, "IN"_STRID, "Logic"_STRID, "I_Weight"_STRID},
      {"Logic"_STRID, "Weight"_STRID, "PubState"_STRID, "SD_1"_STRID},
      {"Logic"_STRID, "Weight"_STRID, "PubUa"_STRID, "SD_1"_STRID},
      {"Logic"_STRID, "Holder"_STRID, "PubState"_STRID, "SD_2"_STRID},
    });

    const SCFB_FBNData cFBNData = {
      .mEventConnections = cEventConnections,
      .mDataConnections = cDataConnections,
      .mAdapterConnections = {},
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_EQ_Scale, "filling::EQ_Scale"_STRID, TypeHash)

  FORTE_EQ_Scale::FORTE_EQ_Scale(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CCompositeFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cFBNData),
      fb_Logic("Logic"_STRID, *this),
      fb_Cycle("Cycle"_STRID, *this),
      fb_Mode("Mode"_STRID, *this),
      fb_SubCmd("SubCmd"_STRID, "iec61499::net::SUBSCRIBE_2", *this),
      fb_SubRelease("SubRelease"_STRID, "iec61499::net::SUBSCRIBE_1", *this),
      fb_PubState("PubState"_STRID, "iec61499::net::PUBLISH_2", *this),
      fb_PubUa("PubUa"_STRID, "iec61499::net::PUBLISH_1", *this),
      fb_In_Weight("In_Weight"_STRID, *this),
      conn_INITO(*this, 0),
      conn_Module(nullptr),
      conn_Name(nullptr),
      conn_UaRoot(nullptr),
      conn_UaEnable(nullptr),
      conn_CycleTime(nullptr),
      conn_Weight_Address(nullptr),
      conn_Weight_Sim(nullptr),
      conn_Weight_Scale(nullptr),
      conn_if2in_Module(*this, 0, u""_WSTRING),
      conn_if2in_Name(*this, 1, u"Scale"_WSTRING),
      conn_if2in_UaRoot(*this, 2, u""_WSTRING),
      conn_if2in_UaEnable(*this, 3, 0_BOOL),
      conn_if2in_CycleTime(*this, 4, 50000000_TIME),
      conn_if2in_Weight_Address(*this, 5, ""_STRING),
      conn_if2in_Weight_Sim(*this, 6, 2.0_LREAL),
      conn_if2in_Weight_Scale(*this, 7, 0.001_LREAL) {
  };

  void FORTE_EQ_Scale::setInitialValues() {
    CCompositeFB::setInitialValues();
    conn_if2in_Module.getValue() = u""_WSTRING;
    conn_if2in_Name.getValue() = u"Scale"_WSTRING;
    conn_if2in_UaRoot.getValue() = u""_WSTRING;
    conn_if2in_UaEnable.getValue() = 0_BOOL;
    conn_if2in_CycleTime.getValue() = 50000000_TIME;
    conn_if2in_Weight_Address.getValue() = ""_STRING;
    conn_if2in_Weight_Sim.getValue() = 2.0_LREAL;
    conn_if2in_Weight_Scale.getValue() = 0.001_LREAL;
  }

  void FORTE_EQ_Scale::setFBNetworkInitialValues() {
    if (auto v = fb_SubCmd->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
    if (auto v = fb_SubRelease->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
    if (auto v = fb_PubState->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
  }

  void FORTE_EQ_Scale::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, conn_if2in_Module.getValue(), conn_Module);
        readData(1, conn_if2in_Name.getValue(), conn_Name);
        readData(2, conn_if2in_UaRoot.getValue(), conn_UaRoot);
        readData(3, conn_if2in_UaEnable.getValue(), conn_UaEnable);
        readData(4, conn_if2in_CycleTime.getValue(), conn_CycleTime);
        readData(5, conn_if2in_Weight_Address.getValue(), conn_Weight_Address);
        readData(6, conn_if2in_Weight_Sim.getValue(), conn_Weight_Sim);
        readData(7, conn_if2in_Weight_Scale.getValue(), conn_Weight_Scale);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_EQ_Scale::writeOutputData(TEventID) {
    // nothing to do
  }

  CIEC_ANY *FORTE_EQ_Scale::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module.getValue();
      case 1: return &conn_if2in_Name.getValue();
      case 2: return &conn_if2in_UaRoot.getValue();
      case 3: return &conn_if2in_UaEnable.getValue();
      case 4: return &conn_if2in_CycleTime.getValue();
      case 5: return &conn_if2in_Weight_Address.getValue();
      case 6: return &conn_if2in_Weight_Sim.getValue();
      case 7: return &conn_if2in_Weight_Scale.getValue();
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_EQ_Scale::getDO(size_t) {
    return nullptr;
  }

  CEventConnection *FORTE_EQ_Scale::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
    }
    return nullptr;
  }

  CDataConnection **FORTE_EQ_Scale::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Module;
      case 1: return &conn_Name;
      case 2: return &conn_UaRoot;
      case 3: return &conn_UaEnable;
      case 4: return &conn_CycleTime;
      case 5: return &conn_Weight_Address;
      case 6: return &conn_Weight_Sim;
      case 7: return &conn_Weight_Scale;
    }
    return nullptr;
  }

  CDataConnection *FORTE_EQ_Scale::getDOConUnchecked(TPortId) {
    return nullptr;
  }

  CDataConnection *FORTE_EQ_Scale::getIf2InConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module;
      case 1: return &conn_if2in_Name;
      case 2: return &conn_if2in_UaRoot;
      case 3: return &conn_if2in_UaEnable;
      case 4: return &conn_if2in_CycleTime;
      case 5: return &conn_if2in_Weight_Address;
      case 6: return &conn_if2in_Weight_Sim;
      case 7: return &conn_if2in_Weight_Scale;
    }
    return nullptr;
  }

}