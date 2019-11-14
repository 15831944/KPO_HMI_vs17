// Copyright (C) 2011 SMS Siemag AG

#include <string>
#include "iSMC_DataDefinitions_s.hh"
#include "cCBS_StdInitBase.h"
#include "CDM_GENTask.h"
#include "CDM_GENEventHandler.h"

CDM_GENEventHandler::CDM_GENEventHandler()
:CDM_EventHandler(CDM_GENTask::getInstance())
{
}

CDM_GENEventHandler::~CDM_GENEventHandler()
{
}

bool CDM_GENEventHandler::checkEventAssignment(CEventMessage& Event)
{
  //default is to do nothing and accept the event for DM GEN
	return true;
}


bool CDM_GENEventHandler::doOnUnknownProduct(CEventMessage& Event)
{
  return false;
}



