// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFTEMPERATURMEASUREMENTWRAPPER_4112745A0328_INCLUDED
#define _INC_CEAFTEMPERATURMEASUREMENTWRAPPER_4112745A0328_INCLUDED

#include "CEAFModelWrapper.h"
#include "CTemperaturMeasurementWrapper.h"

//##ModelId=4112745A0328
class CEAFTemperaturMeasurementWrapper 
: public CTemperaturMeasurementWrapper
, public CEAFModelWrapper
{
public:
	//##ModelId=41580195034A
	 bool doOnTempMeasurement( CEventMessage &Event );

};

#endif /* _INC_CEAFTEMPERATURMEASUREMENTWRAPPER_4112745A0328_INCLUDED */
