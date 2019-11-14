// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFCYCLICMEASUREMENTWRAPPER_4112498F0108_INCLUDED
#define _INC_CLFCYCLICMEASUREMENTWRAPPER_4112498F0108_INCLUDED

#include "CLFModelWrapper.h"

//##ModelId=4112498F0108
class CLFCyclicMeasurementWrapper 
: public CLFModelWrapper
{
public:
	//##ModelId=41124A0202FC
	bool doOnCyclicMeasurements(CEventMessage& Event);

};

#endif /* _INC_CLFCYCLICMEASUREMENTWRAPPER_4112498F0108_INCLUDED */
