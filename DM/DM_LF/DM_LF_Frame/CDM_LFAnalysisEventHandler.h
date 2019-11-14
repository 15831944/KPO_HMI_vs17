// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_LFANALYSISEVENTHANDLER_412F1263039C_INCLUDED
#define _INC_CDM_LFANALYSISEVENTHANDLER_412F1263039C_INCLUDED

#include "CDM_LFEventHandler.h"
#include "CDM_AnalysisEventHandler.h"


class CDM_LFAnalysisEventHandler
: public CDM_AnalysisEventHandler
{
public:
	virtual bool handleEvent(CEventMessage& evMessage);

	virtual ~CDM_LFAnalysisEventHandler();

	CDM_LFAnalysisEventHandler();

	bool doLFSteelAnalysisReceived(CEventMessage& Event);

	bool doLFSlagAnalysisReceived(CEventMessage& Event);

	bool doLFSteelSampleTaken(CEventMessage& Event);

	bool doLFSlagSampleTaken(CEventMessage& Event);

  // overloaded here to sent event LFSetUpOfHeat to create product in TSM
  bool doOnUnknownProduct(CEventMessage& Event);
};

#endif /* _INC_CDM_LFANALYSISEVENTHANDLER_412F1263039C_INCLUDED */
