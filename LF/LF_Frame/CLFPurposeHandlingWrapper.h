// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFPURPOSEHANDLINGWRAPPER_410FD29902F4_INCLUDED
#define _INC_CLFPURPOSEHANDLINGWRAPPER_410FD29902F4_INCLUDED

#include "CPurposeHandlingWrapper.h"
#include "CLFModelWrapper.h"

//##ModelId=410FD29902F4
class CLFPurposeHandlingWrapper 
: public CPurposeHandlingWrapper
, public CLFModelWrapper
{
public:
	//##ModelId=41655D6800A9
	virtual bool doOnUpdatePurpose(CEventMessage& Event);

};

#endif /* _INC_CLFPURPOSEHANDLINGWRAPPER_410FD29902F4_INCLUDED */
