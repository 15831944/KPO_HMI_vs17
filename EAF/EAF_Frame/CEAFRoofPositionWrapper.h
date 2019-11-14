// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFROOFPOSITIONWRAPPER_41121A91022B_INCLUDED
#define _INC_CEAFROOFPOSITIONWRAPPER_41121A91022B_INCLUDED

#include "CEAFModelWrapper.h"
#include "CRoofPositionWrapper.h"

//##ModelId=41121A91022B
class CEAFRoofPositionWrapper 
: public CRoofPositionWrapper
, public CEAFModelWrapper
{
public:
	//##ModelId=4158192C01F9
	virtual bool doOnGantrySwungIn( CEventMessage &Event );

	//##ModelId=4158192D00A6
	virtual bool doOnGantrySwungOut( CEventMessage &Event );

	//##ModelId=4158192D0289
	virtual bool doOnRoofInDownPos( CEventMessage &Event );

	//##ModelId=4158192E00DC
	virtual bool doOnRoofInUpPos( CEventMessage &Event );

	//##ModelId=41121C7D0105
	bool doOnDoorOpened( CEventMessage &Event );

	//##ModelId=41121C9302EA
	bool doOnDoorClosed( CEventMessage &Event );

};

#endif /* _INC_CEAFROOFPOSITIONWRAPPER_41121A91022B_INCLUDED */
