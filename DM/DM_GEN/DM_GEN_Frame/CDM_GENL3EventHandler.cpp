// Copyright (C) 2011 SMS Siemag AG

#include "CEventMessage.h"
#include "CDM_GENL3EventHandler.h"

#include "CDM_GENDBManagerTask.h"

#if defined (HANDLE_EVENT)
  #undef HANDLE_EVENT
#endif
#define HANDLE_EVENT(action) \
	if (L3_EvMsg::ev##action == evMessage.getMessage()) \
           return do##action(evMessage);


CDM_GENL3EventHandler::CDM_GENL3EventHandler()
{
}

CDM_GENL3EventHandler::~CDM_GENL3EventHandler()
{
}

bool CDM_GENL3EventHandler::handleEvent(CEventMessage& evMessage)
{
  HANDLE_EVENT( L3FacilityMaintSchedule );
  HANDLE_EVENT( L3HeatScheduleUpdate );
  HANDLE_EVENT( L3ProductionOrderDataUpdate );
  //HANDLE_EVENT( L3SteelGradeDataUpdate );
  HANDLE_EVENT( L3UndefinedGradeRequest );

  HANDLE_EVENT( L3SteelGradeCodeDefinitionUpdate );
  HANDLE_EVENT( L3DelayCodeUpdate );
  HANDLE_EVENT( L3MaterialCodeUpdate );
  HANDLE_EVENT( L3FacilityStatusRequest );

  HANDLE_EVENT( L3OpenDelaysRequest );
  HANDLE_EVENT( L3CurrentHeatStatusRequest );
  HANDLE_EVENT( L3HeatReportsRequest );
  HANDLE_EVENT( L3ProductionOrderChanged );
  return false;
}

bool CDM_GENL3EventHandler::doL3SteelGradeCodeDefinitionUpdate(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}
bool CDM_GENL3EventHandler::doL3DelayCodeUpdate(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}
bool CDM_GENL3EventHandler::doL3MaterialCodeUpdate(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}
bool CDM_GENL3EventHandler::doL3FacilityStatusRequest(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}

bool CDM_GENL3EventHandler::doL3FacilityMaintSchedule(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}

bool CDM_GENL3EventHandler::doL3HeatScheduleUpdate(CEventMessage& evMessage)
{
	//sankar schedule updation is handled in DH_L3_IN
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

bool CDM_GENL3EventHandler::doL3ProductionOrderDataUpdate(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}

bool CDM_GENL3EventHandler::doL3SteelGradeDataUpdate(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}

bool CDM_GENL3EventHandler::doL3UndefinedGradeRequest(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}

bool CDM_GENL3EventHandler::doL3OpenDelaysRequest(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}

bool CDM_GENL3EventHandler::doL3CurrentHeatStatusRequest(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}

bool CDM_GENL3EventHandler::doL3HeatReportsRequest(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}

bool CDM_GENL3EventHandler::doL3ProductionOrderChanged(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}


bool CDM_GENL3EventHandler::checkEventAssignment(CEventMessage& Event)
{
  //
  // check if event could be assigned to existing product
  //

  //
  // In the case of L3 specific events, just bypass
  // the strict product idenfication check.
  //
  return true;
}
