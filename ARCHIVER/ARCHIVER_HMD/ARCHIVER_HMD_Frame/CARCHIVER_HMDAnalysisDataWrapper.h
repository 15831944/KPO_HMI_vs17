// Copyright (C) 2012 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_HMDANALYSISDATAWRAPPER_45D30C9700CF_INCLUDED
#define _INC_CARCHIVER_HMDANALYSISDATAWRAPPER_45D30C9700CF_INCLUDED

#include "CARCHIVER_AnalysisDataWrapper.h"

class CARCHIVER_HMDAnalysisDataWrapper 
: public CARCHIVER_AnalysisDataWrapper
{
protected:
	virtual void deleteDBClasses();

	virtual void initDBClasses();

public:
	bool doOnSampleTaken(CEventMessage& Event);

  ~CARCHIVER_HMDAnalysisDataWrapper();
	CARCHIVER_HMDAnalysisDataWrapper();

};

#endif /* _INC_CARCHIVER_HMDANALYSISDATAWRAPPER_45D30C9700CF_INCLUDED */
