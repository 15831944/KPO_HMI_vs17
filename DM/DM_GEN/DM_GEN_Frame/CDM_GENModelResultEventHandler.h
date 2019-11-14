// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_GENMODELRESULTEVENTHANDLER_416E994C0136_INCLUDED
#define _INC_CDM_GENMODELRESULTEVENTHANDLER_416E994C0136_INCLUDED

#include "CDM_GENEventHandler.h"

class CDM_GENModelResultEventHandler 
: public CDM_GENEventHandler
{
public:
	CDM_GENModelResultEventHandler();

	virtual ~CDM_GENModelResultEventHandler();

	//This hook operation would be called automatically by 
	//handleEvent( FRISEVENT &event) 
	//when an event is received. And this operation must be 
	//implemented by the user or client
	//in order to use it.
	virtual bool handleEvent(CEventMessage& evMessage);

	bool doGENModelResult(CEventMessage& Event);

	bool doGENModelResultActualSetpoints(CEventMessage& Event);

	bool doGENModelResultCode( CEventMessage& Event);

	bool doGENModelResultRecipeSetpoints( CEventMessage& Event);

};

#endif /* _INC_CDM_GENMODELRESULTEVENTHANDLER_416E994C0136_INCLUDED */
