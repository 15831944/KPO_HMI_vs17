// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFBASKETMATERIALHANDLINGWRAPPER_411121FA0289_INCLUDED
#define _INC_CEAFBASKETMATERIALHANDLINGWRAPPER_411121FA0289_INCLUDED

#include "CEAFModelWrapper.h"

//##ModelId=411121FA0289
class CEAFBasketMaterialHandlingWrapper 
: public CEAFModelWrapper
{
public:
	//##ModelId=4111226201AC
	bool doOnBasketData(CEventMessage & Event);

  bool doOnBasketAssignment(CEventMessage &Event);

	//##ModelId=4111239E0229
	bool doOnBasketDischarged(CEventMessage & Event);

};

#endif /* _INC_CEAFBASKETMATERIALHANDLINGWRAPPER_411121FA0289_INCLUDED */
