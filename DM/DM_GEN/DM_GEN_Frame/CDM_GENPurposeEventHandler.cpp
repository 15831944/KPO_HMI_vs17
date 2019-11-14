// Copyright (C) 1991 - 1999 Rational Software Corporation

#include "cCBS_StdEventLogFrameController.h"
#include "DM_Definitions.h"
#include "CDM_GENPurposeEventHandler.h"





CDM_GENPurposeEventHandler::CDM_GENPurposeEventHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

CDM_GENPurposeEventHandler::~CDM_GENPurposeEventHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

bool CDM_GENPurposeEventHandler::handleEvent(CEventMessage& evMessage)
{
	HANDLE_EVENT_DATA(GENHandleUpdatePurpose);
	
	return false;
}

