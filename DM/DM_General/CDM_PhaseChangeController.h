// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_PHASECHANGECONTROLLER_4344FD8700C5_INCLUDED
#define _INC_CDM_PHASECHANGECONTROLLER_4344FD8700C5_INCLUDED

#include <string>
#include <map>
#include <set>

class CEventMessage;

class CDM_PhaseChangeController 
{
public:
	virtual bool handleEvent(CEventMessage& evMessage) = 0;

	virtual ~CDM_PhaseChangeController();

protected:
	void createTransitionRule(std::string prevState,  std::string  event, std::string targetState);

	virtual void log(const std::string& Message, long Level) = 0;

  std::map<std::string, std::string> m_TransitionRules;

	//Store the actual phase with key PorductID
	std::map<std::string,std::string>  m_ActualPhase;

	//Check if an event independend phase transition is to be 
	//done. Return true if a phase change was made, no 
	//further investigation about event based transitions is 
	//to be done.
	virtual bool performForcedPhaseChange(std::string &newPhase) = 0;

	//Creates product independend transition rules
	virtual void init() = 0;

	CDM_PhaseChangeController();

};

#endif /* _INC_CDM_PHASECHANGECONTROLLER_4344FD8700C5_INCLUDED */
