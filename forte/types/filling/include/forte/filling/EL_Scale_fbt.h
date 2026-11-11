/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: EL_Scale
 *** Description: The logic of an equipment block: one holder at a time, outputs switched off before new ones go on, all off on release or abort, inputs reported when they change. Technical: Scale: output values from its holder -> outputs (break before make); one holder at a time; all off on release or when the module aborts; inputs -> state channel when they change
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/basicfb.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"

namespace forte::filling {
  class FORTE_EL_Scale final : public CBasicFB {
      DECLARE_FIRMWARE_FB(FORTE_EL_Scale)

    private:
      static const TEventID scmEventINITOID = 0;
      static const TEventID scmEventDRIVEID = 1;
      static const TEventID scmEventSTATEID = 2;
      static const TEventID scmEventINITID = 0;
      static const TEventID scmEventCMDID = 1;
      static const TEventID scmEventRELEASEID = 2;
      static const TEventID scmEventSAMPLEID = 3;
      static const TEventID scmEventREFRESHID = 4;
      static const TEventID scmEventDRIVENID = 5;
      static const TEventID scmEventMOD_CHGID = 6;

      CIEC_BOOL var_Publish;
      CIEC_USINT var_Beat;
      CIEC_WSTRING var_LastHolder;
      CIEC_BOOL var_Pending;
      CIEC_BOOL var_OffPending;
      CIEC_LREAL var_L_Weight;

      CIEC_ANY *getVarInternal(size_t) override;

      void alg_Alg_Init(void);
      void alg_Alg_Sample(void);
      void alg_Alg_Publish(void);
      void alg_Alg_Cmd(void);
      void alg_Alg_Off(void);
      void alg_Alg_QueueB(void);
      void alg_Alg_OffB(void);
      void alg_Alg_QueueM(void);
      void alg_Alg_OffM(void);
      void alg_Alg_CmdPend(void);
      void alg_Alg_Report(void);

      static const TForteInt16 scmStateSTART = 0;
      static const TForteInt16 scmStateInit = 1;
      static const TForteInt16 scmStateSample = 2;
      static const TForteInt16 scmStatePublish = 3;
      static const TForteInt16 scmStateRefresh = 4;
      static const TForteInt16 scmStateCmd = 5;
      static const TForteInt16 scmStateOff = 6;
      static const TForteInt16 scmStateBreak = 7;
      static const TForteInt16 scmStateMake = 8;
      static const TForteInt16 scmStateBreakW = 9;
      static const TForteInt16 scmStateMakeW = 10;
      static const TForteInt16 scmStateQueueB = 11;
      static const TForteInt16 scmStateOffB = 12;
      static const TForteInt16 scmStateQueueM = 13;
      static const TForteInt16 scmStateOffM = 14;
      static const TForteInt16 scmStateCmdPend = 15;
      static const TForteInt16 scmStateSettled = 16;
      static const TForteInt16 scmStateReport = 17;

