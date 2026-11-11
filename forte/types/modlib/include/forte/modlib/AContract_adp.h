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

#pragma once

#include "forte/adapter.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"

namespace forte::modlib {
  class FORTE_AContract : public forte::CAdapter {
      DECLARE_ADAPTER_TYPE(FORTE_AContract)

    private:
      public:
        static const TEventID scmEventSTARTID = 0;
        static const TEventID scmEventSAMPLEID = 1;

      private:
      public:

      private:

      void setInitialValues() override;
    public:
      CIEC_BOOL var_Pre;
      CIEC_BOOL var_Post;
      CIEC_BOOL var_Timed;
      CIEC_TIME var_RunTime;
      CIEC_USINT var_Command;
      CIEC_LREAL var_Arg;
      CIEC_USINT var_StopCommand;
      CIEC_BOOL var_Inv;
      CIEC_WSTRING var_EqHolder;

      TEventID evt_START() {
        return getParentAdapterListEventID() + scmEventSTARTID;
      }

      TEventID evt_SAMPLE() {
        return getParentAdapterListEventID() + scmEventSAMPLEID;
      }

      ~FORTE_AContract() override = default;

    protected:
      FORTE_AContract(CFBContainer &paContainer,
                    const SFBInterfaceSpec &paInterfaceSpec,
                    const StringId paInstanceNameId,
                    TForteUInt8 paParentAdapterlistID);
  };

  class FORTE_AContract_Plug final : public FORTE_AContract {
    public:
      FORTE_AContract_Plug(StringId paInstanceNameId,
                          CFBContainer &paContainer,
                          TForteUInt8 paParentAdapterlistID);
      ~FORTE_AContract_Plug() override = default;

      CDataConnection *conn_Pre;
      CDataConnection *conn_Post;
      CDataConnection *conn_Timed;
      CDataConnection *conn_RunTime;
      CDataConnection *conn_Command;
      CDataConnection *conn_Arg;
      CDataConnection *conn_StopCommand;
      CDataConnection *conn_Inv;
      CDataConnection *conn_EqHolder;

    private:
      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;
  };

  class FORTE_AContract_Socket final : public FORTE_AContract {
    public:
      FORTE_AContract_Socket(StringId paInstanceNameId,
                          CFBContainer &paContainer,
                          TForteUInt8 paParentAdapterlistID);
      ~FORTE_AContract_Socket() override = default;

      CEventConnection conn_START;
      CEventConnection conn_SAMPLE;

      COutDataConnection<CIEC_BOOL> conn_Pre;
      COutDataConnection<CIEC_BOOL> conn_Post;
      COutDataConnection<CIEC_BOOL> conn_Timed;
      COutDataConnection<CIEC_TIME> conn_RunTime;
      COutDataConnection<CIEC_USINT> conn_Command;
      COutDataConnection<CIEC_LREAL> conn_Arg;
      COutDataConnection<CIEC_USINT> conn_StopCommand;
      COutDataConnection<CIEC_BOOL> conn_Inv;
      COutDataConnection<CIEC_WSTRING> conn_EqHolder;

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
