// Copyright (C) 2011 SMS Siemag AG

#include "iEventMessages_s.hh"
#include "CLFAnalysisEventHandler.h"

//##ModelId=462767AE01DE
CLFAnalysisEventHandler::CLFAnalysisEventHandler(CModelTask* pModelTask)
: CLFEventHandler(pModelTask)
{
  LFAnalysisHandlingWrapper.setpModelTask(pModelTask);
}

//##ModelId=4118B86001D0
bool CLFAnalysisEventHandler::handleEvent( CEventMessage& EventMessage)
{
  bool RetValue = true;
  
  if ( checkProductAcceptance(EventMessage) ) 
  {
    std::string Message = EventMessage.getMessage();

    if ( LF_EvMsg::evLFSlagAnalysisReceived == Message )
    { 
      LFAnalysisHandlingWrapper.doOnSlagAnalysisReceived(EventMessage);      
    } 
    else if (LF_EvMsg::evLFSteelAnalysisReceived == Message) 
    { 
      LFAnalysisHandlingWrapper.doOnSteelAnalysisReceived(EventMessage);      
    } 
    else if (LF_EvMsg::evLFSlagSampleTaken == Message) 
    { 
      LFAnalysisHandlingWrapper.doOnSlagSampleTaken(EventMessage);      
    } 
    else if (LF_EvMsg::evLFSteelSampleTaken == Message) 
    { 
      LFAnalysisHandlingWrapper.doOnSteelSampleTaken(EventMessage);      
    }
    else
      RetValue = false; 
  }
  else
    RetValue = false; 

  return RetValue;
}
