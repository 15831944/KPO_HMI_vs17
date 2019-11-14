// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFCELOXMEASUREMENTWRAPPER_411248DA02BF_INCLUDED
#define _INC_CLFCELOXMEASUREMENTWRAPPER_411248DA02BF_INCLUDED

#include "CCeloxMeasurementWrapper.h"
#include "CLFModelWrapper.h"

//##ModelId=411248DA02BF
class CLFCeloxMeasurementWrapper 
: public CCeloxMeasurementWrapper
, public CLFModelWrapper
{
public:
	//##ModelId=4166585002DD
	bool doOnCeloxMeasurement(CEventMessage& Event);

};

#endif /* _INC_CLFCELOXMEASUREMENTWRAPPER_411248DA02BF_INCLUDED */
