/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: EC_LinearAxis
 *** Description: The equipment's command table: turns a command's name (Up, Down, Run, ...) into the output values to switch, phase by phase with their times. Technical: Commands of LinearAxis as output values, in timed phases: Stop=0, Up=1, Down=2, MoveTo=3
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/filling/EC_LinearAxis_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"
#include "forte/iec61131_functions/func_ADD.h"
#include "forte/iec61131_functions/func_AND.h"
#include "forte/iec61131_functions/func_EQ.h"
#include "forte/iec61131_functions/func_NOT.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::filling {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:wBbxWA9TskateMXS2p90E5Gm0uZarObQaq90BJbPuNuWdcIA1c1ce98Bb_xbVMXW_3djWN0rzeesjUQ2Th4Evg=="sv;

    const auto cEventInputNames = std::array{"PLAY"_STRID, "PHASE_T"_STRID};
    const auto cEventOutputNames = std::array{"OUT"_STRID, "PHASE_START"_STRID, "PHASE_STOP"_STRID, "PLAYED"_STRID};
    const auto cDataInputNames = std::array{"Holder"_STRID, "Command"_STRID, "Arg"_STRID, "Release"_STRID};
    const auto cDataOutputNames = std::array{"O_Holder"_STRID, "O_Release"_STRID, "N_Enable"_STRID, "N_Down"_STRID, "N_Step"_STRID, "NE_Step"_STRID, "N_Move"_STRID, "N_Goal"_STRID, "PhaseDT"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_EC_LinearAxis, "filling::EC_LinearAxis"_STRID, TypeHash)

  FORTE_EC_LinearAxis::FORTE_EC_LinearAxis(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CBasicFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cInternalsNames),
      var_Phase(0_USINT),
      var_Timed(0_BOOL),
      var_Holder(u""_WSTRING),
      var_Command(0_USINT),
      var_Arg(0_LREAL),
      var_Release(0_BOOL),
      var_O_Holder(u""_WSTRING),
      var_O_Release(0_BOOL),
      var_N_Enable(0_BOOL),
      var_N_Down(0_BOOL),
      var_N_Step(0_LREAL),
      var_NE_Step(0_BOOL),
      var_N_Move(0_BOOL),
      var_N_Goal(0_LREAL),
      var_PhaseDT(0_TIME),
      conn_OUT(*this, 0),
      conn_PHASE_START(*this, 1),
      conn_PHASE_STOP(*this, 2),
      conn_PLAYED(*this, 3),
      conn_Holder(nullptr),
      conn_Command(nullptr),
      conn_Arg(nullptr),
      conn_Release(nullptr),
      conn_O_Holder(*this, 0, var_O_Holder),
      conn_O_Release(*this, 1, var_O_Release),
      conn_N_Enable(*this, 2, var_N_Enable),
      conn_N_Down(*this, 3, var_N_Down),
      conn_N_Step(*this, 4, var_N_Step),
      conn_NE_Step(*this, 5, var_NE_Step),
      conn_N_Move(*this, 6, var_N_Move),
      conn_N_Goal(*this, 7, var_N_Goal),
      conn_PhaseDT(*this, 8, var_PhaseDT) {
  }

  void FORTE_EC_LinearAxis::setInitialValues() {
    CBasicFB::setInitialValues();
    var_Phase = 0_USINT;
    var_Timed = 0_BOOL;
    var_Holder = u""_WSTRING;
    var_Command = 0_USINT;
    var_Arg = 0_LREAL;
    var_Release = 0_BOOL;
    var_O_Holder = u""_WSTRING;
    var_O_Release = 0_BOOL;
    var_N_Enable = 0_BOOL;
    var_N_Down = 0_BOOL;
    var_N_Step = 0_LREAL;
    var_NE_Step = 0_BOOL;
    var_N_Move = 0_BOOL;
    var_N_Goal = 0_LREAL;
    var_PhaseDT = 0_TIME;
  }

  void FORTE_EC_LinearAxis::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
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

  void FORTE_EC_LinearAxis::enterStateSTART(CEventChainExecutionThread *const) {
    mECCState = scmStateSTART;
  }

  void FORTE_EC_LinearAxis::enterStatePlay(CEventChainExecutionThread *const paECET) {
    mECCState = scmStatePlay;
    alg_Alg_Play();
    sendOutputEvent(scmEventPHASE_STOPID, paECET);
  }

  void FORTE_EC_LinearAxis::enterStateNext(CEventChainExecutionThread *const) {
    mECCState = scmStateNext;
    alg_Alg_Next();
  }

  void FORTE_EC_LinearAxis::enterStateSend(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateSend;
    alg_Alg_Send();
    sendOutputEvent(scmEventOUTID, paECET);
  }

  void FORTE_EC_LinearAxis::enterStateHold(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateHold;
    sendOutputEvent(scmEventPHASE_STARTID, paECET);
  }

  void FORTE_EC_LinearAxis::enterStatePlayed(CEventChainExecutionThread *const paECET) {
    mECCState = scmStatePlayed;
    sendOutputEvent(scmEventPLAYEDID, paECET);
  }

  void FORTE_EC_LinearAxis::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventPLAYID: {
        readData(0, var_Holder, conn_Holder);
        readData(1, var_Command, conn_Command);
        readData(2, var_Arg, conn_Arg);
        readData(3, var_Release, conn_Release);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_EC_LinearAxis::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventOUTID: {
        writeData(4, var_O_Holder, conn_O_Holder);
        writeData(5, var_O_Release, conn_O_Release);
        writeData(6, var_N_Enable, conn_N_Enable);
        writeData(7, var_N_Down, conn_N_Down);
        writeData(8, var_N_Step, conn_N_Step);
        writeData(9, var_NE_Step, conn_NE_Step);
        writeData(10, var_N_Move, conn_N_Move);
        writeData(11, var_N_Goal, conn_N_Goal);
        break;
      }
      case scmEventPHASE_STARTID: {
        writeData(12, var_PhaseDT, conn_PhaseDT);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_EC_LinearAxis::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Holder;
      case 1: return &var_Command;
      case 2: return &var_Arg;
      case 3: return &var_Release;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_EC_LinearAxis::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_O_Holder;
      case 1: return &var_O_Release;
      case 2: return &var_N_Enable;
      case 3: return &var_N_Down;
      case 4: return &var_N_Step;
      case 5: return &var_NE_Step;
      case 6: return &var_N_Move;
      case 7: return &var_N_Goal;
      case 8: return &var_PhaseDT;
    }
    return nullptr;
  }

  CEventConnection *FORTE_EC_LinearAxis::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_OUT;
      case 1: return &conn_PHASE_START;
      case 2: return &conn_PHASE_STOP;
      case 3: return &conn_PLAYED;
    }
    return nullptr;
  }

  CDataConnection **FORTE_EC_LinearAxis::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Holder;
      case 1: return &conn_Command;
      case 2: return &conn_Arg;
      case 3: return &conn_Release;
    }
    return nullptr;
  }

  CDataConnection *FORTE_EC_LinearAxis::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_O_Holder;
      case 1: return &conn_O_Release;
      case 2: return &conn_N_Enable;
      case 3: return &conn_N_Down;
      case 4: return &conn_N_Step;
      case 5: return &conn_NE_Step;
      case 6: return &conn_N_Move;
      case 7: return &conn_N_Goal;
      case 8: return &conn_PhaseDT;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_EC_LinearAxis::getVarInternal(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Phase;
      case 1: return &var_Timed;
    }
    return nullptr;
  }

  void FORTE_EC_LinearAxis::alg_Alg_Play(void) {

    #line 2 "EC_LinearAxis.fbt"
    var_Phase = 0_USINT;
  }

  void FORTE_EC_LinearAxis::alg_Alg_Next(void) {

    #line 6 "EC_LinearAxis.fbt"
    var_Phase = func_ADD<CIEC_USINT>(var_Phase, 1_USINT);
  }

  void FORTE_EC_LinearAxis::alg_Alg_Send(void) {

    #line 10 "EC_LinearAxis.fbt"
    var_N_Enable = false_BOOL;
    #line 11 "EC_LinearAxis.fbt"
    var_N_Down = false_BOOL;
    #line 12 "EC_LinearAxis.fbt"
    var_N_Step = 0.0_LREAL;
    #line 13 "EC_LinearAxis.fbt"
    var_NE_Step = false_BOOL;
    #line 14 "EC_LinearAxis.fbt"
    var_N_Move = false_BOOL;
    #line 15 "EC_LinearAxis.fbt"
    var_N_Goal = 0.0_LREAL;
    #line 16 "EC_LinearAxis.fbt"
    var_Timed = false_BOOL;
    #line 17 "EC_LinearAxis.fbt"
    var_PhaseDT = 0_TIME;
    #line 18 "EC_LinearAxis.fbt"
    if (func_EQ(var_Command, 1_USINT)) {
      #line 19 "EC_LinearAxis.fbt"
      var_N_Enable = true_BOOL;
      #line 20 "EC_LinearAxis.fbt"
      var_N_Step = 50.0_LREAL;
      #line 21 "EC_LinearAxis.fbt"
      var_NE_Step = true_BOOL;
    }
    else if (func_EQ(var_Command, 2_USINT)) {
      #line 23 "EC_LinearAxis.fbt"
      var_N_Enable = true_BOOL;
      #line 24 "EC_LinearAxis.fbt"
      var_N_Down = true_BOOL;
      #line 25 "EC_LinearAxis.fbt"
      var_N_Step = 50.0_LREAL;
      #line 26 "EC_LinearAxis.fbt"
      var_NE_Step = true_BOOL;
    }
    else if (func_EQ(var_Command, 3_USINT)) {
      #line 28 "EC_LinearAxis.fbt"
      var_N_Move = true_BOOL;
      #line 29 "EC_LinearAxis.fbt"
      var_N_Goal = var_Arg;
    }
    #line 31 "EC_LinearAxis.fbt"
    var_O_Holder = var_Holder;
    #line 32 "EC_LinearAxis.fbt"
    var_O_Release = func_AND<CIEC_BOOL>(var_Release, func_NOT<CIEC_BOOL>(var_Timed));
  }

}