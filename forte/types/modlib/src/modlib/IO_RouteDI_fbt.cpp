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

#include "forte/modlib/IO_RouteDI_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_char.h"
#include "forte/datatypes/forte_int.h"
#include "forte/datatypes/forte_sint.h"
#include "forte/datatypes/forte_string.h"
#include "forte/datatypes/forte_udint.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_iterator.h"
#include "forte/forte_st_util.h"
#include "forte/iec61131_functions/func_ADD.h"
#include "forte/iec61131_functions/func_AND.h"
#include "forte/iec61131_functions/func_EQ.h"
#include "forte/iec61131_functions/func_FIND.h"
#include "forte/iec61131_functions/func_GT.h"
#include "forte/iec61131_functions/func_INT_TO_UDINT.h"
#include "forte/iec61131_functions/func_LEFT.h"
#include "forte/iec61131_functions/func_LEN.h"
#include "forte/iec61131_functions/func_MID.h"
#include "forte/iec61131_functions/func_MUL.h"
#include "forte/iec61131_functions/func_OR.h"
#include "forte/iec61131_functions/func_STRING_TO_WSTRING.h"
#include "forte/iec61131_functions/func_SUB.h"
#include "forte/iec61131_functions/func_UDINT_TO_UINT.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:L61znhY3QrVH8EGAaE1Od6CTtxnTowK30xLdGNW_EkQx0oh3LIxOwhu05x19HKZx1udag6-OkhEbblx4pqyrXg=="sv;

    const auto cEventInputNames = std::array{"INIT"_STRID, "IO_READY"_STRID, "CNF_G"_STRID, "CNF_M"_STRID, "REQ"_STRID};
    const auto cEventOutputNames = std::array{"INIT_IO"_STRID, "INITO"_STRID, "REQ_G"_STRID, "REQ_M"_STRID, "CNF"_STRID};
    const auto cDataInputNames = std::array{"Address"_STRID, "QO_G"_STRID, "QO_M"_STRID, "SimValue"_STRID, "IN_G"_STRID, "IN_M"_STRID};
    const auto cDataOutputNames = std::array{"GQI"_STRID, "MQI"_STRID, "IoName"_STRID, "ModbusId"_STRID, "QO"_STRID, "LineQI"_STRID, "LineName"_STRID, "ChipNo"_STRID, "LineNo"_STRID, "LineBias"_STRID, "LineLow"_STRID, "IN"_STRID};
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

  DEFINE_FIRMWARE_FB(FORTE_IO_RouteDI, "modlib::IO_RouteDI"_STRID, TypeHash)

  FORTE_IO_RouteDI::FORTE_IO_RouteDI(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CBasicFB(paContainer, cFBInterfaceSpec, paInstanceNameId, cInternalsNames),
      var_Backend(0_USINT),
      var_Address(""_STRING),
      var_QO_G(0_BOOL),
      var_QO_M(0_BOOL),
      var_SimValue(0_BOOL),
      var_IN_G(0_BOOL),
      var_IN_M(0_BOOL),
      var_GQI(0_BOOL),
      var_MQI(0_BOOL),
      var_IoName(""_STRING),
      var_ModbusId(u""_WSTRING),
      var_QO(0_BOOL),
      var_LineQI(0_BOOL),
      var_LineName(u""_WSTRING),
      var_ChipNo(0_UINT),
      var_LineNo(0_UINT),
      var_LineBias(0_UINT),
      var_LineLow(0_BOOL),
      var_IN(0_BOOL),
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
      conn_GQI(*this, 0, var_GQI),
      conn_MQI(*this, 1, var_MQI),
      conn_IoName(*this, 2, var_IoName),
      conn_ModbusId(*this, 3, var_ModbusId),
      conn_QO(*this, 4, var_QO),
      conn_LineQI(*this, 5, var_LineQI),
      conn_LineName(*this, 6, var_LineName),
      conn_ChipNo(*this, 7, var_ChipNo),
      conn_LineNo(*this, 8, var_LineNo),
      conn_LineBias(*this, 9, var_LineBias),
      conn_LineLow(*this, 10, var_LineLow),
      conn_IN(*this, 11, var_IN) {
  }

  void FORTE_IO_RouteDI::setInitialValues() {
    CBasicFB::setInitialValues();
    var_Backend = 0_USINT;
    var_Address = ""_STRING;
    var_QO_G = 0_BOOL;
    var_QO_M = 0_BOOL;
    var_SimValue = 0_BOOL;
    var_IN_G = 0_BOOL;
    var_IN_M = 0_BOOL;
    var_GQI = 0_BOOL;
    var_MQI = 0_BOOL;
    var_IoName = ""_STRING;
    var_ModbusId = u""_WSTRING;
    var_QO = 0_BOOL;
    var_LineQI = 0_BOOL;
    var_LineName = u""_WSTRING;
    var_ChipNo = 0_UINT;
    var_LineNo = 0_UINT;
    var_LineBias = 0_UINT;
    var_LineLow = 0_BOOL;
    var_IN = 0_BOOL;
  }

  void FORTE_IO_RouteDI::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
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

  void FORTE_IO_RouteDI::enterStateSTART(CEventChainExecutionThread *const) {
    mECCState = scmStateSTART;
  }

  void FORTE_IO_RouteDI::enterStateInit(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateInit;
    alg_Alg_Init();
    sendOutputEvent(scmEventINIT_IOID, paECET);
  }

  void FORTE_IO_RouteDI::enterStateReady(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateReady;
    alg_Alg_Ready();
    sendOutputEvent(scmEventINITOID, paECET);
  }

  void FORTE_IO_RouteDI::enterStateReqG(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateReqG;
    sendOutputEvent(scmEventREQ_GID, paECET);
  }

  void FORTE_IO_RouteDI::enterStateReqM(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateReqM;
    sendOutputEvent(scmEventREQ_MID, paECET);
  }

  void FORTE_IO_RouteDI::enterStateSim(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateSim;
    alg_Alg_Sim();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_IO_RouteDI::enterStateNone(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateNone;
    alg_Alg_None();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_IO_RouteDI::enterStateDoneG(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateDoneG;
    alg_Alg_DoneG();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_IO_RouteDI::enterStateDoneM(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateDoneM;
    alg_Alg_DoneM();
    sendOutputEvent(scmEventCNFID, paECET);
  }

  void FORTE_IO_RouteDI::readInputData(const TEventID paEIID) {
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
        break;
      }
      default:
        break;
    }
  }

  void FORTE_IO_RouteDI::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventINIT_IOID: {
        writeData(6, var_GQI, conn_GQI);
        writeData(7, var_MQI, conn_MQI);
        writeData(8, var_IoName, conn_IoName);
        writeData(9, var_ModbusId, conn_ModbusId);
        writeData(11, var_LineQI, conn_LineQI);
        writeData(12, var_LineName, conn_LineName);
        writeData(13, var_ChipNo, conn_ChipNo);
        writeData(14, var_LineNo, conn_LineNo);
        writeData(15, var_LineBias, conn_LineBias);
        writeData(16, var_LineLow, conn_LineLow);
        break;
      }
      case scmEventINITOID: {
        writeData(10, var_QO, conn_QO);
        break;
      }
      case scmEventCNFID: {
        writeData(10, var_QO, conn_QO);
        writeData(17, var_IN, conn_IN);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_IO_RouteDI::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Address;
      case 1: return &var_QO_G;
      case 2: return &var_QO_M;
      case 3: return &var_SimValue;
      case 4: return &var_IN_G;
      case 5: return &var_IN_M;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_IO_RouteDI::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_GQI;
      case 1: return &var_MQI;
      case 2: return &var_IoName;
      case 3: return &var_ModbusId;
      case 4: return &var_QO;
      case 5: return &var_LineQI;
      case 6: return &var_LineName;
      case 7: return &var_ChipNo;
      case 8: return &var_LineNo;
      case 9: return &var_LineBias;
      case 10: return &var_LineLow;
      case 11: return &var_IN;
    }
    return nullptr;
  }

  CEventConnection *FORTE_IO_RouteDI::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_INIT_IO;
      case 1: return &conn_INITO;
      case 2: return &conn_REQ_G;
      case 3: return &conn_REQ_M;
      case 4: return &conn_CNF;
    }
    return nullptr;
  }

  CDataConnection **FORTE_IO_RouteDI::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Address;
      case 1: return &conn_QO_G;
      case 2: return &conn_QO_M;
      case 3: return &conn_SimValue;
      case 4: return &conn_IN_G;
      case 5: return &conn_IN_M;
    }
    return nullptr;
  }

  CDataConnection *FORTE_IO_RouteDI::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_GQI;
      case 1: return &conn_MQI;
      case 2: return &conn_IoName;
      case 3: return &conn_ModbusId;
      case 4: return &conn_QO;
      case 5: return &conn_LineQI;
      case 6: return &conn_LineName;
      case 7: return &conn_ChipNo;
      case 8: return &conn_LineNo;
      case 9: return &conn_LineBias;
      case 10: return &conn_LineLow;
      case 11: return &conn_IN;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_IO_RouteDI::getVarInternal(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Backend;
    }
    return nullptr;
  }

  void FORTE_IO_RouteDI::alg_Alg_Init(void) {
    CIEC_STRING st_lv_Field = ""_STRING;
    CIEC_INT st_lv_Length = 0_INT;
    CIEC_INT st_lv_Cut = 0_INT;
    CIEC_INT st_lv_Pos = 0_INT;
    CIEC_INT st_lv_Digit = 0_INT;
    CIEC_UDINT st_lv_Number = 0_UDINT;

    #line 10 "IO_RouteDI.fbt"
    var_Backend = 3_USINT;
    #line 11 "IO_RouteDI.fbt"
    var_LineQI = false_BOOL;
    #line 12 "IO_RouteDI.fbt"
    if (func_EQ(var_Address, "sim"_STRING)) {
      #line 13 "IO_RouteDI.fbt"
      var_Backend = 0_USINT;
    }
    else if (func_EQ(func_LEFT(var_Address, 7_SINT), "modbus["_STRING)) {
      #line 15 "IO_RouteDI.fbt"
      var_Backend = 2_USINT;
      #line 16 "IO_RouteDI.fbt"
      var_ModbusId = func_STRING_TO_WSTRING(var_Address);
    }
    else if (func_EQ(func_LEFT(var_Address, 5_SINT), "gpio["_STRING)) {
      #line 18 "IO_RouteDI.fbt"
      var_Backend = 1_USINT;
      #line 19 "IO_RouteDI.fbt"
      var_IoName = var_Address;
      #line 20 "IO_RouteDI.fbt"
      var_LineQI = true_BOOL;
      #line 21 "IO_RouteDI.fbt"
      var_LineName = func_STRING_TO_WSTRING(var_Address);
      #line 22 "IO_RouteDI.fbt"
      st_lv_Length = func_LEN<CIEC_INT>(var_Address);
      #line 23 "IO_RouteDI.fbt"
      st_lv_Field = func_MID(var_Address, func_SUB<CIEC_INT>(st_lv_Length, 5_INT), 6_SINT);
      #line 24 "IO_RouteDI.fbt"
      st_lv_Cut = func_FIND<CIEC_INT>(st_lv_Field, 0x3a_CHAR);
      #line 25 "IO_RouteDI.fbt"
      if (func_EQ(st_lv_Cut, 0_INT)) {
        #line 26 "IO_RouteDI.fbt"
        st_lv_Cut = func_FIND<CIEC_INT>(st_lv_Field, 0x5d_CHAR);
      }
      #line 28 "IO_RouteDI.fbt"
      st_lv_Number = 0_UDINT;
      #line 29 "IO_RouteDI.fbt"
      for (auto st_lv_synthetic_0 : ST_FOR_ITER<CIEC_INT>(st_lv_Digit, 1_INT, func_SUB<CIEC_INT>(st_lv_Cut, 1_INT))) {
        #line 30 "IO_RouteDI.fbt"
        st_lv_Pos = func_FIND<CIEC_INT>("0123456789"_STRING, func_MID(st_lv_Field, 1_SINT, st_lv_Digit));
        #line 31 "IO_RouteDI.fbt"
        st_lv_Number = func_ADD<CIEC_UDINT>(func_MUL<CIEC_UDINT>(st_lv_Number, 10_UDINT), func_INT_TO_UDINT(func_SUB<CIEC_INT>(st_lv_Pos, 1_INT)));
      }
      #line 33 "IO_RouteDI.fbt"
      var_ChipNo = func_UDINT_TO_UINT(st_lv_Number);
      #line 34 "IO_RouteDI.fbt"
      st_lv_Length = func_LEN<CIEC_INT>(st_lv_Field);
      #line 35 "IO_RouteDI.fbt"
      st_lv_Field = func_MID(st_lv_Field, func_SUB<CIEC_INT>(st_lv_Length, st_lv_Cut), func_ADD<CIEC_INT>(st_lv_Cut, 1_INT));
      #line 36 "IO_RouteDI.fbt"
      st_lv_Cut = func_FIND<CIEC_INT>(st_lv_Field, 0x3a_CHAR);
      #line 37 "IO_RouteDI.fbt"
      if (func_EQ(st_lv_Cut, 0_INT)) {
        #line 38 "IO_RouteDI.fbt"
        st_lv_Cut = func_FIND<CIEC_INT>(st_lv_Field, 0x5d_CHAR);
      }
      #line 40 "IO_RouteDI.fbt"
      st_lv_Number = 0_UDINT;
      #line 41 "IO_RouteDI.fbt"
      for (auto st_lv_synthetic_1 : ST_FOR_ITER<CIEC_INT>(st_lv_Digit, 1_INT, func_SUB<CIEC_INT>(st_lv_Cut, 1_INT))) {
        #line 42 "IO_RouteDI.fbt"
        st_lv_Pos = func_FIND<CIEC_INT>("0123456789"_STRING, func_MID(st_lv_Field, 1_SINT, st_lv_Digit));
        #line 43 "IO_RouteDI.fbt"
        st_lv_Number = func_ADD<CIEC_UDINT>(func_MUL<CIEC_UDINT>(st_lv_Number, 10_UDINT), func_INT_TO_UDINT(func_SUB<CIEC_INT>(st_lv_Pos, 1_INT)));
      }
      #line 45 "IO_RouteDI.fbt"
      var_LineNo = func_UDINT_TO_UINT(st_lv_Number);
      #line 46 "IO_RouteDI.fbt"
      st_lv_Length = func_LEN<CIEC_INT>(st_lv_Field);
      #line 47 "IO_RouteDI.fbt"
      st_lv_Field = func_MID(st_lv_Field, func_SUB<CIEC_INT>(st_lv_Length, st_lv_Cut), func_ADD<CIEC_INT>(st_lv_Cut, 1_INT));
      #line 48 "IO_RouteDI.fbt"
      if (func_GT(func_FIND<CIEC_SINT>(var_Address, ":pull_up"_STRING), 0_SINT)) {
        #line 49 "IO_RouteDI.fbt"
        var_LineBias = 2_UINT;
      }
      else if (func_GT(func_FIND<CIEC_SINT>(var_Address, ":pull_down"_STRING), 0_SINT)) {
        #line 51 "IO_RouteDI.fbt"
        var_LineBias = 3_UINT;
      }
      else {
        #line 53 "IO_RouteDI.fbt"
        var_LineBias = 0_UINT;
      }
      #line 55 "IO_RouteDI.fbt"
      var_LineLow = func_GT(func_FIND<CIEC_SINT>(var_Address, ":active_low"_STRING), 0_SINT);
    }
    else if (func_GT(func_LEN<CIEC_SINT>(var_Address), 0_SINT)) {
      #line 57 "IO_RouteDI.fbt"
      var_Backend = 1_USINT;
      #line 58 "IO_RouteDI.fbt"
      var_IoName = var_Address;
    }
    #line 60 "IO_RouteDI.fbt"
    var_GQI = func_EQ(var_Backend, 1_USINT);
    #line 61 "IO_RouteDI.fbt"
    var_MQI = func_EQ(var_Backend, 2_USINT);
  }

  void FORTE_IO_RouteDI::alg_Alg_Ready(void) {

    #line 65 "IO_RouteDI.fbt"
    var_QO = func_OR<CIEC_BOOL>(func_OR<CIEC_BOOL>(func_EQ(var_Backend, 0_USINT), func_AND<CIEC_BOOL>(func_EQ(var_Backend, 1_USINT), var_QO_G)), func_AND<CIEC_BOOL>(func_EQ(var_Backend, 2_USINT), var_QO_M));
  }

  void FORTE_IO_RouteDI::alg_Alg_Sim(void) {

    #line 69 "IO_RouteDI.fbt"
    var_QO = true_BOOL;
    #line 70 "IO_RouteDI.fbt"
    var_IN = var_SimValue;
  }

  void FORTE_IO_RouteDI::alg_Alg_None(void) {

    #line 74 "IO_RouteDI.fbt"
    var_QO = false_BOOL;
  }

  void FORTE_IO_RouteDI::alg_Alg_DoneG(void) {

    #line 78 "IO_RouteDI.fbt"
    var_QO = var_QO_G;
    #line 79 "IO_RouteDI.fbt"
    var_IN = var_IN_G;
  }

  void FORTE_IO_RouteDI::alg_Alg_DoneM(void) {

    #line 83 "IO_RouteDI.fbt"
    var_QO = var_QO_M;
    #line 84 "IO_RouteDI.fbt"
    var_IN = var_IN_M;
  }

}