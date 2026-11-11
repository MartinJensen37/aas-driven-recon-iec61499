/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: EC_Pump
 *** Description: The equipment's command table: turns a command's name (Up, Down, Run, ...) into the output values to switch, phase by phase with their times. Technical: Commands of Pump as output values, in timed phases: Idle=0, Run=1
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/filling/EC_Pump_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"
#include "forte/iec61131_functions/func_ADD.h"
#include "forte/iec61131_functions/func_AND.h"
#include "forte/iec61131_functions/func_NOT.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::filling {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:aBqj0_t3eGJSHZW_pNHDFe5oGczyd5zSXe0FxFZl6YqixYlr59xMH2rlFrt8ZTKf09FsL87tZkcupmCPlNkyqw=="sv;

    const auto cEventInputNames = std::array{"PLAY"_STRID, "PHASE_T"_STRID};
    const auto cEventOutputNames = std::array{"OUT"_STRID, "PHASE_START"_STRID, "PHASE_STOP"_STRID, "PLAYED"_STRID};
    const auto cDataInputNames = std::array{"Holder"_STRID, "Command"_STRID, "Release"_STRID};
    const auto cDataOutputNames = std::array{"O_Holder"_STRID, "O_Release"_STRID, "PhaseDT"_STRID};
    const SFBInterfaceSpec cFBInterfaceSpec = {
        .mEINames = cEventInputNames,
        .mEITypeNames = {},
        .mEONames = cEventOutputNames,
        .mEOTypeNames = {},
        .mDINames = cDataInputNames,
        .mDONames = cDataOutputNames,
        .mDIONames = {},
        .mSocketNames = {},
        .mPlugNames = {},
    };

    const auto cInternalsNames = std::array{"Phase"_STRID, "Timed"_STRID};
  }

  DEFINE_FIRMWARE_FB(FORTE_EC_Pump, "filling::EC_Pump"_STRID, TypeHash)

  FORTE_EC_Pump::FORTE_EC_Pump(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CBasicFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cInternalsNames),
      var_Phase(0_USINT),
      var_Timed(0_BOOL),
      var_Holder(u""_WSTRING),
      var_Command(0_USINT),
      var_Release(0_BOOL),
      var_O_Holder(u""_WSTRING),
      var_O_Release(0_BOOL),
      var_PhaseDT(0_TIME),
      conn_OUT(*this, 0),
      conn_PHASE_START(*this, 1),
      conn_PHASE_STOP(*this, 2),
      conn_PLAYED(*this, 3),
      conn_Holder(nullptr),
      conn_Command(nullptr),
      conn_Release(nullptr),
      conn_O_Holder(*this, 0, var_O_Holder),
      conn_O_Release(*this, 1, var_O_Release),
      conn_PhaseDT(*this, 2, var_PhaseDT) {
  }

  void FORTE_EC_Pump::setInitialValues() {
    CBasicFB::setInitialValues();
    var_Phase = 0_USINT;
    var_Timed = 0_BOOL;
    var_Holder = u""_WSTRING;
    var_Command = 0_USINT;
    var_Release = 0_BOOL;
    var_O_Holder = u""_WSTRING;
    var_O_Release = 0_BOOL;
    var_PhaseDT = 0_TIME;
  }

  void FORTE_EC_Pump::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
    do {
      switch(mECCState) {
        case scmStateSTART:
          if(scmEventPLAYID == paEIID) enterStatePlay(paECET);
          else
          if(scmEventPHASE_TID == paEIID) enterStateNext(paECET);
          else return; //no transition cleared
          break;
        case scmStatePlay:
          if(1) enterStateSend(paECET);
          else return; //no transition cleared
          break;
        case scmStateNext:
          if(1) enterStateSend(paECET);
          else return; //no transition cleared
          break;
        case scmStateSend:
          if(var_Timed) enterStateHold(paECET);
          else
          if(1) enterStatePlayed(paECET);
          else return; //no transition cleared
          break;
        case scmStateHold:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStatePlayed:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        default:
          DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 6.", mECCState.operator TForteUInt16 ());
          mECCState = 0; // 0 is always the initial state
          return;
      }
      paEIID = cgInvalidEventID; // we have to clear the event after the first check in order to ensure correct behavior
    } while(true);
  }

  void FORTE_EC_Pump::enterStateSTART(CEventChainExecutionThread *const) {
    mECCState = scmStateSTART;
  }

  void FORTE_EC_Pump::enterStatePlay(CEventChainExecutionThread *const paECET) {
    mECCState = scmStatePlay;
    alg_Alg_Play();
    sendOutputEvent(scmEventPHASE_STOPID, paECET);
  }

  void FORTE_EC_Pump::enterStateNext(CEventChainExecutionThread *const) {
    mECCState = scmStateNext;
    alg_Alg_Next();
  }

  void FORTE_EC_Pump::enterStateSend(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateSend;
    alg_Alg_Send();
    sendOutputEvent(scmEventOUTID, paECET);
  }

  void FORTE_EC_Pump::enterStateHold(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateHold;
    sendOutputEvent(scmEventPHASE_STARTID, paECET);
  }

  void FORTE_EC_Pump::enterStatePlayed(CEventChainExecutionThread *const paECET) {
    mECCState = scmStatePlayed;
    sendOutputEvent(scmEventPLAYEDID, paECET);
  }

  void FORTE_EC_Pump::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventPLAYID: {
        readData(0, var_Holder, conn_Holder);
        readData(1, var_Command, conn_Command);
        readData(2, var_Release, conn_Release);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_EC_Pump::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventOUTID: {
        writeData(3, var_O_Holder, conn_O_Holder);
        writeData(4, var_O_Release, conn_O_Release);
        break;
      }
      case scmEventPHASE_STARTID: {
        writeData(5, var_PhaseDT, conn_PhaseDT);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_EC_Pump::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Holder;
      case 1: return &var_Command;
      case 2: return &var_Release;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_EC_Pump::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_O_Holder;
      case 1: return &var_O_Release;
      case 2: return &var_PhaseDT;
    }
    return nullptr;
  }

  CEventConnection *FORTE_EC_Pump::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_OUT;
      case 1: return &conn_PHASE_START;
      case 2: return &conn_PHASE_STOP;
      case 3: return &conn_PLAYED;
    }
    return nullptr;
  }

  CDataConnection **FORTE_EC_Pump::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Holder;
      case 1: return &conn_Command;
      case 2: return &conn_Release;
    }
    return nullptr;
  }

  CDataConnection *FORTE_EC_Pump::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_O_Holder;
      case 1: return &conn_O_Release;
      case 2: return &conn_PhaseDT;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_EC_Pump::getVarInternal(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Phase;
      case 1: return &var_Timed;
    }
    return nullptr;
  }

  void FORTE_EC_Pump::alg_Alg_Play(void) {

    #line 2 "EC_Pump.fbt"
    var_Phase = 0_USINT;
  }

  void FORTE_EC_Pump::alg_Alg_Next(void) {

    #line 6 "EC_Pump.fbt"
    var_Phase = func_ADD<CIEC_USINT>(var_Phase, 1_USINT);
  }

  void FORTE_EC_Pump::alg_Alg_Send(void) {

    #line 10 "EC_Pump.fbt"
    var_Timed = false_BOOL;
    #line 11 "EC_Pump.fbt"
    var_PhaseDT = 0_TIME;
    #line 12 "EC_Pump.fbt"
    var_O_Holder = var_Holder;
    #line 13 "EC_Pump.fbt"
    var_O_Release = func_AND<CIEC_BOOL>(var_Release, func_NOT<CIEC_BOOL>(var_Timed));
  }

}