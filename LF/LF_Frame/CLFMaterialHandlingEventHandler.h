// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFCELOXMEASUREMENTEVENTHANDLER_4118E6540332_INCLUDED
#define _INC_CLFCELOXMEASUREMENTEVENTHANDLER_4118E6540332_INCLUDED

#include "CLFEventHandler.h"

#include "CLFChangePhysicalMaterialAvailibilityWrapper.h"
#include "CLFLiquidMaterialsHandlingWrapper.h"
#include "CLFManualMaterialBatchWrapper.h"
#include "CLFSolidMaterialsHandlingWrapper.h"

//##ModelId=4118E6540332
class CLFMaterialHandlingEventHandler 
: public CLFEventHandler
{
protected:
	//##ModelId=41669225032E
	CLFChangePhysicalMaterialAvailibilityWrapper LFChangePhysicalMaterialAvailabilityWrapper;

	//##ModelId=41669264020C
	CLFLiquidMaterialsHandlingWrapper LFLiquidMaterialsHandlingWrapper;

	//##ModelId=416692A301A8
	CLFManualMaterialBatchWrapper LFManualMaterialBatchWrapper;

	//##ModelId=416692C902D9
	CLFSolidMaterialsHandlingWrapper LFSolidMaterialsHandlingWrapper;

public:
	//##ModelId=4118E70903E6
	virtual bool handleEvent( CEventMessage& EventMessage);

	//##ModelId=462767AE00E4
  CLFMaterialHandlingEventHandler(CModelTask* pModelTask);

};

#endif /* _INC_CLFCELOXMEASUREMENTEVENTHANDLER_4118E6540332_INCLUDED */
