// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFSOLIDMATERIALSHANDLINGWRAPPER_4110C8E802C7_INCLUDED
#define _INC_CLFSOLIDMATERIALSHANDLINGWRAPPER_4110C8E802C7_INCLUDED

#include "CSolidMaterialHandlingWrapper.h"
#include "CLFModelWrapper.h"

//class std::string;

//##ModelId=4110C8E802C7
class CLFSolidMaterialsHandlingWrapper 
: public CSolidMaterialHandlingWrapper
, public CLFModelWrapper
{
public:
	//##ModelId=417E1109024E
	bool doOnRecipeWeighingCompleteUpdate(CEventMessage& Event);

	//##ModelId=416691B80315
	 bool doOnChangedMatSetPointsOperator(CEventMessage& Event);

	//##ModelId=416691B90279
	 bool doOnDisableSourceRecipe(CEventMessage& Event);

	//##ModelId=416691BA01B2
	 bool doOnEnableSourceRecipe(CEventMessage& Event);

	//##ModelId=416691BB0034
	 bool doOnRecipeMaterialCharged(CEventMessage& Event);

	//##ModelId=416691BB02E7
	 bool doOnRecipeMaterialDischarged(CEventMessage& Event);

	//##ModelId=416691BC01C6
	 bool doOnRecipeWeighingComplete(CEventMessage& Event);

	//##ModelId=41111A2302FB
	bool doOnWireFeedingEnd(CEventMessage& Event);

	//##ModelId=41111AA6024F
	bool doOnWireFeedingStart(CEventMessage& Event);

	bool doOnRecipeDischargeStart(CEventMessage & Event);

  bool doOnMaterialData(CEventMessage & Event);


private:

};

#endif /* _INC_CLFSOLIDMATERIALSHANDLINGWRAPPER_4110C8E802C7_INCLUDED */
