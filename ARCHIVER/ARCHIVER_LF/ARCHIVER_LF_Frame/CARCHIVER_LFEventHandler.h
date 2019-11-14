// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_LFEVENTHANDLER_414018470156_INCLUDED
#define _INC_CARCHIVER_LFEVENTHANDLER_414018470156_INCLUDED

#include "CARCHIVER_EventHandler.h"

#include "CARCHIVER_LFMaterialHandlingWrapper.h"
#include "CARCHIVER_LFModelResultWrapper.h"
#include "CARCHIVER_LFSignalsAndMeasurementWrapper.h"
#include "CARCHIVER_LFTreatmentWrapper.h"
#include "CARCHIVER_LFAnalysisDataWrapper.h"
#include "CARCHIVER_LFComputerModeWrapper.h"
#include "CARCHIVER_LFDelayWrapper.h"


//##ModelId=41A4A11601A2
class CARCHIVER_LFEventHandler : public CARCHIVER_EventHandler
{
protected:
	//##ModelId=462F26460238
	CARCHIVER_LFMaterialHandlingWrapper m_MaterialHandlingWrapper;

	//##ModelId=41DACB060375
	CARCHIVER_LFSignalsAndMeasurementWrapper m_SignalsAndMeasurementWrapper;

	//##ModelId=462F2631020F
	CARCHIVER_LFTreatmentWrapper m_TreatmentWrapper;

	//##ModelId=462F2623007E
	CARCHIVER_LFAnalysisDataWrapper m_AnalysisDataWrapper;

	//##ModelId=462F261302FA
	CARCHIVER_LFComputerModeWrapper m_ComputerModeWrapper;

	//##ModelId=41A4A2B102EF
	CARCHIVER_LFModelResultWrapper m_ModelResultWrapper;

	//##ModelId=462F25DE027F
	CARCHIVER_LFDelayWrapper m_DelayWrapper;

public:
	//##ModelId=42B04BDE022E
	virtual bool handleEvent(CEventMessage& Event);

	//##ModelId=41A4A2B102DA
	virtual ~CARCHIVER_LFEventHandler();

	//##ModelId=41A4A2B102E5
	CARCHIVER_LFEventHandler(CARCHIVER_Task *Task);

};

#endif /* _INC_CARCHIVER_LFEVENTHANDLER_414018470156_INCLUDED */
