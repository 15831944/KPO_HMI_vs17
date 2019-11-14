// Copyright (C) 2011 SMS Siemag AG

#include "cCBS_StdEventLogFrameController.h"
#include "CDM_EAFTask.h"
#include "CDM_EAFDBManagerTask.h"
#include "CDM_EAFPurposeEventHandler.h"

CDM_EAFPurposeEventHandler::CDM_EAFPurposeEventHandler()
{
}

CDM_EAFPurposeEventHandler::~CDM_EAFPurposeEventHandler()
{
}

bool CDM_EAFPurposeEventHandler::handleEvent(CEventMessage& evMessage)
{
  HANDLE_EVENT(EAFHandleUpdatePurpose);

  return false;
}

bool CDM_EAFPurposeEventHandler::doEAFHandleUpdatePurpose(CEventMessage& Event)
{
  bool RetValue = false;
  
  // copy data from DH to DM_DataInterface
  copyDataEventData(Event);

  // try to update Event with assigend data (ProductID...)
  if ( checkEventAssignment(Event) )
  {
    if ( CDM_EAFDBManagerTask::getInstance()->getDBManager()->evHandleUpdatePurpose(Event) )
    {
      RetValue = dispatchEvent( Event );
    }
  }

  return RetValue;
}


