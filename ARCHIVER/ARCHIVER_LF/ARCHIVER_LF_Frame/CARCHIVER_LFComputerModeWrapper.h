// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_LFCOMPUTERMODEWRAPPER_INCLUDED
#define _INC_CARCHIVER_LFCOMPUTERMODEWRAPPER_INCLUDED

#include "CARCHIVER_ComputerModeWrapper.h"

//##ModelId=462E2BC802FC
class CARCHIVER_LFComputerModeWrapper 
: public CARCHIVER_ComputerModeWrapper
{
public:
	//##ModelId=462E2BE203E0
	CARCHIVER_LFComputerModeWrapper();

	//##ModelId=462E2BE30266
	virtual ~CARCHIVER_LFComputerModeWrapper();

	//##ModelId=462E2C4E022E
	bool doOnSetComputerMode(CEventMessage& Event);

protected:
	//##ModelId=462E2BE501C7
	virtual void initDBClasses();

	//##ModelId=462E2BE60042
	virtual void deleteDBClasses();

};

#endif /* _INC_CARCHIVER_LFCOMPUTERMODEWRAPPER_INCLUDED */
