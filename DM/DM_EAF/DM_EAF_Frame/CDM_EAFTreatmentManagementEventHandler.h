// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_EAFTREATMENTMANAGEMENTEVENTHANDLER_412F15CF0224_INCLUDED
#define _INC_CDM_EAFTREATMENTMANAGEMENTEVENTHANDLER_412F15CF0224_INCLUDED

#include "CDM_EAFEventHandler.h"
#include "CDM_TreatmentManagementEventHandler.h"

class CDM_EAFTreatmentManagementEventHandler : 
  public CDM_TreatmentManagementEventHandler
{
public:

	bool doEAFSetUpOfHeat(CEventMessage& Event);

  bool doEAFManipInjectLanceAvail(CEventMessage& Event);

	bool doEAFBurnerGasAvail(CEventMessage& Event);

	bool sendAdditionalEvents(CEventMessage& Event);

  bool doEAFTapLadleData(CEventMessage& Event);

	bool doEAFChangeTapLadleData(CEventMessage& Event);

  bool doEAFChangeProdPracPointerInjection(CEventMessage& Event);

  bool doEAFChangeProdPracPointerOxygen(CEventMessage& Event);

  bool doEAFChangeProdPracPointerParameter(CEventMessage& Event);

  bool doEAFChangeProdPracPointerBurner(CEventMessage& Event);

  bool doEAFChangeProdPracPointerScrapLoading(CEventMessage& Event);

  bool doEAFChangeProdPracPointerProcess(CEventMessage& Event);

  bool doEAFChangeAimData(CEventMessage& Event);

  bool doEAFChangeHotHeelData(CEventMessage& Event);

  bool doEAFChangeProdPracPointerRestriction(CEventMessage& Event);

  bool doEAFChangeThermalStatus(CEventMessage& Event);

  bool doEAFProductionOrderChanged(CEventMessage& Event);

  bool doEAFSteelGradeChanged(CEventMessage& Event);

  bool doEAFChangeTreatmentMode(CEventMessage& Event);

	bool doEAFCreateTreatmentID(CEventMessage& Event);

	bool doEAFHeatScheduleUpdate(CEventMessage& Event);

	//This hook operation would be called automatically by 
	//handleEvent( FRISEVENT &event) 
	//when an event is received. And this operation must be 
	//implemented by the user or client
	//in order to use it.
	virtual bool handleEvent(CEventMessage& evMessage);

	bool doEAFHeatStart(CEventMessage& Event);

	bool doEAFHeatEnd(CEventMessage& Event);

	bool doEAFHeatAnnouncement(CEventMessage& Event);

  bool doEAFAutoHeatAnnouncement(CEventMessage& Event);

	bool doEAFHeatCancellation(CEventMessage& Event);

	bool doEAFHeatDeparture(CEventMessage& Event);

  bool doEAFBasketRequest(CEventMessage& Event);

  bool doEAFPhaseReport(CEventMessage& Event);

  bool doEAFBasketHotMetalInfomationRequest(CEventMessage& Event);

	CDM_EAFTreatmentManagementEventHandler();

	virtual ~CDM_EAFTreatmentManagementEventHandler();

  bool doEAFDelayStatus(CEventMessage& Event);

  bool doOnUnknownProduct(CEventMessage& Event);

  bool doEAFOrderScrap(CEventMessage& Event);

  bool doEAFUpdatePlantStatus(CEventMessage& Event);

private:

  seqDeviceGasData getGasCons4PhaseReport(CEventMessage& Event);

  double getLastBurnerO2Cons(const std::string& dataKey, const std::string& Plant);

  double getLastBurnerBGCons(const std::string& dataKey, const std::string& Plant);

  double getLastLanceO2Cons(const std::string& dataKey, const std::string& Plant);

  double getLastLanceN2Cons(const std::string& dataKey, const std::string& Plant);

  double getLastStirrArCons(const std::string& dataKey, const std::string& Plant);

  double getLastStirrN2Cons(const std::string& dataKey, const std::string& Plant);

};

#endif /* _INC_CDM_EAFTREATMENTMANAGEMENTEVENTHANDLER_412F15CF0224_INCLUDED */
