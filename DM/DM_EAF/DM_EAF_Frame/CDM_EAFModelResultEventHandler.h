// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_EAFMODELRESULTEVENTHANDLER_416E994C0136_INCLUDED
#define _INC_CDM_EAFMODELRESULTEVENTHANDLER_416E994C0136_INCLUDED

#include "CDM_EAFEventHandler.h"

class CDM_EAFModelResultEventHandler 
: public CDM_EAFEventHandler
{
public:
	bool doEAFHeatAnnounceStatus(CEventMessage& Event);

	CDM_EAFModelResultEventHandler();

	virtual ~CDM_EAFModelResultEventHandler();

	//This hook operation would be called automatically by 
	//handleEvent( FRISEVENT &event) 
	//when an event is received. And this operation must be 
	//implemented by the user or client
	//in order to use it.
	virtual bool handleEvent(CEventMessage& evMessage);

	bool doEAFModelResult(CEventMessage& Event);

	bool doEAFModelResultActualSetpoints(CEventMessage& Event);

	bool doEAFModelResultCode( CEventMessage& Event);

	bool doEAFModelResultRecipeSetpoints( CEventMessage& Event);


};

#endif /* _INC_CDM_EAFMODELRESULTEVENTHANDLER_416E994C0136_INCLUDED */
