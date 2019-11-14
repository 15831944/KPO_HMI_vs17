// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFTREATMENTMANAGERDATAWRAPPER_4113A0D10125_INCLUDED
#define _INC_CLFTREATMENTMANAGERDATAWRAPPER_4113A0D10125_INCLUDED

#include "CTreatmentManagerAimDataWrapper.h"
#include "CLFModelWrapper.h"

//##ModelId=4113A0D10125
class CLFTreatmentManagerDataWrapper 
: public CTreatmentManagerAimDataWrapper
, public CLFModelWrapper
{
public:

	//##ModelId=42A06E2A01CB
  bool doOnHeatStart(CEventMessage& Event);

	//##ModelId=411893AA0367
	bool doOnHeatDeparture(CEventMessage& Event);

	//##ModelId=411893C60000
	bool doOnHeatCancellation(CEventMessage& Event);

	//##ModelId=411893E0017A
	bool doOnHandleHeatAnnouncement(CEventMessage& Event);

	//##ModelId=42A06E2A01E9
	bool doOnChangeLiquidSteelData(CEventMessage& Event);

	//##ModelId=411894030224
	bool doOnChangeProdPracStirring(CEventMessage& Event);

	//##ModelId=4118942302FD
	bool doOnChangeProdPracElectric(CEventMessage& Event);

	//##ModelId=42A06E2A01FD
	bool doOnChangeProdPracRestriction(CEventMessage& Event);

	bool doOnChangeProdPracParameter(CEventMessage& Event);

	//##ModelId=42A06E2A0211
  bool doOnSwitchEvent(CEventMessage& Event);
	//##ModelId=4165575903B1
	virtual bool doOnChangeAimData(CEventMessage& Event);

	bool doOnUpdateAimDepartureTime(CEventMessage& Event);

	bool doOnUpdateAimTemperature  (CEventMessage& Event);

  bool doOnLadleDataChanged(CEventMessage& Event);
};

#endif /* _INC_CLFTREATMENTMANAGERDATAWRAPPER_4113A0D10125_INCLUDED */
