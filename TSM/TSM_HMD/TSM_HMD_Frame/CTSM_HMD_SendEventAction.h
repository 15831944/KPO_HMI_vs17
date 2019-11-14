// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTSM_HMD_SENDEVENTACTION_INCLUDED
#define _INC_CTSM_HMD_SENDEVENTACTION_INCLUDED

#include "CEventMessage.h"
#include "IAction.h"

//##ModelId=45A21C630353
class CTSM_HMD_SendEventAction 
: public IAction
{
protected:
	//##ModelId=45A226FD01F4
	CEventMessage m_eventMessage;

	//Delay time after the event will be sent
	//##ModelId=45A21E8D0335
	long m_delay;

public:
	//This operation executes the action of the action 
	//object. It must be overwritten to provide specialized 
	//action behaviour in derived classes.
	//##ModelId=45A21E8D034D
	virtual void execute(CTrackingObject* pObjectForAction);

	//##ModelId=45A21E8D036B
	CTSM_HMD_SendEventAction(const std::string& eventSender, const std::string& eventReceiver, const std::string& eventMessage, bool isPlantEvent, long delay);
};

#endif /* _INC_CTSM_HMD_SENDEVENTACTION_413DA516013B_INCLUDED */
