/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SKILL_Join2
 *** Description: Ends a block of steps that run side by side: done when every branch is done; if one fails, the others are halted and the block fails. Technical: Ends a parallel block of 2 branches: DONE when all are done; on the first failure HALT to the others, then FAILED with its error once all have ended
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/SKILL_Join2_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/forte_st_util.h"
#include "forte/iec61131_functions/func_AND.h"
#include "forte/iec61131_functions/func_NOT.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:tFJ5vI5fiErfw-SuvGvW91pJyM-bLA4r8feF-MVFuk400_O3UrGQimEhK6O_hoFW8F08HSRKBu-hZDAVJQC8zA=="sv;

    const auto cEventInputNames = std::array{"START"_STRID, "DONE_1"_STRID, "DONE_2"_STRID, "FAILED_1"_STRID, "FAILED_2"_STRID};
    const auto cEventOutputNames = std::array{"DONE"_STRID, "FAILED"_STRID, "HALT"_STRID};
    const auto cDataInputNames = std::array{"Error1"_STRID, "Error2"_STRID};
    const auto cDataOutputNames = std::array{"Error"_STRID};
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

    const auto cInternalsNames = std::array{"Ended1"_STRID, "Ended2"_STRID, "AnyFailed"_STRID, "First"_STRID};
  }

  DEFINE_FIRMWARE_FB(FORTE_SKILL_Join2, "modlib::SKILL_Join2"_STRID, TypeHash)

  FORTE_SKILL_Join2::FORTE_SKILL_Join2(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CBasicFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cInternalsNames),
      var_Ended1(0_BOOL),
      var_Ended2(0_BOOL),
      var_AnyFailed(0_BOOL),
      var_First(0_UINT),
      var_Error1(0_UINT),
      var_Error2(0_UINT),
      var_Error(0_UINT),
      conn_DONE(*this, 0),
      conn_FAILED(*this, 1),
      conn_HALT(*this, 2),
      conn_Error1(nullptr),
      conn_Error2(nullptr),
      conn_Error(*this, 0, var_Error) {
  }

  void FORTE_SKILL_Join2::setInitialValues() {
    CBasicFB::setInitialValues();
    var_Ended1 = 0_BOOL;
    var_Ended2 = 0_BOOL;
    var_AnyFailed = 0_BOOL;
    var_First = 0_UINT;
    var_Error1 = 0_UINT;
    var_Error2 = 0_UINT;
    var_Error = 0_UINT;
  }

  void FORTE_SKILL_Join2::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
    do {
      switch(mECCState) {
        case scmStateSTART:
          if(scmEventSTARTID == paEIID) enterStateReset(paECET);
          else
          if(scmEventDONE_1ID == paEIID) enterStateDone1(paECET);
          else
          if((scmEventFAILED_1ID == paEIID) && (func_NOT<CIEC_BOOL>(var_AnyFailed))) enterStateFirst1(paECET);
          else
          if(scmEventFAILED_1ID == paEIID) enterStateLater1(paECET);
          else
          if(scmEventDONE_2ID == paEIID) enterStateDone2(paECET);
          else
          if((scmEventFAILED_2ID == paEIID) && (func_NOT<CIEC_BOOL>(var_AnyFailed))) enterStateFirst2(paECET);
          else
          if(scmEventFAILED_2ID == paEIID) enterStateLater2(paECET);
          else return; //no transition cleared
          break;
        case scmStateReset:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStateCheck:
          if(func_AND<CIEC_BOOL>(func_AND<CIEC_BOOL>(var_Ended1, var_Ended2), func_NOT<CIEC_BOOL>(var_AnyFailed))) enterStateDone(paECET);
          else
          if(func_AND<CIEC_BOOL>(func_AND<CIEC_BOOL>(var_Ended1, var_Ended2), var_AnyFailed)) enterStateFail(paECET);
          else
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStateDone:
          if(1) enterStateReset(paECET);
          else return; //no transition cleared
          break;
        case scmStateFail:
          if(1) enterStateReset(paECET);
          else return; //no transition cleared
          break;
        case scmStateDone1:
          if(1) enterStateCheck(paECET);
          else return; //no transition cleared
          break;
        case scmStateFirst1:
          if(1) enterStateCheck(paECET);
          else return; //no transition cleared
          break;
        case scmStateLater1:
          if(1) enterStateCheck(paECET);
          else return; //no transition cleared
          break;
        case scmStateDone2:
          if(1) enterStateCheck(paECET);
          else return; //no transition cleared
          break;
        case scmStateFirst2:
          if(1) enterStateCheck(paECET);
          else return; //no transition cleared
          break;
        case scmStateLater2:
          if(1) enterStateCheck(paECET);
          else return; //no transition cleared
          break;
        default:
          DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 11.", mECCState.operator TForteUInt16 ());
          mECCState = 0; // 0 is always the initial state
          return;
      }
      paEIID = cgInvalidEventID; // we have to clear the event after the first check in order to ensure correct behavior
    } while(true);
  }

  void FORTE_SKILL_Join2::enterStateSTART(CEventChainExecutionThread *const) {
    mECCState = scmStateSTART;
  }

  void FORTE_SKILL_Join2::enterStateReset(CEventChainExecutionThread *const) {
    mECCState = scmStateReset;
    alg_Alg_Reset();
  }

  void FORTE_SKILL_Join2::enterStateCheck(CEventChainExecutionThread *const) {
    mECCState = scmStateCheck;
  }

  void FORTE_SKILL_Join2::enterStateDone(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateDone;
    sendOutputEvent(scmEventDONEID, paECET);
  }

  void FORTE_SKILL_Join2::enterStateFail(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateFail;
    alg_Alg_Fail();
    sendOutputEvent(scmEventFAILEDID, paECET);
  }

  void FORTE_SKILL_Join2::enterStateDone1(CEventChainExecutionThread *const) {
    mECCState = scmStateDone1;
    alg_Alg_Done1();
  }

  void FORTE_SKILL_Join2::enterStateFirst1(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateFirst1;
    alg_Alg_First1();
    sendOutputEvent(scmEventHALTID, paECET);
  }

  void FORTE_SKILL_Join2::enterStateLater1(CEventChainExecutionThread *const) {
    mECCState = scmStateLater1;
    alg_Alg_Later1();
  }

  void FORTE_SKILL_Join2::enterStateDone2(CEventChainExecutionThread *const) {
    mECCState = scmStateDone2;
    alg_Alg_Done2();
  }

  void FORTE_SKILL_Join2::enterStateFirst2(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateFirst2;
    alg_Alg_First2();
    sendOutputEvent(scmEventHALTID, paECET);
  }

  void FORTE_SKILL_Join2::enterStateLater2(CEventChainExecutionThread *const) {
    mECCState = scmStateLater2;
    alg_Alg_Later2();
  }

  void FORTE_SKILL_Join2::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventFAILED_1ID: {
        readData(0, var_Error1, conn_Error1);
        break;
      }
      case scmEventFAILED_2ID: {
        readData(1, var_Error2, conn_Error2);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_SKILL_Join2::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventFAILEDID: {
        writeData(2, var_Error, conn_Error);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_SKILL_Join2::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Error1;
      case 1: return &var_Error2;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SKILL_Join2::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Error;
    }
    return nullptr;
  }

  CEventConnection *FORTE_SKILL_Join2::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_DONE;
      case 1: return &conn_FAILED;
      case 2: return &conn_HALT;
    }
    return nullptr;
  }

  CDataConnection **FORTE_SKILL_Join2::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Error1;
      case 1: return &conn_Error2;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SKILL_Join2::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Error;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SKILL_Join2::getVarInternal(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Ended1;
      case 1: return &var_Ended2;
      case 2: return &var_AnyFailed;
      case 3: return &var_First;
    }
    return nullptr;
  }

  void FORTE_SKILL_Join2::alg_Alg_Reset(void) {

    #line 2 "SKILL_Join2.fbt"
    var_Ended1 = false_BOOL;
    #line 2 "SKILL_Join2.fbt"
    var_Ended2 = false_BOOL;
    #line 2 "SKILL_Join2.fbt"
    var_AnyFailed = false_BOOL;
  }

  void FORTE_SKILL_Join2::alg_Alg_Fail(void) {

    #line 6 "SKILL_Join2.fbt"
    var_Error = var_First;
  }

  void FORTE_SKILL_Join2::alg_Alg_Done1(void) {

    #line 10 "SKILL_Join2.fbt"
    var_Ended1 = true_BOOL;
  }

  void FORTE_SKILL_Join2::alg_Alg_First1(void) {

    #line 14 "SKILL_Join2.fbt"
    var_Ended1 = true_BOOL;
    #line 14 "SKILL_Join2.fbt"
    var_AnyFailed = true_BOOL;
    #line 14 "SKILL_Join2.fbt"
    var_First = var_Error1;
  }

  void FORTE_SKILL_Join2::alg_Alg_Later1(void) {

    #line 18 "SKILL_Join2.fbt"
    var_Ended1 = true_BOOL;
  }

  void FORTE_SKILL_Join2::alg_Alg_Done2(void) {

    #line 22 "SKILL_Join2.fbt"
    var_Ended2 = true_BOOL;
  }

  void FORTE_SKILL_Join2::alg_Alg_First2(void) {

    #line 26 "SKILL_Join2.fbt"
    var_Ended2 = true_BOOL;
    #line 26 "SKILL_Join2.fbt"
    var_AnyFailed = true_BOOL;
    #line 26 "SKILL_Join2.fbt"
    var_First = var_Error2;
  }

  void FORTE_SKILL_Join2::alg_Alg_Later2(void) {

    #line 30 "SKILL_Join2.fbt"
    var_Ended2 = true_BOOL;
  }

}