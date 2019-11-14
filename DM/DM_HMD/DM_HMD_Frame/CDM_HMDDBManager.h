// Copyright (C) 2009 SMS Demag AG
// 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_HMDDBMANAGER_INCLUDED
#define _INC_CDM_HMDDBMANAGER_INCLUDED

#include "CDM_DBManager.h"

//const string which is used in database mostly in EXPIRATIONDATE columns
const string sValidConst = "VALID";

//HM information
typedef struct
{
  string ProductId;
	string ProdOrderId;
  string HMId;
  string TreatId;
  string Plant;
  long PlantNo;
  long HotMetalCounter;
  string TreatEndOper;
	string TreatStartOper;
  double HMWeight;
  double SlagWeight;
  long HMTemp;
  double SAim;
  double SAct;
  long LadleFreeBoard;
  long CalcMode;
  long TreatType;
  long onRequest;
} sHMInfo;

const string sPlantConst = "HMD";

class CDM_HMDDBManager
: CDM_DBManager
{
public:
  CDM_HMDDBManager(CDM_DBManagerTask* _task);
  virtual ~CDM_HMDDBManager();

  void init();

	bool evHeatAnnouncement(CEventMessage &pMsg);
	bool evCancelHeat(CEventMessage &pMsg);
	bool evHeatDeparture(CEventMessage &pMsg);
	bool evDelayStatus(CEventMessage &pMsg);
	bool evHotMetalSampleTaken(CEventMessage &pMsg);
	bool evSlagSampleTaken(CEventMessage &pMsg);
	bool evTempMeasurement(CEventMessage &pMsg);
	bool evCeloxMeasurement(CEventMessage &pMsg);
	bool evHotMetalAnalysisReceived(CEventMessage &pMsg);
	bool evSlagAnalysisReceived(CEventMessage &pMsg);
	bool evHeatStart(CEventMessage &pMsg);
	bool evHeatEnd(CEventMessage &pMsg);

  // following functions have to be called after event handling in tracking
  bool doHeatDeparture(CEventMessage &Event);
  bool doHeatAnnouncement(CEventMessage &Event);
  bool doModelResult(CEventMessage &Event); //SANKAR

  bool AutomaticlyFillRelativeDelays(CEventMessage &Event,bool pCommit,bool &isDelay);
	bool doCyclicMeasurement(CEventMessage &Event);
	bool doPhaseDataChange(CEventMessage &Event);
	bool doOnPowerBlowing(CEventMessage &Event, bool res);
	bool evHMDModelResult(CEventMessage &Event, bool res);
	
	//bool evRetreatment(CEventMessage &pMsg);
  //bool evCleaninessStirringReceived(CEventMessage &pMsg);
  //bool evFurnPowerOnReceived(CEventMessage &pMsg);
  //bool evFurnPowerOffReceived(CEventMessage &pMsg);
  //bool evProductionOrderChanged(CEventMessage &pMsg);
	//bool evChangeProdPracPointerStirring(CEventMessage &pMsg);
	//bool evChangeProdPracPointerRestriction(CEventMessage &pMsg);
	//bool evChangeProdPracPointerParameter(CEventMessage &pMsg);
	//bool evChangeProdPracPointerElec(CEventMessage &pMsg);
  //bool evChangeAimData(CEventMessage &pMsg);
  //bool evLadleDataChanged(CEventMessage &pMsg);
  //bool evHMIMaterialDischarged(CEventMessage &pMsg);
  //bool evChangeLiquidAdditionData(CEventMessage &pMsg);
  //bool evSetupOfHeat(CEventMessage &pMsg);

protected:
  void log(const std::string& _message, long _level);

	bool copyHDHCyclMeasData(sHeatInfo &pHeatInfo, bool pCommit);
	bool copyHDHHMData(sHeatInfo &pHeatInfo, bool pCommit);
  bool copyHDHPpBaseVal(sHeatInfo &pHeatInfo, bool pCommit);
  bool copyHDHPpBaseValStep(sHeatInfo &pHeatInfo, bool pCommit);
  bool copyHDHPpBlowing(sHeatInfo &pHeatInfo, bool pCommit);
  bool copyHDHPpInjection(sHeatInfo &pHeatInfo, bool pCommit);
  bool copyHDHPpTempCorr(sHeatInfo &pHeatInfo, bool pCommit);
  bool handlePDTablesOnAnnounce(sHMInfo &pHMInfo,sDate &pTreatStartOper,sDate &pTreatEndOper, bool pCommit); //SANKAR
	bool handleHDTablesOnCancelHeat(sHMInfo &pHMInfo, bool pCommit);
	bool handlePDTablesOnHeatDeparture(sHMInfo &pHMInfo, bool pCommit,long pLadleNo, const std::string& pLadleType,long mDurSinceHeatStart,long mDurSinceHeatAnnounce);
	bool handlePDTablesOnHeatStart(sHMInfo &pHMInfo, bool pCommit,long mDurSinceHeatStart,long mDurSinceHeatAnnounce);
	bool handlePDTablesOnDelayStatus(sHeatInfo &pHeatInfo, CDateTime &pStartTime, CDateTime &pEndTime, const string &pCode, const string &pUser, const string &pDelayComment,long Status, bool pCommit);
  bool setPlantEquipmentAge(sHeatInfo &pHeatInfo);
  bool AutomaticlyFillRelativeDelays(sHeatInfo &pHeatInfo,const string &pUser,bool pCommit);

  //bool setHeatDataSlagFormer(sHeatInfo &pHeatInfo,bool pCommit);
  //bool setHeatDataBinWeight(sHeatInfo &pHeatInfo,bool pCommit);
  //bool setHeatDataAlloyWeight(sHeatInfo &pHeatInfo,bool pCommit);
  //bool setHeatDataElectConsTotal(sHeatInfo &pHeatInfo,bool pCommit);
  //bool setGasConsumptions(CEventMessage &Event, bool pCommit);
	string checkStringParam(const string &pValue, bool bClear = false);

	void setHMInfo(const CEventMessage& Event, sHMInfo& HMInfo);
};

#endif /* _INC_CDM_HMDDBMANAGER_INCLUDED */