// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAF_ANALYSIS_EVENTHANDLER_4110EC99033E_INCLUDED
#define _INC_CEAF_ANALYSIS_EVENTHANDLER_4110EC99033E_INCLUDED

#include "CEAFEventHandler.h"
#include "CEAFAnalysisHandlingWrapper.h"


//##ModelId=4118AE9C0333
class CEAFAnalysisEventHandler : public CEAFEventHandler
  
{

protected:
	//##ModelId=41470F9C010C
	CEAFAnalysisHandlingWrapper EAFAnalysisHandlingWrapper;

public:
	//##ModelId=414711A301B2
	virtual bool handleEvent( CEventMessage& EventMessage);

	//##ModelId=467645DF00F8
  CEAFAnalysisEventHandler(CModelTask* pModelTask);
};

#endif /* _INC_CEAF_ANALYSIS_EVENTHANDLER_4110EC99033E_INCLUDED */
