// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_LFANALYSISDATAWRAPPER_45D001A3_INCLUDED
#define _INC_CARCHIVER_LFANALYSISDATAWRAPPER_45D001A3_INCLUDED

#include "CARCHIVER_AnalysisDataWrapper.h"

class CPDL_HEAT_DATA;

//##ModelId=462EFAC6006F
class CARCHIVER_LFAnalysisDataWrapper 
: public CARCHIVER_AnalysisDataWrapper
{
public:
	//##ModelId=462EFAE20213
	CARCHIVER_LFAnalysisDataWrapper();

	//##ModelId=462EFAE300D3
	virtual ~CARCHIVER_LFAnalysisDataWrapper();

	//##ModelId=462EFB0D004C
	bool doOnSampleTaken(CEventMessage& Event );

	//##ModelId=462EFB2E02BC
  //do in DM, remove later
	//bool doOnAnalysisReceived(CEventMessage& Event, bool Steel);

protected:
	//##ModelId=462EFAE403B6
	virtual void initDBClasses();

	//##ModelId=462EFAE501F2
	virtual void deleteDBClasses();
	
    CPDL_HEAT_DATA* m_pPDL_HEAT_DATA;

};

#endif /* _INC_CARCHIVER_LFANALYSISDATAWRAPPER_45D001A3_INCLUDED */
