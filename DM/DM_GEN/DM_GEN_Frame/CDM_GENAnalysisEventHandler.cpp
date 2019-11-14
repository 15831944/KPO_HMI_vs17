// Copyright (C) 2011 SMS Siemag AG
#include "CEventMessage.h"
#include "iEventMessages_s.hh"

#include "CDM_GENTask.h"
#include "CDM_GENDBManagerTask.h"
#include "CDM_GENAnalysisEventHandler.h"

CDM_GENAnalysisEventHandler::~CDM_GENAnalysisEventHandler()
{
}

CDM_GENAnalysisEventHandler::CDM_GENAnalysisEventHandler()
: CDM_AnalysisEventHandler(CDM_GENTask::getInstance())
{
}

bool CDM_GENAnalysisEventHandler::handleEvent(CEventMessage& evMessage)
{
  if (evMessage.getMessage()== HMP_EvMsg::evHMPAnalysisReceived)
    return doHMPAnalysisReceived(evMessage);

  if (evMessage.getMessage() == HMP_EvMsg::evHMPTempMeasurement)
    return doHMPTempMeasurement(evMessage);

  if (evMessage.getMessage() == CCS_EvMsg::evCCSSteelAnalysisReceived)
    return doCCSAnalysisReceived(evMessage);

	return false;
}

bool CDM_GENAnalysisEventHandler::doCCSAnalysisReceived(CEventMessage& Event)
{
  if ( checkEventAssignment( Event ) )
  {
    if ( copyDataEventData( Event ))
    {
      dispatchEvent(Event);
    }
  }
	return true;
}//bool CDM_GENAnalysisEventHandler::doCCSAnalysisReceived(CEventMessage& Event)

bool CDM_GENAnalysisEventHandler::doHMPTempMeasurement(CEventMessage& Event)
{
  if ( checkEventAssignment( Event) )
  {
    if ( copyDataEventData( Event ) )
    {
      if ( CDM_GENDBManagerTask::getInstance()->getDBManager()->evHotMetalTemperatureReceived(Event) )
      {
        dispatchEvent(Event);
      }
    }
  }

	return true;
}//bool CDM_GENAnalysisEventHandler::doHMPTempMeasurement(CEventMessage& Event)

bool CDM_GENAnalysisEventHandler::doHMPAnalysisReceived(CEventMessage& Event)
{
  if ( checkEventAssignment( Event ) )
  {
    if ( copyDataEventData( Event ) )
    {
      if ( CDM_GENDBManagerTask::getInstance()->getDBManager()->evHotMetalAnalysisReceived(Event) )
      {
        dispatchEvent(Event);
      }
    }
  }

	return true;
}//bool CDM_GENAnalysisEventHandler::doHMPAnalysisReceived(CEventMessage& Event)

bool CDM_GENAnalysisEventHandler::checkEventAssignment(CEventMessage& Event)
{
  return checkReceiver(Event);
}
