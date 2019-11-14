// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_LFMODELRESULTEVENTHANDLER_416E994C0136_INCLUDED
#define _INC_CDM_LFMODELRESULTEVENTHANDLER_416E994C0136_INCLUDED

#include "CDM_EventHandler.h"
#include "CDM_LFEventHandler.h"

class CDM_LFModelResultEventHandler 
: public CDM_LFEventHandler
{
public:
	bool doLFModelResultActualSetpointsOffline(CEventMessage& Event);
	bool doLFModelResultCodeOffline(CEventMessage& Event);
	bool doLFModelResultRecipeSetpointsOffline(CEventMessage& Event);
	bool doLFModelResultOffline(CEventMessage& Event);
	bool doLFHeatAnnounceStatusOffline(CEventMessage& Event);

	virtual bool handleEvent(CEventMessage& evMessage);

	bool doLFHeatAnnounceStatus(CEventMessage& Event);

	CDM_LFModelResultEventHandler();

	virtual ~CDM_LFModelResultEventHandler();

	bool doLFModelResult(CEventMessage& Event);

	bool doLFModelResultActualSetpoints(CEventMessage& Event);

	bool doLFModelResultCode( CEventMessage& Event);

	bool doLFModelResultRecipeSetpoints( CEventMessage& Event);

};

#endif /* _INC_CDM_LFMODELRESULTEVENTHANDLER_416E994C0136_INCLUDED */
