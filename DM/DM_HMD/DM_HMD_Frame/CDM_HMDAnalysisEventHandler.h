#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_HMDANALYSISEVENTHANDLER_412F1263039C_INCLUDED
#define _INC_CDM_HMDANALYSISEVENTHANDLER_412F1263039C_INCLUDED

#include "CDM_AnalysisEventHandler.h"

class CDM_HMDAnalysisEventHandler : public CDM_AnalysisEventHandler
  
{
public:
	virtual bool handleEvent(CEventMessage& evMessage);
	virtual ~CDM_HMDAnalysisEventHandler();
	CDM_HMDAnalysisEventHandler();
	bool doHMDSlagAnalysisReceived(CEventMessage& Event);
	bool doHMDSlagSampleTaken(CEventMessage& Event);
	bool doHMDHotMetalSampleTaken(CEventMessage& Event);
	bool doHMDHotMetalAnalysisReceived(CEventMessage& Event);

};

#endif
