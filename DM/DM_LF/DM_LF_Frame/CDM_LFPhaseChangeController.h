// Copyright (C) 2004 SMS Demag AG, Germany

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_LFPHASECHANGECONTROLLER_434501A403A5_INCLUDED
#define _INC_CDM_LFPHASECHANGECONTROLLER_434501A403A5_INCLUDED

#include "CDM_PhaseChangeController.h"

class CDM_LFPhaseChangeController 
: public CDM_PhaseChangeController
{
public:
	virtual bool handleEvent(CEventMessage& evMessage);

	virtual ~CDM_LFPhaseChangeController();

	CDM_LFPhaseChangeController();

protected:
	//Check if an event independend phase transition is to be 
	//done. Return true if a phase change was made, no 
	//further investigation about event based transitions is 
	//to be done.
	virtual bool performForcedPhaseChange(std::string& newPhase);

	//Dirceting Task relevant programming outputs to 
	//cCBS_StdLog_Task depending on Task Trace Level.
	virtual void log(const std::string& Message, long Level);

	//Creates product independend transition rules
	virtual void init();

};

#endif /* _INC_CDM_LFPHASECHANGECONTROLLER_434501A403A5_INCLUDED */
