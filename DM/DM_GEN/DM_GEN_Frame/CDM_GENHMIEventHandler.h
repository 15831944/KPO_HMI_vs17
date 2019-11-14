// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_GENHMIEVENTHANDLER_41E5187A011C_INCLUDED
#define _INC_CDM_GENHMIEVENTHANDLER_41E5187A011C_INCLUDED

#include "CDM_GENEventHandler.h"

class CDM_GENHMIEventHandler 
: public CDM_GENEventHandler
{
public:
	CDM_GENHMIEventHandler();

	virtual ~CDM_GENHMIEventHandler();

	virtual bool checkEventAssignment(CEventMessage& Event);

	//This hook operation would be called automatically by 
	//handleEvent( FRISEVENT &event) 
	//when an event is received. And this operation must be 
	//implemented by the user or client
	//in order to use it.
	virtual bool handleEvent(CEventMessage& evMessage);

	bool doHMIHeatScheduleUpdate(CEventMessage& evMessage);

	bool doHMIProductionOrderDataUpdate(CEventMessage& evMessage);

	bool doHMISetUpOfHeat(CEventMessage& evMessage);
	bool doHMIResetOfHeat(CEventMessage& evMessage);

	bool doHMISteelGradeDataUpdate(CEventMessage& evMessage);

  bool doHMIRequestPlanningData(CEventMessage& evMessage);
  bool doHMIRequestHeatSchedule(CEventMessage& evMessage);


};

#endif /* _INC_CDM_GENHMIEVENTHANDLER_41E5187A011C_INCLUDED */
