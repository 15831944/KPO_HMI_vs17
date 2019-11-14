// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFBOTTOMSTIRRINGEVENTHANDLER_4118E63B00AB_INCLUDED
#define _INC_CLFBOTTOMSTIRRINGEVENTHANDLER_4118E63B00AB_INCLUDED

#include "CLFEventHandler.h"
#include "CLFBottomStirringWrapper.h"
#include "CLFCeloxMeasurementWrapper.h"
#include "CLFCyclicMeasurementWrapper.h"
#include "CLFElectricSignalsWrapper.h"
#include "CLFRoofPositionWrapper.h"
#include "CLFTemperaturMeasurementWrapper.h"

//##ModelId=4118E63B00AB
class CLFSignalsAndMeasurementEventHandler 
: public CLFEventHandler
{
protected:
	//##ModelId=416656C400ED
	CLFBottomStirringWrapper LFBottomStirringWrapper;

	//##ModelId=416656FA032F
	CLFCeloxMeasurementWrapper LFCeloxMeasurementWrapper;

	//##ModelId=416657230099
	CLFCyclicMeasurementWrapper LFCyclicMeasurementWrapper;

	//##ModelId=41665748009C
	CLFElectricSignalsWrapper LFElectricSignalsWrapper;

	//##ModelId=4166576700AA
	CLFRoofPositionWrapper LFRoofPositionWrapper;

	//##ModelId=4166578B0124
	CLFTemperaturMeasurementWrapper LFTemperaturMeasurementWrapper;

public:
	//##ModelId=4118E6FD0013
	virtual bool handleEvent( CEventMessage& EventMessage);

	//##ModelId=462767AB001D
  CLFSignalsAndMeasurementEventHandler(CModelTask* pModelTask);

};

#endif /* _INC_CLFBOTTOMSTIRRINGEVENTHANDLER_4118E63B00AB_INCLUDED */
