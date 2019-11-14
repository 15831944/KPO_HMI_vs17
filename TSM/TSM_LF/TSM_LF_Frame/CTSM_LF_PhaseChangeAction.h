// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTSM_LF_PHASECHANGEACTION_434A243D0120_INCLUDED
#define _INC_CTSM_LF_PHASECHANGEACTION_434A243D0120_INCLUDED

#include "CTsmPhaseChangeAction.h"

class CTSM_LF_PhaseChangeAction 
: public CTsmPhaseChangeAction
{
public:
	virtual ~CTSM_LF_PhaseChangeAction();

	CTSM_LF_PhaseChangeAction();

	static std::string relatedEventName;

	//This operation executes the action of the action 
	//object. It must be overwritten to provide specialized 
	//action behaviour in derived classes.
	virtual void execute(CTrackingObject* pObjectForAction);
};

#endif /* _INC_CTSM_LF_PHASECHANGEACTION_434A243D0120_INCLUDED */
