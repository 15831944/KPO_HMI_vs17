// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_ANALYSISEVENTHANDLER_41C7FC650330_INCLUDED
#define _INC_CDM_ANALYSISEVENTHANDLER_41C7FC650330_INCLUDED

#include "CDM_EventHandler.h"

class CDM_Task;

class CDM_AnalysisEventHandler 
: public CDM_EventHandler
{
public:
	virtual ~CDM_AnalysisEventHandler();

	CDM_AnalysisEventHandler(CDM_Task* pDMTask);

	virtual bool doSteelAnalysisReceived(CEventMessage& Event);

	virtual bool doSlagAnalysisReceived(CEventMessage& Event);

	virtual bool doSteelSampleTaken(CEventMessage& Event);

	virtual bool doSlagSampleTaken(CEventMessage& Event);

protected:
	bool doOnSampleEvent(CEventMessage& Event);

	//This is a helper member function to be called 
	//internally  by all Analysis-related event handlers.
	bool doOnAnalysisEvent(CEventMessage& Event);

};

#endif /* _INC_CDM_ANALYSISEVENTHANDLER_41C7FC650330_INCLUDED */
