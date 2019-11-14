// Copyright (C) 2011 SMS Siemag AG

#include <string>
#include "CDM_EAFTask.h"
#include "CDM_EAFEventHandler.h"


CDM_EAFEventHandler::CDM_EAFEventHandler()
:CDM_EventHandler(CDM_EAFTask::getInstance())
{
}

CDM_EAFEventHandler::~CDM_EAFEventHandler()
{
}


bool CDM_EAFEventHandler::doOnUnknownProduct(CEventMessage& Event)
{
  // send event to tsm to add product and be able to pass all product events
  CEventMessage NewEvent(Event);

  NewEvent.setMessage(EAF_EvMsg::evEAFTsmCreateProduct);

  return dispatchEvent(NewEvent);;
}



