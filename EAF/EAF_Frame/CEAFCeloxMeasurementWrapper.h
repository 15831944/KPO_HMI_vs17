// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFCELOXMEASUREMENTWRAPPER_411273830161_INCLUDED
#define _INC_CEAFCELOXMEASUREMENTWRAPPER_411273830161_INCLUDED

#include "CEAFModelWrapper.h"
#include "CCeloxMeasurementWrapper.h"

//##ModelId=411273830161
class CEAFCeloxMeasurementWrapper 
: public CCeloxMeasurementWrapper
, public CEAFModelWrapper
{
public:
	//##ModelId=4158056903C1
	virtual bool doOnCeloxMeasurement( CEventMessage &Event );

};

#endif /* _INC_CEAFCELOXMEASUREMENTWRAPPER_411273830161_INCLUDED */
