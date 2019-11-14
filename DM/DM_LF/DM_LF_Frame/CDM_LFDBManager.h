//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by (DB)ClassCodeUtility BETA 0.6.0 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_LFDBMANAGER_INCLUDED
#define _INC_CDM_LFDBMANAGER_INCLUDED

#include "CDM_DBManager.h"

class CDM_LFDBManager
: public CDM_DBManager
{

public:

  CDM_LFDBManager(CDM_DBManagerTask* _task);

  virtual ~CDM_LFDBManager();

  void init();

protected:

  bool copyHDLCyclMeasData(sHeatInfo &HeatInfo, bool Commit);

  bool copyHDLHeatData(sHeatInfo &HeatInfo, bool Commit);

  bool checkHDLHeatData(sHeatInfo &HeatInfo, bool Commit);

  bool copyHDLHeatDataMelt(sHeatInfo &HeatInfo, bool Commit);

  bool copyHDLHeatPhaseData(sHeatInfo &HeatInfo, bool Commit);

  bool copyHDLPpEls(sHeatInfo &HeatInfo, const std::string &SteelGradeCode, bool Commit);

  bool copyHDLPpStirrs(sHeatInfo &HeatInfo, const std::string &SteelGradeCode, bool Commit);

public:

  bool evChangeProdPracPointerElec(CEventMessage &Event);

  bool evChangeProdPracPointerStirring(CEventMessage &Event);

  bool evCleaninessStirringReceived(CEventMessage &Event);

  bool evCyclicMeasurementElectric(CEventMessage& Event);

  bool evHeatAnnouncement(CEventMessage &Event, bool commit);

  bool evHeatDeparture(CEventMessage &Event);

  bool evHeatEnd(CEventMessage &Event);

  bool evHeatStart(CEventMessage &Event);

  bool evLFHandleUpdatePurpose(CEventMessage &Event);

  bool evLFSteelGradeChanged(CEventMessage& Event);

  bool evPowerOff(CEventMessage &Event);

  bool evPowerOn(CEventMessage &Event);

  bool evProductionOrderChanged(CEventMessage &Event);

  bool evRetreatment(CEventMessage &Event);

  bool evSetupOfHeat(CEventMessage &Event);

  bool evSlagAnalysisReceived(CEventMessage &Event);

	//bool evSteelSampleTaken(CEventMessage &Event);
	//bool evSlagSampleTaken(CEventMessage &Event);
  bool evSteelAnalysisReceived(CEventMessage &Event);

  bool evMaterialHandlingReport(CEventMessage& Event);
	bool AutomaticlyFillRelativeDelays(CEventMessage &Event,bool pCommit,bool &isDelay); //SARS

protected:

  double getHeatTotalWeight(sHeatInfo &HeatInfo);

  virtual CDateTime getLastTreatmentEndTime(sHeatInfo &HeatInfo, long TreatmentPosition);


protected:

  bool handlePDTablesOnAnnounce(sHeatInfo &HeatInfo, const std::string &Order, const std::string &SteelGradeCode, const std::string &UserCode, sPDData &PDData, long &SampleRef, long TreatmentPosition, bool Commit );

  bool handlePDTablesOnSetupOfHeat(sHeatInfo &HeatInfo, sPDData &PDData, long Status, const std::string &OrderId, const CDateTime &HeatStart, const CDateTime &HeatEnd, const std::string &SteelgradeCode, const std::string &UserCode, long TreatmentPosition, bool Commit );

  void log(const std::string& _message, long _level);

public:

  bool setGasConsumptions(CEventMessage &Event, bool Commit);

  bool setHeatDataAlloyWeight(sHeatInfo &HeatInfo,bool Commit);

  bool setHeatDataBinWeight(sHeatInfo &HeatInfo,bool Commit);

  bool setHeatDataElectConsTotal(sHeatInfo &HeatInfo,bool Commit);

  bool setHeatDataSlagFormer(sHeatInfo &HeatInfo,bool Commit);

  bool setHeatLadleData(sHeatInfo &HeatInfo,bool Commit);

  bool setStirrBypass(CEventMessage &Event,bool Commit);

  virtual long getActTreatmentPosition(CEventMessage &Event);

  bool handlePDLTablesOnHeatDeparture(sHeatInfo &HeatInfo, const std::string &UserCode, bool Commit);

};

#endif /* _INC_CDM_LFDBManager_INCLUDED */
