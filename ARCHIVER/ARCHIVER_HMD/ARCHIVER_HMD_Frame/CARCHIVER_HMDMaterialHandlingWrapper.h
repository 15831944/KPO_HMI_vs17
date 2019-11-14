// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_HMDMATERIALHANDLINGWRAPPER_45D5A75F0185_INCLUDED
#define _INC_CARCHIVER_HMDMATERIALHANDLINGWRAPPER_45D5A75F0185_INCLUDED

#include "CARCHIVER_MaterialHandlingWrapper.h"

class CPDH_HM_DATA;

// JAST #include "CPDH_LANCE_DATA.h"

//##ModelId=45D5A75F0185
class CARCHIVER_HMDMaterialHandlingWrapper 
: public CARCHIVER_MaterialHandlingWrapper
{
public:
	//##ModelId=45D5B754013B
	bool doOnPowderBlowing(CEventMessage& Event, bool start = true);

	bool doOnMaterialAvailability(CEventMessage& Event);
  

	//##ModelId=45D5A7D90347
	CARCHIVER_HMDMaterialHandlingWrapper();

	//##ModelId=45D5A7DA0110
	virtual ~CARCHIVER_HMDMaterialHandlingWrapper();

protected:
	CPDH_HM_DATA* m_pPDH_HM_DATA;
	//##ModelId=45D5A7DC03D7
	virtual void deleteDBClasses();

	//##ModelId=45D5A7DD02B7
	virtual void initDBClasses();

};

#endif /* _INC_CARCHIVER_HMDMATERIALHANDLINGWRAPPER_45D5A75F0185_INCLUDED */
