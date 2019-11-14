// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_GENL3EVENTHANDLER_41E516F0038C_INCLUDED
#define _INC_CDM_GENL3EVENTHANDLER_41E516F0038C_INCLUDED

#include "CDM_GENEventHandler.h"

class CDM_GENL3EventHandler 
: public CDM_GENEventHandler
{
public:

	CDM_GENL3EventHandler();

	virtual ~CDM_GENL3EventHandler();

	virtual bool checkEventAssignment(CEventMessage& Event);

  //This hook operation would be called automatically by 
	//handleEvent( FRISEVENT &event) 
	//when an event is received. And this operation must be 
	//implemented by the user or client
	//in order to use it.
	virtual bool handleEvent(CEventMessage& evMessage);

  bool doL3SteelGradeCodeDefinitionUpdate(CEventMessage& evMessage);
  bool doL3DelayCodeUpdate(CEventMessage& evMessage);
  bool doL3MaterialCodeUpdate(CEventMessage& evMessage);
  bool doL3FacilityStatusRequest(CEventMessage& evMessage);

	bool doL3FacilityMaintSchedule(CEventMessage& evMessage);

	bool doL3HeatScheduleUpdate(CEventMessage& evMessage);

	bool doL3ProductionOrderDataUpdate(CEventMessage& evMessage);

	bool doL3SteelGradeDataUpdate(CEventMessage& evMessage);

	bool doL3UndefinedGradeRequest(CEventMessage& evMessage);

  bool doL3OpenDelaysRequest(CEventMessage& evMessage);

  bool doL3CurrentHeatStatusRequest(CEventMessage& evMessage);

  bool doL3HeatReportsRequest(CEventMessage& evMessage);

  bool doL3ProductionOrderChanged(CEventMessage& evMessage);


};

#endif /* _INC_CDM_GENL3EVENTHANDLER_41E516F0038C_INCLUDED */
