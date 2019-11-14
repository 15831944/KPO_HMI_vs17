// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFCELOXMEASUREMENTEVENTHANDLER_4118C1DE0256_INCLUDED
#define _INC_CEAFCELOXMEASUREMENTEVENTHANDLER_4118C1DE0256_INCLUDED

#include "CEAFCeloxMeasurementWrapper.h"

#include "CEAFBurnerWrapper.h"
#include "CEAFComputerModeWrapper.h"
#include "CEAFCyclicMeasurementWrapper.h"
#include "CEAFDeslaggingWrapper.h"
#include "CEAFElectricSignalsWrapper.h"
#include "CEAFJetModuleWrapper.h"
#include "CEAFLanceManipWrapper.h"
#include "CEAFOxygenMeasurementWrapper.h"
#include "CEAFOxygenSideLancesWrapper.h"
#include "CEAFRoofPositionWrapper.h"
#include "CEAFTappedWeightWrapper.h"
#include "CEAFTappingLadleWrapper.h"
#include "CEAFTappingWrapper.h"
#include "CEAFTemperaturMeasurementWrapper.h"

#include "CEAFEventHandler.h"

//##ModelId=4118C1DE0256
class CEAFSignalAndMeasurementEventHandler 
: public CEAFEventHandler
{
protected:
	//##ModelId=422C2D320045
	CEAFBurnerWrapper EAFBurnerWrapper;

	//##ModelId=422C2D9A00AB
	CEAFComputerModeWrapper EAFComputerModeWrapper;

	//##ModelId=422C2DC0022D
	CEAFCyclicMeasurementWrapper EAFCyclicMeasurementWrapper;

	//##ModelId=422C2DE203C7
	CEAFDeslaggingWrapper EAFDeslaggingWrapper;

	//##ModelId=422C2E0A005E
	CEAFElectricSignalsWrapper EAFElectricSignalsWrapper;

	//##ModelId=422C2E300335
	CEAFJetModuleWrapper EAFJetModuleWrapper;

	//##ModelId=422C2E5F00C6
	CEAFLanceManipWrapper EAFLanceManipWrapper;

	//##ModelId=422C2ECB022C
	CEAFOxygenMeasurementWrapper EAFOxygenMeasurementWrapper;

	//##ModelId=422C2EE80379
	CEAFOxygenSideLancesWrapper EAFOxygenSideLancesWrapper;

	//##ModelId=422C2F4000BA
	CEAFRoofPositionWrapper EAFRoofPositionWrapper;

	//##ModelId=422C2F900388
	CEAFTappedWeightWrapper EAFTappedWeightWrapper;

	//##ModelId=422C2FB900DF
	CEAFTappingLadleWrapper EAFTappingLadleWrapper;

	//##ModelId=422C2FD801E8
	CEAFTappingWrapper EAFTappingWrapper;

	//##ModelId=422C2FEF0097
	CEAFTemperaturMeasurementWrapper EAFTemperatureMeasurementWrapper;

	//##ModelId=4157D61001AF
	CEAFCeloxMeasurementWrapper EAFCeloxMeasurementWrapper;

public:
	//##ModelId=4118DE15015F
	virtual bool handleEvent( CEventMessage& EventMessage);

	//##ModelId=467645D603BC
  CEAFSignalAndMeasurementEventHandler(CModelTask* pModelTask);
};

#endif /* _INC_CEAFCELOXMEASUREMENTEVENTHANDLER_4118C1DE0256_INCLUDED */
