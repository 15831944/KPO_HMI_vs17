// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_EAFCOMPUTERMODESANDAVAILABILITYWRAPPER_41DAAFF10146_INCLUDED
#define _INC_CARCHIVER_EAFCOMPUTERMODESANDAVAILABILITYWRAPPER_41DAAFF10146_INCLUDED

#include "CARCHIVER_ComputerModeWrapper.h"

//##ModelId=41DAAFF10146 
class CARCHIVER_EAFComputerModesAndAvailabilityWrapper 
: public CARCHIVER_ComputerModeWrapper
{
public:
	//##ModelId=41DAB08B02E5
	virtual ~CARCHIVER_EAFComputerModesAndAvailabilityWrapper();

	//##ModelId=41DAB08B03AF
	CARCHIVER_EAFComputerModesAndAvailabilityWrapper();

	//##ModelId=41DAB460015F
	bool doOnSetComputerMode(CEventMessage& Event);

protected:
	//##ModelId=41DAB08A0077
	virtual void deleteDBClasses();

	//##ModelId=41DAB08A01C2
	virtual void initDBClasses();

};

#endif /* _INC_CARCHIVER_EAFCOMPUTERMODESANDAVAILABILITYWRAPPER_41DAAFF10146_INCLUDED */
