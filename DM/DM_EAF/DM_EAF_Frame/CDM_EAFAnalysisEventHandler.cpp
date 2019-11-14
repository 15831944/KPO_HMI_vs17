// Copyright (C) 2011 SMS Siemag AG

#include "CDM_EAFTask.h"
#include "CDM_EAFDBManagerTask.h"
#include "CDM_EAFAnalysisEventHandler.h"

CDM_EAFAnalysisEventHandler::~CDM_EAFAnalysisEventHandler()
{
}

CDM_EAFAnalysisEventHandler::CDM_EAFAnalysisEventHandler()
: CDM_AnalysisEventHandler(CDM_EAFTask::getInstance())
{
}

bool CDM_EAFAnalysisEventHandler::handleEvent(CEventMessage& evMessage)
{
  HANDLE_EVENT(EAFSteelAnalysisReceived);
  HANDLE_EVENT(EAFSteelSampleTaken);
  HANDLE_EVENT(EAFSlagAnalysisReceived);
  HANDLE_EVENT(EAFSlagSampleTaken);

  return false;
}

bool CDM_EAFAnalysisEventHandler::doEAFSteelAnalysisReceived(CEventMessage& Event)
{

  bool RetValue = false;
  
  copyDataEventData(Event);

  if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evSteelAnalysisReceived(Event))
  {
    RetValue = doSteelAnalysisReceived( Event );
  }

  return RetValue;
}

bool CDM_EAFAnalysisEventHandler::doEAFSlagAnalysisReceived(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_EAFDBManagerTask::getInstance()->getDBManager()->evSlagAnalysisReceived(Event))
  {
    RetValue = doSlagAnalysisReceived( Event );
  }

  return RetValue;
}

bool CDM_EAFAnalysisEventHandler::doEAFSteelSampleTaken(CEventMessage& Event)
{
  bool RetValue = false;
  
  RetValue = doSteelSampleTaken( Event );
  
  return RetValue;
}

bool CDM_EAFAnalysisEventHandler::doEAFSlagSampleTaken(CEventMessage& Event)
{
  bool RetValue = false;
  
  RetValue = doSlagSampleTaken( Event );
  
  return RetValue;
}

bool CDM_EAFAnalysisEventHandler::doOnUnknownProduct(CEventMessage& Event)
{
  // send event to tsm to add product and be able to pass all product events
  CEventMessage NewEvent(Event);

  NewEvent.setMessage(EAF_EvMsg::evEAFTsmCreateProduct);

  return dispatchEvent(NewEvent);;
}