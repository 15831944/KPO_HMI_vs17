// Copyright (C) 2004 SMS Demag AG

#include <string>
#include "CDM_LFTask.h"
#include "CDM_LFEventHandler.h"

CDM_LFEventHandler::CDM_LFEventHandler()
:CDM_EventHandler(CDM_LFTask::getInstance())
{
}

CDM_LFEventHandler::~CDM_LFEventHandler()
{
}

bool CDM_LFEventHandler::doOnUnknownProduct(CEventMessage& Event)
{
  // send event to tsm to add product and be able to pass all product events
  CEventMessage NewEvent(Event);

  NewEvent.setMessage(LF_EvMsg::evLFTsmCreateProduct);

  return dispatchEvent(NewEvent);;
}
