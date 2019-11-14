// Copyright (C) 2011 SMS Siemag AG

#include "CDM_LFTask.h"
#include "CDM_LFAnalysisEventHandler.h"

CDM_LFAnalysisEventHandler::~CDM_LFAnalysisEventHandler()
{
  // ToDo: Add your specialized code here and/or call the base class
}

CDM_LFAnalysisEventHandler::CDM_LFAnalysisEventHandler()
: CDM_AnalysisEventHandler(CDM_LFTask::getInstance())
{
  // ToDo: Add your specialized code here and/or call the base class
}

bool CDM_LFAnalysisEventHandler::handleEvent(CEventMessage& evMessage)
{
  HANDLE_EVENT(LFSteelAnalysisReceived);
  HANDLE_EVENT(LFSteelSampleTaken);
  HANDLE_EVENT(LFSlagAnalysisReceived);
  HANDLE_EVENT(LFSlagSampleTaken);

  return false;
}

bool CDM_LFAnalysisEventHandler::doLFSteelAnalysisReceived(CEventMessage& Event)
{  
  bool RetValue = false;
  
  copyDataEventData(Event);
  
  if(CDM_LFDBManagerTask::getInstance()->getDBManager()->evSteelAnalysisReceived(Event))
  {
    RetValue = doSteelAnalysisReceived( Event );
  }

  return RetValue;
}

bool CDM_LFAnalysisEventHandler::doLFSlagAnalysisReceived(CEventMessage& Event)
{
  bool RetValue = false;

  copyDataEventData(Event);

  if(CDM_LFDBManagerTask::getInstance()->getDBManager()->evSlagAnalysisReceived(Event))
  {
    RetValue = doSlagAnalysisReceived( Event );
  }

  return RetValue;
}

bool CDM_LFAnalysisEventHandler::doLFSteelSampleTaken(CEventMessage& Event)
{
  bool RetValue = false;

  RetValue = doSteelSampleTaken( Event );

  return RetValue;
}

bool CDM_LFAnalysisEventHandler::doLFSlagSampleTaken(CEventMessage& Event)
{
  bool RetValue = false;

  RetValue = doSlagSampleTaken( Event );

  return RetValue;
}

bool CDM_LFAnalysisEventHandler::doOnUnknownProduct(CEventMessage& Event)
{
  // send event to tsm to add product and be able to pass all product events
  CEventMessage NewEvent(Event);

  NewEvent.setMessage(LF_EvMsg::evLFTsmCreateProduct);

  return dispatchEvent(NewEvent);
}
