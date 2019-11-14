// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_HMDTREATMENTMANAGEMENTEVENTHANDLER_412F15CF0224_INCLUDED
#define _INC_CDM_HMDTREATMENTMANAGEMENTEVENTHANDLER_412F15CF0224_INCLUDED

#include "CDM_HMDEventHandler.h"
#include "CDM_TreatmentManagementEventHandler.h"
class CDM_HMDTreatmentManagementEventHandler : public CDM_TreatmentManagementEventHandler
{
public:

  virtual bool doOnRemoveProduct(CEventMessage& Event, const std::string& ProductID);

  bool doHMDPlantStatus(CEventMessage& Event);

  bool doHMDHeatAnnouncementOffline(CEventMessage& Event);

  bool doHMDHeatScheduleUpdate(CEventMessage& Event);

  virtual bool handleEvent(CEventMessage& evMessage);

  bool doHMDHeatStart(CEventMessage& Event);

  bool doHMDHeatEnd(CEventMessage& Event);

  bool doHMDHeatAnnouncement(CEventMessage& Event);

  bool doHMDHeatCancellation(CEventMessage& Event);

  bool doHMDHeatDeparture(CEventMessage& Event);

	bool doHMDDelayStatus(CEventMessage& Event);

  CDM_HMDTreatmentManagementEventHandler();

  virtual ~CDM_HMDTreatmentManagementEventHandler();

  bool doOnUnknownProduct(CEventMessage& Event);

  bool makeEntryInHeatSchedule(CEventMessage& Event);
  
private:
  cCBS_Connection         *m_pConnection;

};

#endif /* _INC_CDM_HMDTREATMENTMANAGEMENTEVENTHANDLER_412F15CF0224_INCLUDED */
