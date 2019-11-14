// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTSMSENDEVENTACTION_41052DFA003D_INCLUDED
#define _INC_CTSMSENDEVENTACTION_41052DFA003D_INCLUDED

#include "CEventMessage.h"
#include "IAction.h"

class CTsmSendEventAction 
: public IAction
{
protected:
	//Delay time after the event will be sent
	long m_delay;

	CEventMessage m_eventMessage;

public:
	//This operation executes the action of the action 
	//object. It must be overwritten to provide specialized 
	//action behaviour in derived classes.
	virtual void execute(CTrackingObject* pObjectForAction);

	CTsmSendEventAction(const std::string & eventSender, const std::string& eventReceiver, const std::string& eventMessage, bool isPlantEvent, long delay);

};

#endif /* _INC_CTSMSENDEVENTACTION_41052DFA003D_INCLUDED */
