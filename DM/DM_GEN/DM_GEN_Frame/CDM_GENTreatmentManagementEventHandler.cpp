// Copyright (C) 2011 SMS Siemag AG

#include "CEventMessage.h"
#include "CDM_GENTask.h"
#include "CDM_GENDBManagerTask.h"

#include "CDM_GENTreatmentManagementEventHandler.h"

CDM_GENTreatmentManagementEventHandler::CDM_GENTreatmentManagementEventHandler()
: CDM_TreatmentManagementEventHandler( CDM_GENTask::getInstance() )
{
}

CDM_GENTreatmentManagementEventHandler::~CDM_GENTreatmentManagementEventHandler()
{
}

bool CDM_GENTreatmentManagementEventHandler::handleEvent(CEventMessage& evMessage)
{
  HANDLE_EVENT( GenParameterUpdate );
  HANDLE_EVENT( GenOrderStatusUpdate );
  HANDLE_EVENT( GenHeatStatusUpdate );
  HANDLE_EVENT( GenAnalysisData );
  HANDLE_EVENT( GenHeatScheduleUpdate );
  HANDLE_EVENT( GenProductionOrderDataUpdate );

  return false;
}

bool CDM_GENTreatmentManagementEventHandler::doGenParameterUpdate(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}

bool CDM_GENTreatmentManagementEventHandler::doGenOrderStatusUpdate(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}

bool CDM_GENTreatmentManagementEventHandler::doGenHeatStatusUpdate(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}

bool CDM_GENTreatmentManagementEventHandler::doGenAnalysisData(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}

bool CDM_GENTreatmentManagementEventHandler::doGenHeatScheduleUpdate(CEventMessage& evMessage)
{

  copyDataEventData(evMessage);

  bool RetValue = CDM_GENDBManagerTask::getInstance()->getDBManager()->evHeatScheduleUpdate(evMessage);

  if ( RetValue ) 
  {
    //
	  // Just forward this event to respective destinations
    //
    evMessage.setMessage(EAF_EvMsg::evEAFHeatScheduleUpdate);
    dispatchEvent(evMessage);

    evMessage.setMessage(AOD_EvMsg::evAODHeatScheduleUpdate);
    dispatchEvent(evMessage);

    evMessage.setMessage(LF_EvMsg::evLFHeatScheduleUpdate);
    dispatchEvent(evMessage);

  }

  return RetValue;
}

bool CDM_GENTreatmentManagementEventHandler::doGenProductionOrderDataUpdate(CEventMessage& evMessage)
{
  //
	// Just forward this event to respective destinations
  //
  evMessage.setMessage(EAF_EvMsg::evEAFProductionOrderDataUpdate);
  dispatchEvent(evMessage);

  evMessage.setMessage(AOD_EvMsg::evAODProductionOrderDataUpdate);
  dispatchEvent(evMessage);

  evMessage.setMessage(LF_EvMsg::evLFProductionOrderDataUpdate);
  dispatchEvent(evMessage);

  return true;
}

bool CDM_GENTreatmentManagementEventHandler::checkEventAssignment(CEventMessage& Event)
{
  //
  // check if event could be assigned to existing product
  //

  // In the case of production management specific events, just bypass
  // the strict product idenfication check.
  //
  return true;
}
