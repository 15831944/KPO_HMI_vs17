// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_LFSIGNALSANDMEASUREMENTSEVENTHANDLER_412F15C0022B_INCLUDED
#define _INC_CDM_LFSIGNALSANDMEASUREMENTSEVENTHANDLER_412F15C0022B_INCLUDED

#include "CDM_EventHandler.h"
#include "CDM_LFEventHandler.h"

class CDM_LFSignalsAndMeasurementsEventHandler 
: public CDM_LFEventHandler
{
public:
  bool doLFRoofArrivesInUpPosition(CEventMessage& Event);
  bool doLFRoofArrivesInDownPosition(CEventMessage& Event);
  bool doLFEmergencyLanceStirringStart(CEventMessage& Event);
  bool doLFEmergencyLanceStirringEnd(CEventMessage& Event);
  bool doLFGantrySwungIn(CEventMessage& Event);
  bool doLFGantrySwungOut(CEventMessage& Event);

	//##
  bool doLFTapChangeStart(CEventMessage& Event);
	//##
  bool doLFTapChangeFinished(CEventMessage& Event);
  
  bool doLFImpCurveChanged(CEventMessage& Event);

  bool doLFPowerOn(CEventMessage& Event);
  bool doLFPowerOff(CEventMessage& Event);

	bool doLFCyclicMeasurementTransferCar(CEventMessage& Event);

	bool doLFTransferCarPositionChanged(CEventMessage& Event);

	bool doLFBottomStirringByPassOn(CEventMessage& Event);

	bool doLFBottomStirringByPassOff(CEventMessage& Event);

	bool doLFBottomStirringStart(CEventMessage& Event);

	bool doLFBottomStirringEnd(CEventMessage& Event);

	virtual bool handleEvent(CEventMessage& evMessage);

	virtual ~CDM_LFSignalsAndMeasurementsEventHandler();

	CDM_LFSignalsAndMeasurementsEventHandler();

	bool doLFStirring(CEventMessage& Event);

	bool doLFCyclicMeasurement(CEventMessage& Event);

};

#endif /* _INC_CDM_LFSIGNALSANDMEASUREMENTSEVENTHANDLER_412F15C0022B_INCLUDED */
