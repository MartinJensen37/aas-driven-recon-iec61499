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

#pragma once

#include "forte/adapter.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"

namespace forte::modlib {
  class FORTE_AEquipment : public forte::CAdapter {
      DECLARE_ADAPTER_TYPE(FORTE_AEquipment)

    private:
      public:
        static const TEventID scmEventSENDID = 0;

      private:
      public:
        static const TEventID scmEventPLAYEDID = 0;

      private:

      void setInitialValues() override;
    public:
      CIEC_WSTRING var_Holder;
      CIEC_USINT var_Command;
      CIEC_LREAL var_Arg;
      CIEC_BOOL var_Release;

      TEventID evt_PLAYED() {
        return getParentAdapterListEventID() + scmEventPLAYEDID;
      }

      TEventID evt_SEND() {
        return getParentAdapterListEventID() + scmEventSENDID;
      }

      ~FORTE_AEquipment() override = default;

    protected:
      FORTE_AEquipment(CFBContainer &paContainer,
                    const SFBInterfaceSpec &paInterfaceSpec,
                    const StringId paInstanceNameId,
                    TForteUInt8 paParentAdapterlistID);
  };

  class FORTE_AEquipment_Plug final : public FORTE_AEquipment {
    public:
      FORTE_AEquipment_Plug(StringId paInstanceNameId,
                          CFBContainer &paContainer,
                          TForteUInt8 paParentAdapterlistID);
      ~FORTE_AEquipment_Plug() override = default;

      CEventConnection conn_PLAYED;

      CDataConnection *conn_Holder;
      CDataConnection *conn_Command;
      CDataConnection *conn_Arg;
      CDataConnection *conn_Release;

    private:
      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;
  };

  class FORTE_AEquipment_Socket final : public FORTE_AEquipment {
    public:
      FORTE_AEquipment_Socket(StringId paInstanceNameId,
                          CFBContainer &paContainer,
                          TForteUInt8 paParentAdapterlistID);
      ~FORTE_AEquipment_Socket() override = default;

      CEventConnection conn_SEND;

      COutDataConnection<CIEC_WSTRING> conn_Holder;
      COutDataConnection<CIEC_USINT> conn_Command;
      COutDataConnection<CIEC_LREAL> conn_Arg;
      COutDataConnection<CIEC_BOOL> conn_Release;

    private:
      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;
  };
}
