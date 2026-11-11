/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SKILL_Run
 *** Description: One run of a skill primitive, the same for every primitive: waits until the equipment is free, checks the precondition, sends the command, then watches the conditions (or a timer) until the skill is done, has failed or has timed out, and sends the closing command. What the skill is comes in from its contract (SC_). Technical: One run of a skill primitive, the same for every primitive: what the skill is comes in from its contract (socket Contract, AContract); the command goes out to the equipment (plug Equipment, AEquipment)
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/SKILL_Run_fbt.h"

#include "forte/datatypes/forte_time.h"
#include "forte/forte_st_util.h"
#include "forte/modlib/AContract_adp.h"
#include "forte/modlib/AEquipment_adp.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:B0KH1U6R9D73xAgA3kZ8-Irg-EP6bJgtmxrW7OmS5ErAIXGb6Db2SRMEPiOwKIj5l8p8pzbtTtGbvoSm_9W5ZQ=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "HALT"_STRID, "ABORT"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "DONE"_STRID, "FAILED"_STRID, "HALTED"_STRID, "EQ_FREE"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"Holder"_STRID, "ReleaseAfter"_STRID};
    const auto cDataOutputNames = std::array{"ErrorID"_STRID, "EquipmentFree"_STRID};
    const auto cSocketNameIds = std::array{"Contract"_STRID};
    const auto cPlugNameIds = std::array{"Equipment"_STRID};

    const SFBInterfaceSpec cFBInterfaceSpec = {
        .mEINames = cEventInputNames,
        .mEITypeNames = cEventInputTypeIds,
        .mEONames = cEventOutputNames,
        .mEOTypeNames = cEventOutputTypeIds,
        .mDINames = cDataInputNames,
        .mDONames = cDataOutputNames,
        .mDIONames = {},
        .mSocketNames = cSocketNameIds,
        .mPlugNames = cPlugNameIds,
    };

    const auto cEventConnections = std::to_array<SCFB_FBConnectionData>({
      {{}, "INIT"_STRID, {}, "INITO"_STRID},
      {{}, "HALT"_STRID, "Logic"_STRID, "HALT"_STRID},
      {{}, "ABORT"_STRID, "Logic"_STRID, "ABORT"_STRID},
      {"Contract"_STRID, "START"_STRID, "Logic"_STRID, "START"_STRID},
      {"Contract"_STRID, "SAMPLE"_STRID, "Logic"_STRID, "SAMPLE"_STRID},
      {"Logic"_STRID, "DONE"_STRID, {}, "DONE"_STRID},
      {"Logic"_STRID, "FAILED"_STRID, {}, "FAILED"_STRID},
      {"Logic"_STRID, "HALTED"_STRID, {}, "HALTED"_STRID},
      {"Logic"_STRID, "EQ_FREE"_STRID, {}, "EQ_FREE"_STRID},
      {"Logic"_STRID, "CMD"_STRID, "Equipment"_STRID, "SEND"_STRID},
      {"Equipment"_STRID, "PLAYED"_STRID, "Logic"_STRID, "PLAYED"_STRID},
      {"Logic"_STRID, "TIMER_START"_STRID, "Timer"_STRID, "START"_STRID},
      {"Logic"_STRID, "TIMER_STOP"_STRID, "Timer"_STRID, "STOP"_STRID},
      {"Timer"_STRID, "EO"_STRID, "Logic"_STRID, "TIMER"_STRID},
      {"Logic"_STRID, "WAIT_START"_STRID, "WaitT"_STRID, "START"_STRID},
      {"Logic"_STRID, "WAIT_STOP"_STRID, "WaitT"_STRID, "STOP"_STRID},
      {"WaitT"_STRID, "EO"_STRID, "Logic"_STRID, "WAIT_OVER"_STRID},
    });

    const auto cDataConnections = std::to_array<SCFB_FBConnectionData>({
      {{}, "Holder"_STRID, "Logic"_STRID, "Holder"_STRID},
      {{}, "ReleaseAfter"_STRID, "Logic"_STRID, "ReleaseAfter"_STRID},
      {"Contract"_STRID, "Pre"_STRID, "Logic"_STRID, "Pre"_STRID},
      {"Contract"_STRID, "Post"_STRID, "Logic"_STRID, "Post"_STRID},
      {"Contract"_STRID, "Timed"_STRID, "Logic"_STRID, "Timed"_STRID},
      {"Contract"_STRID, "RunTime"_STRID, "Logic"_STRID, "RunTime"_STRID},
      {"Contract"_STRID, "Command"_STRID, "Logic"_STRID, "Command"_STRID},
      {"Contract"_STRID, "Arg"_STRID, "Logic"_STRID, "Arg"_STRID},
      {"Contract"_STRID, "StopCommand"_STRID, "Logic"_STRID, "StopCommand"_STRID},
      {"Contract"_STRID, "Inv"_STRID, "Logic"_STRID, "Inv"_STRID},
      {"Contract"_STRID, "EqHolder"_STRID, "Logic"_STRID, "EqHolder"_STRID},
      {"Logic"_STRID, "ErrorID"_STRID, {}, "ErrorID"_STRID},
      {"Logic"_STRID, "EquipmentFree"_STRID, {}, "EquipmentFree"_STRID},
      {"Logic"_STRID, "C_Holder"_STRID, "Equipment"_STRID, "Holder"_STRID},
      {"Logic"_STRID, "C_Command"_STRID, "Equipment"_STRID, "Command"_STRID},
      {"Logic"_STRID, "C_Arg"_STRID, "Equipment"_STRID, "Arg"_STRID},
      {"Logic"_STRID, "C_Release"_STRID, "Equipment"_STRID, "Release"_STRID},
      {"Logic"_STRID, "TimerDT"_STRID, "Timer"_STRID, "DT"_STRID},
    });

    const SCFB_FBNData cFBNData = {
      .mEventConnections = cEventConnections,
      .mDataConnections = cDataConnections,
      .mAdapterConnections = {},
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_SKILL_Run, "modlib::SKILL_Run"_STRID, TypeHash)

  FORTE_SKILL_Run::FORTE_SKILL_Run(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CCompositeFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cFBNData),
      fb_Logic("Logic"_STRID, *this),
      fb_Timer("Timer"_STRID, *this),
      fb_WaitT("WaitT"_STRID, *this),
      var_Contract("Contract"_STRID, *this, forte::cgCFBParentAdapterlistIDMarker),
      var_Equipment("Equipment"_STRID, *this, forte::cgCFBParentAdapterlistIDMarker),
      conn_INITO(*this, 0),
      conn_DONE(*this, 1),
      conn_FAILED(*this, 2),
      conn_HALTED(*this, 3),
      conn_EQ_FREE(*this, 4),
      conn_Holder(nullptr),
      conn_ReleaseAfter(nullptr),
      conn_ErrorID(*this, 0, 0_UINT),
      conn_EquipmentFree(*this, 1, 0_BOOL),
      conn_if2in_Holder(*this, 0, u""_WSTRING),
      conn_if2in_ReleaseAfter(*this, 1, 0_BOOL) {
  };

  void FORTE_SKILL_Run::setInitialValues() {
    CCompositeFB::setInitialValues();
    conn_if2in_Holder.getValue() = u""_WSTRING;
    conn_if2in_ReleaseAfter.getValue() = 0_BOOL;
    fb_Logic->conn_ErrorID.getValue() = 0_UINT;
    fb_Logic->conn_EquipmentFree.getValue() = 0_BOOL;
  }

  void FORTE_SKILL_Run::setFBNetworkInitialValues() {
    fb_WaitT->var_DT = 500000000_TIME;
  }

  void FORTE_SKILL_Run::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, conn_if2in_Holder.getValue(), conn_Holder);
        readData(1, conn_if2in_ReleaseAfter.getValue(), conn_ReleaseAfter);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_SKILL_Run::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventFAILEDID: {
        writeData(2, fb_Logic->conn_ErrorID.getValue(), conn_ErrorID);
        break;
      }
      case scmEventHALTEDID: {
        writeData(2, fb_Logic->conn_ErrorID.getValue(), conn_ErrorID);
        break;
      }
      case scmEventEQ_FREEID: {
        writeData(3, fb_Logic->conn_EquipmentFree.getValue(), conn_EquipmentFree);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_SKILL_Run::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Holder.getValue();
      case 1: return &conn_if2in_ReleaseAfter.getValue();
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SKILL_Run::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &fb_Logic->conn_ErrorID.getValue();
      case 1: return &fb_Logic->conn_EquipmentFree.getValue();
    }
    return nullptr;
  }

  forte::ISocketPin *FORTE_SKILL_Run::getSocketPinUnchecked(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Contract;
    }
    return nullptr;
  }

  forte::IPlugPin *FORTE_SKILL_Run::getPlugPinUnchecked(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Equipment;
    }
    return nullptr;
  }

  CEventConnection *FORTE_SKILL_Run::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_DONE;
      case 2: return &conn_FAILED;
      case 3: return &conn_HALTED;
      case 4: return &conn_EQ_FREE;
    }
    return nullptr;
  }

  CDataConnection **FORTE_SKILL_Run::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Holder;
      case 1: return &conn_ReleaseAfter;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SKILL_Run::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_ErrorID;
      case 1: return &conn_EquipmentFree;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SKILL_Run::getIf2InConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_if2in_Holder;
      case 1: return &conn_if2in_ReleaseAfter;
    }
    return nullptr;
  }

}