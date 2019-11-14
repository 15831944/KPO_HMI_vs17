// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_TREATMENTMANAGEMENTEVENTHANDLER_41C8037300D4_INCLUDED
#define _INC_CDM_TREATMENTMANAGEMENTEVENTHANDLER_41C8037300D4_INCLUDED

#include "CDM_EventHandler.h"

class CDM_Task;

class CDM_TreatmentManagementEventHandler 
: public CDM_EventHandler
{
public:
	virtual bool doHeatAnnouncementOffline(CEventMessage& Event);

	virtual bool doCreateTreatmentID(CEventMessage& Event);

	CDM_TreatmentManagementEventHandler(CDM_Task* pDMTask);

	virtual ~CDM_TreatmentManagementEventHandler();

	virtual bool doHeatAnnouncement(CEventMessage& Event);

	virtual bool doHeatCancellation(CEventMessage& Event);

	virtual bool doHeatDeparture(CEventMessage& Event);

	virtual bool doHeatStart(CEventMessage& Event);

  virtual bool doHeatEnd(CEventMessage& Event);

protected:
  virtual bool doProductionOrderChanged(CEventMessage& Event);
};

#endif /* _INC_CDM_TREATMENTMANAGEMENTEVENTHANDLER_41C8037300D4_INCLUDED */
