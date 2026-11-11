/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SKILL_Condition_LREAL
 *** Description: One comparison in a decision of a skill (for example Weight greater than 1.9): answers YES or NO. Technical: Compares Operand with Expected by Operator (eq, ne, gt, gte, lt, lte): YES or NO
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/SKILL_Condition_LREAL_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_string.h"
#include "forte/iec61131_functions/func_AND.h"
#include "forte/iec61131_functions/func_EQ.h"
#include "forte/iec61131_functions/func_GE.h"
#include "forte/iec61131_functions/func_GT.h"
#include "forte/iec61131_functions/func_LE.h"
#include "forte/iec61131_functions/func_LT.h"
#include "forte/iec61131_functions/func_NE.h"
#include "forte/iec61131_functions/func_OR.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:SprDawpeLGg0Kz8Ooh69eCCijNQp7qpQmiENqAdW7prl2DuS80wkiIOEWgdNYaZ1KzYBEWXq5ITI2q9kImAyoQ=="sv;

    const auto cEventInputNames = std::array{"EVAL"_STRID};
    const auto cEventOutputNames = std::array{"YES"_STRID, "NO"_STRID};
    const auto cDataInputNames = std::array{"Operand"_STRID, "Expected"_STRID, "Operator"_STRID};
    const SFBInterfaceSpec cFBInterfaceSpec = {
        .mEINames = cEventInputNames,
        .mEITypeNames = {},
        .mEONames = cEventOutputNames,
        .mEOTypeNames = {},
        .mDINames = cDataInputNames,
        .mDONames = {},
        .mDIONames = {},
        .mSocketNames = {},
        .mPlugNames = {},
    };

    const auto cInternalsNames = std::array{"Holds"_STRID};
  }

  DEFINE_FIRMWARE_FB(FORTE_SKILL_Condition_LREAL, "modlib::SKILL_Condition_LREAL"_STRID, TypeHash)

  FORTE_SKILL_Condition_LREAL::FORTE_SKILL_Condition_LREAL(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CBasicFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cInternalsNames),
      var_Holds(0_BOOL),
      var_Operand(0_LREAL),
      var_Expected(0_LREAL),
      var_Operator("eq"_STRING),
      conn_YES(*this, 0),
      conn_NO(*this, 1),
      conn_Operand(nullptr),
      conn_Expected(nullptr),
      conn_Operator(nullptr) {
  }

  void FORTE_SKILL_Condition_LREAL::setInitialValues() {
    CBasicFB::setInitialValues();
    var_Holds = 0_BOOL;
    var_Operand = 0_LREAL;
    var_Expected = 0_LREAL;
    var_Operator = "eq"_STRING;
  }

  void FORTE_SKILL_Condition_LREAL::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
    do {
      switch(mECCState) {
        case scmStateSTART:
          if(scmEventEVALID == paEIID) enterStateEval(paECET);
          else return; //no transition cleared
          break;
        case scmStateEval:
          if(var_Holds) enterStateYes(paECET);
          else
          if(1) enterStateNo(paECET);
          else return; //no transition cleared
          break;
        case scmStateYes:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStateNo:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        default:
          DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 4.", mECCState.operator TForteUInt16 ());
          mECCState = 0; // 0 is always the initial state
          return;
      }
      paEIID = cgInvalidEventID; // we have to clear the event after the first check in order to ensure correct behavior
    } while(true);
  }

  void FORTE_SKILL_Condition_LREAL::enterStateSTART(CEventChainExecutionThread *const) {
    mECCState = scmStateSTART;
  }

  void FORTE_SKILL_Condition_LREAL::enterStateEval(CEventChainExecutionThread *const) {
    mECCState = scmStateEval;
    alg_Alg_Eval();
  }

  void FORTE_SKILL_Condition_LREAL::enterStateYes(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateYes;
    sendOutputEvent(scmEventYESID, paECET);
  }

  void FORTE_SKILL_Condition_LREAL::enterStateNo(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateNo;
    sendOutputEvent(scmEventNOID, paECET);
  }

  void FORTE_SKILL_Condition_LREAL::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventEVALID: {
        readData(0, var_Operand, conn_Operand);
        readData(1, var_Expected, conn_Expected);
        readData(2, var_Operator, conn_Operator);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_SKILL_Condition_LREAL::writeOutputData(TEventID) {
    // nothing to do
  }

  CIEC_ANY *FORTE_SKILL_Condition_LREAL::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Operand;
      case 1: return &var_Expected;
      case 2: return &var_Operator;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_SKILL_Condition_LREAL::getDO(size_t) {
    return nullptr;
  }

  CEventConnection *FORTE_SKILL_Condition_LREAL::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_YES;
      case 1: return &conn_NO;
    }
    return nullptr;
  }

  CDataConnection **FORTE_SKILL_Condition_LREAL::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Operand;
      case 1: return &conn_Expected;
      case 2: return &conn_Operator;
    }
    return nullptr;
  }

  CDataConnection *FORTE_SKILL_Condition_LREAL::getDOConUnchecked(TPortId) {
    return nullptr;
  }

  CIEC_ANY *FORTE_SKILL_Condition_LREAL::getVarInternal(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Holds;
    }
    return nullptr;
  }

  void FORTE_SKILL_Condition_LREAL::alg_Alg_Eval(void) {

    #line 2 "SKILL_Condition_LREAL.fbt"
    var_Holds = func_OR<CIEC_BOOL>(func_OR<CIEC_BOOL>(func_OR<CIEC_BOOL>(func_OR<CIEC_BOOL>(func_OR<CIEC_BOOL>(func_AND<CIEC_BOOL>(func_EQ(var_Operator, "eq"_STRING), func_EQ(var_Operand, var_Expected)), func_AND<CIEC_BOOL>(func_EQ(var_Operator, "ne"_STRING), func_NE(var_Operand, var_Expected))), func_AND<CIEC_BOOL>(func_EQ(var_Operator, "gt"_STRING), func_GT(var_Operand, var_Expected))), func_AND<CIEC_BOOL>(func_EQ(var_Operator, "gte"_STRING), func_GE(var_Operand, var_Expected))), func_AND<CIEC_BOOL>(func_EQ(var_Operator, "lt"_STRING), func_LT(var_Operand, var_Expected))), func_AND<CIEC_BOOL>(func_EQ(var_Operator, "lte"_STRING), func_LE(var_Operand, var_Expected)));
  }

}