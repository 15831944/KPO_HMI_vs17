// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFPURPOSEEVENTHANDLER_4118B90D0084_INCLUDED
#define _INC_CLFPURPOSEEVENTHANDLER_4118B90D0084_INCLUDED

#include "CLFEventHandler.h"
#include "CLFPurposeHandlingWrapper.h"

//##ModelId=4118B90D0084
class CLFPurposeEventHandler 
: public CLFEventHandler
{
public:
	//##ModelId=4118B91A0245
	virtual bool handleEvent( CEventMessage& EventMessage);

	//##ModelId=462767AB005A
  CLFPurposeEventHandler(CModelTask* pModelTask);

protected:
	//##ModelId=41655D230136
	CLFPurposeHandlingWrapper LFPurposeHandlingWrapper;

};

#endif /* _INC_CLFPURPOSEEVENTHANDLER_4118B90D0084_INCLUDED */
