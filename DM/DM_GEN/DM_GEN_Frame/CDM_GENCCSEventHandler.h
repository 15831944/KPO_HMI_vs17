// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_GENCCSEVENTHANDLER_41E516F0038C_INCLUDED
#define _INC_CDM_GENCCSEVENTHANDLER_41E516F0038C_INCLUDED

#include "CDM_GENEventHandler.h"

class CDM_GENCCSEventHandler 
: public CDM_GENEventHandler
{
public:

	CDM_GENCCSEventHandler();

	virtual ~CDM_GENCCSEventHandler();

	virtual bool checkEventAssignment(CEventMessage& Event);

  //This hook operation would be called automatically by 
	//handleEvent( FRISEVENT &event) 
	//when an event is received. And this operation must be 
	//implemented by the user or client
	//in order to use it.
	virtual bool handleEvent(CEventMessage& evMessage);

	bool doCCSCastBehaviour(CEventMessage& evMessage);

	bool doCCSHeatStatus(CEventMessage& evMessage);

	bool doCCSEndOfCast(CEventMessage& evMessage);

	bool doCCSRequiredLadleArrivalTime(CEventMessage& evMessage);

	bool doCCSSteelAnalysisReceived(CEventMessage& evMessage);

};

#endif /* _INC_CDM_GENCCSEVENTHANDLER_41E516F0038C_INCLUDED */
