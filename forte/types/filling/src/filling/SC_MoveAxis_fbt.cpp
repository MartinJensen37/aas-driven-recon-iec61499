/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SC_MoveAxis
 *** Description: The contract of a skill primitive, the only part that is its own: which command it sends (and with what argument, and which when it ends), how long it may run, and three conditions on the equipment's signals and its parameters: when it may start, when it is done, what must hold while it runs. Technical: MoveAxis: Precondition Homed; LinearAxis.MoveTo until NOT Moving AND ABS(ActualPosition - Position) < 0.001; Invariant TRUE
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/filling/SC_MoveAxis_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"
#include "forte/iec61131_functions/func_ABS.h"
#include "forte/iec61131_functions/func_AND.h"
#include "forte/iec61131_functions/func_CONCAT.h"
#include "forte/iec61131_functions/func_LT.h"
#include "forte/iec61131_functions/func_NOT.h"
#include "forte/iec61131_functions/func_SUB.h"
#include "forte/modlib/AContract_adp.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::filling {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:Q68gOTAB73V9t0c1wYLY4SXOYmIxVC4SISgihCUg1rOtazBe_iXcZ-ym_S6yZ1-AvpEbEvnZiZVv2pOMsxqktg=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "START"_STRID, "SAMPLE"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID};
    const auto cDataInputNames = std::array{"UaRoot"_STRID, "UaPath"_STRID, "Position"_STRID, "Timeout"_STRID, "ActualPosition"_STRID, "Homed"_STRID, "Moving"_STRID, "EqHolder"_STRID};
    const auto cDataOutputNames = std::array{"IdParams"_STRID};
    const auto cPlugNameIds = std::array{"Run"_STRID};
    const SFBInterfaceSpec cFBInterfaceSpec = {
        .mEINames = cEventInputNames,
        .mEITypeNames = cEventInputTypeIds,
        .mEONames = cEventOutputNames,
        .mEOTypeNames = cEventOutputTypeIds,
        .mDINames = cDataInputNames,
        .mDONames = cDataOutputNames,
        .mDIONames = {},
        .mSocketNames = {},
        .mPlugNames = cPlugNameIds,
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_SC_MoveAxis, "filling::SC_MoveAxis"_STRID, TypeHash)

  FORTE_SC_MoveAxis::FORTE_SC_MoveAxis(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CBasicFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_UaRoot(u""_WSTRING),
      var_UaPath(u""_WSTRING),
      var_Position(0_LREAL),
      var_Timeout(0_TIME),
      var_ActualPosition(0_LREAL),
      var_Homed(0_BOOL),
      var_Moving(0_BOOL),
      var_EqHolder(u""_WSTRING),
      var_IdParams(u""_WSTRING),
      var_Run("Run"_STRID, *this, 0),
      conn_INITO(*this, 0),
      conn_UaRoot(nullptr),
      conn_UaPath(nullptr),
      conn_Position(nullptr),
      conn_Timeout(nullptr),
      conn_ActualPosition(nullptr),
      conn_Homed(nullptr),
      conn_Moving(nullptr),
      conn_EqHolder(nullptr),
      conn_IdParams(*this, 0, var_IdParams) {
  }

  void FORTE_SC_MoveAxis::setInitialValues() {
    CBasicFB::setInitialValues();
    var_UaRoot = u""_WSTRING;
    var_UaPath = u""_WSTRING;
    var_Position = 0_LREAL;
    var_Timeout = 0_TIME;
    var_ActualPosition = 0_LREAL;
    var_Homed = 0_BOOL;
    var_Moving = 0_BOOL;
    var_EqHolder = u""_WSTRING;
    var_IdParams = u""_WSTRING;
  }

  void FORTE_SC_MoveAxis::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
    do {
      switch(mECCState) {
        case scmStateWait:
          if(scmEventINITID == paEIID) enterStateInit(paECET);
          else
          if(scmEventSTARTID == paEIID) enterStateStart(paECET);
          else
          if(scmEventSAMPLEID == paEIID) enterStateSample(paECET);
          else return; //no transition cleared
          break;
        case scmStateInit:
          if(1) enterStateWait(paECET);
          else return; //no transition cleared
          break;
        case scmStateStart:
          if(1) enterStateStarted(paECET);
          else return; //no transition cleared
          break;
        case scmStateStarted:
          if(1) enterStateWait(paECET);
          else return; //no transition cleared
          break;
        case scmStateSample:
          if(1) enterStateJudge(paECET);
          else return; //no transition cleared
          break;
        case scmStateJudge:
          if(1) enterStateWait(paECET);
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

  void FORTE_SC_MoveAxis::enterStateWait(CEventChainExecutionThread *const) {
    mECCState = scmStateWait;
  }

  void FORTE_SC_MoveAxis::enterStateInit(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateInit;
    alg_Alg_Init();
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_SC_MoveAxis::enterStateStart(CEventChainExecutionThread *const) {
    mECCState = scmStateStart;
    alg_Alg_Start();
  }

  void FORTE_SC_MoveAxis::enterStateStarted(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateStarted;
    alg_Alg_Evaluate();
    sendAdapterEvent(*var_Run, forte::modlib::FORTE_AContract::scmEventSTARTID, paECET);
  }

  void FORTE_SC_MoveAxis::enterStateSample(CEventChainExecutionThread *const) {
    mECCState = scmStateSample;
    alg_Alg_Sample();
  }

  void FORTE_SC_MoveAxis::enterStateJudge(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateJudge;
    alg_Alg_Evaluate();
    sendAdapterEvent(*var_Run, forte::modlib::FORTE_AContract::scmEventSAMPLEID, paECET);
  }

  void FORTE_SC_MoveAxis::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, var_UaRoot, conn_UaRoot);
        readData(1, var_UaPath, conn_UaPath);
        break;
      }
      case scmEventSTARTID: {
        readData(2, var_Position, conn_Position);
        readData(3, var_Timeout, conn_Timeout);
        break;
      }
      case scmEventSAMPLEID: {
        readData(4, var_ActualPosition, conn_ActualPosition);
        readData(5, var_Homed, conn_Homed);
        readData(6, var_Moving, conn_Moving);
        readData(7, var_EqHolder, conn_EqHolder);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_SC_MoveAxis::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(8, var_IdParams, conn_IdParams);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_SC_MoveAxis::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_UaRoot;
      case 1: return &var_UaPath;
      case 2: return &var_Position;
      case 3: return &var_Timeout;
      case 4: return &var_ActualPosition;
      case 5: return &var_Homed;
      case 6: return &var_Moving;
      case 7: return &var_EqHolder;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SC_MoveAxis::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_IdParams;
    }
    return nullptr;
  }

  forte::IPlugPin *FORTE_SC_MoveAxis::getPlugPinUnchecked(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Run;
    }
    return nullptr;
  }

  CEventConnection *FORTE_SC_MoveAxis::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
    }
    return nullptr;
  }

  CDataConnection **FORTE_SC_MoveAxis::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_UaRoot;
      case 1: return &conn_UaPath;
      case 2: return &conn_Position;
      case 3: return &conn_Timeout;
      case 4: return &conn_ActualPosition;
      case 5: return &conn_Homed;
      case 6: return &conn_Moving;
      case 7: return &conn_EqHolder;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SC_MoveAxis::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_IdParams;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SC_MoveAxis::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_SC_MoveAxis::alg_Alg_Init(void) {

    #line 2 "SC_MoveAxis.fbt"
    var_IdParams = func_CONCAT(func_CONCAT(func_CONCAT(u"opc_ua[WRITE;"_WSTRING, func_CONCAT(var_UaRoot, var_UaPath)), u"/Parameters/Position"_WSTRING), u"]"_WSTRING);
  }

  void FORTE_SC_MoveAxis::alg_Alg_Start(void) {

    #line 6 "SC_MoveAxis.fbt"
    var_Run->var_Timed = false_BOOL;
    #line 7 "SC_MoveAxis.fbt"
    var_Run->var_RunTime = var_Timeout;
    #line 8 "SC_MoveAxis.fbt"
    var_Run->var_Command = 3_USINT;
    #line 9 "SC_MoveAxis.fbt"
    var_Run->var_Arg = var_Position;
    #line 10 "SC_MoveAxis.fbt"
    var_Run->var_StopCommand = 0_USINT;
  }

  void FORTE_SC_MoveAxis::alg_Alg_Evaluate(void) {

    #line 14 "SC_MoveAxis.fbt"
    var_Run->var_Pre = var_Homed;
    #line 15 "SC_MoveAxis.fbt"
    var_Run->var_Post = func_AND<CIEC_BOOL>(func_NOT<CIEC_BOOL>(var_Moving), func_LT(func_ABS(func_SUB<CIEC_LREAL>(var_ActualPosition, var_Position)), 0.001_LREAL));
    #line 16 "SC_MoveAxis.fbt"
    var_Run->var_Inv = true_BOOL;
  }

  void FORTE_SC_MoveAxis::alg_Alg_Sample(void) {

    #line 20 "SC_MoveAxis.fbt"
    var_Run->var_EqHolder = var_EqHolder;
  }

}