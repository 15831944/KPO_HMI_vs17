// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEAF_ANALYSIS_HANDLING_INTERFACE_410F4304019E_INCLUDED
#define _INC_CEAF_ANALYSIS_HANDLING_INTERFACE_410F4304019E_INCLUDED

#include "CAnalysisHandlingWrapper.h"
#include "CEAFModelWrapper.h"


//##ModelId=410FC5300382
class CEAFAnalysisHandlingWrapper : 
  public CAnalysisHandlingWrapper, 
  public CEAFModelWrapper
  
{
protected:
public:
	//##ModelId=4151336E0287
	virtual bool doOnSlagSampleTaken( CEventMessage &Event );

	//##ModelId=4151336F0171
	virtual bool doOnSteelAnalysisReceived( CEventMessage &Event );

	//##ModelId=4151336F03A2
	virtual bool doOnSteelSampleTaken( CEventMessage &Event );

	//##ModelId=41513374013D
	virtual bool doOnSlagAnalysisReceived( CEventMessage &Event );


};

#endif /* _INC_CEAF_ANALYSIS_HANDLING_INTERFACE_410F4304019E_INCLUDED */
