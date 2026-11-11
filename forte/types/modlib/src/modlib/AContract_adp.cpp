/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: AContract
 *** Description: An adapter: one connection from a primitive's contract (SC_, the plug) to its run (SKILL_Run, the socket) that carries what the contract says: at the start what to do and whether it may start, at each new state of the equipment whether it is done and may go on. Technical: What a skill primitive's contract (SC_, the plug) tells its run (SKILL_Run, the socket): at START what to do and whether it may start, at SAMPLE whether the newest state of the equipment ends the run
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/AContract_adp.h"


using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:xu1th1IUXvB0jSnrDBgIPt13tm-R2lpXmiLX1PZQrGs_W6db70LzLIzYFCVQOWz0qomO4t4suej-IIk6G-kBhg=="sv;

    const auto cEventOutputNames = std::array{"START"_STRID, "SAMPLE"_STRID};
    const auto cDataOutputNames = std::array{"Pre"_STRID, "Post"_STRID, "Timed"_STRID, "RunTime"_STRID, "Command"_STRID, "Arg"_STRID, "StopCommand"_STRID, "Inv"_STRID, "EqHolder"_STRID};

    const SFBInterfaceSpec cFBInterfaceSpecSocket = {
        .mEINames = {},
        .mEITypeNames = {},
        .mEONames = cEventOutputNames,
        .mEOTypeNames = {},
        .mDINames = {},
        .mDONames = cDataOutputNames,
        .mDIONames = {},
        .mSocketNames = {},
        .mPlugNames = {},
    };

    const SFBInterfaceSpec cFBInterfaceSpecPlug = {
        .mEINames = cEventOutputNames,
        .mEITypeNames = {},
        .mEONames = {},
        .mEOTypeNames = {},
        .mDINames = cDataOutputNames,
        .mDONames = {},
        .mDIONames = {},
        .mSocketNames = {},
        .mPlugNames = {},
    };
  }

  DEFINE_ADAPTER_TYPE(FORTE_AContract, "modlib::AContract"_STRID, TypeHash)


  FORTE_AContract::FORTE_AContract(CFBContainer &paContainer,
                               const SFBInterfaceSpec &paInterfaceSpec,
                               const StringId paInstanceNameId,
                               TForteUInt8 paParentAdapterlistID) :
      CAdapter(paContainer, paInterfaceSpec, paInstanceNameId, paParentAdapterlistID),
      var_Pre(0_BOOL),
      var_Post(0_BOOL),
      var_Timed(0_BOOL),
      var_RunTime(0_TIME),
      var_Command(0_USINT),
      var_Arg(0_LREAL),
      var_StopCommand(0_USINT),
      var_Inv(0_BOOL),
      var_EqHolder(u""_WSTRING) {
  }

  void FORTE_AContract::setInitialValues() {
    forte::CAdapter::setInitialValues();
    var_Pre = 0_BOOL;
    var_Post = 0_BOOL;
    var_Timed = 0_BOOL;
    var_RunTime = 0_TIME;
    var_Command = 0_USINT;
    var_Arg = 0_LREAL;
    var_StopCommand = 0_USINT;
    var_Inv = 0_BOOL;
    var_EqHolder = u""_WSTRING;
  }


  FORTE_AContract_Plug::FORTE_AContract_Plug(StringId paInstanceNameId,
                                           CFBContainer &paContainer,
                                           TForteUInt8 paParentAdapterlistID) :
      FORTE_AContract(paContainer, cFBInterfaceSpecPlug, paInstanceNameId, paParentAdapterlistID),
      conn_Pre(nullptr),
      conn_Post(nullptr),
      conn_Timed(nullptr),
      conn_RunTime(nullptr),
      conn_Command(nullptr),
      conn_Arg(nullptr),
      conn_StopCommand(nullptr),
      conn_Inv(nullptr),
      conn_EqHolder(nullptr) {
  }

  void FORTE_AContract_Plug::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventSTARTID: {
        readData(0, var_Pre, conn_Pre);
        readData(1, var_Post, conn_Post);
        readData(2, var_Timed, conn_Timed);
        readData(3, var_RunTime, conn_RunTime);
        readData(4, var_Command, conn_Command);
        readData(5, var_Arg, conn_Arg);
        readData(6, var_StopCommand, conn_StopCommand);
        if(auto peer = static_cast<FORTE_AContract_Socket *>(getPeer()); peer) {
          peer->var_Pre = var_Pre;
          peer->var_Post = var_Post;
          peer->var_Timed = var_Timed;
          peer->var_RunTime = var_RunTime;
          peer->var_Command = var_Command;
          peer->var_Arg = var_Arg;
          peer->var_StopCommand = var_StopCommand;
        }
        break;
      }
      case scmEventSAMPLEID: {
        readData(1, var_Post, conn_Post);
        readData(7, var_Inv, conn_Inv);
        readData(8, var_EqHolder, conn_EqHolder);
        if(auto peer = static_cast<FORTE_AContract_Socket *>(getPeer()); peer) {
          peer->var_Post = var_Post;
          peer->var_Inv = var_Inv;
          peer->var_EqHolder = var_EqHolder;
        }
        break;
      }
      default:
        break;
    }
  }

  void FORTE_AContract_Plug::writeOutputData(TEventID) {
    // nothing to do
  }
  CIEC_ANY *FORTE_AContract_Plug::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Pre;
      case 1: return &var_Post;
      case 2: return &var_Timed;
      case 3: return &var_RunTime;
      case 4: return &var_Command;
      case 5: return &var_Arg;
      case 6: return &var_StopCommand;
      case 7: return &var_Inv;
      case 8: return &var_EqHolder;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_AContract_Plug::getDO(size_t) {
    return nullptr;
  }

  CEventConnection *FORTE_AContract_Plug::getEOConUnchecked(TPortId) {
    return nullptr;
  }

  CDataConnection **FORTE_AContract_Plug::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Pre;
      case 1: return &conn_Post;
      case 2: return &conn_Timed;
      case 3: return &conn_RunTime;
      case 4: return &conn_Command;
      case 5: return &conn_Arg;
      case 6: return &conn_StopCommand;
      case 7: return &conn_Inv;
      case 8: return &conn_EqHolder;
    }
    return nullptr;
  }

  CDataConnection *FORTE_AContract_Plug::getDOConUnchecked(TPortId) {
    return nullptr;
  }


  FORTE_AContract_Socket::FORTE_AContract_Socket(StringId paInstanceNameId,
                                           CFBContainer &paContainer,
                                           TForteUInt8 paParentAdapterlistID) :
      FORTE_AContract(paContainer, cFBInterfaceSpecSocket, paInstanceNameId, paParentAdapterlistID),
      conn_START(*this, 0),
      conn_SAMPLE(*this, 1),
      conn_Pre(*this, 0, var_Pre),
      conn_Post(*this, 1, var_Post),
      conn_Timed(*this, 2, var_Timed),
      conn_RunTime(*this, 3, var_RunTime),
      conn_Command(*this, 4, var_Command),
      conn_Arg(*this, 5, var_Arg),
      conn_StopCommand(*this, 6, var_StopCommand),
      conn_Inv(*this, 7, var_Inv),
      conn_EqHolder(*this, 8, var_EqHolder) {
  }

  void FORTE_AContract_Socket::readInputData(TEventID) {
    // nothing to do
  }

  void FORTE_AContract_Socket::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventSTARTID: {
        writeData(0, var_Pre, conn_Pre);
        writeData(1, var_Post, conn_Post);
        writeData(2, var_Timed, conn_Timed);
        writeData(3, var_RunTime, conn_RunTime);
        writeData(4, var_Command, conn_Command);
        writeData(5, var_Arg, conn_Arg);
        writeData(6, var_StopCommand, conn_StopCommand);
        break;
      }
      case scmEventSAMPLEID: {
        writeData(1, var_Post, conn_Post);
        writeData(7, var_Inv, conn_Inv);
        writeData(8, var_EqHolder, conn_EqHolder);
        break;
      }
      default:
        break;
    }
  }
  CIEC_ANY *FORTE_AContract_Socket::getDI(size_t) {
    return nullptr;
  }

  CIEC_ANY *FORTE_AContract_Socket::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Pre;
      case 1: return &var_Post;
      case 2: return &var_Timed;
      case 3: return &var_RunTime;
      case 4: return &var_Command;
      case 5: return &var_Arg;
      case 6: return &var_StopCommand;
      case 7: return &var_Inv;
      case 8: return &var_EqHolder;
    }
    return nullptr;
  }

  CEventConnection *FORTE_AContract_Socket::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_START;
      case 1: return &conn_SAMPLE;
    }
    return nullptr;
  }

  CDataConnection **FORTE_AContract_Socket::getDIConUnchecked(TPortId) {
    return nullptr;
  }

  CDataConnection *FORTE_AContract_Socket::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Pre;
      case 1: return &conn_Post;
      case 2: return &conn_Timed;
      case 3: return &conn_RunTime;
      case 4: return &conn_Command;
      case 5: return &conn_Arg;
      case 6: return &conn_StopCommand;
      case 7: return &conn_Inv;
      case 8: return &conn_EqHolder;
    }
    return nullptr;
  }

}