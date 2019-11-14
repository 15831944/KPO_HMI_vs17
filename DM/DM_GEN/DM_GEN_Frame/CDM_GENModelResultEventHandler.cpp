// Copyright (C) 2004 SMS Demag AG

#include "cCBS_StdEventLogFrameController.h"

#include "DM_Definitions.h"

#include "CDM_GENModelResultEventHandler.h"






CDM_GENModelResultEventHandler::CDM_GENModelResultEventHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

CDM_GENModelResultEventHandler::~CDM_GENModelResultEventHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

bool CDM_GENModelResultEventHandler::handleEvent(CEventMessage& evMessage)
{
	HANDLE_EVENT(GENModelResultActualSetpoints);
	HANDLE_EVENT(GENModelResultCode);
	HANDLE_EVENT(GENModelResultRecipeSetpoints);
	return false;
}



bool CDM_GENModelResultEventHandler::doGENModelResultActualSetpoints(CEventMessage& Event)
{
	return doGENModelResult(Event);
}

bool CDM_GENModelResultEventHandler::doGENModelResultCode( CEventMessage& Event)
{
	return doGENModelResult(Event);
}

bool CDM_GENModelResultEventHandler::doGENModelResultRecipeSetpoints( CEventMessage& Event)
{
	return doGENModelResult(Event);
}



bool CDM_GENModelResultEventHandler::doGENModelResult(CEventMessage& Event)
{
  bool RetValue = false;

  // try to update Event with assigend data (ProductID...)
  if ( checkEventAssignment(Event) )
  {
    RetValue = doModelEvent(Event);
  }

  return RetValue; 
}
