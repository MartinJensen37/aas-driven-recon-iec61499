/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: IO_RouteAI
 *** Description: Picks the way an IO block reaches its signal from the Address (a Pi line, a local IO handle, Modbus or simulated) and passes values through that way only. Technical: Backend router for IO_AI; Address: 'gpio[chip:line(:pull_up|:pull_down)(:active_low)]' or 'pwm[chip:channel:period_ns]' a Raspberry Pi's line, set up here; 'modbus[...]' a Modbus CLIENT ID; 'sim' simulated; another name a local IO handle set up elsewhere (IX/QX PARAMS); empty: not connected (QO = FALSE)
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/IO_RouteAI_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_sint.h"
#include "forte/datatypes/forte_string.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_word.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"
#include "forte/iec61131_functions/func_AND.h"
#include "forte/iec61131_functions/func_EQ.h"
#include "forte/iec61131_functions/func_GT.h"
#include "forte/iec61131_functions/func_LEFT.h"
#include "forte/iec61131_functions/func_LEN.h"
#include "forte/iec61131_functions/func_MUL.h"
#include "forte/iec61131_functions/func_OR.h"
#include "forte/iec61131_functions/func_STRING_TO_WSTRING.h"
#include "forte/iec61131_functions/func_UINT_TO_LREAL.h"
#include "forte/iec61131_functions/func_WORD_TO_UINT.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:96OVdzQQ5qUG73Bxkg0Vfed_c4sCxcXxtze4fbJQ_VYSkzZLU1nVqooianaPwXgGtphzD2C90R5ey-rfCGIyXA=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "IO_READY"_STRID, "CNF_G"_STRID, "CNF_M"_STRID, "REQ"_STRID};
    const auto cEventOutputNames = std::array{"INIT_IO"_STRID, "INITO"_STRID, "REQ_G"_STRID, "REQ_M"_STRID, "CNF"_STRID};
    const auto cDataInputNames = std::array{"Address"_STRID, "QO_G"_STRID, "QO_M"_STRID, "SimValue"_STRID, "IN_G"_STRID, "IN_M"_STRID, "Scale"_STRID};
    const auto cDataOutputNames = std::array{"GQI"_STRID, "MQI"_STRID, "IoName"_STRID, "ModbusId"_STRID, "QO"_STRID, "IN"_STRID};
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

    const auto cInternalsNames = std::array{"Backend"_STRID};
  }

  DEFINE_FIRMWARE_FB(FORTE_IO_RouteAI, "modlib::IO_RouteAI"_STRID, TypeHash)

  FORTE_IO_RouteAI::FORTE_IO_RouteAI(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CBasicFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cInternalsNames),
      var_Backend(0_USINT),
      var_Address(""_STRING),
      var_QO_G(0_BOOL),
      var_QO_M(0_BOOL),
      var_SimValue(0_LREAL),
      var_IN_G(0_WORD),
      var_IN_M(0_WORD),
      var_Scale(1.0_LREAL),
      var_GQI(0_BOOL),
      var_MQI(0_BOOL),
      var_IoName(""_STRING),
      var_ModbusId(u""_WSTRING),
      var_QO(0_BOOL),
      var_IN(0_LREAL),
      conn_INIT_IO(*this, 0),
      conn_INITO(*this, 1),
      conn_REQ_G(*this, 2),
      conn_REQ_M(*this, 3),
      conn_CNF(*this, 4),
      conn_Address(nullptr),
      conn_QO_G(nullptr),
      conn_QO_M(nullptr),
      conn_SimValue(nullptr),
      conn_IN_G(nullptr),
      conn_IN_M(nullptr),
      conn_Scale(nullptr),
      conn_GQI(*this, 0, var_GQI),
      conn_MQI(*this, 1, var_MQI),
      conn_IoName(*this, 2, var_IoName),
      conn_ModbusId(*this, 3, var_ModbusId),
      conn_QO(*this, 4, var_QO),
      conn_IN(*this, 5, var_IN) {
  }

  void FORTE_IO_RouteAI::setInitialValues() {
    CBasicFB::setInitialValues();
    var_Backend = 0_USINT;
    var_Address = ""_STRING;
    var_QO_G = 0_BOOL;
    var_QO_M = 0_BOOL;
    var_SimValue = 0_LREAL;
    var_IN_G = 0_WORD;
    var_IN_M = 0_WORD;
    var_Scale = 1.0_LREAL;
    var_GQI = 0_BOOL;
    var_MQI = 0_BOOL;
    var_IoName = ""_STRING;
    var_ModbusId = u""_WSTRING;
    var_QO = 0_BOOL;
    var_IN = 0_LREAL;
  }

  void FORTE_IO_RouteAI::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
    do {
      switch(mECCState) {
        case scmStateSTART:
          if(scmEventINITID == paEIID) enterStateInit(paECET);
          else
          if(scmEventIO_READYID == paEIID) enterStateReady(paECET);
          else
          if((scmEventREQID == paEIID) && (func_EQ(var_Backend, 1_USINT))) enterStateReqG(paECET);
          else
          if((scmEventREQID == paEIID) && (func_EQ(var_Backend, 2_USINT))) enterStateReqM(paECET);
          else
          if((scmEventREQID == paEIID) && (func_EQ(var_Backend, 3_USINT))) enterStateNone(paECET);
          else
          if(scmEventREQID == paEIID) enterStateSim(paECET);
          else
          if(scmEventCNF_GID == paEIID) enterStateDoneG(paECET);
          else
          if(scmEventCNF_MID == paEIID) enterStateDoneM(paECET);
          else return; //no transition cleared
          break;
        case scmStateInit:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStateReady:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStateReqG:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStateReqM:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStateSim:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStateNone:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStateDoneG:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStateDoneM:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        default:
          DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 9.", mECCState.operator TForteUInt16 ());
          mECCState = 0; // 0 is always the initial state
          return;
      }
      paEIID = cgInvalidEventID; // we have to clear the event after the first check in order to ensure correct behavior
    } while(true);
  }

  void FORTE_IO_RouteAI::enterStateSTART(CEventChainExecutionThread *const) {
    mECCState = scmStateSTART;
  }

  void FORTE_IO_RouteAI::enterStateInit(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateInit;
    alg_Alg_Init();
    sendOutputEvent(scmEventINIT_IOID, paECET);
  }

  void FORTE_IO_RouteAI::enterStateReady(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateReady;
    alg_Alg_Ready();
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_IO_RouteAI::enterStateReqG(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateReqG;
    sendOutputEvent(scmEventREQ_GID, paECET);
  }

  void FORTE_IO_RouteAI::enterStateReqM(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateReqM;
    sendOutputEvent(scmEventREQ_MID, paECET);
  }

  void FORTE_IO_RouteAI::enterStateSim(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateSim;
    alg_Alg_Sim();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_IO_RouteAI::enterStateNone(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateNone;
    alg_Alg_None();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_IO_RouteAI::enterStateDoneG(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateDoneG;
    alg_Alg_DoneG();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_IO_RouteAI::enterStateDoneM(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateDoneM;
    alg_Alg_DoneM();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_IO_RouteAI::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINITID: {
        readData(0, var_Address, conn_Address);
        break;
      }
      case scmEventIO_READYID: {
        readData(1, var_QO_G, conn_QO_G);
        readData(2, var_QO_M, conn_QO_M);
        break;
      }
      case scmEventCNF_GID: {
        readData(1, var_QO_G, conn_QO_G);
        readData(4, var_IN_G, conn_IN_G);
        break;
      }
      case scmEventCNF_MID: {
        readData(2, var_QO_M, conn_QO_M);
        readData(5, var_IN_M, conn_IN_M);
        break;
      }
      case scmEventREQID: {
        readData(3, var_SimValue, conn_SimValue);
        readData(6, var_Scale, conn_Scale);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_IO_RouteAI::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINIT_IOID: {
        writeData(7, var_GQI, conn_GQI);
        writeData(8, var_MQI, conn_MQI);
        writeData(9, var_IoName, conn_IoName);
        writeData(10, var_ModbusId, conn_ModbusId);
        break;
      }
      case scmEventINITOID: {
        writeData(11, var_QO, conn_QO);
        break;
      }
      case scmEventCNFID: {
        writeData(11, var_QO, conn_QO);
        writeData(12, var_IN, conn_IN);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_IO_RouteAI::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Address;
      case 1: return &var_QO_G;
      case 2: return &var_QO_M;
      case 3: return &var_SimValue;
      case 4: return &var_IN_G;
      case 5: return &var_IN_M;
      case 6: return &var_Scale;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_IO_RouteAI::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_GQI;
      case 1: return &var_MQI;
      case 2: return &var_IoName;
      case 3: return &var_ModbusId;
      case 4: return &var_QO;
      case 5: return &var_IN;
    }
    return nullptr;
  }

  CEventConnection *FORTE_IO_RouteAI::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INIT_IO;
      case 1: return &conn_INITO;
      case 2: return &conn_REQ_G;
      case 3: return &conn_REQ_M;
      case 4: return &conn_CNF;
    }
    return nullptr;
  }

  CDataConnection **FORTE_IO_RouteAI::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Address;
      case 1: return &conn_QO_G;
      case 2: return &conn_QO_M;
      case 3: return &conn_SimValue;
      case 4: return &conn_IN_G;
      case 5: return &conn_IN_M;
      case 6: return &conn_Scale;
    }
    return nullptr;
  }

  CDataConnection *FORTE_IO_RouteAI::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_GQI;
      case 1: return &conn_MQI;
      case 2: return &conn_IoName;
      case 3: return &conn_ModbusId;
      case 4: return &conn_QO;
      case 5: return &conn_IN;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_IO_RouteAI::getVarInternal(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Backend;
    }
    return nullptr;
  }

  void FORTE_IO_RouteAI::alg_Alg_Init(void) {

    #line 2 "IO_RouteAI.fbt"
    var_Backend = 3_USINT;
    #line 3 "IO_RouteAI.fbt"
    if (func_EQ(var_Address, "sim"_STRING)) {
      #line 4 "IO_RouteAI.fbt"
      var_Backend = 0_USINT;
    }
    else if (func_EQ(func_LEFT(var_Address, 7_SINT), "modbus["_STRING)) {
      #line 6 "IO_RouteAI.fbt"
      var_Backend = 2_USINT;
      #line 7 "IO_RouteAI.fbt"
      var_ModbusId = func_STRING_TO_WSTRING(var_Address);
    }
    else if (func_GT(func_LEN<CIEC_SINT>(var_Address), 0_SINT)) {
      #line 9 "IO_RouteAI.fbt"
      var_Backend = 1_USINT;
      #line 10 "IO_RouteAI.fbt"
      var_IoName = var_Address;
    }
    #line 12 "IO_RouteAI.fbt"
    var_GQI = func_EQ(var_Backend, 1_USINT);
    #line 13 "IO_RouteAI.fbt"
    var_MQI = func_EQ(var_Backend, 2_USINT);
  }

  void FORTE_IO_RouteAI::alg_Alg_Ready(void) {

    #line 17 "IO_RouteAI.fbt"
    var_QO = func_OR<CIEC_BOOL>(func_OR<CIEC_BOOL>(func_EQ(var_Backend, 0_USINT), func_AND<CIEC_BOOL>(func_EQ(var_Backend, 1_USINT), var_QO_G)), func_AND<CIEC_BOOL>(func_EQ(var_Backend, 2_USINT), var_QO_M));
  }

  void FORTE_IO_RouteAI::alg_Alg_Sim(void) {

    #line 21 "IO_RouteAI.fbt"
    var_QO = true_BOOL;
    #line 22 "IO_RouteAI.fbt"
    var_IN = var_SimValue;
  }

  void FORTE_IO_RouteAI::alg_Alg_None(void) {

    #line 26 "IO_RouteAI.fbt"
    var_QO = false_BOOL;
  }

  void FORTE_IO_RouteAI::alg_Alg_DoneG(void) {

    #line 30 "IO_RouteAI.fbt"
    var_QO = var_QO_G;
    #line 31 "IO_RouteAI.fbt"
    var_IN = func_MUL<CIEC_LREAL>(func_UINT_TO_LREAL(func_WORD_TO_UINT(var_IN_G)), var_Scale);
  }

  void FORTE_IO_RouteAI::alg_Alg_DoneM(void) {

    #line 35 "IO_RouteAI.fbt"
    var_QO = var_QO_M;
    #line 36 "IO_RouteAI.fbt"
    var_IN = func_MUL<CIEC_LREAL>(func_UINT_TO_LREAL(func_WORD_TO_UINT(var_IN_M)), var_Scale);
  }

}