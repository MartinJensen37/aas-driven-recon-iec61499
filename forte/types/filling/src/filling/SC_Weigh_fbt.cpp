/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SC_Weigh
 *** Description: The contract of a skill primitive, the only part that is its own: which command it sends (and with what argument, and which when it ends), how long it may run, and three conditions on the equipment's signals and its parameters: when it may start, when it is done, what must hold while it runs. Technical: Weigh: Precondition TRUE; Scale.Measure until 0.2 s; Invariant TRUE
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/filling/SC_Weigh_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"
#include "forte/iec61131_functions/func_CONCAT.h"
#include "forte/iec61131_functions/func_MUL_TIME.h"
#include "forte/modlib/AContract_adp.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::filling {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:5GJbBb9_cEEOIQBN6AhdbYvnyMLwUodNLay7Ds8ZTafZk9m-jrq96NsRyFMUjvS_TomMhjZc4_s4ZgE3BUeM9g=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "START"_STRID, "SAMPLE"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID, "RESULTS"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID, "Event"_STRID};
    const auto cDataInputNames = std::array{"UaRoot"_STRID, "UaPath"_STRID, "Weight"_STRID, "EqHolder"_STRID};
    const auto cDataOutputNames = std::array{"R_Weight"_STRID, "IdResults"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_SC_Weigh, "filling::SC_Weigh"_STRID, TypeHash)

  FORTE_SC_Weigh::FORTE_SC_Weigh(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CBasicFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_UaRoot(u""_WSTRING),
      var_UaPath(u""_WSTRING),
      var_Weight(0_LREAL),
      var_EqHolder(u""_WSTRING),
      var_R_Weight(0_LREAL),
      var_IdResults(u""_WSTRING),
      var_Run("Run"_STRID, *this, 0),
      conn_INITO(*this, 0),
      conn_RESULTS(*this, 1),
      conn_UaRoot(nullptr),
      conn_UaPath(nullptr),
      conn_Weight(nullptr),
      conn_EqHolder(nullptr),
      conn_R_Weight(*this, 0, var_R_Weight),
      conn_IdResults(*this, 1, var_IdResults) {
  }

  void FORTE_SC_Weigh::setInitialValues() {
    CBasicFB::setInitialValues();
    var_UaRoot = u""_WSTRING;
    var_UaPath = u""_WSTRING;
    var_Weight = 0_LREAL;
    var_EqHolder = u""_WSTRING;
    var_R_Weight = 0_LREAL;
    var_IdResults = u""_WSTRING;
  }

  void FORTE_SC_Weigh::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
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

  void FORTE_SC_Weigh::enterStateWait(CEventChainExecutionThread *const) {
    mECCState = scmStateWait;
  }

  void FORTE_SC_Weigh::enterStateInit(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateInit;
    alg_Alg_Init();
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_SC_Weigh::enterStateStart(CEventChainExecutionThread *const) {
    mECCState = scmStateStart;
    alg_Alg_Start();
  }

  void FORTE_SC_Weigh::enterStateStarted(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateStarted;
    alg_Alg_Evaluate();
    sendAdapterEvent(*var_Run, forte::modlib::FORTE_AContract::scmEventSTARTID, paECET);
    sendOutputEvent(scmEventRESULTSID, paECET);
  }

  void FORTE_SC_Weigh::enterStateSample(CEventChainExecutionThread *const) {
    mECCState = scmStateSample;
    alg_Alg_Sample();
  }

  void FORTE_SC_Weigh::enterStateJudge(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateJudge;
    alg_Alg_Evaluate();
    sendAdapterEvent(*var_Run, forte::modlib::FORTE_AContract::scmEventSAMPLEID, paECET);
    sendOutputEvent(scmEventRESULTSID, paECET);
  }

  void FORTE_SC_Weigh::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, var_UaRoot, conn_UaRoot);
        readData(1, var_UaPath, conn_UaPath);
        break;
      }
      case scmEventSAMPLEID: {
        readData(2, var_Weight, conn_Weight);
        readData(3, var_EqHolder, conn_EqHolder);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_SC_Weigh::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITOID: {
        writeData(5, var_IdResults, conn_IdResults);
        break;
      }
      case scmEventRESULTSID: {
        writeData(4, var_R_Weight, conn_R_Weight);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_SC_Weigh::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_UaRoot;
      case 1: return &var_UaPath;
      case 2: return &var_Weight;
      case 3: return &var_EqHolder;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SC_Weigh::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_R_Weight;
      case 1: return &var_IdResults;
    }
    return nullptr;
  }

  forte::IPlugPin *FORTE_SC_Weigh::getPlugPinUnchecked(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Run;
    }
    return nullptr;
  }

  CEventConnection *FORTE_SC_Weigh::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
      case 1: return &conn_RESULTS;
    }
    return nullptr;
  }

  CDataConnection **FORTE_SC_Weigh::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_UaRoot;
      case 1: return &conn_UaPath;
      case 2: return &conn_Weight;
      case 3: return &conn_EqHolder;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SC_Weigh::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_R_Weight;
      case 1: return &conn_IdResults;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SC_Weigh::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_SC_Weigh::alg_Alg_Init(void) {

    #line 2 "SC_Weigh.fbt"
    var_IdResults = func_CONCAT(func_CONCAT(func_CONCAT(u"opc_ua[WRITE;"_WSTRING, func_CONCAT(var_UaRoot, var_UaPath)), u"/Results/Weight"_WSTRING), u"]"_WSTRING);
  }

  void FORTE_SC_Weigh::alg_Alg_Start(void) {

    #line 6 "SC_Weigh.fbt"
    var_Run->var_Timed = true_BOOL;
    #line 7 "SC_Weigh.fbt"
    var_Run->var_RunTime = func_MUL_TIME(1000000000_TIME, 0.2_LREAL);
    #line 8 "SC_Weigh.fbt"
    var_Run->var_Command = 2_USINT;
    #line 9 "SC_Weigh.fbt"
    var_Run->var_Arg = 0.0_LREAL;
    #line 10 "SC_Weigh.fbt"
    var_Run->var_StopCommand = 0_USINT;
  }

  void FORTE_SC_Weigh::alg_Alg_Evaluate(void) {

    #line 14 "SC_Weigh.fbt"
    var_Run->var_Pre = true_BOOL;
    #line 15 "SC_Weigh.fbt"
    var_Run->var_Post = false_BOOL;
    #line 16 "SC_Weigh.fbt"
    var_Run->var_Inv = true_BOOL;
    #line 17 "SC_Weigh.fbt"
    var_R_Weight = var_Weight;
  }

  void FORTE_SC_Weigh::alg_Alg_Sample(void) {

    #line 21 "SC_Weigh.fbt"
    var_Run->var_EqHolder = var_EqHolder;
  }

}