// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_GENPURPOSEEVENTHANDLER_412F15AD02D5_INCLUDED
#define _INC_CDM_GENPURPOSEEVENTHANDLER_412F15AD02D5_INCLUDED

#include "CDM_GENEventHandler.h"

class CDM_GENPurposeEventHandler 
: public CDM_GENEventHandler
{
public:
	CDM_GENPurposeEventHandler();

	virtual ~CDM_GENPurposeEventHandler();

	//This hook operation would be called automatically by 
	//handleEvent( FRISEVENT &event) 
	//when an event is received. And this operation must be 
	//implemented by the user or client
	//in order to use it.
	virtual bool handleEvent(CEventMessage& evMessage);

};

#endif /* _INC_CDM_GENPURPOSEEVENTHANDLER_412F15AD02D5_INCLUDED */
