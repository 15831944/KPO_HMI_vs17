// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTSM_HMD_STATEMACHINECONSTRUCTCTRL_INCLUDED
#define _INC_CTSM_HMD_STATEMACHINECONSTRUCTCTRL_INCLUDED

#include "CTsmStateMachineConstructCtrl.h"

//##ModelId=45A21C6E0123
class CTSM_HMD_StateMachineConstructCtrl 
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
	//##ModelId=45A21E8D02C1
	virtual IAction* createSendProductMessageAction(const std::string & eventMessageString, const std::string & eventReceiverName, long timeOffsetSeconds) const;

	//##ModelId=45A21E8D0310
	CTSM_HMD_StateMachineConstructCtrl();
};

#endif /* _INC_CTSM_HMD_STATEMACHINECONSTRUCTCTRL_4124B602023D_INCLUDED */
