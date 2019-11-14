// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAF_PURPOSE_EVENTHANDLER_4110FAF30240_INCLUDED
#define _INC_CEAF_PURPOSE_EVENTHANDLER_4110FAF30240_INCLUDED

#include "CEAFEventHandler.h"
#include "CEAFPurposeHandlingWrapper.h"


//##ModelId=4118AFCB019F
class CEAFPurposeEventHandler : public CEAFEventHandler
  
{
protected:
	//##ModelId=41542E980111
	CEAFPurposeHandlingWrapper EAFPurposeHandlingWrapper;

public:
	//##ModelId=4118AFEA00EF
	virtual bool handleEvent( CEventMessage& EventMessage);

	//##ModelId=467645D70010
  CEAFPurposeEventHandler(CModelTask* pModelTask);
};

#endif /* _INC_CEAF_PURPOSE_EVENTHANDLER_4110FAF30240_INCLUDED */
