/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: MOD_OccupationLogic
 *** Description: Decides Occupy and Release: occupy when free (or again by the owner), release only by the owner, and answer Accepted or an error code. Technical: Occupation by session ID: Occupy when free (or again by the owner), Release only by the owner
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/MOD_OccupationLogic_fbt.h"

#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_uint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"
#include "forte/iec61131_functions/func_AND.h"
#include "forte/iec61131_functions/func_EQ.h"
#include "forte/iec61131_functions/func_NE.h"
#include "forte/iec61131_functions/func_OR.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:kKCtp5t_TL5qg2hM5Tet6ru2pX6ksFsd9ks66_KGSkDl3Z1eoXACOXGuEtOZucGpwRkCDmSP0jRm1OJ130Ohrw=="sv;

    const auto cEventInputNames = std::array{"OCCUPY_REQ"_STRID, "RELEASE_REQ"_STRID, "QUERY_REQ"_STRID};
    const auto cEventOutputNames = std::array{"OCCUPY_RSP"_STRID, "RELEASE_RSP"_STRID, "CHG"_STRID};
    const auto cDataInputNames = std::array{"OccupySession"_STRID, "ReleaseSession"_STRID};
    const auto cDataOutputNames = std::array{"Accepted"_STRID, "ErrorID"_STRID, "Owner"_STRID, "Occupied"_STRID};
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
  }

  DEFINE_FIRMWARE_FB(FORTE_MOD_OccupationLogic, "modlib::MOD_OccupationLogic"_STRID, TypeHash)

  FORTE_MOD_OccupationLogic::FORTE_MOD_OccupationLogic(const StringId paInstanceNameId, CFBContainer &paContainer) :
      CBasicFB(paContainer, cFBInterfaceSpec, paInstanceNameId, {}),
      var_OccupySession(u""_WSTRING),
      var_ReleaseSession(u""_WSTRING),
      var_Accepted(0_BOOL),
      var_ErrorID(0_UINT),
      var_Owner(u""_WSTRING),
      var_Occupied(0_BOOL),
      conn_OCCUPY_RSP(*this, 0),
      conn_RELEASE_RSP(*this, 1),
      conn_CHG(*this, 2),
      conn_OccupySession(nullptr),
      conn_ReleaseSession(nullptr),
      conn_Accepted(*this, 0, var_Accepted),
      conn_ErrorID(*this, 1, var_ErrorID),
      conn_Owner(*this, 2, var_Owner),
      conn_Occupied(*this, 3, var_Occupied) {
  }

  void FORTE_MOD_OccupationLogic::setInitialValues() {
    CBasicFB::setInitialValues();
    var_OccupySession = u""_WSTRING;
    var_ReleaseSession = u""_WSTRING;
    var_Accepted = 0_BOOL;
    var_ErrorID = 0_UINT;
    var_Owner = u""_WSTRING;
    var_Occupied = 0_BOOL;
  }

  void FORTE_MOD_OccupationLogic::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
    do {
      switch(mECCState) {
        case scmStateSTART:
          if(scmEventOCCUPY_REQID == paEIID) enterStateOccupy(paECET);
          else
          if(scmEventRELEASE_REQID == paEIID) enterStateRelease(paECET);
          else
          if(scmEventQUERY_REQID == paEIID) enterStateQuery(paECET);
          else return; //no transition cleared
          break;
        case scmStateOccupy:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStateRelease:
          if(1) enterStateSTART(paECET);
          else return; //no transition cleared
          break;
        case scmStateQuery:
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

  void FORTE_MOD_OccupationLogic::enterStateSTART(CEventChainExecutionThread *const) {
    mECCState = scmStateSTART;
  }

  void FORTE_MOD_OccupationLogic::enterStateOccupy(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateOccupy;
    alg_Alg_Occupy();
    sendOutputEvent(scmEventOCCUPY_RSPID, paECET);
    sendOutputEvent(scmEventCHGID, paECET);
  }

  void FORTE_MOD_OccupationLogic::enterStateRelease(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateRelease;
    alg_Alg_Release();
    sendOutputEvent(scmEventRELEASE_RSPID, paECET);
    sendOutputEvent(scmEventCHGID, paECET);
  }

  void FORTE_MOD_OccupationLogic::enterStateQuery(CEventChainExecutionThread *const paECET) {
    mECCState = scmStateQuery;
    sendOutputEvent(scmEventCHGID, paECET);
  }

  void FORTE_MOD_OccupationLogic::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventOCCUPY_REQID: {
        readData(0, var_OccupySession, conn_OccupySession);
        break;
      }
      case scmEventRELEASE_REQID: {
        readData(1, var_ReleaseSession, conn_ReleaseSession);
        break;
      }
      default:
        break;
    }
  }

  void FORTE_MOD_OccupationLogic::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventOCCUPY_RSPID: {
        writeData(2, var_Accepted, conn_Accepted);
        writeData(3, var_ErrorID, conn_ErrorID);
        break;
      }
      case scmEventRELEASE_RSPID: {
        writeData(2, var_Accepted, conn_Accepted);
        writeData(3, var_ErrorID, conn_ErrorID);
        break;
      }
      case scmEventCHGID: {
        writeData(4, var_Owner, conn_Owner);
        writeData(5, var_Occupied, conn_Occupied);
        break;
      }
      default:
        break;
    }
  }

  CIEC_ANY *FORTE_MOD_OccupationLogic::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_OccupySession;
      case 1: return &var_ReleaseSession;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_MOD_OccupationLogic::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Accepted;
      case 1: return &var_ErrorID;
      case 2: return &var_Owner;
      case 3: return &var_Occupied;
    }
    return nullptr;
  }

  CEventConnection *FORTE_MOD_OccupationLogic::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_OCCUPY_RSP;
      case 1: return &conn_RELEASE_RSP;
      case 2: return &conn_CHG;
    }
    return nullptr;
  }

  CDataConnection **FORTE_MOD_OccupationLogic::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_OccupySession;
      case 1: return &conn_ReleaseSession;
    }
    return nullptr;
  }

  CDataConnection *FORTE_MOD_OccupationLogic::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Accepted;
      case 1: return &conn_ErrorID;
      case 2: return &conn_Owner;
      case 3: return &conn_Occupied;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_MOD_OccupationLogic::getVarInternal(size_t) {
    return nullptr;
  }

  void FORTE_MOD_OccupationLogic::alg_Alg_Occupy(void) {

    #line 2 "MOD_OccupationLogic.fbt"
    if (func_AND<CIEC_BOOL>(func_NE(var_OccupySession, u""_WSTRING), func_OR<CIEC_BOOL>(func_EQ(var_Owner, u""_WSTRING), func_EQ(var_Owner, var_OccupySession)))) {
      #line 3 "MOD_OccupationLogic.fbt"
      var_Owner = var_OccupySession;
      #line 4 "MOD_OccupationLogic.fbt"
      var_Occupied = true_BOOL;
      #line 5 "MOD_OccupationLogic.fbt"
      var_Accepted = true_BOOL;
      #line 6 "MOD_OccupationLogic.fbt"
      var_ErrorID = 0_UINT;
    }
    else {
      #line 8 "MOD_OccupationLogic.fbt"
      var_Accepted = false_BOOL;
      #line 9 "MOD_OccupationLogic.fbt"
      var_ErrorID = 5_UINT;
    }
  }

  void FORTE_MOD_OccupationLogic::alg_Alg_Release(void) {

    #line 14 "MOD_OccupationLogic.fbt"
    if (func_AND<CIEC_BOOL>(func_NE(var_Owner, u""_WSTRING), func_EQ(var_Owner, var_ReleaseSession))) {
      #line 15 "MOD_OccupationLogic.fbt"
      var_Owner = u""_WSTRING;
      #line 16 "MOD_OccupationLogic.fbt"
      var_Occupied = false_BOOL;
      #line 17 "MOD_OccupationLogic.fbt"
      var_Accepted = true_BOOL;
      #line 18 "MOD_OccupationLogic.fbt"
      var_ErrorID = 0_UINT;
    }
    else {
      #line 20 "MOD_OccupationLogic.fbt"
      var_Accepted = false_BOOL;
      #line 21 "MOD_OccupationLogic.fbt"
      var_ErrorID = 5_UINT;
    }
  }

}