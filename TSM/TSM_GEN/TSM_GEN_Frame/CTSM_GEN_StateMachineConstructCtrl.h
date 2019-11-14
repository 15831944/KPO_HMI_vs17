// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTSM_GEN_STATEMACHINECONSTRUCTCTRL_4124B602023D_INCLUDED
#define _INC_CTSM_GEN_STATEMACHINECONSTRUCTCTRL_4124B602023D_INCLUDED

#include "CTsmStateMachineConstructCtrl.h"

class CTSM_GEN_StateMachineConstructCtrl 
: public CTsmStateMachineConstructCtrl
{
public:
	//This function creates a send message action object for 
	//product messages. It has to be overwritten to adapt the 
	//state machine software to a given automization project.
	//
	//Return value
	//==========
	//Created action object that sends strip event messages
	IAction* createSendProductMessageAction(const std::string & eventMessageString, const std::string & eventReceiverName, long timeOffsetSeconds) const;

  IAction* createSendPlantMessageAction(const std::string & eventMessageString, const std::string & eventReceiverName, long timeOffsetSeconds) const;

	CTSM_GEN_StateMachineConstructCtrl();

	std::string getEventSenderName();

	std::string getConstructionFileName();

};

#endif /* _INC_CTSM_GEN_STATEMACHINECONSTRUCTCTRL_4124B602023D_INCLUDED */
