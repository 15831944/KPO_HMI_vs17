// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_EAFEVENTHANDLER_4152976301AA_INCLUDED
#define _INC_CARCHIVER_EAFEVENTHANDLER_4152976301AA_INCLUDED

#include "CARCHIVER_EventHandler.h"
#include "CARCHIVER_EAFDelayWrapper.h"
#include "CARCHIVER_EAFComputerModesAndAvailabilityWrapper.h"
#include "CARCHIVER_EAFModelResultsWrapper.h"
#include "CARCHIVER_EAFMaterialHandlingWrapper.h"
#include "CARCHIVER_EAFSignalsAndMeasurementWrapper.h"
#include "CARCHIVER_EAFTreatmentManagementWrapper.h"
#include "CARCHIVER_EAFAnalysisDataWrapper.h"
//##ModelId=4152976301AA
class CARCHIVER_EAFEventHandler : public CARCHIVER_EventHandler
{  
protected:
	//##ModelId=42D26BE70293
	CARCHIVER_EAFMaterialHandlingWrapper m_MaterialHandlingWrapper;

	//##ModelId=41DAC70A02A5
	CARCHIVER_EAFSignalsAndMeasurementWrapper m_SignalsAndMeasurementWrapper;

	CARCHIVER_EAFTreatmentManagementWrapper m_TreatmentManagementWrapper;
	//##ModelId=41529800000A
	CARCHIVER_EAFModelResultsWrapper m_ModelResultWrapper;

	CARCHIVER_EAFDelayWrapper m_DelayWrapper;

	CARCHIVER_EAFAnalysisDataWrapper m_AnalysisDataWrapper;

	CARCHIVER_EAFComputerModesAndAvailabilityWrapper m_ComputerModesAndAvailabilityWrapper;

public:
	//##ModelId=419B7BD403E7
	virtual ~CARCHIVER_EAFEventHandler();

	//##ModelId=419B7BD6000A
	CARCHIVER_EAFEventHandler(CARCHIVER_Task *Task);

	//Handling received EventChannel event and dircting the 
	//Event to the EventHandlerAdapter.
	//##ModelId=4152996E0321
	virtual bool handleEvent(CEventMessage& Event);
};

#endif /* _INC_CARCHIVER_EAFEVENTHANDLER_4152976301AA_INCLUDED */
