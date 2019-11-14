// Copyright (C) 2013 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_HMDEVENTHANDLER_INCLUDED
#define _INC_CARCHIVER_HMDEVENTHANDLER_INCLUDED

#include "CARCHIVER_EventHandler.h"

#include "CARCHIVER_HMDMaterialHandlingWrapper.h"
#include "CARCHIVER_HMDSignalsAndMeasurementWrapper.h"
//#include "CARCHIVER_HMDAnalysisDataWrapper.h"
#include "CARCHIVER_HMDTreatmentWrapper.h"
#include "CARCHIVER_HMDComputerModeWrapper.h"
//#include "CARCHIVER_HMDPhaseReportingWrapper.h"


class CARCHIVER_HMDEventHandler : public CARCHIVER_EventHandler
{
protected:
	//CARCHIVER_HMDPhaseReportingWrapper m_PhaseReportWrapper;

	CARCHIVER_HMDComputerModeWrapper m_ComputerModeWrapper;

	CARCHIVER_HMDTreatmentWrapper m_TreatmentWrapper;

	//CARCHIVER_HMDAnalysisDataWrapper m_AnalysisDataWrapper;

	CARCHIVER_HMDMaterialHandlingWrapper m_MaterialHandlingWrapper;

	CARCHIVER_HMDSignalsAndMeasurementWrapper m_SignalsAndMeasurementWrapper;

public:
	virtual bool handleEvent(CEventMessage& Event);

	virtual ~CARCHIVER_HMDEventHandler();

	CARCHIVER_HMDEventHandler(CARCHIVER_Task *Task);

};

#endif /* _INC_CARCHIVER_HMDEVENTHANDLER_INCLUDED */
