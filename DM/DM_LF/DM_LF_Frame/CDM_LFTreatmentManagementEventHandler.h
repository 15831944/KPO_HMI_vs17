// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_LFTREATMENTMANAGEMENTEVENTHANDLER_412F15CF0224_INCLUDED
#define _INC_CDM_LFTREATMENTMANAGEMENTEVENTHANDLER_412F15CF0224_INCLUDED

#include "CDM_LFEventHandler.h"
#include "CDM_TreatmentManagementEventHandler.h"

class CDM_LFTreatmentManagementEventHandler
  : public CDM_TreatmentManagementEventHandler
{
public:
  // overloaded here to sent event LFSetUpOfHeat to create product in TSM
  virtual bool doOnUnknownProduct(CEventMessage& Event);

  virtual bool sendAdditionalEvents(CEventMessage& Event);

  bool doLFCreateTreatmentID(CEventMessage& Event);

  bool doLFSetUpOfHeat(CEventMessage& Event);
  bool doLFResetOfHeat(CEventMessage& Event);

  bool doLFHeatScheduleUpdate(CEventMessage& Event);

  virtual bool handleEvent(CEventMessage& evMessage);

  bool doLFHeatStart(CEventMessage& Event);

  bool doLFHeatEnd(CEventMessage& Event);

  bool doLFHeatAnnouncement(CEventMessage& Event);

  bool doLFHeatAnnouncementOffline(CEventMessage& Event);

  bool doLFHeatCancellation(CEventMessage& Event);

  bool doLFHeatDeparture(CEventMessage& Event);

  bool doLFTemperatureHold(CEventMessage& Event);
  bool doLFCleanlinessStirring(CEventMessage& Event);
  bool doLFCooling(CEventMessage& Event);
  bool doLFDelayStatus(CEventMessage& Event);

  bool doLFCleanStirring(CEventMessage& Event);

  bool doLFFinalHeating(CEventMessage& Event);
  bool doLFInitialHeating(CEventMessage& Event);
  bool doLFMainHeating(CEventMessage& Event);
  bool doOnHeating(CEventMessage& Event);

  bool doLFChangeProdPracPointerStirring(CEventMessage& Event);

  bool doLFChangeProdPracPointerRestriction(CEventMessage& Event);

  bool doLFChangeProdPracPointerParameter(CEventMessage& Event);

  bool doLFChangeProdPracPointerElec(CEventMessage& Event);

  bool doLFChangeAimData(CEventMessage& Event);

  bool doLFProductionOrderChanged(CEventMessage& Event);

  bool doLFLadleDataChanged(CEventMessage& Event);

  bool doLFSteelGradeChanged(CEventMessage& Event);

  bool doLFUpdatePlantStatus(CEventMessage& Event);

  CDM_LFTreatmentManagementEventHandler();

  virtual ~CDM_LFTreatmentManagementEventHandler();

};

#endif /* _INC_CDM_LFTREATMENTMANAGEMENTEVENTHANDLER_412F15CF0224_INCLUDED */
