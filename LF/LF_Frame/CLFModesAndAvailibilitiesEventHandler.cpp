// Copyright (C) 2011 SMS Siemag AG

#include "iEventMessages_s.hh"
#include "CLFModesAndAvailibilitiesEventHandler.h"

//##ModelId=462767AB008C
CLFModesAndAvailibilitiesEventHandler::CLFModesAndAvailibilitiesEventHandler(CModelTask* pModelTask)
: CLFEventHandler(pModelTask)
{
  LFModesAndAvailibilitiesWrapper.setpModelTask(pModelTask);
}


//##ModelId=4118B8BF0227
bool CLFModesAndAvailibilitiesEventHandler::handleEvent( CEventMessage& EventMessage)
{
  bool RetValue = true;
  
  // calling respective model wrapper functions
  if ( checkProductAcceptance(EventMessage) ) 
  {    
    std::string Message = EventMessage.getMessage();

    if ( LF_EvMsg::evLFSetComputerMode == Message )
    { 
      LFModesAndAvailibilitiesWrapper.doOnSetComputerMode(EventMessage);
    } 
    else
      RetValue = false; 
  }
  else
    RetValue = false; 

  return RetValue;
}
