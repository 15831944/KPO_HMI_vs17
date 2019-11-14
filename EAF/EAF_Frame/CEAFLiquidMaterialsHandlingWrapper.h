// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFLIQUIDMATERIALSHANDLINGWRAPPER_41111E7900B2_INCLUDED
#define _INC_CEAFLIQUIDMATERIALSHANDLINGWRAPPER_41111E7900B2_INCLUDED

#include "CEAFModelWrapper.h"
#include "CLiquidMaterialHandlingWrapper.h"

//##ModelId=41111E7900B2
class CEAFLiquidMaterialsHandlingWrapper 
: public CLiquidMaterialHandlingWrapper
, public CEAFModelWrapper
{
protected:
public:
	//##ModelId=415286A60308
	virtual bool doOnRemoveLiquidSteelData(CEventMessage &Event);

	//##ModelId=415286740192
	virtual bool doOnRemoveLiquidFeCrData(CEventMessage &Event);

	//##ModelId=429F12110391
	virtual bool doOnRemoveLiquidAddition(CEventMessage &Event);

	//##ModelId=41528366025E
	virtual bool doOnRemoveHotMetalData(CEventMessage &Event);

	//##ModelId=4152814A03D9
	virtual bool doOnLiquidSteelCharged(CEventMessage &Event);

	//##ModelId=41527F390207
	virtual bool doOnLiquidFeCrCharged(CEventMessage &Event);

	//##ModelId=41527D7D00CD
	virtual bool doOnHotMetalCharged(CEventMessage &Event);

	//##ModelId=429F12120040
	virtual bool doOnLiquidAdditionCharged(CEventMessage &Event);

	//##ModelId=4151A06B0265
  // mrut 2014-12-10
  // IsIncludedInOtherUseCase : a default argument to allow to skip calling for model results. 
  // Useful if called as part of a different event sequence. At JSW-SMS 3 , the data of the liquid material are availble only at discharge, 
  // but the use case 'change of liquid material data is not triggered. So, it makes sense to include this within the 'discharge-event'.
	virtual bool doOnChangeOfLiquidAdditionData(CEventMessage &Event, bool IsIncludedInOtherUseCase = false);

	//##ModelId=4118D2B00093
	CEAFModelWrapper* theCEAFModelWrapper;


};

#endif /* _INC_CEAFLIQUIDMATERIALSHANDLINGWRAPPER_41111E7900B2_INCLUDED */
