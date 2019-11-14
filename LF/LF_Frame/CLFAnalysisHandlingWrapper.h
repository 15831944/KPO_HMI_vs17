// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLFANALYSISHANDLINGWRAPPER_410FBEE00375_INCLUDED
#define _INC_CLFANALYSISHANDLINGWRAPPER_410FBEE00375_INCLUDED

#include "CAnalysisHandlingWrapper.h"
#include "CLFModelWrapper.h"

//##ModelId=410FBEE00375
class CLFAnalysisHandlingWrapper 
: public CAnalysisHandlingWrapper
, public CLFModelWrapper
{
protected:
public:
	//##ModelId=41650A3A0065
	bool doOnSlagSampleTaken(CEventMessage &Event);

	//##ModelId=41650A3A0098
	bool doOnSteelSampleTaken(CEventMessage &Event);

	//##ModelId=41650A3A00C0
	bool doOnSteelAnalysisReceived(CEventMessage &Event);

	//##ModelId=41650A3A00E8
	bool doOnSlagAnalysisReceived(CEventMessage &Event);


};

#endif /* _INC_CLFANALYSISHANDLINGWRAPPER_410FBEE00375_INCLUDED */
