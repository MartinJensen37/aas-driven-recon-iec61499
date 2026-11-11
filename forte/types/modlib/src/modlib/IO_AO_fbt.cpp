/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: IO_AO
 *** Description: One analog output, also a PWM channel (the step pulses of a stepper motor, a motor's speed). Its Address says where it goes: a Raspberry Pi PWM channel, a Modbus register, or simulated. Technical: Analog output (raw = Bias + OUT * Gain, 0..65535; EN = FALSE writes 0); Address: 'gpio[chip:line(:pull_up|:pull_down)(:active_low)]' or 'pwm[chip:channel:period_ns]' a Raspberry Pi's line, set up here; 'modbus[...]' a Modbus CLIENT ID; 'sim' simulated; another name a local IO handle set up elsewhere (QW PARAMS); empty: not connected (QO = FALSE)
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/IO_AO_fbt.h"

#include "forte/datatypes/forte_lreal.h"
#include "forte/forte_st_util.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:IoJHWVbcgJoH_taLxR_jvhOXFHjhOKX2w678tZp_XzGHumAM-c-Y53U0Uk7C-i9nrcQx09ZQ4lgjF4WfAe3OSQ=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "REQ"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "CNF"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"Address"_STRID, "OUT"_STRID, "EN"_STRID, "Gain"_STRID, "Bias"_STRID};
    const auto cDataOutputNames = std::array{"QO"_STRID};

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
      {{}, "INIT"_STRID, "Route"_STRID, "INIT"_STRID},
      {"Route"_STRID, "INIT_IO"_STRID, "Line"_STRID, "INIT"_STRID},
      {"Line"_STRID, "INITO"_STRID, "Local"_STRID, "INIT"_STRID},
      {"Local"_STRID, "INITO"_STRID, "Bus"_STRID, "INIT"_STRID},
      {"Bus"_STRID, "INITO"_STRID, "Route"_STRID, "IO_READY"_STRID},
      {"Route"_STRID, "INITO"_STRID, {}, "INITO"_STRID},
      {{}, "REQ"_STRID, "Route"_STRID, "REQ"_STRID},
      {"Route"_STRID, "REQ_G"_STRID, "Local"_STRID, "REQ"_STRID},
      {"Route"_STRID, "REQ_M"_STRID, "Bus"_STRID, "REQ"_STRID},
      {"Local"_STRID, "CNF"_STRID, "Route"_STRID, "CNF_G"_STRID},
      {"Bus"_STRID, "CNF"_STRID, "Route"_STRID, "CNF_M"_STRID},
      {"Route"_STRID, "CNF"_STRID, {}, "CNF"_STRID},
    });

    const auto cDataConnections = std::to_array<SCFB_FBConnectionData>({
      {"Route"_STRID, "LineQI"_STRID, "Line"_STRID, "QI"_STRID},
      {"Route"_STRID, "LineName"_STRID, "Line"_STRID, "VALUE"_STRID},
      {"Route"_STRID, "ChipNo"_STRID, "Line"_STRID, "ChipNumber"_STRID},
      {"Route"_STRID, "LineNo"_STRID, "Line"_STRID, "Channel"_STRID},
      {"Route"_STRID, "Period"_STRID, "Line"_STRID, "PeriodNs"_STRID},
      {"Route"_STRID, "Root"_STRID, "Line"_STRID, "SysfsRoot"_STRID},
      {{}, "Address"_STRID, "Route"_STRID, "Address"_STRID},
      {"Route"_STRID, "IoName"_STRID, "Local"_STRID, "PARAMS"_STRID},
      {"Route"_STRID, "ModbusId"_STRID, "Bus"_STRID, "ID"_STRID},
      {"Route"_STRID, "GQI"_STRID, "Local"_STRID, "QI"_STRID},
      {"Route"_STRID, "MQI"_STRID, "Bus"_STRID, "QI"_STRID},
      {"Local"_STRID, "QO"_STRID, "Route"_STRID, "QO_G"_STRID},
      {"Bus"_STRID, "QO"_STRID, "Route"_STRID, "QO_M"_STRID},
      {"Route"_STRID, "QO"_STRID, {}, "QO"_STRID},
      {{}, "OUT"_STRID, "Route"_STRID, "OUT"_STRID},
      {{}, "EN"_STRID, "Route"_STRID, "EN"_STRID},
      {{}, "Gain"_STRID, "Route"_STRID, "Gain"_STRID},
      {{}, "Bias"_STRID, "Route"_STRID, "Bias"_STRID},
      {"Route"_STRID, "Value"_STRID, "Local"_STRID, "OUT"_STRID},
      {"Route"_STRID, "Value"_STRID, "Bus"_STRID, "SD_1"_STRID},
    });

    const SCFB_FBNData cFBNData = {
      .mEventConnections = cEventConnections,
      .mDataConnections = cDataConnections,
      .mAdapterConnections = {},
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_IO_AO, "modlib::IO_AO"_STRID, TypeHash)

  FORTE_IO_AO::FORTE_IO_AO(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CCompositeFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cFBNData),
      fb_Route("Route"_STRID, *this),
      fb_Line("Line"_STRID, *this),
      fb_Local("Local"_STRID, *this),
      fb_Bus("Bus"_STRID, "iec61499::net::CLIENT_1_0", *this),
      conn_INITO(*this, 0),
      conn_CNF(*this, 1),
      conn_Address(nullptr),
      conn_OUT(nullptr),
      conn_EN(nullptr),
      conn_Gain(nullptr),
      conn_Bias(nullptr),
      conn_QO(*this, 0, 0_BOOL),
      conn_if2in_Address(*this, 0, ""_STRING),
      conn_if2in_OUT(*this, 1, 0_LREAL),
      conn_if2in_EN(*this, 2, 0_BOOL),
      conn_if2in_Gain(*this, 3, 1.0_LREAL),
      conn_if2in_Bias(*this, 4, 0_LREAL) {
  };

  void FORTE_IO_AO::setInitialValues() {
    CCompositeFB::setInitialValues();
    conn_if2in_Address.getValue() = ""_STRING;
    conn_if2in_OUT.getValue() = 0_LREAL;
    conn_if2in_EN.getValue() = 0_BOOL;
    conn_if2in_Gain.getValue() = 1.0_LREAL;
    conn_if2in_Bias.getValue() = 0_LREAL;
    fb_Route->conn_QO.getValue() = 0_BOOL;
  }

  void FORTE_IO_AO::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, conn_if2in_Address.getValue(), conn_Address);
        break;
      }
      case scmEventREQID: {
        readData(1, conn_if2in_OUT.getValue(), conn_OUT);
        readData(2, conn_if2in_EN.getValue(), conn_EN);
        readData(3, conn_if2in_Gain.getValue(), conn_Gain);
        readData(4, conn_if2in_Bias.getValue(), conn_Bias);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_IO_AO::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(5, fb_Route->conn_QO.getValue(), conn_QO);
        break;
      }
      case scmEventCNFID: {
        writeData(5, fb_Route->conn_QO.getValue(), conn_QO);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_IO_AO::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Address.getValue();
      case 1: return &conn_if2in_OUT.getValue();
      case 2: return &conn_if2in_EN.getValue();
      case 3: return &conn_if2in_Gain.getValue();
      case 4: return &conn_if2in_Bias.getValue();
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_IO_AO::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &fb_Route->conn_QO.getValue();
    }
    return nullptr;
  }

  CEventConnection *FORTE_IO_AO::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_CNF;
    }
    return nullptr;
  }

  CDataConnection **FORTE_IO_AO::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Address;
      case 1: return &conn_OUT;
      case 2: return &conn_EN;
      case 3: return &conn_Gain;
      case 4: return &conn_Bias;
    }
    return nullptr;
  }

  CDataConnection *FORTE_IO_AO::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_QO;
    }
    return nullptr;
  }

  CDataConnection *FORTE_IO_AO::getIf2InConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Address;
      case 1: return &conn_if2in_OUT;
      case 2: return &conn_if2in_EN;
      case 3: return &conn_if2in_Gain;
      case 4: return &conn_if2in_Bias;
    }
    return nullptr;
  }

}