// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFLIQUIDMATERIALSHANDLINGWRAPPER_4110C8A90172_INCLUDED
#define _INC_CLFLIQUIDMATERIALSHANDLINGWRAPPER_4110C8A90172_INCLUDED

#include "CLiquidMaterialHandlingWrapper.h"
#include "CLFModelWrapper.h"

class CLFLiquidMaterialsHandlingWrapper 
: public CLiquidMaterialHandlingWrapper
, public CLFModelWrapper
{
public:
	bool doOnChangeOfLiquidAdditionData(CEventMessage& Event);

	bool doOnLiquidAdditionCharged(CEventMessage& Event);

	bool doOnRemoveLiquidSteelData(CEventMessage& Event);

protected:

	virtual bool doSetLiquidMaterialData(CEventMessage& Event);

	virtual bool doSetLiquidSteelData(CEventMessage& Event);

};

#endif /* _INC_CLFLIQUIDMATERIALSHANDLINGWRAPPER_4110C8A90172_INCLUDED */
