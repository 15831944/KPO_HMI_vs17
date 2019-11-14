// Copyright (C) 1991 - 1999 Rational Software Corporation

#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_EventLogFrameController.h"
#include "CDM_DataInterface_Impl.h"

#include "CIntfData.h"

#include "CDM_GENDBManagerTask.h"

#include "CDM_GENMaterialEventHandler.h"




CDM_GENMaterialEventHandler::~CDM_GENMaterialEventHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

CDM_GENMaterialEventHandler::CDM_GENMaterialEventHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}


bool CDM_GENMaterialEventHandler::handleEvent(CEventMessage& evMessage)
{
  if (BOF_EvMsg::evBOFScrapChuteRequest == evMessage.getMessage())
    return doScrapChuteRequest(evMessage);

  if (BOF_EvMsg::evBOFHotMetalLadleRequest == evMessage.getMessage())
    return doHotMetalLadleRequest(evMessage);
	
	return false;
}

//handle scrap loading instructions request from L1, this can concern more than one unit and must be handled here
bool CDM_GENMaterialEventHandler::doScrapChuteRequest(CEventMessage& Event)
{
  try
  {
    log("++++++ CDM_GENMaterialEventHandler::doScrapChuteRequest",3);

    if( checkEventAssignment(Event) )
    {
      if ( copyDataEventData(Event) )
      {
        if (CDM_GENDBManagerTask::getInstance()->getDBManager()->evScrapChuteRequest(Event))
        {
          beforeDispatchEvent(Event);

          CEventHandler::dispatchEvent("TSM_GEN","DH_L1_BOF_1_OUT",Event);

          afterDispatchEvent(Event);
        }
      }
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"Unknown exception.","CDM_GENMaterialEventHandler::doScrapChuteRequest()"," - ");
  }

  return true; //we handled the event
}//bool CDM_GENMaterialEventHandler::doScrapChuteRequest(CEventMessage& Event)


//handle hot metal loading instructions request from L1, this can concern more than one unit and must be handled here
bool CDM_GENMaterialEventHandler::doHotMetalLadleRequest(CEventMessage& Event)
{
  try
  {
    log("++++++ CDM_GENMaterialEventHandler::doHotMetalLadleRequest",3);

    if (checkEventAssignment(Event))
    {
      if (copyDataEventData(Event))
      {
        if (CDM_GENDBManagerTask::getInstance()->getDBManager()->evHotMetalLadleRequest(Event))
        {
          beforeDispatchEvent(Event);

          CEventHandler::dispatchEvent("TSM_GEN","DH_L1_BOF_1_OUT",Event);

          afterDispatchEvent(Event);
        }
      }
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"Unknown","CDM_GENMaterialEventHandler::doHotMetalLadleRequest()"," - ");
  }

  return true; //we handled the event
}//bool CDM_GENMaterialEventHandler::doHotMetalLadleRequest(CEventMessage& Event)