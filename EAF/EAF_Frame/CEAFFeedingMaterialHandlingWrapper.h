// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFFEEDINGMATERIALHANDLINGWRAPPER_411128CA022C_INCLUDED
#define _INC_CEAFFEEDINGMATERIALHANDLINGWRAPPER_411128CA022C_INCLUDED

#include "CEAFModelWrapper.h"
#include "CChangePhysicalMaterialAvailibilityWrapper.h"

//##ModelId=411128CA022C
class CEAFFeedingMaterialHandlingWrapper 
: public CEAFModelWrapper
{
public:
	//##ModelId=4112638C0101
	class CEAFChangePhysicalMaterialAvailibilityWrapper 
	: public CChangePhysicalMaterialAvailibilityWrapper
	, public CEAFModelWrapper
	{
	};


	//##ModelId=41112916038A
	bool doOnBinMaterialHandlingStart( CEventMessage &Event );

	//##ModelId=4111295903AF
	bool doOnBinMaterialHandlingStop( CEventMessage &Event );

};

#endif /* _INC_CEAFFEEDINGMATERIALHANDLINGWRAPPER_411128CA022C_INCLUDED */
