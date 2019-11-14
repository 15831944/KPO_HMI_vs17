// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTSM_HMD_PHASECHANGEACTION_INCLUDED
#define _INC_CTSM_HMD_PHASECHANGEACTION_INCLUDED

#include "CTsmPhaseChangeAction.h"

//##ModelId=45A21C530287
class CTSM_HMD_PhaseChangeAction 
: public CTsmPhaseChangeAction
{
public:
	//##ModelId=45A21E8E0010
	virtual ~CTSM_HMD_PhaseChangeAction();

	//##ModelId=45A21E8E001A
	CTSM_HMD_PhaseChangeAction();

	//##ModelId=45A21E8E0024
	static std::string relatedEventName;

	//This operation executes the action of the action 
	//object. It must be overwritten to provide specialized 
	//action behaviour in derived classes.
	//##ModelId=45A21E8E002F
	virtual void execute(CTrackingObject* pObjectForAction);
};

#endif /* _INC_CTSM_HMD_PHASECHANGEACTION_434A243D0120_INCLUDED */
