// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_HMDSIGNALSANDMEASUREMENTSEVENTHANDLER_412F15C0022B_INCLUDED
#define _INC_CDM_HMDSIGNALSANDMEASUREMENTSEVENTHANDLER_412F15C0022B_INCLUDED

#include "CDM_HMDEventHandler.h"

class CDM_HMDSignalsAndMeasurementsEventHandler 
: public CDM_HMDEventHandler
{
public:
	bool doHMDPhasePreparation(CEventMessage &Event);

	bool doHMDPhaseMonoInjectionLimeStart(CEventMessage &Event);

	bool doHMDPhaseMonoInjectionCarbideStart(CEventMessage &Event);

	bool doHMDPhaseMonoInjectionContinued(CEventMessage &Event);

	bool doHMDPhaseMonoInjectionLimeEnd(CEventMessage &Event);

	bool doHMDPhaseMonoInjectionCarbideEnd(CEventMessage &Event);

	bool doHMDPhaseCoInjectionMagnesiumStart(CEventMessage &Event);

	bool doHMDPhaseCoInjectionMagnesiumEnd(CEventMessage &Event);

	bool doHMDPhaseDeslagging(CEventMessage &Event);

	bool doHMDPhaseDataChange(CEventMessage &Event);

	bool doHMDLanceBlowing(CEventMessage &Event);

	virtual bool handleEvent(CEventMessage& evMessage);

	virtual ~CDM_HMDSignalsAndMeasurementsEventHandler();

	CDM_HMDSignalsAndMeasurementsEventHandler();

	bool doHMDCyclicMeasurement(CEventMessage& Event);

  bool doHMDTempMeasurement(CEventMessage& Event);

  bool doHMDCeloxMeasurement(CEventMessage& Event);

  bool doHMDMeasurement(CEventMessage& Event);

	

};

#endif /* _INC_CDM_HMDSIGNALSANDMEASUREMENTSEVENTHANDLER_412F15C0022B_INCLUDED */
