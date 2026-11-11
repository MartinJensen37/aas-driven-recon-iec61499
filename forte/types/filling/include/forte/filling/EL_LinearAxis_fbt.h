/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!
 ***
 *** Name: EL_LinearAxis
 *** Description: The logic of an equipment block: one holder at a time, outputs switched off before new ones go on, all off on release or abort, inputs reported when they change. Technical: LinearAxis: output values from its holder -> outputs (break before make); one holder at a time; all off on release or when the module aborts; inputs -> state channel when they change
 *** Version:
 ***     0.1: 2026-09-28/Project contributors - AAU Smart Production Lab -
 *************************************************************************/

#pragma once

#include "forte/basicfb.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_lreal.h"
#include "forte/datatypes/forte_time.h"
#include "forte/datatypes/forte_usint.h"
#include "forte/datatypes/forte_wstring.h"
#include "forte/forte_st_util.h"

namespace forte::filling {
  class FORTE_EL_LinearAxis final : public CBasicFB {
      DECLARE_FIRMWARE_FB(FORTE_EL_LinearAxis)

    private:
      static const TEventID scmEventINITOID = 0;
      static const TEventID scmEventDRIVEID = 1;
      static const TEventID scmEventSTATEID = 2;
      static const TEventID scmEventMOVE_STARTID = 3;
      static const TEventID scmEventMOVE_STOPID = 4;
      static const TEventID scmEventINITID = 0;
      static const TEventID scmEventCMDID = 1;
      static const TEventID scmEventRELEASEID = 2;
      static const TEventID scmEventSAMPLEID = 3;
      static const TEventID scmEventREFRESHID = 4;
      static const TEventID scmEventDRIVENID = 5;
      static const TEventID scmEventMOD_CHGID = 6;
      static const TEventID scmEventMOVE_TID = 7;

      CIEC_BOOL var_Publish;
      CIEC_USINT var_Beat;
      CIEC_WSTRING var_LastHolder;
      CIEC_BOOL var_Pending;
      CIEC_BOOL var_OffPending;
      CIEC_BOOL var_L_AtHome;
      CIEC_BOOL var_L_Homed;
      CIEC_BOOL var_L_Moving;
      CIEC_BOOL var_N_Enable;
      CIEC_BOOL var_N_Down;
      CIEC_LREAL var_N_Step;
      CIEC_BOOL var_NE_Step;
      CIEC_BOOL var_N_Move;
      CIEC_LREAL var_N_Goal;
      CIEC_LREAL var_MoveGoal;
      CIEC_LREAL var_MoveFrom;
      CIEC_LREAL var_MoveDir;
      CIEC_TIME var_MoveSince;
      CIEC_BOOL var_MoveStart;
      CIEC_BOOL var_Uncounted;

      CIEC_ANY *getVarInternal(size_t) override;

