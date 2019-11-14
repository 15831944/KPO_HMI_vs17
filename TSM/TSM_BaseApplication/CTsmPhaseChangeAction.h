// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTSMPHASECHANGEACTION_434A22150248_INCLUDED
#define _INC_CTSMPHASECHANGEACTION_434A22150248_INCLUDED

#include "IAction.h"

class CTsmPhaseChangeAction 
: public IAction
{
protected:
public:
	//This extension to create an unique productID for the 
	//PHASETRACKER, e.g. productID::PT
	static const std::string ProductIdExtension;

	//Store the previous state to indicate transition from-> 
	//to for the product
	static std::map<std::string,std::string> PreviousStates;

};

#endif /* _INC_CTSMPHASECHANGEACTION_434A22150248_INCLUDED */