      void enterStateSTART(CEventChainExecutionThread *const paECET);
      void enterStateInit(CEventChainExecutionThread *const paECET);
      void enterStateSample(CEventChainExecutionThread *const paECET);
      void enterStatePublish(CEventChainExecutionThread *const paECET);
      void enterStateRefresh(CEventChainExecutionThread *const paECET);
      void enterStateCmd(CEventChainExecutionThread *const paECET);
      void enterStateOff(CEventChainExecutionThread *const paECET);
      void enterStateBreak(CEventChainExecutionThread *const paECET);
      void enterStateMake(CEventChainExecutionThread *const paECET);
      void enterStateBreakW(CEventChainExecutionThread *const paECET);
      void enterStateMakeW(CEventChainExecutionThread *const paECET);
      void enterStateQueueB(CEventChainExecutionThread *const paECET);
      void enterStateOffB(CEventChainExecutionThread *const paECET);
      void enterStateQueueM(CEventChainExecutionThread *const paECET);
      void enterStateOffM(CEventChainExecutionThread *const paECET);
      void enterStateCmdPend(CEventChainExecutionThread *const paECET);
      void enterStateSettled(CEventChainExecutionThread *const paECET);
      void enterStateReport(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_EL_Scale(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_WSTRING var_Module;
      CIEC_WSTRING var_Name;
      CIEC_WSTRING var_UaRoot;
      CIEC_WSTRING var_C_Holder;
      CIEC_BOOL var_C_Release;
      CIEC_WSTRING var_R_Holder;
      CIEC_LREAL var_I_Weight;
      CIEC_USINT var_ModuleState;

      CIEC_WSTRING var_IdCmd;
      CIEC_WSTRING var_IdRelease;
      CIEC_WSTRING var_IdState;
      CIEC_WSTRING var_IdPub;
      CIEC_LREAL var_Weight;
      CIEC_WSTRING var_Holder;

      CEventConnection conn_INITO;
      CEventConnection conn_DRIVE;
      CEventConnection conn_STATE;

      CDataConnection *conn_Module;
      CDataConnection *conn_Name;
      CDataConnection *conn_UaRoot;
      CDataConnection *conn_C_Holder;
      CDataConnection *conn_C_Release;
      CDataConnection *conn_R_Holder;
      CDataConnection *conn_I_Weight;
      CDataConnection *conn_ModuleState;

      COutDataConnection<CIEC_WSTRING> conn_IdCmd;
      COutDataConnection<CIEC_WSTRING> conn_IdRelease;
      COutDataConnection<CIEC_WSTRING> conn_IdState;
      COutDataConnection<CIEC_WSTRING> conn_IdPub;
      COutDataConnection<CIEC_LREAL> conn_Weight;
      COutDataConnection<CIEC_WSTRING> conn_Holder;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_INIT(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paName, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paC_Holder, const CIEC_BOOL &paC_Release, const CIEC_WSTRING &paR_Holder, const CIEC_LREAL &paI_Weight, const CIEC_USINT &paModuleState, COutputParameter<CIEC_WSTRING> paIdCmd, COutputParameter<CIEC_WSTRING> paIdRelease, COutputParameter<CIEC_WSTRING> paIdState, COutputParameter<CIEC_WSTRING> paIdPub, COutputParameter<CIEC_LREAL> paWeight, COutputParameter<CIEC_WSTRING> paHolder) {
        COutputGuard guard_IdCmd(paIdCmd);
        COutputGuard guard_IdRelease(paIdRelease);
        COutputGuard guard_IdState(paIdState);
        COutputGuard guard_IdPub(paIdPub);
        COutputGuard guard_Weight(paWeight);
        COutputGuard guard_Holder(paHolder);
        var_Module = paModule;
        var_Name = paName;
        var_UaRoot = paUaRoot;
        var_C_Holder = paC_Holder;
        var_C_Release = paC_Release;
        var_R_Holder = paR_Holder;
        var_I_Weight = paI_Weight;
        var_ModuleState = paModuleState;
        executeEvent(scmEventINITID, nullptr);
        *paIdCmd = var_IdCmd;
        *paIdRelease = var_IdRelease;
        *paIdState = var_IdState;
        *paIdPub = var_IdPub;
        *paWeight = var_Weight;
        *paHolder = var_Holder;
      }

      void evt_CMD(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paName, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paC_Holder, const CIEC_BOOL &paC_Release, const CIEC_WSTRING &paR_Holder, const CIEC_LREAL &paI_Weight, const CIEC_USINT &paModuleState, COutputParameter<CIEC_WSTRING> paIdCmd, COutputParameter<CIEC_WSTRING> paIdRelease, COutputParameter<CIEC_WSTRING> paIdState, COutputParameter<CIEC_WSTRING> paIdPub, COutputParameter<CIEC_LREAL> paWeight, COutputParameter<CIEC_WSTRING> paHolder) {
        COutputGuard guard_IdCmd(paIdCmd);
        COutputGuard guard_IdRelease(paIdRelease);
        COutputGuard guard_IdState(paIdState);
        COutputGuard guard_IdPub(paIdPub);
        COutputGuard guard_Weight(paWeight);
        COutputGuard guard_Holder(paHolder);
        var_Module = paModule;
        var_Name = paName;
        var_UaRoot = paUaRoot;
        var_C_Holder = paC_Holder;
        var_C_Release = paC_Release;
        var_R_Holder = paR_Holder;
        var_I_Weight = paI_Weight;
        var_ModuleState = paModuleState;
        executeEvent(scmEventCMDID, nullptr);
        *paIdCmd = var_IdCmd;
        *paIdRelease = var_IdRelease;
        *paIdState = var_IdState;
        *paIdPub = var_IdPub;
        *paWeight = var_Weight;
        *paHolder = var_Holder;
      }

      void evt_RELEASE(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paName, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paC_Holder, const CIEC_BOOL &paC_Release, const CIEC_WSTRING &paR_Holder, const CIEC_LREAL &paI_Weight, const CIEC_USINT &paModuleState, COutputParameter<CIEC_WSTRING> paIdCmd, COutputParameter<CIEC_WSTRING> paIdRelease, COutputParameter<CIEC_WSTRING> paIdState, COutputParameter<CIEC_WSTRING> paIdPub, COutputParameter<CIEC_LREAL> paWeight, COutputParameter<CIEC_WSTRING> paHolder) {
        COutputGuard guard_IdCmd(paIdCmd);
        COutputGuard guard_IdRelease(paIdRelease);
        COutputGuard guard_IdState(paIdState);
        COutputGuard guard_IdPub(paIdPub);
        COutputGuard guard_Weight(paWeight);
        COutputGuard guard_Holder(paHolder);
        var_Module = paModule;
        var_Name = paName;
        var_UaRoot = paUaRoot;
        var_C_Holder = paC_Holder;
        var_C_Release = paC_Release;
        var_R_Holder = paR_Holder;
        var_I_Weight = paI_Weight;
        var_ModuleState = paModuleState;
        executeEvent(scmEventRELEASEID, nullptr);
        *paIdCmd = var_IdCmd;
        *paIdRelease = var_IdRelease;
        *paIdState = var_IdState;
        *paIdPub = var_IdPub;
        *paWeight = var_Weight;
        *paHolder = var_Holder;
      }

      void evt_SAMPLE(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paName, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paC_Holder, const CIEC_BOOL &paC_Release, const CIEC_WSTRING &paR_Holder, const CIEC_LREAL &paI_Weight, const CIEC_USINT &paModuleState, COutputParameter<CIEC_WSTRING> paIdCmd, COutputParameter<CIEC_WSTRING> paIdRelease, COutputParameter<CIEC_WSTRING> paIdState, COutputParameter<CIEC_WSTRING> paIdPub, COutputParameter<CIEC_LREAL> paWeight, COutputParameter<CIEC_WSTRING> paHolder) {
        COutputGuard guard_IdCmd(paIdCmd);
        COutputGuard guard_IdRelease(paIdRelease);
        COutputGuard guard_IdState(paIdState);
        COutputGuard guard_IdPub(paIdPub);
        COutputGuard guard_Weight(paWeight);
        COutputGuard guard_Holder(paHolder);
        var_Module = paModule;
        var_Name = paName;
        var_UaRoot = paUaRoot;
        var_C_Holder = paC_Holder;
        var_C_Release = paC_Release;
        var_R_Holder = paR_Holder;
        var_I_Weight = paI_Weight;
        var_ModuleState = paModuleState;
        executeEvent(scmEventSAMPLEID, nullptr);
        *paIdCmd = var_IdCmd;
        *paIdRelease = var_IdRelease;
        *paIdState = var_IdState;
        *paIdPub = var_IdPub;
        *paWeight = var_Weight;
        *paHolder = var_Holder;
      }

      void evt_REFRESH(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paName, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paC_Holder, const CIEC_BOOL &paC_Release, const CIEC_WSTRING &paR_Holder, const CIEC_LREAL &paI_Weight, const CIEC_USINT &paModuleState, COutputParameter<CIEC_WSTRING> paIdCmd, COutputParameter<CIEC_WSTRING> paIdRelease, COutputParameter<CIEC_WSTRING> paIdState, COutputParameter<CIEC_WSTRING> paIdPub, COutputParameter<CIEC_LREAL> paWeight, COutputParameter<CIEC_WSTRING> paHolder) {
        COutputGuard guard_IdCmd(paIdCmd);
        COutputGuard guard_IdRelease(paIdRelease);
        COutputGuard guard_IdState(paIdState);
        COutputGuard guard_IdPub(paIdPub);
        COutputGuard guard_Weight(paWeight);
        COutputGuard guard_Holder(paHolder);
        var_Module = paModule;
        var_Name = paName;
        var_UaRoot = paUaRoot;
        var_C_Holder = paC_Holder;
        var_C_Release = paC_Release;
        var_R_Holder = paR_Holder;
        var_I_Weight = paI_Weight;
        var_ModuleState = paModuleState;
        executeEvent(scmEventREFRESHID, nullptr);
        *paIdCmd = var_IdCmd;
        *paIdRelease = var_IdRelease;
        *paIdState = var_IdState;
        *paIdPub = var_IdPub;
        *paWeight = var_Weight;
        *paHolder = var_Holder;
      }

      void evt_DRIVEN(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paName, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paC_Holder, const CIEC_BOOL &paC_Release, const CIEC_WSTRING &paR_Holder, const CIEC_LREAL &paI_Weight, const CIEC_USINT &paModuleState, COutputParameter<CIEC_WSTRING> paIdCmd, COutputParameter<CIEC_WSTRING> paIdRelease, COutputParameter<CIEC_WSTRING> paIdState, COutputParameter<CIEC_WSTRING> paIdPub, COutputParameter<CIEC_LREAL> paWeight, COutputParameter<CIEC_WSTRING> paHolder) {
        COutputGuard guard_IdCmd(paIdCmd);
        COutputGuard guard_IdRelease(paIdRelease);
        COutputGuard guard_IdState(paIdState);
        COutputGuard guard_IdPub(paIdPub);
        COutputGuard guard_Weight(paWeight);
        COutputGuard guard_Holder(paHolder);
        var_Module = paModule;
        var_Name = paName;
        var_UaRoot = paUaRoot;
        var_C_Holder = paC_Holder;
        var_C_Release = paC_Release;
        var_R_Holder = paR_Holder;
        var_I_Weight = paI_Weight;
        var_ModuleState = paModuleState;
        executeEvent(scmEventDRIVENID, nullptr);
        *paIdCmd = var_IdCmd;
        *paIdRelease = var_IdRelease;
        *paIdState = var_IdState;
        *paIdPub = var_IdPub;
        *paWeight = var_Weight;
        *paHolder = var_Holder;
      }

      void evt_MOD_CHG(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paName, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paC_Holder, const CIEC_BOOL &paC_Release, const CIEC_WSTRING &paR_Holder, const CIEC_LREAL &paI_Weight, const CIEC_USINT &paModuleState, COutputParameter<CIEC_WSTRING> paIdCmd, COutputParameter<CIEC_WSTRING> paIdRelease, COutputParameter<CIEC_WSTRING> paIdState, COutputParameter<CIEC_WSTRING> paIdPub, COutputParameter<CIEC_LREAL> paWeight, COutputParameter<CIEC_WSTRING> paHolder) {
        COutputGuard guard_IdCmd(paIdCmd);
        COutputGuard guard_IdRelease(paIdRelease);
        COutputGuard guard_IdState(paIdState);
        COutputGuard guard_IdPub(paIdPub);
        COutputGuard guard_Weight(paWeight);
        COutputGuard guard_Holder(paHolder);
        var_Module = paModule;
        var_Name = paName;
        var_UaRoot = paUaRoot;
        var_C_Holder = paC_Holder;
        var_C_Release = paC_Release;
        var_R_Holder = paR_Holder;
        var_I_Weight = paI_Weight;
        var_ModuleState = paModuleState;
        executeEvent(scmEventMOD_CHGID, nullptr);
        *paIdCmd = var_IdCmd;
        *paIdRelease = var_IdRelease;
        *paIdState = var_IdState;
        *paIdPub = var_IdPub;
        *paWeight = var_Weight;
        *paHolder = var_Holder;
      }
  };
}

