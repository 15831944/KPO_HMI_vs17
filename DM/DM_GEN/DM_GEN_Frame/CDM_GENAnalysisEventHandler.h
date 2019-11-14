// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_GENANALYSISEVENTHANDLER_412F1263039C_INCLUDED
#define _INC_CDM_GENANALYSISEVENTHANDLER_412F1263039C_INCLUDED

#include "CDM_AnalysisEventHandler.h"


class CDM_GENAnalysisEventHandler : public CDM_AnalysisEventHandler
  
{
public:
	//This hook operation would be called automatically by 
	//handleEvent( FRISEVENT &event) 
	//when an event is received. And this operation must be 
	//implemented by the user or client
	//in order to use it.
	virtual bool handleEvent(CEventMessage& evMessage);

	virtual ~CDM_GENAnalysisEventHandler();

	CDM_GENAnalysisEventHandler();

	bool doHMPTempMeasurement(CEventMessage& Event);

	bool doHMPAnalysisReceived(CEventMessage& Event);

	bool checkEventAssignment(CEventMessage& Event);

  bool doCCSAnalysisReceived(CEventMessage& Event);
};

#endif /* _INC_CDM_GENANALYSISEVENTHANDLER_412F1263039C_INCLUDED */
