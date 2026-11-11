/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: SKILL_Condition_BOOL
 *** Description: One comparison in a decision of a skill (for example Weight greater than 1.9): answers YES or NO. Technical: Compares Operand with Expected by Operator (eq, ne): YES or NO
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/basicfb.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_string.h"

namespace forte::modlib {
  class FORTE_SKILL_Condition_BOOL final : public CBasicFB {
      DECLARE_FIRMWARE_FB(FORTE_SKILL_Condition_BOOL)

    private:
      static const TEventID scmEventYESID = 0;
      static const TEventID scmEventNOID = 1;
      static const TEventID scmEventEVALID = 0;

      CIEC_BOOL var_Holds;

      CIEC_ANY *getVarInternal(size_t) override;

      void alg_Alg_Eval(void);

      static const TForteInt16 scmStateSTART = 0;
      static const TForteInt16 scmStateEval = 1;
      static const TForteInt16 scmStateYes = 2;
      static const TForteInt16 scmStateNo = 3;

      void enterStateSTART(CEventChainExecutionThread *const paECET);
      void enterStateEval(CEventChainExecutionThread *const paECET);
      void enterStateYes(CEventChainExecutionThread *const paECET);
      void enterStateNo(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_SKILL_Condition_BOOL(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_BOOL var_Operand;
      CIEC_BOOL var_Expected;
      CIEC_STRING var_Operator;

      CEventConnection conn_YES;
      CEventConnection conn_NO;

      CDataConnection *conn_Operand;
      CDataConnection *conn_Expected;
      CDataConnection *conn_Operator;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_EVAL(const CIEC_BOOL &paOperand, const CIEC_BOOL &paExpected, const CIEC_STRING &paOperator) {
        var_Operand = paOperand;
        var_Expected = paExpected;
        var_Operator = paOperator;
        executeEvent(scmEventEVALID, nullptr);
      }

      void operator()(const CIEC_BOOL &paOperand, const CIEC_BOOL &paExpected, const CIEC_STRING &paOperator) {
        evt_EVAL(std::forward<const CIEC_BOOL &>(paOperand), std::forward<const CIEC_BOOL &>(paExpected), std::forward<const CIEC_STRING &>(paOperator));
      }
  };
}

