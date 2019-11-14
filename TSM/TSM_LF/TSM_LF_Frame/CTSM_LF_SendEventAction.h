// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTSM_LF_SENDEVENTACTION_413DA516013B_INCLUDED
#define _INC_CTSM_LF_SENDEVENTACTION_413DA516013B_INCLUDED

#include "CEventMessage.h"
#include "IAction.h"

class CTSM_LF_SendEventAction 
: public IAction
{
protected:
	CEventMessage m_eventMessage;

	//Delay time after the event will be sent
	long m_delay;

public:
	//This operation executes the action of the action 
	//object. It must be overwritten to provide specialized 
	//action behaviour in derived classes.
	virtual void execute(CTrackingObject* pObjectForAction);

	CTSM_LF_SendEventAction(const std::string& eventSender, const std::string& eventReceiver, const std::string& eventMessage, bool isPlantEvent, long delay);
};

#endif /* _INC_CTSM_LF_SENDEVENTACTION_413DA516013B_INCLUDED */
