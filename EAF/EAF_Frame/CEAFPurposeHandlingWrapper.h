// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFPURPOSEHANDLINGWRAPPER_410FD3FF039D_INCLUDED
#define _INC_CEAFPURPOSEHANDLINGWRAPPER_410FD3FF039D_INCLUDED

#include "CEAFModelWrapper.h"
#include "CPurposeHandlingWrapper.h"

//##ModelId=410FD3FF039D
class CEAFPurposeHandlingWrapper 
: public CEAFModelWrapper
, public CPurposeHandlingWrapper
{
public:
	//##ModelId=415431FA0316
	virtual bool doOnUpdatePurpose( CEventMessage &Event );

};

#endif /* _INC_CEAFPURPOSEHANDLINGWRAPPER_410FD3FF039D_INCLUDED */