      void alg_Alg_Init(void);
      void alg_Alg_Sample(void);
      void alg_Alg_Publish(void);
      void alg_Alg_Cmd(void);
      void alg_Alg_Off(void);
      void alg_Alg_Break(void);
      void alg_Alg_Make(void);
      void alg_Alg_QueueB(void);
      void alg_Alg_OffB(void);
      void alg_Alg_QueueM(void);
      void alg_Alg_OffM(void);
      void alg_Alg_CmdPend(void);
      void alg_Alg_MoveGo(void);
      void alg_Alg_MoveEnd(void);
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
      static const TForteInt16 scmStateMoveGo = 17;
      static const TForteInt16 scmStateMoveEnd = 18;
      static const TForteInt16 scmStateReport = 19;

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
      void enterStateMoveGo(CEventChainExecutionThread *const paECET);
      void enterStateMoveEnd(CEventChainExecutionThread *const paECET);
      void enterStateReport(CEventChainExecutionThread *const paECET);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_EL_LinearAxis(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_WSTRING var_Module;
      CIEC_WSTRING var_Name;
      CIEC_WSTRING var_UaRoot;
      CIEC_WSTRING var_C_Holder;
      CIEC_BOOL var_C_Release;
      CIEC_BOOL var_C_Enable;
      CIEC_BOOL var_C_Down;
      CIEC_LREAL var_C_Step;
      CIEC_BOOL var_CE_Step;
      CIEC_BOOL var_C_Move;
      CIEC_LREAL var_C_Goal;
      CIEC_WSTRING var_R_Holder;
      CIEC_BOOL var_I_AtHome;
      CIEC_USINT var_ModuleState;

      CIEC_WSTRING var_IdCmd;
      CIEC_WSTRING var_IdRelease;
      CIEC_WSTRING var_IdState;
      CIEC_WSTRING var_IdPub;
      CIEC_BOOL var_O_Enable;
      CIEC_BOOL var_O_Down;
      CIEC_LREAL var_O_Step;
      CIEC_BOOL var_E_Step;
      CIEC_BOOL var_AtHome;
      CIEC_LREAL var_ActualPosition;
      CIEC_BOOL var_Homed;
      CIEC_BOOL var_Moving;
      CIEC_WSTRING var_Holder;
      CIEC_TIME var_MoveDT;

      CEventConnection conn_INITO;
      CEventConnection conn_DRIVE;
      CEventConnection conn_STATE;
      CEventConnection conn_MOVE_START;
      CEventConnection conn_MOVE_STOP;

      CDataConnection *conn_Module;
      CDataConnection *conn_Name;
      CDataConnection *conn_UaRoot;
      CDataConnection *conn_C_Holder;
      CDataConnection *conn_C_Release;
      CDataConnection *conn_C_Enable;
      CDataConnection *conn_C_Down;
      CDataConnection *conn_C_Step;
      CDataConnection *conn_CE_Step;
      CDataConnection *conn_C_Move;
      CDataConnection *conn_C_Goal;
      CDataConnection *conn_R_Holder;
      CDataConnection *conn_I_AtHome;
      CDataConnection *conn_ModuleState;

      COutDataConnection<CIEC_WSTRING> conn_IdCmd;
      COutDataConnection<CIEC_WSTRING> conn_IdRelease;
      COutDataConnection<CIEC_WSTRING> conn_IdState;
      COutDataConnection<CIEC_WSTRING> conn_IdPub;
      COutDataConnection<CIEC_BOOL> conn_O_Enable;
      COutDataConnection<CIEC_BOOL> conn_O_Down;
      COutDataConnection<CIEC_LREAL> conn_O_Step;
      COutDataConnection<CIEC_BOOL> conn_E_Step;
      COutDataConnection<CIEC_BOOL> conn_AtHome;
      COutDataConnection<CIEC_LREAL> conn_ActualPosition;
      COutDataConnection<CIEC_BOOL> conn_Homed;
      COutDataConnection<CIEC_BOOL> conn_Moving;
      COutDataConnection<CIEC_WSTRING> conn_Holder;
      COutDataConnection<CIEC_TIME> conn_MoveDT;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_INIT(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paName, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paC_Holder, const CIEC_BOOL &paC_Release, const CIEC_BOOL &paC_Enable, const CIEC_BOOL &paC_Down, const CIEC_LREAL &paC_Step, const CIEC_BOOL &paCE_Step, const CIEC_BOOL &paC_Move, const CIEC_LREAL &paC_Goal, const CIEC_WSTRING &paR_Holder, const CIEC_BOOL &paI_AtHome, const CIEC_USINT &paModuleState, COutputParameter<CIEC_WSTRING> paIdCmd, COutputParameter<CIEC_WSTRING> paIdRelease, COutputParameter<CIEC_WSTRING> paIdState, COutputParameter<CIEC_WSTRING> paIdPub, CAnyBitOutputParameter<CIEC_BOOL> paO_Enable, CAnyBitOutputParameter<CIEC_BOOL> paO_Down, COutputParameter<CIEC_LREAL> paO_Step, CAnyBitOutputParameter<CIEC_BOOL> paE_Step, CAnyBitOutputParameter<CIEC_BOOL> paAtHome, COutputParameter<CIEC_LREAL> paActualPosition, CAnyBitOutputParameter<CIEC_BOOL> paHomed, CAnyBitOutputParameter<CIEC_BOOL> paMoving, COutputParameter<CIEC_WSTRING> paHolder, COutputParameter<CIEC_TIME> paMoveDT) {
        COutputGuard guard_IdCmd(paIdCmd);
        COutputGuard guard_IdRelease(paIdRelease);
        COutputGuard guard_IdState(paIdState);
        COutputGuard guard_IdPub(paIdPub);
        COutputGuard guard_O_Enable(paO_Enable);
        COutputGuard guard_O_Down(paO_Down);
        COutputGuard guard_O_Step(paO_Step);
        COutputGuard guard_E_Step(paE_Step);
        COutputGuard guard_AtHome(paAtHome);
        COutputGuard guard_ActualPosition(paActualPosition);
        COutputGuard guard_Homed(paHomed);
        COutputGuard guard_Moving(paMoving);
        COutputGuard guard_Holder(paHolder);
        COutputGuard guard_MoveDT(paMoveDT);
        var_Module = paModule;
        var_Name = paName;
        var_UaRoot = paUaRoot;
        var_C_Holder = paC_Holder;
        var_C_Release = paC_Release;
        var_C_Enable = paC_Enable;
        var_C_Down = paC_Down;
        var_C_Step = paC_Step;
        var_CE_Step = paCE_Step;
        var_C_Move = paC_Move;
        var_C_Goal = paC_Goal;
        var_R_Holder = paR_Holder;
        var_I_AtHome = paI_AtHome;
        var_ModuleState = paModuleState;
        executeEvent(scmEventINITID, nullptr);
        *paIdCmd = var_IdCmd;
        *paIdRelease = var_IdRelease;
        *paIdState = var_IdState;
        *paIdPub = var_IdPub;
        *paO_Enable = var_O_Enable;
        *paO_Down = var_O_Down;
        *paO_Step = var_O_Step;
        *paE_Step = var_E_Step;
        *paAtHome = var_AtHome;
        *paActualPosition = var_ActualPosition;
        *paHomed = var_Homed;
        *paMoving = var_Moving;
        *paHolder = var_Holder;
        *paMoveDT = var_MoveDT;
      }

      void evt_CMD(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paName, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paC_Holder, const CIEC_BOOL &paC_Release, const CIEC_BOOL &paC_Enable, const CIEC_BOOL &paC_Down, const CIEC_LREAL &paC_Step, const CIEC_BOOL &paCE_Step, const CIEC_BOOL &paC_Move, const CIEC_LREAL &paC_Goal, const CIEC_WSTRING &paR_Holder, const CIEC_BOOL &paI_AtHome, const CIEC_USINT &paModuleState, COutputParameter<CIEC_WSTRING> paIdCmd, COutputParameter<CIEC_WSTRING> paIdRelease, COutputParameter<CIEC_WSTRING> paIdState, COutputParameter<CIEC_WSTRING> paIdPub, CAnyBitOutputParameter<CIEC_BOOL> paO_Enable, CAnyBitOutputParameter<CIEC_BOOL> paO_Down, COutputParameter<CIEC_LREAL> paO_Step, CAnyBitOutputParameter<CIEC_BOOL> paE_Step, CAnyBitOutputParameter<CIEC_BOOL> paAtHome, COutputParameter<CIEC_LREAL> paActualPosition, CAnyBitOutputParameter<CIEC_BOOL> paHomed, CAnyBitOutputParameter<CIEC_BOOL> paMoving, COutputParameter<CIEC_WSTRING> paHolder, COutputParameter<CIEC_TIME> paMoveDT) {
        COutputGuard guard_IdCmd(paIdCmd);
        COutputGuard guard_IdRelease(paIdRelease);
        COutputGuard guard_IdState(paIdState);
        COutputGuard guard_IdPub(paIdPub);
        COutputGuard guard_O_Enable(paO_Enable);
        COutputGuard guard_O_Down(paO_Down);
        COutputGuard guard_O_Step(paO_Step);
        COutputGuard guard_E_Step(paE_Step);
        COutputGuard guard_AtHome(paAtHome);
        COutputGuard guard_ActualPosition(paActualPosition);
        COutputGuard guard_Homed(paHomed);
        COutputGuard guard_Moving(paMoving);
        COutputGuard guard_Holder(paHolder);
        COutputGuard guard_MoveDT(paMoveDT);
        var_Module = paModule;
        var_Name = paName;
        var_UaRoot = paUaRoot;
        var_C_Holder = paC_Holder;
        var_C_Release = paC_Release;
        var_C_Enable = paC_Enable;
        var_C_Down = paC_Down;
        var_C_Step = paC_Step;
        var_CE_Step = paCE_Step;
        var_C_Move = paC_Move;
        var_C_Goal = paC_Goal;
        var_R_Holder = paR_Holder;
        var_I_AtHome = paI_AtHome;
        var_ModuleState = paModuleState;
        executeEvent(scmEventCMDID, nullptr);
        *paIdCmd = var_IdCmd;
        *paIdRelease = var_IdRelease;
        *paIdState = var_IdState;
        *paIdPub = var_IdPub;
        *paO_Enable = var_O_Enable;
        *paO_Down = var_O_Down;
        *paO_Step = var_O_Step;
        *paE_Step = var_E_Step;
        *paAtHome = var_AtHome;
        *paActualPosition = var_ActualPosition;
        *paHomed = var_Homed;
        *paMoving = var_Moving;
        *paHolder = var_Holder;
        *paMoveDT = var_MoveDT;
      }

      void evt_RELEASE(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paName, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paC_Holder, const CIEC_BOOL &paC_Release, const CIEC_BOOL &paC_Enable, const CIEC_BOOL &paC_Down, const CIEC_LREAL &paC_Step, const CIEC_BOOL &paCE_Step, const CIEC_BOOL &paC_Move, const CIEC_LREAL &paC_Goal, const CIEC_WSTRING &paR_Holder, const CIEC_BOOL &paI_AtHome, const CIEC_USINT &paModuleState, COutputParameter<CIEC_WSTRING> paIdCmd, COutputParameter<CIEC_WSTRING> paIdRelease, COutputParameter<CIEC_WSTRING> paIdState, COutputParameter<CIEC_WSTRING> paIdPub, CAnyBitOutputParameter<CIEC_BOOL> paO_Enable, CAnyBitOutputParameter<CIEC_BOOL> paO_Down, COutputParameter<CIEC_LREAL> paO_Step, CAnyBitOutputParameter<CIEC_BOOL> paE_Step, CAnyBitOutputParameter<CIEC_BOOL> paAtHome, COutputParameter<CIEC_LREAL> paActualPosition, CAnyBitOutputParameter<CIEC_BOOL> paHomed, CAnyBitOutputParameter<CIEC_BOOL> paMoving, COutputParameter<CIEC_WSTRING> paHolder, COutputParameter<CIEC_TIME> paMoveDT) {
        COutputGuard guard_IdCmd(paIdCmd);
        COutputGuard guard_IdRelease(paIdRelease);
        COutputGuard guard_IdState(paIdState);
        COutputGuard guard_IdPub(paIdPub);
        COutputGuard guard_O_Enable(paO_Enable);
        COutputGuard guard_O_Down(paO_Down);
        COutputGuard guard_O_Step(paO_Step);
        COutputGuard guard_E_Step(paE_Step);
        COutputGuard guard_AtHome(paAtHome);
        COutputGuard guard_ActualPosition(paActualPosition);
        COutputGuard guard_Homed(paHomed);
        COutputGuard guard_Moving(paMoving);
        COutputGuard guard_Holder(paHolder);
        COutputGuard guard_MoveDT(paMoveDT);
        var_Module = paModule;
        var_Name = paName;
        var_UaRoot = paUaRoot;
        var_C_Holder = paC_Holder;
        var_C_Release = paC_Release;
        var_C_Enable = paC_Enable;
        var_C_Down = paC_Down;
        var_C_Step = paC_Step;
        var_CE_Step = paCE_Step;
        var_C_Move = paC_Move;
        var_C_Goal = paC_Goal;
        var_R_Holder = paR_Holder;
        var_I_AtHome = paI_AtHome;
        var_ModuleState = paModuleState;
        executeEvent(scmEventRELEASEID, nullptr);
        *paIdCmd = var_IdCmd;
        *paIdRelease = var_IdRelease;
        *paIdState = var_IdState;
        *paIdPub = var_IdPub;
        *paO_Enable = var_O_Enable;
        *paO_Down = var_O_Down;
        *paO_Step = var_O_Step;
        *paE_Step = var_E_Step;
        *paAtHome = var_AtHome;
        *paActualPosition = var_ActualPosition;
        *paHomed = var_Homed;
        *paMoving = var_Moving;
        *paHolder = var_Holder;
        *paMoveDT = var_MoveDT;
      }

      void evt_SAMPLE(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paName, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paC_Holder, const CIEC_BOOL &paC_Release, const CIEC_BOOL &paC_Enable, const CIEC_BOOL &paC_Down, const CIEC_LREAL &paC_Step, const CIEC_BOOL &paCE_Step, const CIEC_BOOL &paC_Move, const CIEC_LREAL &paC_Goal, const CIEC_WSTRING &paR_Holder, const CIEC_BOOL &paI_AtHome, const CIEC_USINT &paModuleState, COutputParameter<CIEC_WSTRING> paIdCmd, COutputParameter<CIEC_WSTRING> paIdRelease, COutputParameter<CIEC_WSTRING> paIdState, COutputParameter<CIEC_WSTRING> paIdPub, CAnyBitOutputParameter<CIEC_BOOL> paO_Enable, CAnyBitOutputParameter<CIEC_BOOL> paO_Down, COutputParameter<CIEC_LREAL> paO_Step, CAnyBitOutputParameter<CIEC_BOOL> paE_Step, CAnyBitOutputParameter<CIEC_BOOL> paAtHome, COutputParameter<CIEC_LREAL> paActualPosition, CAnyBitOutputParameter<CIEC_BOOL> paHomed, CAnyBitOutputParameter<CIEC_BOOL> paMoving, COutputParameter<CIEC_WSTRING> paHolder, COutputParameter<CIEC_TIME> paMoveDT) {
        COutputGuard guard_IdCmd(paIdCmd);
        COutputGuard guard_IdRelease(paIdRelease);
        COutputGuard guard_IdState(paIdState);
        COutputGuard guard_IdPub(paIdPub);
        COutputGuard guard_O_Enable(paO_Enable);
        COutputGuard guard_O_Down(paO_Down);
        COutputGuard guard_O_Step(paO_Step);
        COutputGuard guard_E_Step(paE_Step);
        COutputGuard guard_AtHome(paAtHome);
        COutputGuard guard_ActualPosition(paActualPosition);
        COutputGuard guard_Homed(paHomed);
        COutputGuard guard_Moving(paMoving);
        COutputGuard guard_Holder(paHolder);
        COutputGuard guard_MoveDT(paMoveDT);
        var_Module = paModule;
        var_Name = paName;
        var_UaRoot = paUaRoot;
        var_C_Holder = paC_Holder;
        var_C_Release = paC_Release;
        var_C_Enable = paC_Enable;
        var_C_Down = paC_Down;
        var_C_Step = paC_Step;
        var_CE_Step = paCE_Step;
        var_C_Move = paC_Move;
        var_C_Goal = paC_Goal;
        var_R_Holder = paR_Holder;
        var_I_AtHome = paI_AtHome;
        var_ModuleState = paModuleState;
        executeEvent(scmEventSAMPLEID, nullptr);
        *paIdCmd = var_IdCmd;
        *paIdRelease = var_IdRelease;
        *paIdState = var_IdState;
        *paIdPub = var_IdPub;
        *paO_Enable = var_O_Enable;
        *paO_Down = var_O_Down;
        *paO_Step = var_O_Step;
        *paE_Step = var_E_Step;
        *paAtHome = var_AtHome;
        *paActualPosition = var_ActualPosition;
        *paHomed = var_Homed;
        *paMoving = var_Moving;
        *paHolder = var_Holder;
        *paMoveDT = var_MoveDT;
      }

      void evt_REFRESH(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paName, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paC_Holder, const CIEC_BOOL &paC_Release, const CIEC_BOOL &paC_Enable, const CIEC_BOOL &paC_Down, const CIEC_LREAL &paC_Step, const CIEC_BOOL &paCE_Step, const CIEC_BOOL &paC_Move, const CIEC_LREAL &paC_Goal, const CIEC_WSTRING &paR_Holder, const CIEC_BOOL &paI_AtHome, const CIEC_USINT &paModuleState, COutputParameter<CIEC_WSTRING> paIdCmd, COutputParameter<CIEC_WSTRING> paIdRelease, COutputParameter<CIEC_WSTRING> paIdState, COutputParameter<CIEC_WSTRING> paIdPub, CAnyBitOutputParameter<CIEC_BOOL> paO_Enable, CAnyBitOutputParameter<CIEC_BOOL> paO_Down, COutputParameter<CIEC_LREAL> paO_Step, CAnyBitOutputParameter<CIEC_BOOL> paE_Step, CAnyBitOutputParameter<CIEC_BOOL> paAtHome, COutputParameter<CIEC_LREAL> paActualPosition, CAnyBitOutputParameter<CIEC_BOOL> paHomed, CAnyBitOutputParameter<CIEC_BOOL> paMoving, COutputParameter<CIEC_WSTRING> paHolder, COutputParameter<CIEC_TIME> paMoveDT) {
        COutputGuard guard_IdCmd(paIdCmd);
        COutputGuard guard_IdRelease(paIdRelease);
        COutputGuard guard_IdState(paIdState);
        COutputGuard guard_IdPub(paIdPub);
        COutputGuard guard_O_Enable(paO_Enable);
        COutputGuard guard_O_Down(paO_Down);
        COutputGuard guard_O_Step(paO_Step);
        COutputGuard guard_E_Step(paE_Step);
        COutputGuard guard_AtHome(paAtHome);
        COutputGuard guard_ActualPosition(paActualPosition);
        COutputGuard guard_Homed(paHomed);
        COutputGuard guard_Moving(paMoving);
        COutputGuard guard_Holder(paHolder);
        COutputGuard guard_MoveDT(paMoveDT);
        var_Module = paModule;
        var_Name = paName;
        var_UaRoot = paUaRoot;
        var_C_Holder = paC_Holder;
        var_C_Release = paC_Release;
        var_C_Enable = paC_Enable;
        var_C_Down = paC_Down;
        var_C_Step = paC_Step;
        var_CE_Step = paCE_Step;
        var_C_Move = paC_Move;
        var_C_Goal = paC_Goal;
        var_R_Holder = paR_Holder;
        var_I_AtHome = paI_AtHome;
        var_ModuleState = paModuleState;
        executeEvent(scmEventREFRESHID, nullptr);
        *paIdCmd = var_IdCmd;
        *paIdRelease = var_IdRelease;
        *paIdState = var_IdState;
        *paIdPub = var_IdPub;
        *paO_Enable = var_O_Enable;
        *paO_Down = var_O_Down;
        *paO_Step = var_O_Step;
        *paE_Step = var_E_Step;
        *paAtHome = var_AtHome;
        *paActualPosition = var_ActualPosition;
        *paHomed = var_Homed;
        *paMoving = var_Moving;
        *paHolder = var_Holder;
        *paMoveDT = var_MoveDT;
      }

      void evt_DRIVEN(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paName, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paC_Holder, const CIEC_BOOL &paC_Release, const CIEC_BOOL &paC_Enable, const CIEC_BOOL &paC_Down, const CIEC_LREAL &paC_Step, const CIEC_BOOL &paCE_Step, const CIEC_BOOL &paC_Move, const CIEC_LREAL &paC_Goal, const CIEC_WSTRING &paR_Holder, const CIEC_BOOL &paI_AtHome, const CIEC_USINT &paModuleState, COutputParameter<CIEC_WSTRING> paIdCmd, COutputParameter<CIEC_WSTRING> paIdRelease, COutputParameter<CIEC_WSTRING> paIdState, COutputParameter<CIEC_WSTRING> paIdPub, CAnyBitOutputParameter<CIEC_BOOL> paO_Enable, CAnyBitOutputParameter<CIEC_BOOL> paO_Down, COutputParameter<CIEC_LREAL> paO_Step, CAnyBitOutputParameter<CIEC_BOOL> paE_Step, CAnyBitOutputParameter<CIEC_BOOL> paAtHome, COutputParameter<CIEC_LREAL> paActualPosition, CAnyBitOutputParameter<CIEC_BOOL> paHomed, CAnyBitOutputParameter<CIEC_BOOL> paMoving, COutputParameter<CIEC_WSTRING> paHolder, COutputParameter<CIEC_TIME> paMoveDT) {
        COutputGuard guard_IdCmd(paIdCmd);
        COutputGuard guard_IdRelease(paIdRelease);
        COutputGuard guard_IdState(paIdState);
        COutputGuard guard_IdPub(paIdPub);
        COutputGuard guard_O_Enable(paO_Enable);
        COutputGuard guard_O_Down(paO_Down);
        COutputGuard guard_O_Step(paO_Step);
        COutputGuard guard_E_Step(paE_Step);
        COutputGuard guard_AtHome(paAtHome);
        COutputGuard guard_ActualPosition(paActualPosition);
        COutputGuard guard_Homed(paHomed);
        COutputGuard guard_Moving(paMoving);
        COutputGuard guard_Holder(paHolder);
        COutputGuard guard_MoveDT(paMoveDT);
        var_Module = paModule;
        var_Name = paName;
        var_UaRoot = paUaRoot;
        var_C_Holder = paC_Holder;
        var_C_Release = paC_Release;
        var_C_Enable = paC_Enable;
        var_C_Down = paC_Down;
        var_C_Step = paC_Step;
        var_CE_Step = paCE_Step;
        var_C_Move = paC_Move;
        var_C_Goal = paC_Goal;
        var_R_Holder = paR_Holder;
        var_I_AtHome = paI_AtHome;
        var_ModuleState = paModuleState;
        executeEvent(scmEventDRIVENID, nullptr);
        *paIdCmd = var_IdCmd;
        *paIdRelease = var_IdRelease;
        *paIdState = var_IdState;
        *paIdPub = var_IdPub;
        *paO_Enable = var_O_Enable;
        *paO_Down = var_O_Down;
        *paO_Step = var_O_Step;
        *paE_Step = var_E_Step;
        *paAtHome = var_AtHome;
        *paActualPosition = var_ActualPosition;
        *paHomed = var_Homed;
        *paMoving = var_Moving;
        *paHolder = var_Holder;
        *paMoveDT = var_MoveDT;
      }

      void evt_MOD_CHG(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paName, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paC_Holder, const CIEC_BOOL &paC_Release, const CIEC_BOOL &paC_Enable, const CIEC_BOOL &paC_Down, const CIEC_LREAL &paC_Step, const CIEC_BOOL &paCE_Step, const CIEC_BOOL &paC_Move, const CIEC_LREAL &paC_Goal, const CIEC_WSTRING &paR_Holder, const CIEC_BOOL &paI_AtHome, const CIEC_USINT &paModuleState, COutputParameter<CIEC_WSTRING> paIdCmd, COutputParameter<CIEC_WSTRING> paIdRelease, COutputParameter<CIEC_WSTRING> paIdState, COutputParameter<CIEC_WSTRING> paIdPub, CAnyBitOutputParameter<CIEC_BOOL> paO_Enable, CAnyBitOutputParameter<CIEC_BOOL> paO_Down, COutputParameter<CIEC_LREAL> paO_Step, CAnyBitOutputParameter<CIEC_BOOL> paE_Step, CAnyBitOutputParameter<CIEC_BOOL> paAtHome, COutputParameter<CIEC_LREAL> paActualPosition, CAnyBitOutputParameter<CIEC_BOOL> paHomed, CAnyBitOutputParameter<CIEC_BOOL> paMoving, COutputParameter<CIEC_WSTRING> paHolder, COutputParameter<CIEC_TIME> paMoveDT) {
        COutputGuard guard_IdCmd(paIdCmd);
        COutputGuard guard_IdRelease(paIdRelease);
        COutputGuard guard_IdState(paIdState);
        COutputGuard guard_IdPub(paIdPub);
        COutputGuard guard_O_Enable(paO_Enable);
        COutputGuard guard_O_Down(paO_Down);
        COutputGuard guard_O_Step(paO_Step);
        COutputGuard guard_E_Step(paE_Step);
        COutputGuard guard_AtHome(paAtHome);
        COutputGuard guard_ActualPosition(paActualPosition);
        COutputGuard guard_Homed(paHomed);
        COutputGuard guard_Moving(paMoving);
        COutputGuard guard_Holder(paHolder);
        COutputGuard guard_MoveDT(paMoveDT);
        var_Module = paModule;
        var_Name = paName;
        var_UaRoot = paUaRoot;
        var_C_Holder = paC_Holder;
        var_C_Release = paC_Release;
        var_C_Enable = paC_Enable;
        var_C_Down = paC_Down;
        var_C_Step = paC_Step;
        var_CE_Step = paCE_Step;
        var_C_Move = paC_Move;
        var_C_Goal = paC_Goal;
        var_R_Holder = paR_Holder;
        var_I_AtHome = paI_AtHome;
        var_ModuleState = paModuleState;
        executeEvent(scmEventMOD_CHGID, nullptr);
        *paIdCmd = var_IdCmd;
        *paIdRelease = var_IdRelease;
        *paIdState = var_IdState;
        *paIdPub = var_IdPub;
        *paO_Enable = var_O_Enable;
        *paO_Down = var_O_Down;
        *paO_Step = var_O_Step;
        *paE_Step = var_E_Step;
        *paAtHome = var_AtHome;
        *paActualPosition = var_ActualPosition;
        *paHomed = var_Homed;
        *paMoving = var_Moving;
        *paHolder = var_Holder;
        *paMoveDT = var_MoveDT;
      }

      void evt_MOVE_T(const CIEC_WSTRING &paModule, const CIEC_WSTRING &paName, const CIEC_WSTRING &paUaRoot, const CIEC_WSTRING &paC_Holder, const CIEC_BOOL &paC_Release, const CIEC_BOOL &paC_Enable, const CIEC_BOOL &paC_Down, const CIEC_LREAL &paC_Step, const CIEC_BOOL &paCE_Step, const CIEC_BOOL &paC_Move, const CIEC_LREAL &paC_Goal, const CIEC_WSTRING &paR_Holder, const CIEC_BOOL &paI_AtHome, const CIEC_USINT &paModuleState, COutputParameter<CIEC_WSTRING> paIdCmd, COutputParameter<CIEC_WSTRING> paIdRelease, COutputParameter<CIEC_WSTRING> paIdState, COutputParameter<CIEC_WSTRING> paIdPub, CAnyBitOutputParameter<CIEC_BOOL> paO_Enable, CAnyBitOutputParameter<CIEC_BOOL> paO_Down, COutputParameter<CIEC_LREAL> paO_Step, CAnyBitOutputParameter<CIEC_BOOL> paE_Step, CAnyBitOutputParameter<CIEC_BOOL> paAtHome, COutputParameter<CIEC_LREAL> paActualPosition, CAnyBitOutputParameter<CIEC_BOOL> paHomed, CAnyBitOutputParameter<CIEC_BOOL> paMoving, COutputParameter<CIEC_WSTRING> paHolder, COutputParameter<CIEC_TIME> paMoveDT) {
        COutputGuard guard_IdCmd(paIdCmd);
        COutputGuard guard_IdRelease(paIdRelease);
        COutputGuard guard_IdState(paIdState);
        COutputGuard guard_IdPub(paIdPub);
        COutputGuard guard_O_Enable(paO_Enable);
        COutputGuard guard_O_Down(paO_Down);
        COutputGuard guard_O_Step(paO_Step);
        COutputGuard guard_E_Step(paE_Step);
        COutputGuard guard_AtHome(paAtHome);
        COutputGuard guard_ActualPosition(paActualPosition);
        COutputGuard guard_Homed(paHomed);
        COutputGuard guard_Moving(paMoving);
        COutputGuard guard_Holder(paHolder);
        COutputGuard guard_MoveDT(paMoveDT);
        var_Module = paModule;
        var_Name = paName;
        var_UaRoot = paUaRoot;
        var_C_Holder = paC_Holder;
        var_C_Release = paC_Release;
        var_C_Enable = paC_Enable;
        var_C_Down = paC_Down;
        var_C_Step = paC_Step;
        var_CE_Step = paCE_Step;
        var_C_Move = paC_Move;
        var_C_Goal = paC_Goal;
        var_R_Holder = paR_Holder;
        var_I_AtHome = paI_AtHome;
        var_ModuleState = paModuleState;
        executeEvent(scmEventMOVE_TID, nullptr);
        *paIdCmd = var_IdCmd;
        *paIdRelease = var_IdRelease;
        *paIdState = var_IdState;
        *paIdPub = var_IdPub;
        *paO_Enable = var_O_Enable;
        *paO_Down = var_O_Down;
        *paO_Step = var_O_Step;
        *paE_Step = var_E_Step;
        *paAtHome = var_AtHome;
        *paActualPosition = var_ActualPosition;
        *paHomed = var_Homed;
        *paMoving = var_Moving;
        *paHolder = var_Holder;
        *paMoveDT = var_MoveDT;
      }
  };
}

