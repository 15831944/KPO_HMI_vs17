// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_HMDCOMPUTERMODEWRAPPER_45E534A90008_INCLUDED
#define _INC_CARCHIVER_HMDCOMPUTERMODEWRAPPER_45E534A90008_INCLUDED

#include "CARCHIVER_ComputerModeWrapper.h"

//##ModelId=45E534A90008
class CARCHIVER_HMDComputerModeWrapper 
: public CARCHIVER_ComputerModeWrapper
{
public:
	//##ModelId=45E534D3006C
	CARCHIVER_HMDComputerModeWrapper();

	//##ModelId=45E534D303E7
	virtual ~CARCHIVER_HMDComputerModeWrapper();

	//##ModelId=45E535280277
	bool doOnSetComputerMode(CEventMessage& Event);

protected:
	//##ModelId=45E534D700AE
	virtual void initDBClasses();

	//##ModelId=45E534D7029B
	virtual void deleteDBClasses();

};

#endif /* _INC_CARCHIVER_HMDCOMPUTERMODEWRAPPER_45E534A90008_INCLUDED */
