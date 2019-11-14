// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFOXYGENMEASUREMENTWRAPPER_411237B10140_INCLUDED
#define _INC_CEAFOXYGENMEASUREMENTWRAPPER_411237B10140_INCLUDED

#include "CEAFModelWrapper.h"

//##ModelId=411237B10140
class CEAFOxygenMeasurementWrapper 
: public CEAFModelWrapper
{
public:
	//##ModelId=41123803012A
	bool doOnOxygenMeusurement( CEventMessage &Event );

};

#endif /* _INC_CEAFOXYGENMEASUREMENTWRAPPER_411237B10140_INCLUDED */
