/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: IO_RouteDI
 *** Description: Picks the way an IO block reaches its signal from the Address (a Pi line, a local IO handle, Modbus or simulated) and passes values through that way only. Technical: Backend router for IO_DI; Address: 'gpio[chip:line(:pull_up|:pull_down)(:active_low)]' or 'pwm[chip:channel:period_ns]' a Raspberry Pi's line, set up here; 'modbus[...]' a Modbus CLIENT ID; 'sim' simulated; another name a local IO handle set up elsewhere (IX/QX PARAMS); empty: not connected (QO = FALSE)
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/basicfb.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_string.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"

namespace forte::modlib {
  class FORTE_IO_RouteDI final : public CBasicFB {
      DECLARE_FIRMWARE_FB(FORTE_IO_RouteDI)

    private:
      static const TEventID scmEventINIT_IOID = 0;
      static const TEventID scmEventINITOID = 1;
      static const TEventID scmEventREQ_GID = 2;
      static const TEventID scmEventREQ_MID = 3;
      static const TEventID scmEventCNFID = 4;
      static const TEventID scmEventINITID = 0;
      static const TEventID scmEventIO_READYID = 1;
      static const TEventID scmEventCNF_GID = 2;
      static const TEventID scmEventCNF_MID = 3;
      static const TEventID scmEventREQID = 4;

      CIEC_USINT var_Backend;

      CIEC_ANY *getVarInternal(size_t) override;

      void alg_Alg_Init(void);
      void alg_Alg_Ready(void);
      void alg_Alg_Sim(void);
      void alg_Alg_None(void);
      void alg_Alg_DoneG(void);
      void alg_Alg_DoneM(void);

      static const TForteInt16 scmStateSTART = 0;
      static const TForteInt16 scmStateInit = 1;
      static const TForteInt16 scmStateReady = 2;
      static const TForteInt16 scmStateReqG = 3;
      static const TForteInt16 scmStateReqM = 4;
      static const TForteInt16 scmStateSim = 5;
      static const TForteInt16 scmStateNone = 6;
      static const TForteInt16 scmStateDoneG = 7;
      static const TForteInt16 scmStateDoneM = 8;

