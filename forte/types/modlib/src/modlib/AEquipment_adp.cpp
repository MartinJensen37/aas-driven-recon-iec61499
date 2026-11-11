/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: AEquipment
 *** Description: An adapter: one connection from a skill's run (the plug) to its equipment's port (EP_, the socket) that carries a command out and the word that it was played back. Technical: What a skill's run (SKILL_Run, the plug) sends its equipment's port (EP_, the socket): SEND a command; PLAYED comes back when all its phases are out
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#include "forte/modlib/AEquipment_adp.h"

#include "forte/forte_st_util.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::modlib {
  namespace {
    constexpr std::string_view TypeHash ="v2:SHA3-512:N4lP7iWATKeaPcFsvC8tQzOQkjXfkxDj_HoujlGhkQKquqHq3ILMVuDJfHbGV_zvrOhid8s6wa4h8z7oXBFAYw=="sv;

    const auto cEventInputNames = std::array{"PLAYED"_STRID};
    const auto cEventOutputNames = std::array{"SEND"_STRID};
    const auto cDataOutputNames = std::array{"Holder"_STRID, "Command"_STRID, "Arg"_STRID, "Release"_STRID};

    const SFBInterfaceSpec cFBInterfaceSpecSocket = {
        .mEINames = cEventInputNames,
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
        .mEONames = cEventInputNames,
        .mEOTypeNames = {},
        .mDINames = cDataOutputNames,
        .mDONames = {},
        .mDIONames = {},
        .mSocketNames = {},
        .mPlugNames = {},
    };
  }

  DEFINE_ADAPTER_TYPE(FORTE_AEquipment, "modlib::AEquipment"_STRID, TypeHash)


  FORTE_AEquipment::FORTE_AEquipment(CFBContainer &paContainer,
                               const SFBInterfaceSpec &paInterfaceSpec,
                               const StringId paInstanceNameId,
                               TForteUInt8 paParentAdapterlistID) :
      CAdapter(paContainer, paInterfaceSpec, paInstanceNameId, paParentAdapterlistID),
      var_Holder(u""_WSTRING),
      var_Command(0_USINT),
      var_Arg(0_LREAL),
      var_Release(0_BOOL) {
  }

  void FORTE_AEquipment::setInitialValues() {
    forte::CAdapter::setInitialValues();
    var_Holder = u""_WSTRING;
    var_Command = 0_USINT;
    var_Arg = 0_LREAL;
    var_Release = 0_BOOL;
  }


  FORTE_AEquipment_Plug::FORTE_AEquipment_Plug(StringId paInstanceNameId,
                                           CFBContainer &paContainer,
                                           TForteUInt8 paParentAdapterlistID) :
      FORTE_AEquipment(paContainer, cFBInterfaceSpecPlug, paInstanceNameId, paParentAdapterlistID),
      conn_PLAYED(*this, 0),
      conn_Holder(nullptr),
      conn_Command(nullptr),
      conn_Arg(nullptr),
      conn_Release(nullptr) {
  }

  void FORTE_AEquipment_Plug::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventSENDID: {
        readData(0, var_Holder, conn_Holder);
        readData(1, var_Command, conn_Command);
        readData(2, var_Arg, conn_Arg);
        readData(3, var_Release, conn_Release);
        if(auto peer = static_cast<FORTE_AEquipment_Socket *>(getPeer()); peer) {
          peer->var_Holder = var_Holder;
          peer->var_Command = var_Command;
          peer->var_Arg = var_Arg;
          peer->var_Release = var_Release;
        }
        break;
      }
      default:
        break;
    }
  }

  void FORTE_AEquipment_Plug::writeOutputData(TEventID) {
    // nothing to do
  }
  CIEC_ANY *FORTE_AEquipment_Plug::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Holder;
      case 1: return &var_Command;
      case 2: return &var_Arg;
      case 3: return &var_Release;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_AEquipment_Plug::getDO(size_t) {
    return nullptr;
  }

  CEventConnection *FORTE_AEquipment_Plug::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_PLAYED;
    }
    return nullptr;
  }

  CDataConnection **FORTE_AEquipment_Plug::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Holder;
      case 1: return &conn_Command;
      case 2: return &conn_Arg;
      case 3: return &conn_Release;
    }
    return nullptr;
  }

  CDataConnection *FORTE_AEquipment_Plug::getDOConUnchecked(TPortId) {
    return nullptr;
  }


  FORTE_AEquipment_Socket::FORTE_AEquipment_Socket(StringId paInstanceNameId,
                                           CFBContainer &paContainer,
                                           TForteUInt8 paParentAdapterlistID) :
      FORTE_AEquipment(paContainer, cFBInterfaceSpecSocket, paInstanceNameId, paParentAdapterlistID),
      conn_SEND(*this, 0),
      conn_Holder(*this, 0, var_Holder),
      conn_Command(*this, 1, var_Command),
      conn_Arg(*this, 2, var_Arg),
      conn_Release(*this, 3, var_Release) {
  }

  void FORTE_AEquipment_Socket::readInputData(TEventID) {
    // nothing to do
  }

  void FORTE_AEquipment_Socket::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventSENDID: {
        writeData(0, var_Holder, conn_Holder);
        writeData(1, var_Command, conn_Command);
        writeData(2, var_Arg, conn_Arg);
        writeData(3, var_Release, conn_Release);
        break;
      }
      default:
        break;
    }
  }
  CIEC_ANY *FORTE_AEquipment_Socket::getDI(size_t) {
    return nullptr;
  }

  CIEC_ANY *FORTE_AEquipment_Socket::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Holder;
      case 1: return &var_Command;
      case 2: return &var_Arg;
      case 3: return &var_Release;
    }
    return nullptr;
  }

  CEventConnection *FORTE_AEquipment_Socket::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_SEND;
    }
    return nullptr;
  }

  CDataConnection **FORTE_AEquipment_Socket::getDIConUnchecked(TPortId) {
    return nullptr;
  }

  CDataConnection *FORTE_AEquipment_Socket::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Holder;
      case 1: return &conn_Command;
      case 2: return &conn_Arg;
      case 3: return &conn_Release;
    }
    return nullptr;
  }

}