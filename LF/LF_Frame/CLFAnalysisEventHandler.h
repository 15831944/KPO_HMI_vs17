// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFANALYSISEVENTHANDLER_4118B84F0059_INCLUDED
#define _INC_CLFANALYSISEVENTHANDLER_4118B84F0059_INCLUDED

#include "CLFEventHandler.h"
#include "CLFAnalysisHandlingWrapper.h"

//##ModelId=4118B84F0059
class CLFAnalysisEventHandler 
: public CLFEventHandler
{
public:
	//##ModelId=4118B86001D0
	virtual bool handleEvent( CEventMessage& EventMessage);

	//##ModelId=462767AE01DE
  CLFAnalysisEventHandler(CModelTask* pModelTask);

protected:
	//##ModelId=41518554039D
	CLFAnalysisHandlingWrapper LFAnalysisHandlingWrapper;

};

#endif /* _INC_CLFANALYSISEVENTHANDLER_4118B84F0059_INCLUDED */
