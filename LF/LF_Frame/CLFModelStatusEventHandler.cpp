// Copyright (C) 2011 SMS Siemag AG

#include "iEventMessages_s.hh"
#include "CLFModelStatusEventHandler.h"

//##ModelId=462767AE0057
CLFModelStatusEventHandler::CLFModelStatusEventHandler(CModelTask* pModelTask)
: CLFEventHandler(pModelTask)
{
  LFModelStatusWrapper.setpModelTask(pModelTask);
}


//##ModelId=41762D060229
bool CLFModelStatusEventHandler::handleEvent( CEventMessage& EventMessage)
{
  bool RetValue = true;
  
  // calling respective model wrapper functions
  if ( checkProductAcceptance(EventMessage) ) 
  {
          
    std::string Message = EventMessage.getMessage();

    if ( LF_EvMsg::evLFGetModelStatus == Message )
    { // LF_GET_MODEL_STATUS
      LFModelStatusWrapper.doOnGetModelStatus(EventMessage);      
    }
    else
      RetValue = false; // The event is not for this handler
  }
  else
    RetValue = false; // The event is not for this product

  return RetValue;
}
