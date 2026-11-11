/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SK_Home
 *** Description: A skill primitive: one action of one piece of equipment (move the axis, run the pump, weigh). It can be called on its own over OPC UA, or be a step of a bigger skill. Inside: SKILL_Core (state machine and OPC UA methods), a parameter block per parameter, SC_ (its contract: what this skill does and when it is done), SKILL_Run (one run, the same for every primitive) and EP_ (the equipment as the skill sees it). Technical: Skill primitive Home: Needle up to the limit switch; from there its position is known (parameters: none). OPC UA Start(Session, parameters...)/Stop/Abort/Reset(Session) -> [Accepted, ErrorID]; START/HALT/ABORT/RESET from a parent -> SUCCESS or FAILURE(ErrorID)
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/filling/SK_Home_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_time.h"
#include "forte/forte_st_util.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::filling {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:vYr9_7Ba6NjmJbQI9CYTDv3PeGfVEc1C6_xqUfvhh-Zc2RQWlZHV71Kzu6IjVdIL00ic79glHQEuuVxfmCaK1A=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "START"_STRID, "HALT"_STRID, "ABORT"_STRID, "RESET"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "SUCCESS"_STRID, "FAILURE"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"Module"_STRID, "UaRoot"_STRID, "UaPath"_STRID, "UaEnable"_STRID, "Methods"_STRID, "Holder"_STRID, "ReleaseAfter"_STRID, "Timeout"_STRID};
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
      {"UaStart"_STRID, "IND"_STRID, "Control"_STRID, "START_REQ"_STRID},
      {{}, "INIT"_STRID, "Control"_STRID, "INIT"_STRID},
      {"Control"_STRID, "INITO"_STRID, "Contract"_STRID, "INIT"_STRID},
      {"Contract"_STRID, "INITO"_STRID, "UaStart"_STRID, "INIT"_STRID},
      {"UaStart"_STRID, "INITO"_STRID, "Run"_STRID, "INIT"_STRID},
      {"Run"_STRID, "INITO"_STRID, "Port"_STRID, "INIT"_STRID},
      {"Port"_STRID, "INITO"_STRID, {}, "INITO"_STRID},
      {{}, "START"_STRID, "Control"_STRID, "START"_STRID},
      {{}, "HALT"_STRID, "Control"_STRID, "HALT"_STRID},
      {{}, "ABORT"_STRID, "Control"_STRID, "ABORT"_STRID},
      {{}, "RESET"_STRID, "Control"_STRID, "RESET"_STRID},
      {"Control"_STRID, "SUCCESS"_STRID, {}, "SUCCESS"_STRID},
      {"Control"_STRID, "FAILURE"_STRID, {}, "FAILURE"_STRID},
      {"Control"_STRID, "RUN"_STRID, "Contract"_STRID, "START"_STRID},
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
      {{}, "Module"_STRID, "Control"_STRID, "Module"_STRID},
      {{}, "UaRoot"_STRID, "Control"_STRID, "UaRoot"_STRID},
      {{}, "UaPath"_STRID, "Control"_STRID, "UaPath"_STRID},
      {{}, "UaEnable"_STRID, "Control"_STRID, "UaEnable"_STRID},
      {{}, "Methods"_STRID, "Control"_STRID, "Methods"_STRID},
      {{}, "Methods"_STRID, "UaStart"_STRID, "QI"_STRID},
      {"Control"_STRID, "State"_STRID, {}, "State"_STRID},
      {"Control"_STRID, "ErrorID"_STRID, {}, "ErrorID"_STRID},
      {{}, "Timeout"_STRID, "Contract"_STRID, "Timeout"_STRID},
      {{}, "Holder"_STRID, "Run"_STRID, "Holder"_STRID},
      {{}, "ReleaseAfter"_STRID, "Run"_STRID, "ReleaseAfter"_STRID},
      {"Run"_STRID, "ErrorID"_STRID, "Control"_STRID, "ExecuteError"_STRID},
      {{}, "Module"_STRID, "Port"_STRID, "Module"_STRID},
      {"Port"_STRID, "AtHome"_STRID, "Contract"_STRID, "AtHome"_STRID},
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

  DEFINE_FIRMWARE_FB(FORTE_SK_Home, "filling::SK_Home"_STRID, TypeHash)

  FORTE_SK_Home::FORTE_SK_Home(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CCompositeFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cFBNData),
      fb_Control("Control"_STRID, *this),
      fb_Contract("Contract"_STRID, *this),
      fb_UaStart("UaStart"_STRID, "iec61499::net::SERVER_2_1", *this),
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
      conn_State(*this, 0, 0_USINT),
      conn_ErrorID(*this, 1, 0_UINT),
      conn_if2in_Module(*this, 0, u""_WSTRING),
      conn_if2in_UaRoot(*this, 1, u""_WSTRING),
      conn_if2in_UaPath(*this, 2, u""_WSTRING),
      conn_if2in_UaEnable(*this, 3, 0_BOOL),
      conn_if2in_Methods(*this, 4, 0_BOOL),
      conn_if2in_Holder(*this, 5, u""_WSTRING),
      conn_if2in_ReleaseAfter(*this, 6, true_BOOL),
      conn_if2in_Timeout(*this, 7, 60000000000_TIME) {
  };

  void FORTE_SK_Home::setInitialValues() {
    CCompositeFB::setInitialValues();
    conn_if2in_Module.getValue() = u""_WSTRING;
    conn_if2in_UaRoot.getValue() = u""_WSTRING;
    conn_if2in_UaPath.getValue() = u""_WSTRING;
    conn_if2in_UaEnable.getValue() = 0_BOOL;
    conn_if2in_Methods.getValue() = 0_BOOL;
    conn_if2in_Holder.getValue() = u""_WSTRING;
    conn_if2in_ReleaseAfter.getValue() = true_BOOL;
    conn_if2in_Timeout.getValue() = 60000000000_TIME;
    fb_Control->conn_State.getValue() = 0_USINT;
    fb_Control->conn_ErrorID.getValue() = 0_UINT;
  }

  void FORTE_SK_Home::readInputData(const TEventID paEIID) {
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
        break;
      }
      default:
        break;
    }
  }

  void FORTE_SK_Home::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventFAILUREID: {
        writeData(9, fb_Control->conn_ErrorID.getValue(), conn_ErrorID);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_SK_Home::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module.getValue();
      case 1: return &conn_if2in_UaRoot.getValue();
      case 2: return &conn_if2in_UaPath.getValue();
      case 3: return &conn_if2in_UaEnable.getValue();
      case 4: return &conn_if2in_Methods.getValue();
      case 5: return &conn_if2in_Holder.getValue();
      case 6: return &conn_if2in_ReleaseAfter.getValue();
      case 7: return &conn_if2in_Timeout.getValue();
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SK_Home::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &fb_Control->conn_State.getValue();
      case 1: return &fb_Control->conn_ErrorID.getValue();
    }
    return nullptr;
  }

  CEventConnection *FORTE_SK_Home::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_SUCCESS;
      case 2: return &conn_FAILURE;
    }
    return nullptr;
  }

  CDataConnection **FORTE_SK_Home::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Module;
      case 1: return &conn_UaRoot;
      case 2: return &conn_UaPath;
      case 3: return &conn_UaEnable;
      case 4: return &conn_Methods;
      case 5: return &conn_Holder;
      case 6: return &conn_ReleaseAfter;
      case 7: return &conn_Timeout;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SK_Home::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_State;
      case 1: return &conn_ErrorID;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SK_Home::getIf2InConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Module;
      case 1: return &conn_if2in_UaRoot;
      case 2: return &conn_if2in_UaPath;
      case 3: return &conn_if2in_UaEnable;
      case 4: return &conn_if2in_Methods;
      case 5: return &conn_if2in_Holder;
      case 6: return &conn_if2in_ReleaseAfter;
      case 7: return &conn_if2in_Timeout;
    }
    return nullptr;
  }

}