// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFTEMPERATURMEASUREMENTWRAPPER_411244180023_INCLUDED
#define _INC_CLFTEMPERATURMEASUREMENTWRAPPER_411244180023_INCLUDED

#include "CTemperaturMeasurementWrapper.h"
#include "CLFModelWrapper.h"

//##ModelId=411244180023
class CLFTemperaturMeasurementWrapper 
: public CTemperaturMeasurementWrapper
, public CLFModelWrapper
{
public:
	//##ModelId=41665D960141
	 bool doOnTempMeasurement(CEventMessage& Event);

};

#endif /* _INC_CLFTEMPERATURMEASUREMENTWRAPPER_411244180023_INCLUDED */
