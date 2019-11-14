// Copyright (C) 2011 SMS Siemag AG

#include "CEventMessage.h"
#include "CDM_GENDBManagerTask.h"
#include "CDM_GENCCSEventHandler.h"

#if defined (HANDLE_EVENT)
  #undef HANDLE_EVENT
#endif
#define HANDLE_EVENT(action) \
	if (CCS_EvMsg::ev##action == evMessage.getMessage()) \
           return do##action(evMessage);


CDM_GENCCSEventHandler::CDM_GENCCSEventHandler()
{
}

CDM_GENCCSEventHandler::~CDM_GENCCSEventHandler()
{
}

bool CDM_GENCCSEventHandler::handleEvent(CEventMessage& evMessage)
{
  HANDLE_EVENT( CCSCastBehaviour );
  HANDLE_EVENT( CCSHeatStatus );
  HANDLE_EVENT( CCSEndOfCast );
  HANDLE_EVENT( CCSRequiredLadleArrivalTime );
  HANDLE_EVENT( CCSSteelAnalysisReceived );

  return false;
}


bool CDM_GENCCSEventHandler::doCCSCastBehaviour(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}

bool CDM_GENCCSEventHandler::doCCSHeatStatus(CEventMessage& evMessage)
{
  if (checkEventAssignment( evMessage ) )
  {
    if (copyDataEventData(evMessage))
    {
      if (CDM_GENDBManagerTask::getInstance()->getDBManager()->evCCSHeatStatus(evMessage))
      {
        dispatchEvent(evMessage);
      }
    }
  }
  return true;
}//bool CDM_GENCCSEventHandler::doCCSHeatStatus(CEventMessage& evMessage)

bool CDM_GENCCSEventHandler::doCCSEndOfCast(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}

bool CDM_GENCCSEventHandler::doCCSRequiredLadleArrivalTime(CEventMessage& evMessage)
{
  bool RetValue = false;

  if ( checkEventAssignment(evMessage) )
  {
    if ( copyDataEventData(evMessage) )
    {
      // function moved to DH_CCS_OUT
      // if( CDM_GENDBManagerTask::getInstance()->getDBManager()->evCCSRequiredLadleArrivalTime(evMessage) )

      RetValue = dispatchEvent(evMessage);
    }
  }

  return true;
}

bool CDM_GENCCSEventHandler::doCCSSteelAnalysisReceived(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}

bool CDM_GENCCSEventHandler::checkEventAssignment(CEventMessage& Event)
{
  //
  // check if event could be assigned to existing product
  //

  //
  // In the case of CCS specific events, just bypass
  // the strict product idenfication check.
  //
  return true;
}
