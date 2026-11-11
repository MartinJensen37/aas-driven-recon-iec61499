/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SC_Home
 *** Description: The contract of a skill primitive, the only part that is its own: which command it sends (and with what argument, and which when it ends), how long it may run, and three conditions on the equipment's signals and its parameters: when it may start, when it is done, what must hold while it runs. Technical: Home: Precondition TRUE; LinearAxis.Up until AtHome; Invariant TRUE
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/filling/SC_Home_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/modlib/AContract_adp.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::filling {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:xAJUuCAn1cWMi_wiZwJoxWWjX6OJMBerqox7Eq69CKzLDR1GbykcQ-U_Ky6itO24P9bgf-5FHFxNp5bRKRoveg=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "START"_STRID, "SAMPLE"_STRID};
    const auto cEventInputTypeIds = std::array{"EInit"_STRID, "Event"_STRID, "Event"_STRID};
    const auto cEventOutputNames = std::array{"INITO"_STRID};
    const auto cEventOutputTypeIds = std::array{"EInit"_STRID};
    const auto cDataInputNames = std::array{"Timeout"_STRID, "AtHome"_STRID, "EqHolder"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_SC_Home, "filling::SC_Home"_STRID, TypeHash)

  FORTE_SC_Home::FORTE_SC_Home(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CBasicFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_Timeout(0_TIME),
      var_AtHome(0_BOOL),
      var_EqHolder(u""_WSTRING),
      var_Run("Run"_STRID, *this, 0),
      conn_INITO(*this, 0),
      conn_Timeout(nullptr),
      conn_AtHome(nullptr),
      conn_EqHolder(nullptr) {
  }

  void FORTE_SC_Home::setInitialValues() {
    CBasicFB::setInitialValues();
    var_Timeout = 0_TIME;
    var_AtHome = 0_BOOL;
    var_EqHolder = u""_WSTRING;
  }

  void FORTE_SC_Home::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
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

  void FORTE_SC_Home::enterStateWait(CEventChainExecutionThread *const) {
    mECCState = scmStateWait;
  }

  void FORTE_SC_Home::enterStateInit(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateInit;
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_SC_Home::enterStateStart(CEventChainExecutionThread *const) {
    mECCState = scmStateStart;
    alg_Alg_Start();
  }

  void FORTE_SC_Home::enterStateStarted(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateStarted;
    alg_Alg_Evaluate();
    sendAdapterEvent(*var_Run, forte::modlib::FORTE_AContract::scmEventSTARTID, paECET);
  }

  void FORTE_SC_Home::enterStateSample(CEventChainExecutionThread *const) {
    mECCState = scmStateSample;
    alg_Alg_Sample();
  }

  void FORTE_SC_Home::enterStateJudge(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateJudge;
    alg_Alg_Evaluate();
    sendAdapterEvent(*var_Run, forte::modlib::FORTE_AContract::scmEventSAMPLEID, paECET);
  }

  void FORTE_SC_Home::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventSTARTID: {
        readData(0, var_Timeout, conn_Timeout);
        break;
      }
      case scmEventSAMPLEID: {
        readData(1, var_AtHome, conn_AtHome);
        readData(2, var_EqHolder, conn_EqHolder);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_SC_Home::writeOutputData(TEventID) {
    // nothing to do
  }

  CIEC_ANY *FORTE_SC_Home::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Timeout;
      case 1: return &var_AtHome;
      case 2: return &var_EqHolder;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SC_Home::getDO(size_t) {
    return nullptr;
  }

  forte::IPlugPin *FORTE_SC_Home::getPlugPinUnchecked(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Run;
    }
    return nullptr;
  }

  CEventConnection *FORTE_SC_Home::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INITO;
    }
    return nullptr;
  }

  CDataConnection **FORTE_SC_Home::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Timeout;
      case 1: return &conn_AtHome;
      case 2: return &conn_EqHolder;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SC_Home::getDOConUnchecked(TPortId) {
    return nullptr;
  }

  CIEC_ANY *FORTE_SC_Home::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_SC_Home::alg_Alg_Start(void) {

    #line 2 "SC_Home.fbt"
    var_Run->var_Timed = false_BOOL;
    #line 3 "SC_Home.fbt"
    var_Run->var_RunTime = var_Timeout;
    #line 4 "SC_Home.fbt"
    var_Run->var_Command = 1_USINT;
    #line 5 "SC_Home.fbt"
    var_Run->var_Arg = 0.0_LREAL;
    #line 6 "SC_Home.fbt"
    var_Run->var_StopCommand = 0_USINT;
  }

  void FORTE_SC_Home::alg_Alg_Evaluate(void) {

    #line 10 "SC_Home.fbt"
    var_Run->var_Pre = true_BOOL;
    #line 11 "SC_Home.fbt"
    var_Run->var_Post = var_AtHome;
    #line 12 "SC_Home.fbt"
    var_Run->var_Inv = true_BOOL;
  }

  void FORTE_SC_Home::alg_Alg_Sample(void) {

    #line 16 "SC_Home.fbt"
    var_Run->var_EqHolder = var_EqHolder;
  }

}