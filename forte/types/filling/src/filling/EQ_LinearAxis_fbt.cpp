/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: EQ_LinearAxis
 *** Description: An equipment block: the only block that touches this equipment's pins. Skills send it what to switch over a local channel; it switches the outputs (off first, then on), reads the inputs every cycle and reports them to the skills and to OPC UA. One skill holds it at a time; on release or when the module aborts it switches everything off. Technical: Needle lift, a stepper motor through a step and direction driver, with a limit switch at the top (home); equipment IO: owns its IO points, writes the output values its holder sends, reads its inputs every cycle and reports changes
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/filling/EQ_LinearAxis_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_wstring.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::filling {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:KYhXdUNm31m1xy1ldJ-eHcK2NViVz37wgSrtO_hok64zty-rzQhtWaZTNh73qp_fY6tpyhU6TsOTWAmJRFI6TQ=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID};
    const auto cDataInputNames = std::array{"Module"_STRID, "Name"_STRID, "UaRoot"_STRID, "UaEnable"_STRID, "CycleTime"_STRID, "AtHome_Address"_STRID, "AtHome_Sim"_STRID, "Enable_Address"_STRID, "Down_Address"_STRID, "Step_Address"_STRID, "Step_Gain"_STRID, "Step_Bias"_STRID};

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
      {"Logic"_STRID, "MOVE_START"_STRID, "MoveT"_STRID, "START"_STRID},
      {"Logic"_STRID, "MOVE_STOP"_STRID, "MoveT"_STRID, "STOP"_STRID},
      {"MoveT"_STRID, "EO"_STRID, "Logic"_STRID, "MOVE_T"_STRID},
      {{}, "INIT"_STRID, "Logic"_STRID, "INIT"_STRID},
      {"Logic"_STRID, "INITO"_STRID, "Mode"_STRID, "INIT"_STRID},
      {"Mode"_STRID, "INITO"_STRID, "SubCmd"_STRID, "INIT"_STRID},
      {"SubCmd"_STRID, "INITO"_STRID, "SubRelease"_STRID, "INIT"_STRID},
      {"SubRelease"_STRID, "INITO"_STRID, "PubState"_STRID, "INIT"_STRID},
      {"PubState"_STRID, "INITO"_STRID, "PubUa"_STRID, "INIT"_STRID},
      {"PubUa"_STRID, "INITO"_STRID, "In_AtHome"_STRID, "INIT"_STRID},
      {"In_AtHome"_STRID, "INITO"_STRID, "Out_Enable"_STRID, "INIT"_STRID},
      {"Out_Enable"_STRID, "INITO"_STRID, "Out_Down"_STRID, "INIT"_STRID},
      {"Out_Down"_STRID, "INITO"_STRID, "Out_Step"_STRID, "INIT"_STRID},
      {"Out_Step"_STRID, "INITO"_STRID, "Cycle"_STRID, "START"_STRID},
      {"Out_Step"_STRID, "INITO"_STRID, {}, "INITO"_STRID},
      {"SubCmd"_STRID, "IND"_STRID, "Logic"_STRID, "CMD"_STRID},
      {"SubRelease"_STRID, "IND"_STRID, "Logic"_STRID, "RELEASE"_STRID},
      {"Mode"_STRID, "CHG"_STRID, "Logic"_STRID, "MOD_CHG"_STRID},
      {"Cycle"_STRID, "EO"_STRID, "Logic"_STRID, "REFRESH"_STRID},
      {"Cycle"_STRID, "EO"_STRID, "In_AtHome"_STRID, "REQ"_STRID},
      {"In_AtHome"_STRID, "CNF"_STRID, "Logic"_STRID, "SAMPLE"_STRID},
      {"Logic"_STRID, "STATE"_STRID, "PubState"_STRID, "REQ"_STRID},
      {"Logic"_STRID, "STATE"_STRID, "PubUa"_STRID, "REQ"_STRID},
      {"Logic"_STRID, "DRIVE"_STRID, "Out_Enable"_STRID, "REQ"_STRID},
      {"Out_Enable"_STRID, "CNF"_STRID, "Out_Down"_STRID, "REQ"_STRID},
      {"Out_Down"_STRID, "CNF"_STRID, "Out_Step"_STRID, "REQ"_STRID},
      {"Out_Step"_STRID, "CNF"_STRID, "Logic"_STRID, "DRIVEN"_STRID},
    });

    const auto cDataConnections = std::to_array<SCFB_FBConnectionData>({
      {"Logic"_STRID, "MoveDT"_STRID, "MoveT"_STRID, "DT"_STRID},
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
      {"SubCmd"_STRID, "RD_3"_STRID, "Logic"_STRID, "C_Enable"_STRID},
      {"SubCmd"_STRID, "RD_4"_STRID, "Logic"_STRID, "C_Down"_STRID},
      {"SubCmd"_STRID, "RD_5"_STRID, "Logic"_STRID, "C_Step"_STRID},
      {"SubCmd"_STRID, "RD_6"_STRID, "Logic"_STRID, "CE_Step"_STRID},
      {"SubCmd"_STRID, "RD_7"_STRID, "Logic"_STRID, "C_Move"_STRID},
      {"SubCmd"_STRID, "RD_8"_STRID, "Logic"_STRID, "C_Goal"_STRID},
      {"SubRelease"_STRID, "RD_1"_STRID, "Logic"_STRID, "R_Holder"_STRID},
      {"Mode"_STRID, "State"_STRID, "Logic"_STRID, "ModuleState"_STRID},
      {{}, "AtHome_Address"_STRID, "In_AtHome"_STRID, "Address"_STRID},
      {{}, "AtHome_Sim"_STRID, "In_AtHome"_STRID, "SimValue"_STRID},
      {"In_AtHome"_STRID, "IN"_STRID, "Logic"_STRID, "I_AtHome"_STRID},
      {"Logic"_STRID, "AtHome"_STRID, "PubState"_STRID, "SD_1"_STRID},
      {"Logic"_STRID, "AtHome"_STRID, "PubUa"_STRID, "SD_1"_STRID},
      {"Logic"_STRID, "ActualPosition"_STRID, "PubState"_STRID, "SD_2"_STRID},
      {"Logic"_STRID, "ActualPosition"_STRID, "PubUa"_STRID, "SD_2"_STRID},
      {"Logic"_STRID, "Homed"_STRID, "PubState"_STRID, "SD_3"_STRID},
      {"Logic"_STRID, "Homed"_STRID, "PubUa"_STRID, "SD_3"_STRID},
      {"Logic"_STRID, "Moving"_STRID, "PubState"_STRID, "SD_4"_STRID},
      {"Logic"_STRID, "Moving"_STRID, "PubUa"_STRID, "SD_4"_STRID},
      {"Logic"_STRID, "Holder"_STRID, "PubState"_STRID, "SD_5"_STRID},
      {{}, "Enable_Address"_STRID, "Out_Enable"_STRID, "Address"_STRID},
      {"Logic"_STRID, "O_Enable"_STRID, "Out_Enable"_STRID, "OUT"_STRID},
      {{}, "Down_Address"_STRID, "Out_Down"_STRID, "Address"_STRID},
      {"Logic"_STRID, "O_Down"_STRID, "Out_Down"_STRID, "OUT"_STRID},
      {{}, "Step_Address"_STRID, "Out_Step"_STRID, "Address"_STRID},
      {"Logic"_STRID, "O_Step"_STRID, "Out_Step"_STRID, "OUT"_STRID},
      {"Logic"_STRID, "E_Step"_STRID, "Out_Step"_STRID, "EN"_STRID},
      {{}, "Step_Gain"_STRID, "Out_Step"_STRID, "Gain"_STRID},
      {{}, "Step_Bias"_STRID, "Out_Step"_STRID, "Bias"_STRID},
    });

    const SCFB_FBNData cFBNData = {
      .mEventConnections = cEventConnections,
      .mDataConnections = cDataConnections,
      .mAdapterConnections = {},
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_EQ_LinearAxis, "filling::EQ_LinearAxis"_STRID, TypeHash)

  FORTE_EQ_LinearAxis::FORTE_EQ_LinearAxis(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CCompositeFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cFBNData),
      fb_Logic("Logic"_STRID, *this),
      fb_Cycle("Cycle"_STRID, *this),
      fb_MoveT("MoveT"_STRID, *this),
      fb_Mode("Mode"_STRID, *this),
      fb_SubCmd("SubCmd"_STRID, "iec61499::net::SUBSCRIBE_8", *this),
      fb_SubRelease("SubRelease"_STRID, "iec61499::net::SUBSCRIBE_1", *this),
      fb_PubState("PubState"_STRID, "iec61499::net::PUBLISH_5", *this),
      fb_PubUa("PubUa"_STRID, "iec61499::net::PUBLISH_4", *this),
      fb_In_AtHome("In_AtHome"_STRID, *this),
      fb_Out_Enable("Out_Enable"_STRID, *this),
      fb_Out_Down("Out_Down"_STRID, *this),
      fb_Out_Step("Out_Step"_STRID, *this),
      conn_INITO(*this, 0),
      conn_Module(nullptr),
      conn_Name(nullptr),
      conn_UaRoot(nullptr),
      conn_UaEnable(nullptr),
      conn_CycleTime(nullptr),
      conn_AtHome_Address(nullptr),
      conn_AtHome_Sim(nullptr),
      conn_Enable_Address(nullptr),
      conn_Down_Address(nullptr),
      conn_Step_Address(nullptr),
      conn_Step_Gain(nullptr),
      conn_Step_Bias(nullptr),
      conn_if2in_Module(*this, 0, u""_WSTRING),
      conn_if2in_Name(*this, 1, u"LinearAxis"_WSTRING),
      conn_if2in_UaRoot(*this, 2, u""_WSTRING),
      conn_if2in_UaEnable(*this, 3, 0_BOOL),
      conn_if2in_CycleTime(*this, 4, 50000000_TIME),
      conn_if2in_AtHome_Address(*this, 5, ""_STRING),
      conn_if2in_AtHome_Sim(*this, 6, false_BOOL),
      conn_if2in_Enable_Address(*this, 7, ""_STRING),
      conn_if2in_Down_Address(*this, 8, ""_STRING),
      conn_if2in_Step_Address(*this, 9, ""_STRING),
      conn_if2in_Step_Gain(*this, 10, 655.35_LREAL),
      conn_if2in_Step_Bias(*this, 11, 0.0_LREAL) {
  };

  void FORTE_EQ_LinearAxis::setInitialValues() {
    CCompositeFB::setInitialValues();
    conn_if2in_Module.getValue() = u""_WSTRING;
    conn_if2in_Name.getValue() = u"LinearAxis"_WSTRING;
    conn_if2in_UaRoot.getValue() = u""_WSTRING;
    conn_if2in_UaEnable.getValue() = 0_BOOL;
    conn_if2in_CycleTime.getValue() = 50000000_TIME;
    conn_if2in_AtHome_Address.getValue() = ""_STRING;
    conn_if2in_AtHome_Sim.getValue() = false_BOOL;
    conn_if2in_Enable_Address.getValue() = ""_STRING;
    conn_if2in_Down_Address.getValue() = ""_STRING;
    conn_if2in_Step_Address.getValue() = ""_STRING;
    conn_if2in_Step_Gain.getValue() = 655.35_LREAL;
    conn_if2in_Step_Bias.getValue() = 0.0_LREAL;
  }

  void FORTE_EQ_LinearAxis::setFBNetworkInitialValues() {
    if (auto v = fb_SubCmd->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
    if (auto v = fb_SubRelease->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
    if (auto v = fb_PubState->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
  }

  void FORTE_EQ_LinearAxis::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, conn_if2in_Module.getValue(), conn_Module);
        readData(1, conn_if2in_Name.getValue(), conn_Name);
        readData(2, conn_if2in_UaRoot.getValue(), conn_UaRoot);
        readData(3, conn_if2in_UaEnable.getValue(), conn_UaEnable);
        readData(4, conn_if2in_CycleTime.getValue(), conn_CycleTime);
        readData(5, conn_if2in_AtHome_Address.getValue(), conn_AtHome_Address);
        readData(6, conn_if2in_AtHome_Sim.getValue(), conn_AtHome_Sim);
        readData(7, conn_if2in_Enable_Address.getValue(), conn_Enable_Address);
        readData(8, conn_if2in_Down_Address.getValue(), conn_Down_Address);
        readData(9, conn_if2in_Step_Address.getValue(), conn_Step_Address);
        readData(10, conn_if2in_Step_Gain.getValue(), conn_Step_Gain);
        readData(11, conn_if2in_Step_Bias.getValue(), conn_Step_Bias);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_EQ_LinearAxis::writeOutputData(TEventID) {
    // nothing to do
  }

  CIEC_ANY *FORTE_EQ_LinearAxis::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module.getValue();
      case 1: return &conn_if2in_Name.getValue();
      case 2: return &conn_if2in_UaRoot.getValue();
      case 3: return &conn_if2in_UaEnable.getValue();
      case 4: return &conn_if2in_CycleTime.getValue();
      case 5: return &conn_if2in_AtHome_Address.getValue();
      case 6: return &conn_if2in_AtHome_Sim.getValue();
      case 7: return &conn_if2in_Enable_Address.getValue();
      case 8: return &conn_if2in_Down_Address.getValue();
      case 9: return &conn_if2in_Step_Address.getValue();
      case 10: return &conn_if2in_Step_Gain.getValue();
      case 11: return &conn_if2in_Step_Bias.getValue();
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_EQ_LinearAxis::getDO(size_t) {
    return nullptr;
  }

  CEventConnection *FORTE_EQ_LinearAxis::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
    }
    return nullptr;
  }

  CDataConnection **FORTE_EQ_LinearAxis::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Module;
      case 1: return &conn_Name;
      case 2: return &conn_UaRoot;
      case 3: return &conn_UaEnable;
      case 4: return &conn_CycleTime;
      case 5: return &conn_AtHome_Address;
      case 6: return &conn_AtHome_Sim;
      case 7: return &conn_Enable_Address;
      case 8: return &conn_Down_Address;
      case 9: return &conn_Step_Address;
      case 10: return &conn_Step_Gain;
      case 11: return &conn_Step_Bias;
    }
    return nullptr;
  }

  CDataConnection *FORTE_EQ_LinearAxis::getDOConUnchecked(TPortId) {
    return nullptr;
  }

  CDataConnection *FORTE_EQ_LinearAxis::getIf2InConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module;
      case 1: return &conn_if2in_Name;
      case 2: return &conn_if2in_UaRoot;
      case 3: return &conn_if2in_UaEnable;
      case 4: return &conn_if2in_CycleTime;
      case 5: return &conn_if2in_AtHome_Address;
      case 6: return &conn_if2in_AtHome_Sim;
      case 7: return &conn_if2in_Enable_Address;
      case 8: return &conn_if2in_Down_Address;
      case 9: return &conn_if2in_Step_Address;
      case 10: return &conn_if2in_Step_Gain;
      case 11: return &conn_if2in_Step_Bias;
    }
    return nullptr;
  }

}