      void enterStateSTART(CEventChainExecutionThread *const paECET);
      void enterStateInit(CEventChainExecutionThread *const paECET);
      void enterStateReady(CEventChainExecutionThread *const paECET);
      void enterStateReqG(CEventChainExecutionThread *const paECET);
      void enterStateReqM(CEventChainExecutionThread *const paECET);
      void enterStateSim(CEventChainExecutionThread *const paECET);
      void enterStateNone(CEventChainExecutionThread *const paECET);
      void enterStateDoneG(CEventChainExecutionThread *const paECET);
      void enterStateDoneM(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_IO_RouteDI(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_STRING var_Address;
      CIEC_BOOL var_QO_G;
      CIEC_BOOL var_QO_M;
      CIEC_BOOL var_SimValue;
      CIEC_BOOL var_IN_G;
      CIEC_BOOL var_IN_M;

      CIEC_BOOL var_GQI;
      CIEC_BOOL var_MQI;
      CIEC_STRING var_IoName;
      CIEC_WSTRING var_ModbusId;
      CIEC_BOOL var_QO;
      CIEC_BOOL var_LineQI;
      CIEC_WSTRING var_LineName;
      CIEC_UINT var_ChipNo;
      CIEC_UINT var_LineNo;
      CIEC_UINT var_LineBias;
      CIEC_BOOL var_LineLow;
      CIEC_BOOL var_IN;

      CEventConnection conn_INIT_IO;
      CEventConnection conn_INITO;
      CEventConnection conn_REQ_G;
      CEventConnection conn_REQ_M;
      CEventConnection conn_CNF;

      CDataConnection *conn_Address;
      CDataConnection *conn_QO_G;
      CDataConnection *conn_QO_M;
      CDataConnection *conn_SimValue;
      CDataConnection *conn_IN_G;
      CDataConnection *conn_IN_M;

      COutDataConnection<CIEC_BOOL> conn_GQI;
      COutDataConnection<CIEC_BOOL> conn_MQI;
      COutDataConnection<CIEC_STRING> conn_IoName;
      COutDataConnection<CIEC_WSTRING> conn_ModbusId;
      COutDataConnection<CIEC_BOOL> conn_QO;
      COutDataConnection<CIEC_BOOL> conn_LineQI;
      COutDataConnection<CIEC_WSTRING> conn_LineName;
      COutDataConnection<CIEC_UINT> conn_ChipNo;
      COutDataConnection<CIEC_UINT> conn_LineNo;
      COutDataConnection<CIEC_UINT> conn_LineBias;
      COutDataConnection<CIEC_BOOL> conn_LineLow;
      COutDataConnection<CIEC_BOOL> conn_IN;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_INIT(const CIEC_STRING &paAddress, const CIEC_BOOL &paQO_G, const CIEC_BOOL &paQO_M, const CIEC_BOOL &paSimValue, const CIEC_BOOL &paIN_G, const CIEC_BOOL &paIN_M, CAnyBitOutputParameter<CIEC_BOOL> paGQI, CAnyBitOutputParameter<CIEC_BOOL> paMQI, COutputParameter<CIEC_STRING> paIoName, COutputParameter<CIEC_WSTRING> paModbusId, CAnyBitOutputParameter<CIEC_BOOL> paQO, CAnyBitOutputParameter<CIEC_BOOL> paLineQI, COutputParameter<CIEC_WSTRING> paLineName, COutputParameter<CIEC_UINT> paChipNo, COutputParameter<CIEC_UINT> paLineNo, COutputParameter<CIEC_UINT> paLineBias, CAnyBitOutputParameter<CIEC_BOOL> paLineLow, CAnyBitOutputParameter<CIEC_BOOL> paIN) {
        COutputGuard guard_GQI(paGQI);
        COutputGuard guard_MQI(paMQI);
        COutputGuard guard_IoName(paIoName);
        COutputGuard guard_ModbusId(paModbusId);
        COutputGuard guard_QO(paQO);
        COutputGuard guard_LineQI(paLineQI);
        COutputGuard guard_LineName(paLineName);
        COutputGuard guard_ChipNo(paChipNo);
        COutputGuard guard_LineNo(paLineNo);
        COutputGuard guard_LineBias(paLineBias);
        COutputGuard guard_LineLow(paLineLow);
        COutputGuard guard_IN(paIN);
        var_Address = paAddress;
        var_QO_G = paQO_G;
        var_QO_M = paQO_M;
        var_SimValue = paSimValue;
        var_IN_G = paIN_G;
        var_IN_M = paIN_M;
        executeEvent(scmEventINITID, nullptr);
        *paGQI = var_GQI;
        *paMQI = var_MQI;
        *paIoName = var_IoName;
        *paModbusId = var_ModbusId;
        *paQO = var_QO;
        *paLineQI = var_LineQI;
        *paLineName = var_LineName;
        *paChipNo = var_ChipNo;
        *paLineNo = var_LineNo;
        *paLineBias = var_LineBias;
        *paLineLow = var_LineLow;
        *paIN = var_IN;
      }

      void evt_IO_READY(const CIEC_STRING &paAddress, const CIEC_BOOL &paQO_G, const CIEC_BOOL &paQO_M, const CIEC_BOOL &paSimValue, const CIEC_BOOL &paIN_G, const CIEC_BOOL &paIN_M, CAnyBitOutputParameter<CIEC_BOOL> paGQI, CAnyBitOutputParameter<CIEC_BOOL> paMQI, COutputParameter<CIEC_STRING> paIoName, COutputParameter<CIEC_WSTRING> paModbusId, CAnyBitOutputParameter<CIEC_BOOL> paQO, CAnyBitOutputParameter<CIEC_BOOL> paLineQI, COutputParameter<CIEC_WSTRING> paLineName, COutputParameter<CIEC_UINT> paChipNo, COutputParameter<CIEC_UINT> paLineNo, COutputParameter<CIEC_UINT> paLineBias, CAnyBitOutputParameter<CIEC_BOOL> paLineLow, CAnyBitOutputParameter<CIEC_BOOL> paIN) {
        COutputGuard guard_GQI(paGQI);
        COutputGuard guard_MQI(paMQI);
        COutputGuard guard_IoName(paIoName);
        COutputGuard guard_ModbusId(paModbusId);
        COutputGuard guard_QO(paQO);
        COutputGuard guard_LineQI(paLineQI);
        COutputGuard guard_LineName(paLineName);
        COutputGuard guard_ChipNo(paChipNo);
        COutputGuard guard_LineNo(paLineNo);
        COutputGuard guard_LineBias(paLineBias);
        COutputGuard guard_LineLow(paLineLow);
        COutputGuard guard_IN(paIN);
        var_Address = paAddress;
        var_QO_G = paQO_G;
        var_QO_M = paQO_M;
        var_SimValue = paSimValue;
        var_IN_G = paIN_G;
        var_IN_M = paIN_M;
        executeEvent(scmEventIO_READYID, nullptr);
        *paGQI = var_GQI;
        *paMQI = var_MQI;
        *paIoName = var_IoName;
        *paModbusId = var_ModbusId;
        *paQO = var_QO;
        *paLineQI = var_LineQI;
        *paLineName = var_LineName;
        *paChipNo = var_ChipNo;
        *paLineNo = var_LineNo;
        *paLineBias = var_LineBias;
        *paLineLow = var_LineLow;
        *paIN = var_IN;
      }

      void evt_CNF_G(const CIEC_STRING &paAddress, const CIEC_BOOL &paQO_G, const CIEC_BOOL &paQO_M, const CIEC_BOOL &paSimValue, const CIEC_BOOL &paIN_G, const CIEC_BOOL &paIN_M, CAnyBitOutputParameter<CIEC_BOOL> paGQI, CAnyBitOutputParameter<CIEC_BOOL> paMQI, COutputParameter<CIEC_STRING> paIoName, COutputParameter<CIEC_WSTRING> paModbusId, CAnyBitOutputParameter<CIEC_BOOL> paQO, CAnyBitOutputParameter<CIEC_BOOL> paLineQI, COutputParameter<CIEC_WSTRING> paLineName, COutputParameter<CIEC_UINT> paChipNo, COutputParameter<CIEC_UINT> paLineNo, COutputParameter<CIEC_UINT> paLineBias, CAnyBitOutputParameter<CIEC_BOOL> paLineLow, CAnyBitOutputParameter<CIEC_BOOL> paIN) {
        COutputGuard guard_GQI(paGQI);
        COutputGuard guard_MQI(paMQI);
        COutputGuard guard_IoName(paIoName);
        COutputGuard guard_ModbusId(paModbusId);
        COutputGuard guard_QO(paQO);
        COutputGuard guard_LineQI(paLineQI);
        COutputGuard guard_LineName(paLineName);
        COutputGuard guard_ChipNo(paChipNo);
        COutputGuard guard_LineNo(paLineNo);
        COutputGuard guard_LineBias(paLineBias);
        COutputGuard guard_LineLow(paLineLow);
        COutputGuard guard_IN(paIN);
        var_Address = paAddress;
        var_QO_G = paQO_G;
        var_QO_M = paQO_M;
        var_SimValue = paSimValue;
        var_IN_G = paIN_G;
        var_IN_M = paIN_M;
        executeEvent(scmEventCNF_GID, nullptr);
        *paGQI = var_GQI;
        *paMQI = var_MQI;
        *paIoName = var_IoName;
        *paModbusId = var_ModbusId;
        *paQO = var_QO;
        *paLineQI = var_LineQI;
        *paLineName = var_LineName;
        *paChipNo = var_ChipNo;
        *paLineNo = var_LineNo;
        *paLineBias = var_LineBias;
        *paLineLow = var_LineLow;
        *paIN = var_IN;
      }

      void evt_CNF_M(const CIEC_STRING &paAddress, const CIEC_BOOL &paQO_G, const CIEC_BOOL &paQO_M, const CIEC_BOOL &paSimValue, const CIEC_BOOL &paIN_G, const CIEC_BOOL &paIN_M, CAnyBitOutputParameter<CIEC_BOOL> paGQI, CAnyBitOutputParameter<CIEC_BOOL> paMQI, COutputParameter<CIEC_STRING> paIoName, COutputParameter<CIEC_WSTRING> paModbusId, CAnyBitOutputParameter<CIEC_BOOL> paQO, CAnyBitOutputParameter<CIEC_BOOL> paLineQI, COutputParameter<CIEC_WSTRING> paLineName, COutputParameter<CIEC_UINT> paChipNo, COutputParameter<CIEC_UINT> paLineNo, COutputParameter<CIEC_UINT> paLineBias, CAnyBitOutputParameter<CIEC_BOOL> paLineLow, CAnyBitOutputParameter<CIEC_BOOL> paIN) {
        COutputGuard guard_GQI(paGQI);
        COutputGuard guard_MQI(paMQI);
        COutputGuard guard_IoName(paIoName);
        COutputGuard guard_ModbusId(paModbusId);
        COutputGuard guard_QO(paQO);
        COutputGuard guard_LineQI(paLineQI);
        COutputGuard guard_LineName(paLineName);
        COutputGuard guard_ChipNo(paChipNo);
        COutputGuard guard_LineNo(paLineNo);
        COutputGuard guard_LineBias(paLineBias);
        COutputGuard guard_LineLow(paLineLow);
        COutputGuard guard_IN(paIN);
        var_Address = paAddress;
        var_QO_G = paQO_G;
        var_QO_M = paQO_M;
        var_SimValue = paSimValue;
        var_IN_G = paIN_G;
        var_IN_M = paIN_M;
        executeEvent(scmEventCNF_MID, nullptr);
        *paGQI = var_GQI;
        *paMQI = var_MQI;
        *paIoName = var_IoName;
        *paModbusId = var_ModbusId;
        *paQO = var_QO;
        *paLineQI = var_LineQI;
        *paLineName = var_LineName;
        *paChipNo = var_ChipNo;
        *paLineNo = var_LineNo;
        *paLineBias = var_LineBias;
        *paLineLow = var_LineLow;
        *paIN = var_IN;
      }

      void evt_REQ(const CIEC_STRING &paAddress, const CIEC_BOOL &paQO_G, const CIEC_BOOL &paQO_M, const CIEC_BOOL &paSimValue, const CIEC_BOOL &paIN_G, const CIEC_BOOL &paIN_M, CAnyBitOutputParameter<CIEC_BOOL> paGQI, CAnyBitOutputParameter<CIEC_BOOL> paMQI, COutputParameter<CIEC_STRING> paIoName, COutputParameter<CIEC_WSTRING> paModbusId, CAnyBitOutputParameter<CIEC_BOOL> paQO, CAnyBitOutputParameter<CIEC_BOOL> paLineQI, COutputParameter<CIEC_WSTRING> paLineName, COutputParameter<CIEC_UINT> paChipNo, COutputParameter<CIEC_UINT> paLineNo, COutputParameter<CIEC_UINT> paLineBias, CAnyBitOutputParameter<CIEC_BOOL> paLineLow, CAnyBitOutputParameter<CIEC_BOOL> paIN) {
        COutputGuard guard_GQI(paGQI);
        COutputGuard guard_MQI(paMQI);
        COutputGuard guard_IoName(paIoName);
        COutputGuard guard_ModbusId(paModbusId);
        COutputGuard guard_QO(paQO);
        COutputGuard guard_LineQI(paLineQI);
        COutputGuard guard_LineName(paLineName);
        COutputGuard guard_ChipNo(paChipNo);
        COutputGuard guard_LineNo(paLineNo);
        COutputGuard guard_LineBias(paLineBias);
        COutputGuard guard_LineLow(paLineLow);
        COutputGuard guard_IN(paIN);
        var_Address = paAddress;
        var_QO_G = paQO_G;
        var_QO_M = paQO_M;
        var_SimValue = paSimValue;
        var_IN_G = paIN_G;
        var_IN_M = paIN_M;
        executeEvent(scmEventREQID, nullptr);
        *paGQI = var_GQI;
        *paMQI = var_MQI;
        *paIoName = var_IoName;
        *paModbusId = var_ModbusId;
        *paQO = var_QO;
        *paLineQI = var_LineQI;
        *paLineName = var_LineName;
        *paChipNo = var_ChipNo;
        *paLineNo = var_LineNo;
        *paLineBias = var_LineBias;
        *paLineLow = var_LineLow;
        *paIN = var_IN;
      }
  };
}

