// Copyright (C) 2011 SMS Siemag AG

#include "CEventMessage.h"
#include "CDM_GENHMIEventHandler.h"

#include "CDM_GENDBManagerTask.h"

#if defined (HANDLE_EVENT)
  #undef HANDLE_EVENT
#endif
#define HANDLE_EVENT(action) \
	if (HMI_EvMsg::ev##action == evMessage.getMessage()) \
           return do##action(evMessage);

CDM_GENHMIEventHandler::CDM_GENHMIEventHandler()
{
}

CDM_GENHMIEventHandler::~CDM_GENHMIEventHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

bool CDM_GENHMIEventHandler::handleEvent(CEventMessage& evMessage)
{
  HANDLE_EVENT( HMIHeatScheduleUpdate );
  HANDLE_EVENT( HMIProductionOrderDataUpdate );
  HANDLE_EVENT( HMISetUpOfHeat );  
  HANDLE_EVENT( HMIResetOfHeat );  
  HANDLE_EVENT( HMISteelGradeDataUpdate );
  HANDLE_EVENT( HMIRequestPlanningData );
  HANDLE_EVENT( HMIRequestHeatSchedule );

	return false;
}

bool CDM_GENHMIEventHandler::doHMIHeatScheduleUpdate(CEventMessage& evMessage)
{
	//sankar
	doDataEvent(evMessage);
	return true;

  //copyDataEventData(evMessage);
  //bool RetValue = CDM_GENDBManagerTask::getInstance()->getDBManager()->evHeatScheduleUpdate(evMessage);

  //if ( RetValue ) 
  //{
  //  doDataEvent(evMessage);
  //}
  //return RetValue;
}

bool CDM_GENHMIEventHandler::doHMIProductionOrderDataUpdate(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}

bool CDM_GENHMIEventHandler::doHMISetUpOfHeat(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}

bool CDM_GENHMIEventHandler::doHMIResetOfHeat(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}


bool CDM_GENHMIEventHandler::doHMISteelGradeDataUpdate(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}

bool CDM_GENHMIEventHandler::doHMIRequestPlanningData(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}
bool CDM_GENHMIEventHandler::doHMIRequestHeatSchedule(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}



bool CDM_GENHMIEventHandler::checkEventAssignment(CEventMessage& Event)
{
  //
  // check if event could be assigned to existing product
  //

  // In the case of event HMI_PRODUCTION_ORDER_DATA_UPDATE, just bypass
  // the strict product idenfication check.
  //
  return true;
}
