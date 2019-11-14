// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_EAFANALYSISEVENTHANDLER_412F1263039C_INCLUDED
#define _INC_CDM_EAFANALYSISEVENTHANDLER_412F1263039C_INCLUDED

#include "CDM_EAFEventHandler.h"

#include "CDM_AnalysisEventHandler.h"


class CDM_EAFAnalysisEventHandler : public CDM_AnalysisEventHandler
  
{
public:
	//This hook operation would be called automatically by 
	//handleEvent( FRISEVENT &event) 
	//when an event is received. And this operation must be 
	//implemented by the user or client
	//in order to use it.
	virtual bool handleEvent(CEventMessage& evMessage);

	virtual ~CDM_EAFAnalysisEventHandler();

	CDM_EAFAnalysisEventHandler();

	bool doEAFSteelAnalysisReceived(CEventMessage& Event);

	bool doEAFSlagAnalysisReceived(CEventMessage& Event);

	bool doEAFSteelSampleTaken(CEventMessage& Event);

	bool doEAFSlagSampleTaken(CEventMessage& Event);

  bool doOnUnknownProduct(CEventMessage& Event);

};

#endif /* _INC_CDM_EAFANALYSISEVENTHANDLER_412F1263039C_INCLUDED */
