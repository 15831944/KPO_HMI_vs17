// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTSM_EAF_PHASECHANGEACTION_4353BAB401EC_INCLUDED
#define _INC_CTSM_EAF_PHASECHANGEACTION_4353BAB401EC_INCLUDED

#include "CTsmPhaseChangeAction.h"
class CTSM_EAF_PhaseChangeAction 
: public CTsmPhaseChangeAction
{
public:
	static std::string relatedEventName;

	//This operation executes the action of the action 
	//object. It must be overwritten to provide specialized 
	//action behaviour in derived classes.
	virtual void execute(CTrackingObject* pObjectForAction);

	virtual ~CTSM_EAF_PhaseChangeAction();

	CTSM_EAF_PhaseChangeAction();

};

#endif /* _INC_CTSM_EAF_PHASECHANGEACTION_4353BAB401EC_INCLUDED */
