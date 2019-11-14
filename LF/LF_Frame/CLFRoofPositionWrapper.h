// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFROOFPOSITIONWRAPPER_411242C401FA_INCLUDED
#define _INC_CLFROOFPOSITIONWRAPPER_411242C401FA_INCLUDED

#include "CLFModelWrapper.h"
#include "CRoofPositionWrapper.h"

//##ModelId=411242C401FA
class CLFRoofPositionWrapper 
: public CRoofPositionWrapper
, public CLFModelWrapper
{
public:
	//##ModelId=41665DED0159
	 bool doOnGantrySwungIn(CEventMessage& Event);

	//##ModelId=41665DED038A
	 bool doOnGantrySwungOut(CEventMessage& Event);

	//##ModelId=41665DEE01B4
	 bool doOnRoofInDownPos(CEventMessage& Event);

	//##ModelId=41665DEF000A
	 bool doOnRoofInUpPos(CEventMessage& Event);

};

#endif /* _INC_CLFROOFPOSITIONWRAPPER_411242C401FA_INCLUDED */
