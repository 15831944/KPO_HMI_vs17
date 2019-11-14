// Copyright (C) 2004 SMS Demag AG
#include "CDM_LFTask.h"
#include "CDM_LFPurposeEventHandler.h"


CDM_LFPurposeEventHandler::CDM_LFPurposeEventHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

CDM_LFPurposeEventHandler::~CDM_LFPurposeEventHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

bool CDM_LFPurposeEventHandler::handleEvent(CEventMessage& evMessage)
{
	//HANDLE_EVENT_DATA(LFHandleUpdatePurpose);
  HANDLE_EVENT(LFHandleUpdatePurpose);
	
	return false;
}

bool CDM_LFPurposeEventHandler::doLFHandleUpdatePurpose(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if ( CDM_LFDBManagerTask::getInstance()->getDBManager()->evLFHandleUpdatePurpose(Event) )
  {
    if ( checkEventAssignment(Event) )
    {
      RetValue = dispatchEvent( Event );
    }
  }

  return RetValue;
}
