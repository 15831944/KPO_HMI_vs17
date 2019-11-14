// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTSMSTATEMACHINECONSTRUCTCTRL_41052BA70082_INCLUDED
#define _INC_CTSMSTATEMACHINECONSTRUCTCTRL_41052BA70082_INCLUDED

#include "CStateMachineFileConstructCtrl.h"

class CTsmStateMachineConstructCtrl 
: public CStateMachineFileConstructCtrl
{
public:
	//This function creates a send message action object for 
	//plant messages. It has to be overwritten to adapt the 
	//state machine software to a given automization project.
	//
	//Return value
	//==========
	//Created action object that sends plant event messages
	virtual IAction* createSendPlantMessageAction(const std::string & eventMessageString, const std::string & eventReceiverName, long timeOffsetSeconds) const;

	//This function creates a send message action object for 
	//product messages. It has to be overwritten to adapt the 
	//state machine software to a given automization project.
	//
	//Return value
	//==========
	//Created action object that sends strip event messages
	virtual IAction* createSendProductMessageAction(const std::string & eventMessageString, const std::string & eventReceiverName, long timeOffsetSeconds) const;

	virtual std::string getEventSenderName();

	virtual std::string getConstructionFileName();

	//This function creates a action that calls the state 
	//machine for a given event
	virtual IAction* createCallStateMachineActionPlant(CStateMachine* pStateMachine, const std::string& eventMessage) const;

	//This function creates a action that calls the state 
	//machine for a given event
	virtual IAction* createCallStateMachineActionProduct(CStateMachine* pStateMachine, const std::string& eventMessage) const;


	CTsmStateMachineConstructCtrl();
  
  CTsmStateMachineConstructCtrl(std::string ConstructionFileName);

protected:
	std::string m_EventSenderName;

};

#endif /* _INC_CTSMSTATEMACHINECONSTRUCTCTRL_41052BA70082_INCLUDED */
