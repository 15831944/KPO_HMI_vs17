// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFBURNERWRAPPER_411220D90371_INCLUDED
#define _INC_CEAFBURNERWRAPPER_411220D90371_INCLUDED

#include "CEAFModelWrapper.h"
#include "CPurposeHandlingWrapper.h"

//##ModelId=411220D90371
class CEAFBurnerWrapper 
: public CEAFModelWrapper
{
public:
	//##ModelId=4112211402BE
	bool doOnBurnerStart( CEventMessage &Event );

	//##ModelId=41122128007A
	bool doOnBurnerEnd( CEventMessage &Event );

};

#endif /* _INC_CEAFBURNERWRAPPER_411220D90371_INCLUDED */
