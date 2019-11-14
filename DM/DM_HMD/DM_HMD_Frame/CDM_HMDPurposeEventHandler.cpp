// Copyright (C) 2007 SMS Demag AG

#include "CDM_HMDPurposeEventHandler.h"
#include "CDM_HMDTask.h"

//##ModelId=45139A71039F
CDM_HMDPurposeEventHandler::CDM_HMDPurposeEventHandler()
{
}

//##ModelId=45139A7103A0
CDM_HMDPurposeEventHandler::~CDM_HMDPurposeEventHandler()
{
}

//##ModelId=45139A7103A2
bool CDM_HMDPurposeEventHandler::handleEvent(CEventMessage& evMessage)
{
	HANDLE_EVENT_DATA_FORWARD(HMD_EvMsg::evHMDHandleUpdatePurpose)

	return false;
}

