// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFMATERIALHANDLINGEVENTHANDLER_4118DFF8004C_INCLUDED
#define _INC_CEAFMATERIALHANDLINGEVENTHANDLER_4118DFF8004C_INCLUDED

#include "CEAFEventHandler.h"
#include "CEAFInjectionMaterialHandlingWrapper.h"
#include "CEAFBasketMaterialHandlingWrapper.h"
#include "CEAFChangePhysicalMaterialAvailibilityWrapper.h"
#include "CEAFFeedingMaterialHandlingWrapper.h"
#include "CEAFLiquidMaterialsHandlingWrapper.h"
#include "CEAFManualMaterialBatchWrapper.h"
#include "CEAFSolidMaterialHandlingWrapper.h"

//##ModelId=4118DFF8004C
class CEAFMaterialHandlingEventHandler 
: public CEAFEventHandler
{
public:
	//##ModelId=4118E0A600E2
	virtual bool handleEvent(CEventMessage& EventMessage);

	//##ModelId=467645DE03C7
  CEAFMaterialHandlingEventHandler(CModelTask* pModelTask);

protected:
	//##ModelId=4153F06D031E
	CEAFInjectionMaterialHandlingWrapper EAFInjectionMaterialHandlingWrapper;

	//##ModelId=422C28500365
	CEAFBasketMaterialHandlingWrapper EAFBasketMaterialHandlingWrapper;

	//##ModelId=422C28A70067
	CEAFChangePhysicalMaterialAvailibilityWrapper EAFChangePhysicalMaterialAvailabilityWrapper;

	//##ModelId=422C28E802EB
	CEAFFeedingMaterialHandlingWrapper EAFFeedingMaterialHandlingWrapper;

	//##ModelId=422C29170054
	CEAFLiquidMaterialsHandlingWrapper EAFLiquidMaterialsHandlingWrapper;

	//##ModelId=422C29420269
	CEAFManualMaterialBatchWrapper EAFManualMaterialBatchWrapper;

	//##ModelId=422C296501C9
	CEAFSolidMaterialHandlingWrapper EAFSolidMaterialHandlingWrapper;

};

#endif /* _INC_CEAFMATERIALHANDLINGEVENTHANDLER_4118DFF8004C_INCLUDED */
