/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: EL_LinearAxis
 *** Description: The logic of an equipment block: one holder at a time, outputs switched off before new ones go on, all off on release or abort, inputs reported when they change. Technical: LinearAxis: output values from its holder -> outputs (break before make); one holder at a time; all off on release or when the module aborts; inputs -> state channel when they change
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/filling/EL_LinearAxis_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"
#include "forte/iec61131_functions/func_ABS.h"
#include "forte/iec61131_functions/func_ADD.h"
#include "forte/iec61131_functions/func_AND.h"
#include "forte/iec61131_functions/func_CONCAT.h"
#include "forte/iec61131_functions/func_DIV.h"
#include "forte/iec61131_functions/func_EQ.h"
#include "forte/iec61131_functions/func_GE.h"
#include "forte/iec61131_functions/func_GT.h"
#include "forte/iec61131_functions/func_MUL.h"
#include "forte/iec61131_functions/func_MUL_TIME.h"
#include "forte/iec61131_functions/func_NE.h"
#include "forte/iec61131_functions/func_NOT.h"
#include "forte/iec61131_functions/func_NOW_MONOTONIC.h"
#include "forte/iec61131_functions/func_OR.h"
#include "forte/iec61131_functions/func_SUB.h"
#include "forte/iec61131_functions/func_TIME_IN_MS_TO_LREAL.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::filling {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:aWJym7WQGzbuGEDVc2yOP7H9dbDr6iC_NBIHf8ldnPfGcqLzzsfDqZ-gSMfn3iKeU8hL0u-_eyvrBF66V0WVTA=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "CMD"_STRID, "RELEASE"_STRID, "SAMPLE"_STRID, "REFRESH"_STRID, "DRIVEN"_STRID, "MOD_CHG"_STRID, "MOVE_T"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "DRIVE"_STRID, "STATE"_STRID, "MOVE_START"_STRID, "MOVE_STOP"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"Module"_STRID, "Name"_STRID, "UaRoot"_STRID, "C_Holder"_STRID, "C_Release"_STRID, "C_Enable"_STRID, "C_Down"_STRID, "C_Step"_STRID, "CE_Step"_STRID, "C_Move"_STRID, "C_Goal"_STRID, "R_Holder"_STRID, "I_AtHome"_STRID, "ModuleState"_STRID};
    const auto cDataOutputNames = std::array{"IdCmd"_STRID, "IdRelease"_STRID, "IdState"_STRID, "IdPub"_STRID, "O_Enable"_STRID, "O_Down"_STRID, "O_Step"_STRID, "E_Step"_STRID, "AtHome"_STRID, "ActualPosition"_STRID, "Homed"_STRID, "Moving"_STRID, "Holder"_STRID, "MoveDT"_STRID};
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

    const auto cInternalsNames = std::array{"Publish"_STRID, "Beat"_STRID, "LastHolder"_STRID, "Pending"_STRID, "OffPending"_STRID, "L_AtHome"_STRID, "L_Homed"_STRID, "L_Moving"_STRID, "N_Enable"_STRID, "N_Down"_STRID, "N_Step"_STRID, "NE_Step"_STRID, "N_Move"_STRID, "N_Goal"_STRID, "MoveGoal"_STRID, "MoveFrom"_STRID, "MoveDir"_STRID, "MoveSince"_STRID, "MoveStart"_STRID, "Uncounted"_STRID};
  }

  DEFINE_FIRMWARE_FB(FORTE_EL_LinearAxis, "filling::EL_LinearAxis"_STRID, TypeHash)

  FORTE_EL_LinearAxis::FORTE_EL_LinearAxis(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CBasicFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cInternalsNames),
      var_Publish(0_BOOL),
      var_Beat(0_USINT),
      var_LastHolder(u""_WSTRING),
      var_Pending(0_BOOL),
      var_OffPending(0_BOOL),
      var_L_AtHome(0_BOOL),
      var_L_Homed(0_BOOL),
      var_L_Moving(0_BOOL),
      var_N_Enable(0_BOOL),
      var_N_Down(0_BOOL),
      var_N_Step(0_LREAL),
      var_NE_Step(0_BOOL),
      var_N_Move(0_BOOL),
      var_N_Goal(0_LREAL),
      var_MoveGoal(0_LREAL),
      var_MoveFrom(0_LREAL),
      var_MoveDir(0_LREAL),
      var_MoveSince(0_TIME),
      var_MoveStart(0_BOOL),
      var_Uncounted(0_BOOL),
      var_Module(u""_WSTRING),
      var_Name(u""_WSTRING),
      var_UaRoot(u""_WSTRING),
      var_C_Holder(u""_WSTRING),
      var_C_Release(0_BOOL),
      var_C_Enable(0_BOOL),
      var_C_Down(0_BOOL),
      var_C_Step(0_LREAL),
      var_CE_Step(0_BOOL),
      var_C_Move(0_BOOL),
      var_C_Goal(0_LREAL),
      var_R_Holder(u""_WSTRING),
      var_I_AtHome(0_BOOL),
      var_ModuleState(0_USINT),
      var_IdCmd(u""_WSTRING),
      var_IdRelease(u""_WSTRING),
      var_IdState(u""_WSTRING),
      var_IdPub(u""_WSTRING),
      var_O_Enable(0_BOOL),
      var_O_Down(0_BOOL),
      var_O_Step(0_LREAL),
      var_E_Step(0_BOOL),
      var_AtHome(0_BOOL),
      var_ActualPosition(0_LREAL),
      var_Homed(0_BOOL),
      var_Moving(0_BOOL),
      var_Holder(u""_WSTRING),
      var_MoveDT(0_TIME),
      conn_INITO(*this, 0),
      conn_DRIVE(*this, 1),
      conn_STATE(*this, 2),
      conn_MOVE_START(*this, 3),
      conn_MOVE_STOP(*this, 4),
      conn_Module(nullptr),
      conn_Name(nullptr),
      conn_UaRoot(nullptr),
      conn_C_Holder(nullptr),
      conn_C_Release(nullptr),
      conn_C_Enable(nullptr),
      conn_C_Down(nullptr),
      conn_C_Step(nullptr),
      conn_CE_Step(nullptr),
      conn_C_Move(nullptr),
      conn_C_Goal(nullptr),
      conn_R_Holder(nullptr),
      conn_I_AtHome(nullptr),
      conn_ModuleState(nullptr),
      conn_IdCmd(*this, 0, var_IdCmd),
      conn_IdRelease(*this, 1, var_IdRelease),
      conn_IdState(*this, 2, var_IdState),
      conn_IdPub(*this, 3, var_IdPub),
      conn_O_Enable(*this, 4, var_O_Enable),
      conn_O_Down(*this, 5, var_O_Down),
      conn_O_Step(*this, 6, var_O_Step),
      conn_E_Step(*this, 7, var_E_Step),
      conn_AtHome(*this, 8, var_AtHome),
      conn_ActualPosition(*this, 9, var_ActualPosition),
      conn_Homed(*this, 10, var_Homed),
      conn_Moving(*this, 11, var_Moving),
      conn_Holder(*this, 12, var_Holder),
      conn_MoveDT(*this, 13, var_MoveDT) {
  }

  void FORTE_EL_LinearAxis::setInitialValues() {
    CBasicFB::setInitialValues();
    var_Publish = 0_BOOL;
    var_Beat = 0_USINT;
    var_LastHolder = u""_WSTRING;
    var_Pending = 0_BOOL;
    var_OffPending = 0_BOOL;
    var_L_AtHome = 0_BOOL;
    var_L_Homed = 0_BOOL;
    var_L_Moving = 0_BOOL;
    var_N_Enable = 0_BOOL;
    var_N_Down = 0_BOOL;
    var_N_Step = 0_LREAL;
    var_NE_Step = 0_BOOL;
    var_N_Move = 0_BOOL;
    var_N_Goal = 0_LREAL;
    var_MoveGoal = 0_LREAL;
    var_MoveFrom = 0_LREAL;
    var_MoveDir = 0_LREAL;
    var_MoveSince = 0_TIME;
    var_MoveStart = 0_BOOL;
    var_Uncounted = 0_BOOL;
    var_Module = u""_WSTRING;
    var_Name = u""_WSTRING;
    var_UaRoot = u""_WSTRING;
    var_C_Holder = u""_WSTRING;
    var_C_Release = 0_BOOL;
    var_C_Enable = 0_BOOL;
    var_C_Down = 0_BOOL;
    var_C_Step = 0_LREAL;
    var_CE_Step = 0_BOOL;
    var_C_Move = 0_BOOL;
    var_C_Goal = 0_LREAL;
    var_R_Holder = u""_WSTRING;
    var_I_AtHome = 0_BOOL;
    var_ModuleState = 0_USINT;
    var_IdCmd = u""_WSTRING;
    var_IdRelease = u""_WSTRING;
    var_IdState = u""_WSTRING;
    var_IdPub = u""_WSTRING;
    var_O_Enable = 0_BOOL;
    var_O_Down = 0_BOOL;
    var_O_Step = 0_LREAL;
    var_E_Step = 0_BOOL;
    var_AtHome = 0_BOOL;
    var_ActualPosition = 0_LREAL;
    var_Homed = 0_BOOL;
    var_Moving = 0_BOOL;
    var_Holder = u""_WSTRING;
    var_MoveDT = 0_TIME;
  }

  void FORTE_EL_LinearAxis::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
    do {
      switch(mECCState) {
        case scmStateSTART:
          if(scmEventINITID == paEIID) enterStateInit(paECET);
          else
          if(scmEventSAMPLEID == paEIID) enterStateSample(paECET);
          else
          if(scmEventREFRESHID == paEIID) enterStateRefresh(paECET);
          else
          if((scmEventCMDID == paEIID) && (func_OR<CIEC_BOOL>(func_EQ(var_Holder, u""_WSTRING), func_EQ(var_C_Holder, var_Holder)))) enterStateCmd(paECET);
          else
          if((scmEventRELEASEID == paEIID) && (func_AND<CIEC_BOOL>(func_EQ(var_R_Holder, var_Holder), func_NE(var_Holder, u""_WSTRING)))) enterStateOff(paECET);
          else
          if((scmEventMOD_CHGID == paEIID) && (func_OR<CIEC_BOOL>(func_EQ(var_ModuleState, 8_USINT), func_EQ(var_ModuleState, 9_USINT)))) enterStateOff(paECET);
          else
          if((scmEventMOVE_TID == paEIID) && (func_AND<CIEC_BOOL>(var_Moving, func_NOT<CIEC_BOOL>(var_MoveStart)))) enterStateMoveEnd(paECET);
          else return; //no transition cleared
          break;
        case scmStateInit:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStateSample:
          if(var_Publish) enterStatePublish(paECET);
          else
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStatePublish:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStateRefresh:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStateCmd:
          if(1) enterStateBreak(paECET);
          else return; //no transition cleared
          break;
        case scmStateOff:
          if(1) enterStateBreak(paECET);
          else return; //no transition cleared
          break;
        case scmStateBreak:
          if(1) enterStateBreakW(paECET);
          else return; //no transition cleared
          break;
        case scmStateMake:
          if(1) enterStateMakeW(paECET);
          else return; //no transition cleared
          break;
        case scmStateBreakW:
          if(scmEventDRIVENID == paEIID) enterStateMake(paECET);
          else
          if(scmEventCMDID == paEIID) enterStateQueueB(paECET);
          else
          if((scmEventRELEASEID == paEIID) && (func_AND<CIEC_BOOL>(func_EQ(var_R_Holder, var_Holder), func_NE(var_Holder, u""_WSTRING)))) enterStateOffB(paECET);
          else
          if((scmEventMOD_CHGID == paEIID) && (func_OR<CIEC_BOOL>(func_EQ(var_ModuleState, 8_USINT), func_EQ(var_ModuleState, 9_USINT)))) enterStateOffB(paECET);
          else return; //no transition cleared
          break;
        case scmStateMakeW:
          if(scmEventDRIVENID == paEIID) enterStateSettled(paECET);
          else
          if(scmEventCMDID == paEIID) enterStateQueueM(paECET);
          else
          if((scmEventRELEASEID == paEIID) && (func_AND<CIEC_BOOL>(func_EQ(var_R_Holder, var_Holder), func_NE(var_Holder, u""_WSTRING)))) enterStateOffM(paECET);
          else
          if((scmEventMOD_CHGID == paEIID) && (func_OR<CIEC_BOOL>(func_EQ(var_ModuleState, 8_USINT), func_EQ(var_ModuleState, 9_USINT)))) enterStateOffM(paECET);
          else return; //no transition cleared
          break;
        case scmStateQueueB:
          if(1) enterStateBreakW(paECET);
          else return; //no transition cleared
          break;
        case scmStateOffB:
          if(1) enterStateBreakW(paECET);
          else return; //no transition cleared
          break;
        case scmStateQueueM:
          if(1) enterStateMakeW(paECET);
          else return; //no transition cleared
          break;
        case scmStateOffM:
          if(1) enterStateMakeW(paECET);
          else return; //no transition cleared
          break;
        case scmStateCmdPend:
          if(func_OR<CIEC_BOOL>(func_EQ(var_Holder, u""_WSTRING), func_EQ(var_C_Holder, var_Holder))) enterStateCmd(paECET);
          else
          if(var_MoveStart) enterStateMoveGo(paECET);
          else
          if(1) enterStateReport(paECET);
          else return; //no transition cleared
          break;
        case scmStateSettled:
          if(var_OffPending) enterStateOff(paECET);
          else
          if(var_Pending) enterStateCmdPend(paECET);
          else
          if(var_MoveStart) enterStateMoveGo(paECET);
          else
          if(1) enterStateReport(paECET);
          else return; //no transition cleared
          break;
        case scmStateMoveGo:
          if(1) enterStateReport(paECET);
          else return; //no transition cleared
          break;
        case scmStateMoveEnd:
          if(1) enterStateBreak(paECET);
          else return; //no transition cleared
          break;
        case scmStateReport:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        default:
          DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 20.", mECCState.operator TForteUInt16 ());
          mECCState = 0; // 0 is always the initial state
          return;
      }
      paEIID = cgInvalidEventID; // we have to clear the event after the first check in order to ensure correct behavior
    } while(true);
  }

  void FORTE_EL_LinearAxis::enterStateSTART(CEventChainExecutionThread *const) {
    mECCState = scmStateSTART;
  }

  void FORTE_EL_LinearAxis::enterStateInit(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateInit;
    alg_Alg_Init();
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_EL_LinearAxis::enterStateSample(CEventChainExecutionThread *const) {
    mECCState = scmStateSample;
    alg_Alg_Sample();
  }

  void FORTE_EL_LinearAxis::enterStatePublish(CEventChainExecutionThread *const paECET) {
    mECCState = scmStatePublish;
    alg_Alg_Publish();
    sendOutputEvent(scmEventSTATEID, paECET);
  }

  void FORTE_EL_LinearAxis::enterStateRefresh(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateRefresh;
    sendOutputEvent(scmEventDRIVEID, paECET);
  }

  void FORTE_EL_LinearAxis::enterStateCmd(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateCmd;
    alg_Alg_Cmd();
    sendOutputEvent(scmEventMOVE_STOPID, paECET);
  }

  void FORTE_EL_LinearAxis::enterStateOff(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateOff;
    alg_Alg_Off();
    sendOutputEvent(scmEventMOVE_STOPID, paECET);
  }

  void FORTE_EL_LinearAxis::enterStateBreak(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateBreak;
    alg_Alg_Break();
    sendOutputEvent(scmEventDRIVEID, paECET);
  }

  void FORTE_EL_LinearAxis::enterStateMake(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateMake;
    alg_Alg_Make();
    sendOutputEvent(scmEventDRIVEID, paECET);
  }

  void FORTE_EL_LinearAxis::enterStateBreakW(CEventChainExecutionThread *const) {
    mECCState = scmStateBreakW;
  }

  void FORTE_EL_LinearAxis::enterStateMakeW(CEventChainExecutionThread *const) {
    mECCState = scmStateMakeW;
  }

  void FORTE_EL_LinearAxis::enterStateQueueB(CEventChainExecutionThread *const) {
    mECCState = scmStateQueueB;
    alg_Alg_QueueB();
  }

  void FORTE_EL_LinearAxis::enterStateOffB(CEventChainExecutionThread *const) {
    mECCState = scmStateOffB;
    alg_Alg_OffB();
  }

  void FORTE_EL_LinearAxis::enterStateQueueM(CEventChainExecutionThread *const) {
    mECCState = scmStateQueueM;
    alg_Alg_QueueM();
  }

  void FORTE_EL_LinearAxis::enterStateOffM(CEventChainExecutionThread *const) {
    mECCState = scmStateOffM;
    alg_Alg_OffM();
  }

  void FORTE_EL_LinearAxis::enterStateCmdPend(CEventChainExecutionThread *const) {
    mECCState = scmStateCmdPend;
    alg_Alg_CmdPend();
  }

  void FORTE_EL_LinearAxis::enterStateSettled(CEventChainExecutionThread *const) {
    mECCState = scmStateSettled;
  }

  void FORTE_EL_LinearAxis::enterStateMoveGo(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateMoveGo;
    alg_Alg_MoveGo();
    sendOutputEvent(scmEventMOVE_STARTID, paECET);
  }

  void FORTE_EL_LinearAxis::enterStateMoveEnd(CEventChainExecutionThread *const) {
    mECCState = scmStateMoveEnd;
    alg_Alg_MoveEnd();
  }

  void FORTE_EL_LinearAxis::enterStateReport(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateReport;
    alg_Alg_Report();
    sendOutputEvent(scmEventSTATEID, paECET);
  }

  void FORTE_EL_LinearAxis::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, var_Module, conn_Module);
        readData(1, var_Name, conn_Name);
        readData(2, var_UaRoot, conn_UaRoot);
        break;
      }
      case scmEventCMDID: {
        readData(3, var_C_Holder, conn_C_Holder);
        readData(4, var_C_Release, conn_C_Release);
        readData(5, var_C_Enable, conn_C_Enable);
        readData(6, var_C_Down, conn_C_Down);
        readData(7, var_C_Step, conn_C_Step);
        readData(8, var_CE_Step, conn_CE_Step);
        readData(9, var_C_Move, conn_C_Move);
        readData(10, var_C_Goal, conn_C_Goal);
        break;
      }
      case scmEventRELEASEID: {
        readData(11, var_R_Holder, conn_R_Holder);
        break;
      }
      case scmEventSAMPLEID: {
        readData(12, var_I_AtHome, conn_I_AtHome);
        break;
      }
      case scmEventMOD_CHGID: {
        readData(13, var_ModuleState, conn_ModuleState);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_EL_LinearAxis::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(14, var_IdCmd, conn_IdCmd);
        writeData(15, var_IdRelease, conn_IdRelease);
        writeData(16, var_IdState, conn_IdState);
        writeData(17, var_IdPub, conn_IdPub);
        break;
      }
      case scmEventDRIVEID: {
        writeData(18, var_O_Enable, conn_O_Enable);
        writeData(19, var_O_Down, conn_O_Down);
        writeData(20, var_O_Step, conn_O_Step);
        writeData(21, var_E_Step, conn_E_Step);
        break;
      }
      case scmEventSTATEID: {
        writeData(22, var_AtHome, conn_AtHome);
        writeData(23, var_ActualPosition, conn_ActualPosition);
        writeData(24, var_Homed, conn_Homed);
        writeData(25, var_Moving, conn_Moving);
        writeData(26, var_Holder, conn_Holder);
        break;
      }
      case scmEventMOVE_STARTID: {
        writeData(27, var_MoveDT, conn_MoveDT);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_EL_LinearAxis::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Module;
      case 1: return &var_Name;
      case 2: return &var_UaRoot;
      case 3: return &var_C_Holder;
      case 4: return &var_C_Release;
      case 5: return &var_C_Enable;
      case 6: return &var_C_Down;
      case 7: return &var_C_Step;
      case 8: return &var_CE_Step;
      case 9: return &var_C_Move;
      case 10: return &var_C_Goal;
      case 11: return &var_R_Holder;
      case 12: return &var_I_AtHome;
      case 13: return &var_ModuleState;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_EL_LinearAxis::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_IdCmd;
      case 1: return &var_IdRelease;
      case 2: return &var_IdState;
      case 3: return &var_IdPub;
      case 4: return &var_O_Enable;
      case 5: return &var_O_Down;
      case 6: return &var_O_Step;
      case 7: return &var_E_Step;
      case 8: return &var_AtHome;
      case 9: return &var_ActualPosition;
      case 10: return &var_Homed;
      case 11: return &var_Moving;
      case 12: return &var_Holder;
      case 13: return &var_MoveDT;
    }
    return nullptr;
  }

  CEventConnection *FORTE_EL_LinearAxis::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_DRIVE;
      case 2: return &conn_STATE;
      case 3: return &conn_MOVE_START;
      case 4: return &conn_MOVE_STOP;
    }
    return nullptr;
  }

  CDataConnection **FORTE_EL_LinearAxis::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Module;
      case 1: return &conn_Name;
      case 2: return &conn_UaRoot;
      case 3: return &conn_C_Holder;
      case 4: return &conn_C_Release;
      case 5: return &conn_C_Enable;
      case 6: return &conn_C_Down;
      case 7: return &conn_C_Step;
      case 8: return &conn_CE_Step;
      case 9: return &conn_C_Move;
      case 10: return &conn_C_Goal;
      case 11: return &conn_R_Holder;
      case 12: return &conn_I_AtHome;
      case 13: return &conn_ModuleState;
    }
    return nullptr;
  }

  CDataConnection *FORTE_EL_LinearAxis::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_IdCmd;
      case 1: return &conn_IdRelease;
      case 2: return &conn_IdState;
      case 3: return &conn_IdPub;
      case 4: return &conn_O_Enable;
      case 5: return &conn_O_Down;
      case 6: return &conn_O_Step;
      case 7: return &conn_E_Step;
      case 8: return &conn_AtHome;
      case 9: return &conn_ActualPosition;
      case 10: return &conn_Homed;
      case 11: return &conn_Moving;
      case 12: return &conn_Holder;
      case 13: return &conn_MoveDT;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_EL_LinearAxis::getVarInternal(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Publish;
      case 1: return &var_Beat;
      case 2: return &var_LastHolder;
      case 3: return &var_Pending;
      case 4: return &var_OffPending;
      case 5: return &var_L_AtHome;
      case 6: return &var_L_Homed;
      case 7: return &var_L_Moving;
      case 8: return &var_N_Enable;
      case 9: return &var_N_Down;
      case 10: return &var_N_Step;
      case 11: return &var_NE_Step;
      case 12: return &var_N_Move;
      case 13: return &var_N_Goal;
      case 14: return &var_MoveGoal;
      case 15: return &var_MoveFrom;
      case 16: return &var_MoveDir;
      case 17: return &var_MoveSince;
      case 18: return &var_MoveStart;
      case 19: return &var_Uncounted;
    }
    return nullptr;
  }

  void FORTE_EL_LinearAxis::alg_Alg_Init(void) {

    #line 2 "EL_LinearAxis.fbt"
    var_IdCmd = func_CONCAT(func_CONCAT(func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/"_WSTRING), var_Name), u"/cmd]"_WSTRING);
    #line 3 "EL_LinearAxis.fbt"
    var_IdRelease = func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/release]"_WSTRING);
    #line 4 "EL_LinearAxis.fbt"
    var_IdState = func_CONCAT(func_CONCAT(func_CONCAT(func_CONCAT(u"loc["_WSTRING, var_Module), u"/"_WSTRING), var_Name), u"/state]"_WSTRING);
    #line 5 "EL_LinearAxis.fbt"
    var_IdPub = func_CONCAT(func_CONCAT(func_CONCAT(func_CONCAT(func_CONCAT(func_CONCAT(func_CONCAT(func_CONCAT(func_CONCAT(func_CONCAT(func_CONCAT(func_CONCAT(func_CONCAT(func_CONCAT(func_CONCAT(func_CONCAT(func_CONCAT(u"opc_ua[WRITE;"_WSTRING, var_UaRoot), u"/Equipment/"_WSTRING), var_Name), u"/AtHome;"_WSTRING), var_UaRoot), u"/Equipment/"_WSTRING), var_Name), u"/ActualPosition;"_WSTRING), var_UaRoot), u"/Equipment/"_WSTRING), var_Name), u"/Homed;"_WSTRING), var_UaRoot), u"/Equipment/"_WSTRING), var_Name), u"/Moving"_WSTRING), u"]"_WSTRING);
  }

  void FORTE_EL_LinearAxis::alg_Alg_Sample(void) {

    #line 9 "EL_LinearAxis.fbt"
    var_AtHome = var_I_AtHome;
    #line 10 "EL_LinearAxis.fbt"
    if (func_AND<CIEC_BOOL>(var_Moving, func_NOT<CIEC_BOOL>(var_MoveStart))) {
      #line 11 "EL_LinearAxis.fbt"
      var_ActualPosition = func_ADD<CIEC_LREAL>(var_MoveFrom, func_DIV<CIEC_LREAL>(func_MUL<CIEC_LREAL>(func_MUL<CIEC_LREAL>(var_MoveDir, 12.5_LREAL), func_TIME_IN_MS_TO_LREAL(func_SUB<CIEC_TIME>(func_NOW_MONOTONIC(), var_MoveSince))), 1000.0_LREAL));
      #line 12 "EL_LinearAxis.fbt"
      if (func_GT(func_MUL<CIEC_LREAL>(var_MoveDir, func_SUB<CIEC_LREAL>(var_ActualPosition, var_MoveGoal)), 0.0_LREAL)) {
        #line 13 "EL_LinearAxis.fbt"
        var_ActualPosition = var_MoveGoal;
      }
    }
    else if (var_AtHome) {
      #line 16 "EL_LinearAxis.fbt"
      var_ActualPosition = 0.0_LREAL;
      #line 17 "EL_LinearAxis.fbt"
      var_Homed = true_BOOL;
    }
    else if (var_Uncounted) {
      #line 19 "EL_LinearAxis.fbt"
      var_Homed = false_BOOL;
    }
    #line 21 "EL_LinearAxis.fbt"
    var_Publish = func_OR<CIEC_BOOL>(func_OR<CIEC_BOOL>(func_OR<CIEC_BOOL>(func_OR<CIEC_BOOL>(func_OR<CIEC_BOOL>(func_NE(var_AtHome, var_L_AtHome), func_NE(var_Homed, var_L_Homed)), func_NE(var_Moving, var_L_Moving)), func_NE(var_Holder, var_LastHolder)), func_GE(var_Beat, 20_USINT)), func_AND<CIEC_BOOL>(var_Moving, func_GE(var_Beat, 4_USINT)));
    #line 22 "EL_LinearAxis.fbt"
    var_Beat = func_ADD<CIEC_USINT>(var_Beat, 1_USINT);
  }

  void FORTE_EL_LinearAxis::alg_Alg_Publish(void) {

    #line 26 "EL_LinearAxis.fbt"
    var_L_AtHome = var_AtHome;
    #line 27 "EL_LinearAxis.fbt"
    var_L_Homed = var_Homed;
    #line 28 "EL_LinearAxis.fbt"
    var_L_Moving = var_Moving;
    #line 29 "EL_LinearAxis.fbt"
    var_LastHolder = var_Holder;
    #line 30 "EL_LinearAxis.fbt"
    var_Beat = 0_USINT;
  }

  void FORTE_EL_LinearAxis::alg_Alg_Cmd(void) {

    #line 34 "EL_LinearAxis.fbt"
    var_Holder = var_C_Holder;
    #line 35 "EL_LinearAxis.fbt"
    var_N_Enable = var_C_Enable;
    #line 36 "EL_LinearAxis.fbt"
    var_N_Down = var_C_Down;
    #line 37 "EL_LinearAxis.fbt"
    var_N_Step = var_C_Step;
    #line 38 "EL_LinearAxis.fbt"
    var_NE_Step = var_CE_Step;
    #line 39 "EL_LinearAxis.fbt"
    var_N_Move = var_C_Move;
    #line 40 "EL_LinearAxis.fbt"
    var_N_Goal = var_C_Goal;
    #line 41 "EL_LinearAxis.fbt"
    if (func_AND<CIEC_BOOL>(var_Moving, func_NOT<CIEC_BOOL>(var_MoveStart))) {
      #line 42 "EL_LinearAxis.fbt"
      var_ActualPosition = func_ADD<CIEC_LREAL>(var_MoveFrom, func_DIV<CIEC_LREAL>(func_MUL<CIEC_LREAL>(func_MUL<CIEC_LREAL>(var_MoveDir, 12.5_LREAL), func_TIME_IN_MS_TO_LREAL(func_SUB<CIEC_TIME>(func_NOW_MONOTONIC(), var_MoveSince))), 1000.0_LREAL));
      #line 43 "EL_LinearAxis.fbt"
      if (func_GT(func_MUL<CIEC_LREAL>(var_MoveDir, func_SUB<CIEC_LREAL>(var_ActualPosition, var_MoveGoal)), 0.0_LREAL)) {
        #line 44 "EL_LinearAxis.fbt"
        var_ActualPosition = var_MoveGoal;
      }
    }
    #line 47 "EL_LinearAxis.fbt"
    var_Moving = false_BOOL;
    #line 48 "EL_LinearAxis.fbt"
    var_MoveStart = false_BOOL;
    #line 49 "EL_LinearAxis.fbt"
    if (var_N_Move) {
      #line 50 "EL_LinearAxis.fbt"
      if (func_AND<CIEC_BOOL>(var_Homed, func_GE(func_ABS(func_SUB<CIEC_LREAL>(var_N_Goal, var_ActualPosition)), 0.0005_LREAL))) {
        #line 51 "EL_LinearAxis.fbt"
        var_MoveGoal = var_N_Goal;
        #line 52 "EL_LinearAxis.fbt"
        var_MoveFrom = var_ActualPosition;
        #line 53 "EL_LinearAxis.fbt"
        var_MoveDT = func_MUL_TIME(1000000000_TIME, func_DIV<CIEC_LREAL>(func_ABS(func_SUB<CIEC_LREAL>(var_N_Goal, var_ActualPosition)), 12.5_LREAL));
        #line 54 "EL_LinearAxis.fbt"
        if (func_GT(var_N_Goal, var_ActualPosition)) {
          #line 55 "EL_LinearAxis.fbt"
          var_MoveDir = 1.0_LREAL;
          #line 56 "EL_LinearAxis.fbt"
          var_N_Enable = true_BOOL;
          #line 57 "EL_LinearAxis.fbt"
          var_N_Down = true_BOOL;
          #line 58 "EL_LinearAxis.fbt"
          var_N_Step = 50.0_LREAL;
          #line 59 "EL_LinearAxis.fbt"
          var_NE_Step = true_BOOL;
        }
        else {
          #line 61 "EL_LinearAxis.fbt"
          var_MoveDir = -1.0_LREAL;
          #line 62 "EL_LinearAxis.fbt"
          var_N_Enable = true_BOOL;
          #line 63 "EL_LinearAxis.fbt"
          var_N_Down = false_BOOL;
          #line 64 "EL_LinearAxis.fbt"
          var_N_Step = 50.0_LREAL;
          #line 65 "EL_LinearAxis.fbt"
          var_NE_Step = true_BOOL;
        }
        #line 67 "EL_LinearAxis.fbt"
        var_Moving = true_BOOL;
        #line 68 "EL_LinearAxis.fbt"
        var_MoveStart = true_BOOL;
      }
      else {
        #line 70 "EL_LinearAxis.fbt"
        var_N_Enable = false_BOOL;
        #line 71 "EL_LinearAxis.fbt"
        var_N_Down = false_BOOL;
        #line 72 "EL_LinearAxis.fbt"
        var_N_Step = 0.0_LREAL;
        #line 73 "EL_LinearAxis.fbt"
        var_NE_Step = false_BOOL;
      }
      #line 75 "EL_LinearAxis.fbt"
      var_Uncounted = false_BOOL;
    }
    else {
      #line 77 "EL_LinearAxis.fbt"
      var_Uncounted = func_OR<CIEC_BOOL>(func_OR<CIEC_BOOL>(var_N_Enable, var_N_Down), var_NE_Step);
    }
    #line 79 "EL_LinearAxis.fbt"
    if (var_C_Release) {
      #line 80 "EL_LinearAxis.fbt"
      var_Holder = u""_WSTRING;
    }
  }

  void FORTE_EL_LinearAxis::alg_Alg_Off(void) {

    #line 85 "EL_LinearAxis.fbt"
    var_N_Enable = false_BOOL;
    #line 86 "EL_LinearAxis.fbt"
    var_N_Down = false_BOOL;
    #line 87 "EL_LinearAxis.fbt"
    var_N_Step = 0.0_LREAL;
    #line 88 "EL_LinearAxis.fbt"
    var_NE_Step = false_BOOL;
    #line 89 "EL_LinearAxis.fbt"
    var_N_Move = false_BOOL;
    #line 90 "EL_LinearAxis.fbt"
    var_N_Goal = 0.0_LREAL;
    #line 91 "EL_LinearAxis.fbt"
    if (func_AND<CIEC_BOOL>(var_Moving, func_NOT<CIEC_BOOL>(var_MoveStart))) {
      #line 92 "EL_LinearAxis.fbt"
      var_ActualPosition = func_ADD<CIEC_LREAL>(var_MoveFrom, func_DIV<CIEC_LREAL>(func_MUL<CIEC_LREAL>(func_MUL<CIEC_LREAL>(var_MoveDir, 12.5_LREAL), func_TIME_IN_MS_TO_LREAL(func_SUB<CIEC_TIME>(func_NOW_MONOTONIC(), var_MoveSince))), 1000.0_LREAL));
      #line 93 "EL_LinearAxis.fbt"
      if (func_GT(func_MUL<CIEC_LREAL>(var_MoveDir, func_SUB<CIEC_LREAL>(var_ActualPosition, var_MoveGoal)), 0.0_LREAL)) {
        #line 94 "EL_LinearAxis.fbt"
        var_ActualPosition = var_MoveGoal;
      }
    }
    #line 97 "EL_LinearAxis.fbt"
    var_Moving = false_BOOL;
    #line 98 "EL_LinearAxis.fbt"
    var_MoveStart = false_BOOL;
    #line 99 "EL_LinearAxis.fbt"
    var_Uncounted = false_BOOL;
    #line 100 "EL_LinearAxis.fbt"
    var_Holder = u""_WSTRING;
    #line 101 "EL_LinearAxis.fbt"
    var_OffPending = false_BOOL;
  }

  void FORTE_EL_LinearAxis::alg_Alg_Break(void) {

    #line 105 "EL_LinearAxis.fbt"
    var_O_Enable = func_AND<CIEC_BOOL>(var_O_Enable, var_N_Enable);
    #line 106 "EL_LinearAxis.fbt"
    var_O_Down = func_AND<CIEC_BOOL>(var_O_Down, var_N_Down);
  }

  void FORTE_EL_LinearAxis::alg_Alg_Make(void) {

    #line 110 "EL_LinearAxis.fbt"
    var_O_Enable = var_N_Enable;
    #line 111 "EL_LinearAxis.fbt"
    var_O_Down = var_N_Down;
    #line 112 "EL_LinearAxis.fbt"
    var_O_Step = var_N_Step;
    #line 113 "EL_LinearAxis.fbt"
    var_E_Step = var_NE_Step;
  }

  void FORTE_EL_LinearAxis::alg_Alg_QueueB(void) {

    #line 117 "EL_LinearAxis.fbt"
    var_Pending = true_BOOL;
  }

  void FORTE_EL_LinearAxis::alg_Alg_OffB(void) {

    #line 121 "EL_LinearAxis.fbt"
    var_OffPending = true_BOOL;
  }

  void FORTE_EL_LinearAxis::alg_Alg_QueueM(void) {

    #line 125 "EL_LinearAxis.fbt"
    var_Pending = true_BOOL;
  }

  void FORTE_EL_LinearAxis::alg_Alg_OffM(void) {

    #line 129 "EL_LinearAxis.fbt"
    var_OffPending = true_BOOL;
  }

  void FORTE_EL_LinearAxis::alg_Alg_CmdPend(void) {

    #line 133 "EL_LinearAxis.fbt"
    var_Pending = false_BOOL;
  }

  void FORTE_EL_LinearAxis::alg_Alg_MoveGo(void) {

    #line 137 "EL_LinearAxis.fbt"
    var_MoveStart = false_BOOL;
    #line 138 "EL_LinearAxis.fbt"
    var_MoveSince = func_NOW_MONOTONIC();
  }

  void FORTE_EL_LinearAxis::alg_Alg_MoveEnd(void) {

    #line 142 "EL_LinearAxis.fbt"
    var_ActualPosition = var_MoveGoal;
    #line 143 "EL_LinearAxis.fbt"
    var_Moving = false_BOOL;
    #line 144 "EL_LinearAxis.fbt"
    var_N_Enable = false_BOOL;
    #line 145 "EL_LinearAxis.fbt"
    var_N_Down = false_BOOL;
    #line 146 "EL_LinearAxis.fbt"
    var_N_Step = 0.0_LREAL;
    #line 147 "EL_LinearAxis.fbt"
    var_NE_Step = false_BOOL;
  }

  void FORTE_EL_LinearAxis::alg_Alg_Report(void) {

    #line 151 "EL_LinearAxis.fbt"
    var_LastHolder = var_Holder;
    #line 152 "EL_LinearAxis.fbt"
    var_Beat = 0_USINT;
  }

}