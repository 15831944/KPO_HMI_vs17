// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAFDESLAGGINGWRAPPER_41123D0100C6_INCLUDED
#define _INC_CEAFDESLAGGINGWRAPPER_41123D0100C6_INCLUDED

#include "CEAFModelWrapper.h"

//##ModelId=411238C901C8
class CEAFDeslaggingWrapper : public CEAFModelWrapper
  
{
public:
	//##ModelId=4112390E005D
	bool doOnDeslaggingStart( CEventMessage &Event );

	//##ModelId=411239200387
	bool doOnDeslaggingEnd( CEventMessage &Event );

};

#endif /* _INC_CEAFDESLAGGINGWRAPPER_41123D0100C6_INCLUDED */
