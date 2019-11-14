// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_EAFSIGNALSANDMEASUREMENTSEVENTHANDLER_412F15C0022B_INCLUDED
#define _INC_CDM_EAFSIGNALSANDMEASUREMENTSEVENTHANDLER_412F15C0022B_INCLUDED

#include "CDM_EAFEventHandler.h"

class CDM_EAFSignalsAndMeasurementsEventHandler 
: public CDM_EAFEventHandler
{
public:
  // cyclic event for ladle stirring
  bool doEAFCyclicMeasurementTapLadle(CEventMessage& Event);
  bool doEAFSetTappingMasses(CEventMessage& Event);

  bool doEAFBottomStirringStart(CEventMessage& Event);
  bool doEAFBottomStirringEnd(CEventMessage& Event);

  bool doEAFManipInjectLanceStart(CEventMessage& Event);
  bool doEAFManipInjectLanceStop(CEventMessage& Event);
  bool doOnManipInjectLance(CEventMessage& Event);


  bool doEAFManipGasLanceStart(CEventMessage& Event);
  bool doEAFManipGasLanceStop(CEventMessage& Event);
  bool doEAFManipGasLance(CEventMessage& Event);

  bool doEAFCarbonInjectStart(CEventMessage& Event);
  bool doEAFCarbonInjectStop(CEventMessage& Event);

  bool doEAFPowerOn(CEventMessage& Event);
  bool doEAFPowerOff(CEventMessage& Event);
  bool doOnHeating(CEventMessage& Event);

  bool doEAFBurnerStart(CEventMessage& Event);
  bool doEAFBurnerStop(CEventMessage& Event);
  bool doEAFBurner(CEventMessage& Event);

  //This hook operation by EventHandlerAdapter 
  //when an event is received.
  virtual bool handleEvent(CEventMessage& evMessage);

  virtual ~CDM_EAFSignalsAndMeasurementsEventHandler();

  CDM_EAFSignalsAndMeasurementsEventHandler();

  bool doEAFLadleStirringStart(CEventMessage& Event);
  bool doEAFLadleStirringStop(CEventMessage& Event);
  bool doEAFStirring(CEventMessage& Event);

  bool doEAFTappingStart(CEventMessage& Event);
  bool doEAFTappingEnd(CEventMessage& Event);
  bool doEAFTapping(CEventMessage& Event);

  bool doEAFCyclicMeasurement(CEventMessage& Event);

};

#endif /* _INC_CDM_EAFSIGNALSANDMEASUREMENTSEVENTHANDLER_412F15C0022B_INCLUDED */
