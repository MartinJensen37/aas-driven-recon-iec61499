/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SKILL_Core
 *** Description: The part every skill shares: its state machine (Idle, Running, Stopping, Succeeded, Failed, Aborted), the OPC UA methods Stop, Abort and Reset, and the State and ErrorID it publishes. It checks a client's Start (the caller holds the occupation, the module is in Execute, the skill is not running, the values are in range, the equipment is free) and then starts the skill's own logic. Technical: Skill core: state machine, OPC UA Stop/Abort/Reset(Session) -> [Accepted, ErrorID], State and ErrorID published, activity counted; the Start method (with the skill's parameters) is wired to START_REQ and START_RSP; RUN starts the execution, SUCCESS or FAILURE(ErrorID) ends it
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/SKILL_Core_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_time.h"
#include "forte/forte_st_util.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:QRcc7knPLMc8bmn8Ngu4Nr6djz6wMceBuOXNuuDRgCEF0Gh-SCIWoLXIHX0mkVl37nIQS4uxECZZ3JDl5yF44A=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "START_REQ"_STRID, "START"_STRID, "HALT"_STRID, "ABORT"_STRID, "RESET"_STRID, "EXECUTE_DONE"_STRID, "EXECUTE_FAILED"_STRID, "STOPPING_DONE"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "START_RSP"_STRID, "RUN"_STRID, "HALT_SEQ"_STRID, "ABORT_SEQ"_STRID, "RESET_SEQ"_STRID, "RUN_STOPPING"_STRID, "SUCCESS"_STRID, "FAILURE"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"Module"_STRID, "UaRoot"_STRID, "UaPath"_STRID, "UaEnable"_STRID, "Methods"_STRID, "Holder"_STRID, "ReleaseAll"_STRID, "Session"_STRID, "ParamsInRange"_STRID, "EquipmentFree"_STRID, "ExecuteError"_STRID};
    const auto cDataOutputNames = std::array{"StartMethodId"_STRID, "Accepted"_STRID, "StartError"_STRID, "CalledByClient"_STRID, "State"_STRID, "ErrorID"_STRID};

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
      {{}, "INIT"_STRID, "Control"_STRID, "INIT"_STRID},
      {"Control"_STRID, "INITO"_STRID, "Owner"_STRID, "INIT"_STRID},
      {"Owner"_STRID, "INITO"_STRID, "Mode"_STRID, "INIT"_STRID},
      {"Mode"_STRID, "INITO"_STRID, "UaStop"_STRID, "INIT"_STRID},
      {"UaStop"_STRID, "INITO"_STRID, "UaAbort"_STRID, "INIT"_STRID},
      {"UaAbort"_STRID, "INITO"_STRID, "UaReset"_STRID, "INIT"_STRID},
      {"UaReset"_STRID, "INITO"_STRID, "PubState"_STRID, "INIT"_STRID},
      {"PubState"_STRID, "INITO"_STRID, "Act"_STRID, "INIT"_STRID},
      {"Act"_STRID, "INITO"_STRID, "PubRelease"_STRID, "INIT"_STRID},
      {"PubRelease"_STRID, "INITO"_STRID, "PubState"_STRID, "REQ"_STRID},
      {"PubRelease"_STRID, "INITO"_STRID, {}, "INITO"_STRID},
      {{}, "START_REQ"_STRID, "Gate"_STRID, "START_REQ"_STRID},
      {"Gate"_STRID, "START_RSP"_STRID, {}, "START_RSP"_STRID},
      {"UaStop"_STRID, "IND"_STRID, "Gate"_STRID, "STOP_REQ"_STRID},
      {"Gate"_STRID, "STOP_RSP"_STRID, "UaStop"_STRID, "RSP"_STRID},
      {"UaAbort"_STRID, "IND"_STRID, "Gate"_STRID, "ABORT_REQ"_STRID},
      {"Gate"_STRID, "ABORT_RSP"_STRID, "UaAbort"_STRID, "RSP"_STRID},
      {"UaReset"_STRID, "IND"_STRID, "Gate"_STRID, "RESET_REQ"_STRID},
      {"Gate"_STRID, "RESET_RSP"_STRID, "UaReset"_STRID, "RSP"_STRID},
      {"Owner"_STRID, "CHG"_STRID, "Gate"_STRID, "OWNER_CHG"_STRID},
      {"Mode"_STRID, "CHG"_STRID, "Gate"_STRID, "MOD_CHG"_STRID},
      {"Gate"_STRID, "GO_START"_STRID, "Control"_STRID, "START"_STRID},
      {"Gate"_STRID, "GO_HALT"_STRID, "Control"_STRID, "HALT"_STRID},
      {"Gate"_STRID, "GO_ABORT"_STRID, "Control"_STRID, "ABORT"_STRID},
      {"Gate"_STRID, "GO_RESET"_STRID, "Control"_STRID, "RESET"_STRID},
      {"Control"_STRID, "PUB"_STRID, "PubState"_STRID, "REQ"_STRID},
      {"Control"_STRID, "PUB"_STRID, "Gate"_STRID, "SKILL_CHG"_STRID},
      {"Control"_STRID, "ACT"_STRID, "Act"_STRID, "REQ"_STRID},
      {{}, "START"_STRID, "Gate"_STRID, "START"_STRID},
      {{}, "HALT"_STRID, "Gate"_STRID, "HALT"_STRID},
      {{}, "ABORT"_STRID, "Gate"_STRID, "ABORT"_STRID},
      {{}, "RESET"_STRID, "Gate"_STRID, "RESET"_STRID},
      {{}, "EXECUTE_DONE"_STRID, "Control"_STRID, "EXECUTE_DONE"_STRID},
      {{}, "EXECUTE_FAILED"_STRID, "Control"_STRID, "EXECUTE_FAILED"_STRID},
      {{}, "STOPPING_DONE"_STRID, "Control"_STRID, "STOPPING_DONE"_STRID},
      {"Control"_STRID, "RUN"_STRID, {}, "RUN"_STRID},
      {"Control"_STRID, "HALT_SEQ"_STRID, {}, "HALT_SEQ"_STRID},
      {"Control"_STRID, "ABORT_SEQ"_STRID, {}, "ABORT_SEQ"_STRID},
      {"Control"_STRID, "RESET_SEQ"_STRID, {}, "RESET_SEQ"_STRID},
      {"Control"_STRID, "RUN_STOPPING"_STRID, {}, "RUN_STOPPING"_STRID},
      {"Control"_STRID, "SUCCESS"_STRID, {}, "SUCCESS"_STRID},
      {"Control"_STRID, "FAILURE"_STRID, {}, "FAILURE"_STRID},
      {"Control"_STRID, "TO_IDLE_START"_STRID, "ToIdle"_STRID, "START"_STRID},
      {"Control"_STRID, "TO_IDLE_STOP"_STRID, "ToIdle"_STRID, "STOP"_STRID},
      {"ToIdle"_STRID, "EO"_STRID, "Control"_STRID, "TO_IDLE"_STRID},
      {"Control"_STRID, "RELEASE"_STRID, "PubRelease"_STRID, "REQ"_STRID},
    });

    const auto cDataConnections = std::to_array<SCFB_FBConnectionData>({
      {{}, "Module"_STRID, "Control"_STRID, "Module"_STRID},
      {{}, "Module"_STRID, "Owner"_STRID, "Module"_STRID},
      {{}, "Module"_STRID, "Mode"_STRID, "Module"_STRID},
      {{}, "UaRoot"_STRID, "Control"_STRID, "UaRoot"_STRID},
      {{}, "UaPath"_STRID, "Control"_STRID, "UaPath"_STRID},
      {{}, "Methods"_STRID, "UaStop"_STRID, "QI"_STRID},
      {{}, "Methods"_STRID, "UaAbort"_STRID, "QI"_STRID},
      {{}, "Methods"_STRID, "UaReset"_STRID, "QI"_STRID},
      {{}, "UaEnable"_STRID, "PubState"_STRID, "QI"_STRID},
      {"Control"_STRID, "StartMethodId"_STRID, {}, "StartMethodId"_STRID},
      {{}, "Session"_STRID, "Gate"_STRID, "Session"_STRID},
      {{}, "ParamsInRange"_STRID, "Gate"_STRID, "ParamsInRange"_STRID},
      {{}, "EquipmentFree"_STRID, "Gate"_STRID, "EquipmentFree"_STRID},
      {"Gate"_STRID, "Accepted"_STRID, {}, "Accepted"_STRID},
      {"Gate"_STRID, "Accepted"_STRID, "UaStop"_STRID, "SD_1"_STRID},
      {"Gate"_STRID, "Accepted"_STRID, "UaAbort"_STRID, "SD_1"_STRID},
      {"Gate"_STRID, "Accepted"_STRID, "UaReset"_STRID, "SD_1"_STRID},
      {"Gate"_STRID, "ResponseError"_STRID, {}, "StartError"_STRID},
      {"Gate"_STRID, "ResponseError"_STRID, "UaStop"_STRID, "SD_2"_STRID},
      {"Gate"_STRID, "ResponseError"_STRID, "UaAbort"_STRID, "SD_2"_STRID},
      {"Gate"_STRID, "ResponseError"_STRID, "UaReset"_STRID, "SD_2"_STRID},
      {"Control"_STRID, "StopMethodId"_STRID, "UaStop"_STRID, "ID"_STRID},
      {"UaStop"_STRID, "RD_1"_STRID, "Gate"_STRID, "StopSession"_STRID},
      {"Control"_STRID, "AbortMethodId"_STRID, "UaAbort"_STRID, "ID"_STRID},
      {"UaAbort"_STRID, "RD_1"_STRID, "Gate"_STRID, "AbortSession"_STRID},
      {"Control"_STRID, "ResetMethodId"_STRID, "UaReset"_STRID, "ID"_STRID},
      {"UaReset"_STRID, "RD_1"_STRID, "Gate"_STRID, "ResetSession"_STRID},
      {"Owner"_STRID, "Owner"_STRID, "Gate"_STRID, "Owner"_STRID},
      {"Mode"_STRID, "State"_STRID, "Gate"_STRID, "ModuleState"_STRID},
      {"Gate"_STRID, "ByClient"_STRID, "Control"_STRID, "ByClient"_STRID},
      {"Control"_STRID, "StateId"_STRID, "PubState"_STRID, "ID"_STRID},
      {"Control"_STRID, "State"_STRID, "PubState"_STRID, "SD_1"_STRID},
      {"Control"_STRID, "State"_STRID, {}, "State"_STRID},
      {"Control"_STRID, "State"_STRID, "Gate"_STRID, "State"_STRID},
      {"Control"_STRID, "ErrorID"_STRID, "PubState"_STRID, "SD_2"_STRID},
      {"Control"_STRID, "ErrorID"_STRID, {}, "ErrorID"_STRID},
      {"Control"_STRID, "ActivityId"_STRID, "Act"_STRID, "ID"_STRID},
      {"Control"_STRID, "ActivityDelta"_STRID, "Act"_STRID, "SD_1"_STRID},
      {{}, "ExecuteError"_STRID, "Control"_STRID, "ExecuteError"_STRID},
      {"Control"_STRID, "CalledByClient"_STRID, {}, "CalledByClient"_STRID},
      {{}, "ReleaseAll"_STRID, "PubRelease"_STRID, "QI"_STRID},
      {"Control"_STRID, "ReleaseId"_STRID, "PubRelease"_STRID, "ID"_STRID},
      {{}, "Holder"_STRID, "PubRelease"_STRID, "SD_1"_STRID},
    });

    const SCFB_FBNData cFBNData = {
      .mEventConnections = cEventConnections,
      .mDataConnections = cDataConnections,
      .mAdapterConnections = {},
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_SKILL_Core, "modlib::SKILL_Core"_STRID, TypeHash)

  FORTE_SKILL_Core::FORTE_SKILL_Core(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CCompositeFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cFBNData),
      fb_Gate("Gate"_STRID, *this),
      fb_Control("Control"_STRID, *this),
      fb_Owner("Owner"_STRID, *this),
      fb_Mode("Mode"_STRID, *this),
      fb_UaStop("UaStop"_STRID, "iec61499::net::SERVER_2_1", *this),
      fb_UaAbort("UaAbort"_STRID, "iec61499::net::SERVER_2_1", *this),
      fb_UaReset("UaReset"_STRID, "iec61499::net::SERVER_2_1", *this),
      fb_PubState("PubState"_STRID, "iec61499::net::PUBLISH_2", *this),
      fb_Act("Act"_STRID, "iec61499::net::PUBLISH_1", *this),
      fb_ToIdle("ToIdle"_STRID, *this),
      fb_PubRelease("PubRelease"_STRID, "iec61499::net::PUBLISH_1", *this),
      conn_INITO(*this, 0),
      conn_START_RSP(*this, 1),
      conn_RUN(*this, 2),
      conn_HALT_SEQ(*this, 3),
      conn_ABORT_SEQ(*this, 4),
      conn_RESET_SEQ(*this, 5),
      conn_RUN_STOPPING(*this, 6),
      conn_SUCCESS(*this, 7),
      conn_FAILURE(*this, 8),
      conn_Module(nullptr),
      conn_UaRoot(nullptr),
      conn_UaPath(nullptr),
      conn_UaEnable(nullptr),
      conn_Methods(nullptr),
      conn_Holder(nullptr),
      conn_ReleaseAll(nullptr),
      conn_Session(nullptr),
      conn_ParamsInRange(nullptr),
      conn_EquipmentFree(nullptr),
      conn_ExecuteError(nullptr),
      conn_StartMethodId(*this, 0, u""_WSTRING),
      conn_Accepted(*this, 1, 0_BOOL),
      conn_StartError(*this, 2, 0_UINT),
      conn_CalledByClient(*this, 3, 0_BOOL),
      conn_State(*this, 4, 0_USINT),
      conn_ErrorID(*this, 5, 0_UINT),
      conn_if2in_Module(*this, 0, u""_WSTRING),
      conn_if2in_UaRoot(*this, 1, u""_WSTRING),
      conn_if2in_UaPath(*this, 2, u""_WSTRING),
      conn_if2in_UaEnable(*this, 3, 0_BOOL),
      conn_if2in_Methods(*this, 4, 0_BOOL),
      conn_if2in_Holder(*this, 5, u""_WSTRING),
      conn_if2in_ReleaseAll(*this, 6, false_BOOL),
      conn_if2in_Session(*this, 7, u""_WSTRING),
      conn_if2in_ParamsInRange(*this, 8, true_BOOL),
      conn_if2in_EquipmentFree(*this, 9, true_BOOL),
      conn_if2in_ExecuteError(*this, 10, 0_UINT) {
  };

  void FORTE_SKILL_Core::setInitialValues() {
    CCompositeFB::setInitialValues();
    conn_if2in_Module.getValue() = u""_WSTRING;
    conn_if2in_UaRoot.getValue() = u""_WSTRING;
    conn_if2in_UaPath.getValue() = u""_WSTRING;
    conn_if2in_UaEnable.getValue() = 0_BOOL;
    conn_if2in_Methods.getValue() = 0_BOOL;
    conn_if2in_Holder.getValue() = u""_WSTRING;
    conn_if2in_ReleaseAll.getValue() = false_BOOL;
    conn_if2in_Session.getValue() = u""_WSTRING;
    conn_if2in_ParamsInRange.getValue() = true_BOOL;
    conn_if2in_EquipmentFree.getValue() = true_BOOL;
    conn_if2in_ExecuteError.getValue() = 0_UINT;
    fb_Control->conn_StartMethodId.getValue() = u""_WSTRING;
    fb_Gate->conn_Accepted.getValue() = 0_BOOL;
    fb_Gate->conn_ResponseError.getValue() = 0_UINT;
    fb_Control->conn_CalledByClient.getValue() = 0_BOOL;
    fb_Control->conn_State.getValue() = 0_USINT;
    fb_Control->conn_ErrorID.getValue() = 0_UINT;
  }

  void FORTE_SKILL_Core::setFBNetworkInitialValues() {
    if (auto v = fb_Act->getDataInput("QI"_STRID)) { v->setValue(true_BOOL); }
    fb_ToIdle->var_DT = 1500000000_TIME;
  }

  void FORTE_SKILL_Core::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, conn_if2in_Module.getValue(), conn_Module);
        readData(1, conn_if2in_UaRoot.getValue(), conn_UaRoot);
        readData(2, conn_if2in_UaPath.getValue(), conn_UaPath);
        readData(3, conn_if2in_UaEnable.getValue(), conn_UaEnable);
        readData(4, conn_if2in_Methods.getValue(), conn_Methods);
        readData(5, conn_if2in_Holder.getValue(), conn_Holder);
        readData(6, conn_if2in_ReleaseAll.getValue(), conn_ReleaseAll);
        break;
      }
      case scmEventSTART_REQID: {
        readData(7, conn_if2in_Session.getValue(), conn_Session);
        readData(8, conn_if2in_ParamsInRange.getValue(), conn_ParamsInRange);
        readData(9, conn_if2in_EquipmentFree.getValue(), conn_EquipmentFree);
        break;
      }
      case scmEventEXECUTE_FAILEDID: {
        readData(10, conn_if2in_ExecuteError.getValue(), conn_ExecuteError);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_SKILL_Core::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(11, fb_Control->conn_StartMethodId.getValue(), conn_StartMethodId);
        break;
      }
      case scmEventSTART_RSPID: {
        writeData(12, fb_Gate->conn_Accepted.getValue(), conn_Accepted);
        writeData(13, fb_Gate->conn_ResponseError.getValue(), conn_StartError);
        break;
      }
      case scmEventRUNID: {
        writeData(14, fb_Control->conn_CalledByClient.getValue(), conn_CalledByClient);
        break;
      }
      case scmEventFAILUREID: {
        writeData(16, fb_Control->conn_ErrorID.getValue(), conn_ErrorID);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_SKILL_Core::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module.getValue();
      case 1: return &conn_if2in_UaRoot.getValue();
      case 2: return &conn_if2in_UaPath.getValue();
      case 3: return &conn_if2in_UaEnable.getValue();
      case 4: return &conn_if2in_Methods.getValue();
      case 5: return &conn_if2in_Holder.getValue();
      case 6: return &conn_if2in_ReleaseAll.getValue();
      case 7: return &conn_if2in_Session.getValue();
      case 8: return &conn_if2in_ParamsInRange.getValue();
      case 9: return &conn_if2in_EquipmentFree.getValue();
      case 10: return &conn_if2in_ExecuteError.getValue();
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SKILL_Core::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &fb_Control->conn_StartMethodId.getValue();
      case 1: return &fb_Gate->conn_Accepted.getValue();
      case 2: return &fb_Gate->conn_ResponseError.getValue();
      case 3: return &fb_Control->conn_CalledByClient.getValue();
      case 4: return &fb_Control->conn_State.getValue();
      case 5: return &fb_Control->conn_ErrorID.getValue();
    }
    return nullptr;
  }

  CEventConnection *FORTE_SKILL_Core::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_START_RSP;
      case 2: return &conn_RUN;
      case 3: return &conn_HALT_SEQ;
      case 4: return &conn_ABORT_SEQ;
      case 5: return &conn_RESET_SEQ;
      case 6: return &conn_RUN_STOPPING;
      case 7: return &conn_SUCCESS;
      case 8: return &conn_FAILURE;
    }
    return nullptr;
  }

  CDataConnection **FORTE_SKILL_Core::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Module;
      case 1: return &conn_UaRoot;
      case 2: return &conn_UaPath;
      case 3: return &conn_UaEnable;
      case 4: return &conn_Methods;
      case 5: return &conn_Holder;
      case 6: return &conn_ReleaseAll;
      case 7: return &conn_Session;
      case 8: return &conn_ParamsInRange;
      case 9: return &conn_EquipmentFree;
      case 10: return &conn_ExecuteError;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SKILL_Core::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_StartMethodId;
      case 1: return &conn_Accepted;
      case 2: return &conn_StartError;
      case 3: return &conn_CalledByClient;
      case 4: return &conn_State;
      case 5: return &conn_ErrorID;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SKILL_Core::getIf2InConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module;
      case 1: return &conn_if2in_UaRoot;
      case 2: return &conn_if2in_UaPath;
      case 3: return &conn_if2in_UaEnable;
      case 4: return &conn_if2in_Methods;
      case 5: return &conn_if2in_Holder;
      case 6: return &conn_if2in_ReleaseAll;
      case 7: return &conn_if2in_Session;
      case 8: return &conn_if2in_ParamsInRange;
      case 9: return &conn_if2in_EquipmentFree;
      case 10: return &conn_if2in_ExecuteError;
    }
    return nullptr;
  }

}