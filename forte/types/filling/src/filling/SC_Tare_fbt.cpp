/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SC_Tare
 *** Description: The contract of a skill primitive, the only part that is its own: which command it sends (and with what argument, and which when it ends), how long it may run, and three conditions on the equipment's signals and its parameters: when it may start, when it is done, what must hold while it runs. Technical: Tare: Precondition TRUE; Scale.Tare until 2.0 s; Invariant TRUE
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/filling/SC_Tare_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/iec61131_functions/func_MUL_TIME.h"
#include "forte/modlib/AContract_adp.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::filling {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:QgLNSXCJISDXnEOOVKv6LLI0ehUO7UlBrXaTedwYf3UxJkstb3-Sicx7UvwXOKQJJYuuUFZdARz0N2jE099zbA=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "START"_STRID, "SAMPLE"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID};
    const auto cDataInputNames = std::array{"EqHolder"_STRID};
    const auto cPlugNameIds = std::array{"Run"_STRID};
    const SFBInterfaceSpec cFBInterfaceSpec = {
        .mEINames = cEventInputNames,
        .mEITypeNames = cEventInputTypeIds,
        .mEONames = cEventOutputNames,
        .mEOTypeNames = cEventOutputTypeIds,
        .mDINames = cDataInputNames,
        .mDONames = {},
        .mDIONames = {},
        .mSocketNames = {},
        .mPlugNames = cPlugNameIds,
    };
  }

  DEFINE_FIRMWARE_FB(FORTE_SC_Tare, "filling::SC_Tare"_STRID, TypeHash)

  FORTE_SC_Tare::FORTE_SC_Tare(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CBasicFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_EqHolder(u""_WSTRING),
      var_Run("Run"_STRID, *this, 0),
      conn_INITO(*this, 0),
      conn_EqHolder(nullptr) {
  }

  void FORTE_SC_Tare::setInitialValues() {
    CBasicFB::setInitialValues();
    var_EqHolder = u""_WSTRING;
  }

  void FORTE_SC_Tare::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
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

  void FORTE_SC_Tare::enterStateWait(CEventChainExecutionThread *const) {
    mECCState = scmStateWait;
  }

  void FORTE_SC_Tare::enterStateInit(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateInit;
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_SC_Tare::enterStateStart(CEventChainExecutionThread *const) {
    mECCState = scmStateStart;
    alg_Alg_Start();
  }

  void FORTE_SC_Tare::enterStateStarted(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateStarted;
    alg_Alg_Evaluate();
    sendAdapterEvent(*var_Run, forte::modlib::FORTE_AContract::scmEventSTARTID, paECET);
  }

  void FORTE_SC_Tare::enterStateSample(CEventChainExecutionThread *const) {
    mECCState = scmStateSample;
    alg_Alg_Sample();
  }

  void FORTE_SC_Tare::enterStateJudge(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateJudge;
    alg_Alg_Evaluate();
    sendAdapterEvent(*var_Run, forte::modlib::FORTE_AContract::scmEventSAMPLEID, paECET);
  }

  void FORTE_SC_Tare::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventSAMPLEID: {
        readData(0, var_EqHolder, conn_EqHolder);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_SC_Tare::writeOutputData(TEventID) {
    // nothing to do
  }

  CIEC_ANY *FORTE_SC_Tare::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_EqHolder;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SC_Tare::getDO(size_t) {
    return nullptr;
  }

  forte::IPlugPin *FORTE_SC_Tare::getPlugPinUnchecked(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Run;
    }
    return nullptr;
  }

  CEventConnection *FORTE_SC_Tare::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
    }
    return nullptr;
  }

  CDataConnection **FORTE_SC_Tare::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_EqHolder;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SC_Tare::getDOConUnchecked(TPortId) {
    return nullptr;
  }

  CIEC_ANY *FORTE_SC_Tare::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_SC_Tare::alg_Alg_Start(void) {

    #line 2 "SC_Tare.fbt"
    var_Run->var_Timed = true_BOOL;
    #line 3 "SC_Tare.fbt"
    var_Run->var_RunTime = func_MUL_TIME(1000000000_TIME, 2.0_LREAL);
    #line 4 "SC_Tare.fbt"
    var_Run->var_Command = 1_USINT;
    #line 5 "SC_Tare.fbt"
    var_Run->var_Arg = 0.0_LREAL;
    #line 6 "SC_Tare.fbt"
    var_Run->var_StopCommand = 0_USINT;
  }

  void FORTE_SC_Tare::alg_Alg_Evaluate(void) {

    #line 10 "SC_Tare.fbt"
    var_Run->var_Pre = true_BOOL;
    #line 11 "SC_Tare.fbt"
    var_Run->var_Post = false_BOOL;
    #line 12 "SC_Tare.fbt"
    var_Run->var_Inv = true_BOOL;
  }

  void FORTE_SC_Tare::alg_Alg_Sample(void) {

    #line 16 "SC_Tare.fbt"
    var_Run->var_EqHolder = var_EqHolder;
  }

}