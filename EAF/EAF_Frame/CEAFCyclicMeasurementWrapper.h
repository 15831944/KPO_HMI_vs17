// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFCYCLICMEASUREMENTWRAPPER_411276320016_INCLUDED
#define _INC_CEAFCYCLICMEASUREMENTWRAPPER_411276320016_INCLUDED

#include "CEAFModelWrapper.h"

//##ModelId=411276320016
class CEAFCyclicMeasurementWrapper 
: public CEAFModelWrapper
{
public:
	//##ModelId=411276A3006C
	bool doOnCyclicMeasurement( CEventMessage &Event );

};

#endif /* _INC_CEAFCYCLICMEASUREMENTWRAPPER_411276320016_INCLUDED */
