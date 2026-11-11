/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SK_MoveAxis
 *** Description: A skill primitive: one action of one piece of equipment (move the axis, run the pump, weigh). It can be called on its own over OPC UA, or be a step of a bigger skill. Inside: SKILL_Core (state machine and OPC UA methods), a parameter block per parameter, SC_ (its contract: what this skill does and when it is done), SKILL_Run (one run, the same for every primitive) and EP_ (the equipment as the skill sees it). Technical: Skill primitive MoveAxis: Needle to Position, measured down from the limit switch; the direction follows from where it is (parameters: Position [mm] 0.0..60.0, default 0.0). OPC UA Start(Session, parameters...)/Stop/Abort/Reset(Session) -> [Accepted, ErrorID]; START/HALT/ABORT/RESET from a parent -> SUCCESS or FAILURE(ErrorID)
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/filling/SK_MoveAxis_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_time.h"
#include "forte/forte_st_util.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::filling {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:ZCHmy1XOGewh2e3rkDMt5AM9ZvgsN5qkT0HtK5dXcI7o-BvLZoNIpyhJmKbTiGM93LVlZGa44VBORi3N4tPzAw=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "START"_STRID, "HALT"_STRID, "ABORT"_STRID, "RESET"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "SUCCESS"_STRID, "FAILURE"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"Module"_STRID, "UaRoot"_STRID, "UaPath"_STRID, "UaEnable"_STRID, "Methods"_STRID, "Holder"_STRID, "ReleaseAfter"_STRID, "Timeout"_STRID, "Position"_STRID};
    const auto cDataOutputNames = std::array{"State"_STRID, "ErrorID"_STRID};

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
      {"Control"_STRID, "START_RSP"_STRID, "UaStart"_STRID, "RSP"_STRID},
      {"UaStart"_STRID, "IND"_STRID, "Par_Position"_STRID, "CHECK"_STRID},
      {"Control"_STRID, "RUN"_STRID, "Par_Position"_STRID, "LATCH"_STRID},
      {"Par_Position"_STRID, "CHECKED"_STRID, "Control"_STRID, "START_REQ"_STRID},
      {"Par_Position"_STRID, "LATCHED"_STRID, "PubParams"_STRID, "REQ"_STRID},
      {"PubParams"_STRID, "INITO"_STRID, "PubParams"_STRID, "REQ"_STRID},
      {{}, "INIT"_STRID, "Control"_STRID, "INIT"_STRID},
      {"Control"_STRID, "INITO"_STRID, "Contract"_STRID, "INIT"_STRID},
      {"Contract"_STRID, "INITO"_STRID, "UaStart"_STRID, "INIT"_STRID},
      {"UaStart"_STRID, "INITO"_STRID, "Par_Position"_STRID, "INIT"_STRID},
      {"Par_Position"_STRID, "INITO"_STRID, "PubParams"_STRID, "INIT"_STRID},
      {"PubParams"_STRID, "INITO"_STRID, "Run"_STRID, "INIT"_STRID},
      {"Run"_STRID, "INITO"_STRID, "Port"_STRID, "INIT"_STRID},
      {"Port"_STRID, "INITO"_STRID, {}, "INITO"_STRID},
      {{}, "START"_STRID, "Control"_STRID, "START"_STRID},
      {{}, "HALT"_STRID, "Control"_STRID, "HALT"_STRID},
      {{}, "ABORT"_STRID, "Control"_STRID, "ABORT"_STRID},
      {{}, "RESET"_STRID, "Control"_STRID, "RESET"_STRID},
      {"Control"_STRID, "SUCCESS"_STRID, {}, "SUCCESS"_STRID},
      {"Control"_STRID, "FAILURE"_STRID, {}, "FAILURE"_STRID},
      {"Par_Position"_STRID, "LATCHED"_STRID, "Contract"_STRID, "START"_STRID},
      {"Control"_STRID, "HALT_SEQ"_STRID, "Run"_STRID, "HALT"_STRID},
      {"Control"_STRID, "ABORT_SEQ"_STRID, "Run"_STRID, "ABORT"_STRID},
      {"Control"_STRID, "RUN_STOPPING"_STRID, "Control"_STRID, "STOPPING_DONE"_STRID},
      {"Run"_STRID, "DONE"_STRID, "Control"_STRID, "EXECUTE_DONE"_STRID},
      {"Run"_STRID, "FAILED"_STRID, "Control"_STRID, "EXECUTE_FAILED"_STRID},
      {"Run"_STRID, "HALTED"_STRID, "Control"_STRID, "EXECUTE_FAILED"_STRID},
      {"Port"_STRID, "STATE"_STRID, "Contract"_STRID, "SAMPLE"_STRID},
    });

    const auto cDataConnections = std::to_array<SCFB_FBConnectionData>({
      {"Control"_STRID, "StartMethodId"_STRID, "UaStart"_STRID, "ID"_STRID},
      {"UaStart"_STRID, "RD_1"_STRID, "Control"_STRID, "Session"_STRID},
      {"Control"_STRID, "Accepted"_STRID, "UaStart"_STRID, "SD_1"_STRID},
      {"Control"_STRID, "StartError"_STRID, "UaStart"_STRID, "SD_2"_STRID},
      {"UaStart"_STRID, "RD_2"_STRID, "Par_Position"_STRID, "Requested"_STRID},
      {"Control"_STRID, "CalledByClient"_STRID, "Par_Position"_STRID, "CalledByClient"_STRID},
      {"Par_Position"_STRID, "Value"_STRID, "PubParams"_STRID, "SD_1"_STRID},
      {"Par_Position"_STRID, "AllInRange"_STRID, "Control"_STRID, "ParamsInRange"_STRID},
      {{}, "Module"_STRID, "Control"_STRID, "Module"_STRID},
      {{}, "UaRoot"_STRID, "Control"_STRID, "UaRoot"_STRID},
      {{}, "UaPath"_STRID, "Control"_STRID, "UaPath"_STRID},
      {{}, "UaEnable"_STRID, "Control"_STRID, "UaEnable"_STRID},
      {{}, "Methods"_STRID, "Control"_STRID, "Methods"_STRID},
      {{}, "Methods"_STRID, "UaStart"_STRID, "QI"_STRID},
      {"Control"_STRID, "State"_STRID, {}, "State"_STRID},
      {"Control"_STRID, "ErrorID"_STRID, {}, "ErrorID"_STRID},
      {{}, "UaRoot"_STRID, "Contract"_STRID, "UaRoot"_STRID},
      {{}, "UaPath"_STRID, "Contract"_STRID, "UaPath"_STRID},
      {{}, "Timeout"_STRID, "Contract"_STRID, "Timeout"_STRID},
      {{}, "UaEnable"_STRID, "PubParams"_STRID, "QI"_STRID},
      {"Contract"_STRID, "IdParams"_STRID, "PubParams"_STRID, "ID"_STRID},
      {{}, "Position"_STRID, "Par_Position"_STRID, "Default"_STRID},
      {"Par_Position"_STRID, "Value"_STRID, "Contract"_STRID, "Position"_STRID},
      {{}, "Holder"_STRID, "Run"_STRID, "Holder"_STRID},
      {{}, "ReleaseAfter"_STRID, "Run"_STRID, "ReleaseAfter"_STRID},
      {"Run"_STRID, "ErrorID"_STRID, "Control"_STRID, "ExecuteError"_STRID},
      {{}, "Module"_STRID, "Port"_STRID, "Module"_STRID},
      {"Port"_STRID, "ActualPosition"_STRID, "Contract"_STRID, "ActualPosition"_STRID},
      {"Port"_STRID, "Homed"_STRID, "Contract"_STRID, "Homed"_STRID},
      {"Port"_STRID, "Moving"_STRID, "Contract"_STRID, "Moving"_STRID},
      {"Port"_STRID, "EqHolder"_STRID, "Contract"_STRID, "EqHolder"_STRID},
      {"Run"_STRID, "EquipmentFree"_STRID, "Control"_STRID, "EquipmentFree"_STRID},
    });

    const auto cAdapterConnections = std::to_array<SCFB_FBConnectionData>({
      {"Contract"_STRID, "Run"_STRID, "Run"_STRID, "Contract"_STRID},
      {"Run"_STRID, "Equipment"_STRID, "Port"_STRID, "Skill"_STRID},
    });

    const SCFB_FBNData cFBNData = {
      .mEventConnections = cEventConnections,
      .mDataConnections = cDataConnections,
      .mAdapterConnections = cAdapterConnections,
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_SK_MoveAxis, "filling::SK_MoveAxis"_STRID, TypeHash)

  FORTE_SK_MoveAxis::FORTE_SK_MoveAxis(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CCompositeFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cFBNData),
      fb_Control("Control"_STRID, *this),
      fb_Contract("Contract"_STRID, *this),
      fb_UaStart("UaStart"_STRID, "iec61499::net::SERVER_2_2", *this),
      fb_Par_Position("Par_Position"_STRID, *this),
      fb_PubParams("PubParams"_STRID, "iec61499::net::PUBLISH_1", *this),
      fb_Run("Run"_STRID, *this),
      fb_Port("Port"_STRID, *this),
      conn_INITO(*this, 0),
      conn_SUCCESS(*this, 1),
      conn_FAILURE(*this, 2),
      conn_Module(nullptr),
      conn_UaRoot(nullptr),
      conn_UaPath(nullptr),
      conn_UaEnable(nullptr),
      conn_Methods(nullptr),
      conn_Holder(nullptr),
      conn_ReleaseAfter(nullptr),
      conn_Timeout(nullptr),
      conn_Position(nullptr),
      conn_State(*this, 0, 0_USINT),
      conn_ErrorID(*this, 1, 0_UINT),
      conn_if2in_Module(*this, 0, u""_WSTRING),
      conn_if2in_UaRoot(*this, 1, u""_WSTRING),
      conn_if2in_UaPath(*this, 2, u""_WSTRING),
      conn_if2in_UaEnable(*this, 3, 0_BOOL),
      conn_if2in_Methods(*this, 4, 0_BOOL),
      conn_if2in_Holder(*this, 5, u""_WSTRING),
      conn_if2in_ReleaseAfter(*this, 6, true_BOOL),
      conn_if2in_Timeout(*this, 7, 30000000000_TIME),
      conn_if2in_Position(*this, 8, 0.0_LREAL) {
  };

  void FORTE_SK_MoveAxis::setInitialValues() {
    CCompositeFB::setInitialValues();
    conn_if2in_Module.getValue() = u""_WSTRING;
    conn_if2in_UaRoot.getValue() = u""_WSTRING;
    conn_if2in_UaPath.getValue() = u""_WSTRING;
    conn_if2in_UaEnable.getValue() = 0_BOOL;
    conn_if2in_Methods.getValue() = 0_BOOL;
    conn_if2in_Holder.getValue() = u""_WSTRING;
    conn_if2in_ReleaseAfter.getValue() = true_BOOL;
    conn_if2in_Timeout.getValue() = 30000000000_TIME;
    conn_if2in_Position.getValue() = 0.0_LREAL;
    fb_Control->conn_State.getValue() = 0_USINT;
    fb_Control->conn_ErrorID.getValue() = 0_UINT;
  }

  void FORTE_SK_MoveAxis::setFBNetworkInitialValues() {
    fb_Par_Position->var_Lower = 0.0_LREAL;
    fb_Par_Position->var_Upper = 60.0_LREAL;
  }

  void FORTE_SK_MoveAxis::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, conn_if2in_Module.getValue(), conn_Module);
        readData(1, conn_if2in_UaRoot.getValue(), conn_UaRoot);
        readData(2, conn_if2in_UaPath.getValue(), conn_UaPath);
        readData(3, conn_if2in_UaEnable.getValue(), conn_UaEnable);
        readData(4, conn_if2in_Methods.getValue(), conn_Methods);
        readData(5, conn_if2in_Holder.getValue(), conn_Holder);
        readData(6, conn_if2in_ReleaseAfter.getValue(), conn_ReleaseAfter);
        readData(7, conn_if2in_Timeout.getValue(), conn_Timeout);
        readData(8, conn_if2in_Position.getValue(), conn_Position);
        break;
      }
      case scmEventSTARTID: {
        readData(8, conn_if2in_Position.getValue(), conn_Position);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_SK_MoveAxis::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventFAILUREID: {
        writeData(10, fb_Control->conn_ErrorID.getValue(), conn_ErrorID);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_SK_MoveAxis::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module.getValue();
      case 1: return &conn_if2in_UaRoot.getValue();
      case 2: return &conn_if2in_UaPath.getValue();
      case 3: return &conn_if2in_UaEnable.getValue();
      case 4: return &conn_if2in_Methods.getValue();
      case 5: return &conn_if2in_Holder.getValue();
      case 6: return &conn_if2in_ReleaseAfter.getValue();
      case 7: return &conn_if2in_Timeout.getValue();
      case 8: return &conn_if2in_Position.getValue();
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SK_MoveAxis::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &fb_Control->conn_State.getValue();
      case 1: return &fb_Control->conn_ErrorID.getValue();
    }
    return nullptr;
  }

  CEventConnection *FORTE_SK_MoveAxis::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_SUCCESS;
      case 2: return &conn_FAILURE;
    }
    return nullptr;
  }

  CDataConnection **FORTE_SK_MoveAxis::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Module;
      case 1: return &conn_UaRoot;
      case 2: return &conn_UaPath;
      case 3: return &conn_UaEnable;
      case 4: return &conn_Methods;
      case 5: return &conn_Holder;
      case 6: return &conn_ReleaseAfter;
      case 7: return &conn_Timeout;
      case 8: return &conn_Position;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SK_MoveAxis::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_State;
      case 1: return &conn_ErrorID;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SK_MoveAxis::getIf2InConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module;
      case 1: return &conn_if2in_UaRoot;
      case 2: return &conn_if2in_UaPath;
      case 3: return &conn_if2in_UaEnable;
      case 4: return &conn_if2in_Methods;
      case 5: return &conn_if2in_Holder;
      case 6: return &conn_if2in_ReleaseAfter;
      case 7: return &conn_if2in_Timeout;
      case 8: return &conn_if2in_Position;
    }
    return nullptr;
  }

}