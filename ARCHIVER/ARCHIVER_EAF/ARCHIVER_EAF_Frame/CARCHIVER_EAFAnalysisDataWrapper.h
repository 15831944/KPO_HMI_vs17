// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_EAFANALYSISDATAWRAPPER_41DAABF7037D_INCLUDED
#define _INC_CARCHIVER_EAFANALYSISDATAWRAPPER_41DAABF7037D_INCLUDED

#include "CARCHIVER_AnalysisDataWrapper.h"


//##ModelId=41DAABF7037D
class CARCHIVER_EAFAnalysisDataWrapper 
	: public CARCHIVER_AnalysisDataWrapper
{
public:
	//##ModelId=44ABC7E70270
	//bool doOnHotMetalAnalysisReceived(CEventMessage& Event);

	////##ModelId=44ABC7E702CA
	//bool doOnHotMetalSampleTaken(CEventMessage& Event);

	//##ModelId=41DE593A025D
	//bool doOnAnalysisReceived(CEventMessage& Event, bool Steel);

	//##ModelId=41DAAC9B00C9
	CARCHIVER_EAFAnalysisDataWrapper();

	//##ModelId=41DAAC9B0318
	virtual ~CARCHIVER_EAFAnalysisDataWrapper();

	//##ModelId=41DE593B004B
	bool doOnSampleTaken(CEventMessage& Event, bool Steel);

protected:

	//##ModelId=41DAAC9801FB
	virtual void deleteDBClasses();

	//##ModelId=41DAAC9901D5
	virtual void initDBClasses();

};

#endif /* _INC_CARCHIVER_EAFANALYSISDATAWRAPPER_41DAABF7037D_INCLUDED */
