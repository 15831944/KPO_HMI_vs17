// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_GENTREATMENTMANAGEMENTEVENTHANDLER_412F15CF0224_INCLUDED
#define _INC_CDM_GENTREATMENTMANAGEMENTEVENTHANDLER_412F15CF0224_INCLUDED

#include "CDM_GENEventHandler.h"
#include "CDM_TreatmentManagementEventHandler.h"


//
// This event handler is not used as of implementing the General Data Manager.
// But it maybe necessary to use it some time later, and it depends on whether
// or not change the functionality of this server.
//
class CDM_GENTreatmentManagementEventHandler : public CDM_TreatmentManagementEventHandler
  
{
public:

	//This hook operation would be called automatically by 
	//handleEvent( FRISEVENT &event) 
	//when an event is received. And this operation must be 
	//implemented by the user or client
	//in order to use it.
	virtual bool handleEvent(CEventMessage& evMessage);

	CDM_GENTreatmentManagementEventHandler();

	virtual ~CDM_GENTreatmentManagementEventHandler();

  bool doGenParameterUpdate(CEventMessage& evMessage);

  bool doGenOrderStatusUpdate(CEventMessage& evMessage);

  bool doGenHeatStatusUpdate(CEventMessage& evMessage);

  bool doGenAnalysisData(CEventMessage& evMessage);

  bool doGenHeatScheduleUpdate(CEventMessage& evMessage);

  bool doGenProductionOrderDataUpdate(CEventMessage& evMessage);

  bool checkEventAssignment(CEventMessage& Event);

};

#endif /* _INC_CDM_GENTREATMENTMANAGEMENTEVENTHANDLER_412F15CF0224_INCLUDED */
