// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTSM_GEN_HEATTRACKINGACTION_4368F72500AF_INCLUDED
#define _INC_CTSM_GEN_HEATTRACKINGACTION_4368F72500AF_INCLUDED

#include <string>
#include "IAction.h"

class CGC_HEAT_STAT;

class CTSM_GEN_HeatTrackingAction 
: public IAction
{
public:
	static std::string relatedEventName;

	//This operation executes the action of the action 
	//object. It must be overwritten to provide specialized 
	//action behaviour in derived classes.
	virtual void execute(CTrackingObject* pObjectForAction);

	CTSM_GEN_HeatTrackingAction();

	//Store the previous state to indicate transition from-> 
	//to for the product
	static std::map<std::string,std::string> PreviousStates;
protected:
	//If we have databse access we will use the descriptions 
	//instead of the pure state names
	static bool isDataBaseAccess;


	//Stores the status code and description read from table 
	//CGC_HEAT_STAT
	static std::map<std::string,std::string> StateDescriptions;

	void initialize();

};

#endif /* _INC_CTSM_GEN_HEATTRACKINGACTION_4368F72500AF_INCLUDED */
