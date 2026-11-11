/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: IO_DI
 *** Description: One digital input (a switch, a sensor). Its Address says where the signal is: a Raspberry Pi pin, a Modbus register, or simulated. It reads the value when asked. Technical: Digital input; Address: 'gpio[chip:line(:pull_up|:pull_down)(:active_low)]' or 'pwm[chip:channel:period_ns]' a Raspberry Pi's line, set up here; 'modbus[...]' a Modbus CLIENT ID; 'sim' simulated; another name a local IO handle set up elsewhere (IX PARAMS); empty: not connected (QO = FALSE)
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/IO_DI_fbt.h"

#include "forte/datatypes/forte_uint.h"
#include "forte/forte_st_util.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:pe6CO4y-OYzk2tJ2cKogPPvYtK5bjAFSATZN2uilhMLQh1OKpkjSV-Gi8RdYh0CmS5kj6J7Ge7ILOjJ-g-foIA=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "REQ"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "CNF"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"Address"_STRID, "SimValue"_STRID};
    const auto cDataOutputNames = std::array{"QO"_STRID, "IN"_STRID};

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
      {"Route"_STRID, "LineNo"_STRID, "Line"_STRID, "LineNumber"_STRID},
      {"Route"_STRID, "LineBias"_STRID, "Line"_STRID, "BiasMode"_STRID},
      {"Route"_STRID, "LineLow"_STRID, "Line"_STRID, "ActiveLow"_STRID},
      {{}, "Address"_STRID, "Route"_STRID, "Address"_STRID},
      {"Route"_STRID, "IoName"_STRID, "Local"_STRID, "PARAMS"_STRID},
      {"Route"_STRID, "ModbusId"_STRID, "Bus"_STRID, "ID"_STRID},
      {"Route"_STRID, "GQI"_STRID, "Local"_STRID, "QI"_STRID},
      {"Route"_STRID, "MQI"_STRID, "Bus"_STRID, "QI"_STRID},
      {"Local"_STRID, "QO"_STRID, "Route"_STRID, "QO_G"_STRID},
      {"Bus"_STRID, "QO"_STRID, "Route"_STRID, "QO_M"_STRID},
      {"Route"_STRID, "QO"_STRID, {}, "QO"_STRID},
      {{}, "SimValue"_STRID, "Route"_STRID, "SimValue"_STRID},
      {"Local"_STRID, "IN"_STRID, "Route"_STRID, "IN_G"_STRID},
      {"Bus"_STRID, "RD_1"_STRID, "Route"_STRID, "IN_M"_STRID},
      {"Route"_STRID, "IN"_STRID, {}, "IN"_STRID},
    });

    const SCFB_FBNData cFBNData = {
      .mEventConnections = cEventConnections,
      .mDataConnections = cDataConnections,
      .mAdapterConnections = {},
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_IO_DI, "modlib::IO_DI"_STRID, TypeHash)

  FORTE_IO_DI::FORTE_IO_DI(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CCompositeFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cFBNData),
      fb_Route("Route"_STRID, *this),
      fb_Line("Line"_STRID, *this),
      fb_Local("Local"_STRID, *this),
      fb_Bus("Bus"_STRID, "iec61499::net::CLIENT_0_1", *this),
      conn_INITO(*this, 0),
      conn_CNF(*this, 1),
      conn_Address(nullptr),
      conn_SimValue(nullptr),
      conn_QO(*this, 0, 0_BOOL),
      conn_IN(*this, 1, 0_BOOL),
      conn_if2in_Address(*this, 0, ""_STRING),
      conn_if2in_SimValue(*this, 1, 0_BOOL) {
  };

  void FORTE_IO_DI::setInitialValues() {
    CCompositeFB::setInitialValues();
    conn_if2in_Address.getValue() = ""_STRING;
    conn_if2in_SimValue.getValue() = 0_BOOL;
    fb_Route->conn_QO.getValue() = 0_BOOL;
    fb_Route->conn_IN.getValue() = 0_BOOL;
  }

  void FORTE_IO_DI::setFBNetworkInitialValues() {
    fb_Line->var_ReadWriteMode = 0_UINT;
  }

  void FORTE_IO_DI::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, conn_if2in_Address.getValue(), conn_Address);
        break;
      }
      case scmEventREQID: {
        readData(1, conn_if2in_SimValue.getValue(), conn_SimValue);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_IO_DI::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(2, fb_Route->conn_QO.getValue(), conn_QO);
        break;
      }
      case scmEventCNFID: {
        writeData(2, fb_Route->conn_QO.getValue(), conn_QO);
        writeData(3, fb_Route->conn_IN.getValue(), conn_IN);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_IO_DI::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Address.getValue();
      case 1: return &conn_if2in_SimValue.getValue();
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_IO_DI::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &fb_Route->conn_QO.getValue();
      case 1: return &fb_Route->conn_IN.getValue();
    }
    return nullptr;
  }

  CEventConnection *FORTE_IO_DI::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_CNF;
    }
    return nullptr;
  }

  CDataConnection **FORTE_IO_DI::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Address;
      case 1: return &conn_SimValue;
    }
    return nullptr;
  }

  CDataConnection *FORTE_IO_DI::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_QO;
      case 1: return &conn_IN;
    }
    return nullptr;
  }

  CDataConnection *FORTE_IO_DI::getIf2InConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Address;
      case 1: return &conn_if2in_SimValue;
    }
    return nullptr;
  }

}